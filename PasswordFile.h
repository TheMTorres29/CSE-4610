#ifndef PASSWORDFILE_H
#define PASSWORDFILE_H
#include <vector>
#include <string>

class PasswordFile{
    public:
        PasswordFile(std::string filename); // opens the file and reads the names/passwords in the vectors user and password. DONE
        void addpw(std::string newuser, std::string newpassword); // adds a new user/password to the vectors and writes the vectors to the file filename. DONE
        bool checkpw(std::string usr, std::string passwd); // returns true if user exists and password matches.

    private: 
        std::string filename; // file that contains password file info
        std::vector<std::string> user; // list of users
        std::vector<std::string> password; //list of passwords
        void sync(); // writes user/password to the password file
};
#endif