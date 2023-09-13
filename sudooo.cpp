#include <bits/stdc++.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <pwd.h>
#include <shadow.h>
#include <crypt.h>

using namespace std;

bool check_password(const char* username, const char* password) {
    struct spwd* sp = getspnam(username);
    if (sp == NULL) {
        cerr << "Error: Cannot get user's entry from shadow file." << endl;
        return false;
    }
    const char* encrypted = sp->sp_pwdp;
    const char* salt = encrypted;
    const char* hashed = crypt(password, salt);
    if (hashed == NULL) {
        cerr << "Error: Cannot encrypt password." << endl;
        return false;
    }
    return strcmp(encrypted, hashed) == 0;
}

void execute_command(int argc, char* argv[]) {
    uid_t uid = getuid();
    struct passwd* pw = getpwuid(uid);
    if (pw == NULL) {
        cerr << "Error: Cannot get user's name from user ID." << endl;
        exit(1);
    }
    const char* username = pw->pw_name;
    cout << "[sudo] password for " << username << ": ";
    system("stty -echo");
    
    string password;
    getline(cin, password);
    system("stty echo");
    cout << endl;
    if (!check_password(username, password.c_str())) {
        cerr << "Sorry, try again." << endl;
        exit(1);
    }
    if (seteuid(0) == -1) {
        cerr << "Error: Cannot set effective user ID to root." << endl;
        exit(1);
    }
    if (execvp(argv[1], argv + 1) == -1) {
        cerr << "Error: Cannot execute command: " << argv[1] << endl;
        exit(1);
    }
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " command [arguments]" << endl;
        exit(1);
    }
    pid_t pid = fork();
    if (pid == -1) {
        cerr << "Error: Cannot fork a child process." << endl;
        exit(1);
    }
    else if (pid == 0) {
        execute_command(argc, argv);
    }
    else {
        int status;
        if (waitpid(pid, &status, 0) == -1) {
            cerr << "Error: Cannot wait for child process." << endl;
            exit(1);
        }
        if (WIFEXITED(status)) {
            int code = WEXITSTATUS(status);
            cout << "Command exited with code: " << code << endl;
        }
        else {
            cout << "Command terminated abnormally." << endl;
        }
    }
    return 0;
}
