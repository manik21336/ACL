#include <iostream>
#include <vector> 
#include <string>

using namespace std;


class FileData{
    private:
        unsigned int acl_len;
        vector<string> aclString;
        unsigned int data_len;
        string filedata;
    
    public:
    bool hasPermission(uid_t userUID, const std::string& filename) {
    // Implement your ACL checking logic here
    // Check if the user represented by 'userUID' has the necessary permissions
    // based on the ACLs associated with the file specified by 'filename'

    // Sample implementation: Assume 'acl' contains ACL entries in the format "type:name:permissions"
    for (const string& aclEntry : aclString) {
        size_t pos1 = aclEntry.find(":");
        size_t pos2 = aclEntry.find(":", pos1 + 1);

        if (pos1 !=string::npos && pos2 != string::npos) {
            string type = aclEntry.substr(0, pos1);
            string name = aclEntry.substr(pos1 + 1, pos2 - pos1 - 1);
            string permissions = aclEntry.substr(pos2 + 1);

            if (type == "user" && userUID ==1007) {
                // Check if 'userUID' matches the UID associated with 'name'
                // and if the permissions grant access
                if (permissions.find("read") != string::npos) {
                    return true; // User has read permission
                }
            } else if (type == "group" && userUID==1007) {
                // Check if 'userUID' belongs to the group specified by 'name'
                // and if the permissions grant access
                if (permissions.find("write") != string::npos) {
                    return true; // User belongs to the group and has write permission
                }
            }
        }
    }

    return false; // Default to denying access if no specific rules apply
}





};

