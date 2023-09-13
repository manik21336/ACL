# sudooo

A C++ program that serves as a sudo-like program.

## Description

This program allows the user to execute commands with root privileges, after verifying their identity and password. It uses the `getspnam` function to access the shadow file, which stores the encrypted passwords of the users. It also uses the `crypt` function to encrypt the given password and compare it with the stored one. It then uses the `seteuid` function to set the effective user ID to root, and the `execvp` function to execute the command with its arguments. The program forks a child process to execute the command, and waits for it to finish. It then displays the exit code or termination status of the command.


The program seems to use the /GS (Buffer Security Check) compiler option, which instructs the compiler to insert overrun detection code into functions that are at risk of being exploited1. This could help defend against buffer overflow attacks, which are a common way of exploiting software vulnerabilities.
The program also seems to use the SafeInt Library, which helps prevent integer overflows and other exploitable errors that might occur when the application performs mathematical operations1. This could help defend against arithmetic errors that could lead to incorrect results or memory corruption.
The program checks the user’s password using the crypt function and the shadow file, which stores the encrypted passwords of the users1. This could help defend against password cracking attacks, which are a common way of gaining unauthorized access to a system.
The program forks a child process to execute the command, and waits for it to finish. It then displays the exit code or termination status of the command1. This could help defend against zombie processes, which are processes that have terminated but have not been reaped by their parent process. Zombie processes can consume system resources and cause performance issues.




## Requirements

- A Linux operating system
- A C++ compiler that supports C++11 or higher
- The crypt library
- The shadow file and its permissions

## Installation

- Clone or download this repository
- Navigate to the directory where the source file is located
- Compile the source file using a command such as:

    g++ sudooo.cpp -o sudooo -lcrypt

- Make sure that the binary file is owned by root and has the setuid bit set, using a command such as:

    sudo chown root:root sudooo
    sudo chmod u+s sudooo

## Usage

- Run the binary file with a command and its arguments as parameters, such as:

    ./sudooo ls -l

- Enter your password when prompted
- See the output of the command or any errors or warnings
- If you recieve an error make sure to check whether Set Ownership and Permissions: After compiling, set the ownership of the executable to root and set the setuid bit to ensure it runs with elevated privileges:
    sudo chown root:root sudooo
    sudo chmod u+s sudooo
