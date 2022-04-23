#include "PasswordFile.h"
#include <iostream>
#include <fstream>
#include <string>

PasswordFile::PasswordFile(std::string filename){
    std::ifstream myfile;
    myfile.open("password.txt");

    std::string u, pw;
    while(myfile >> u >> pw){
        user.push_back(u);
        password.push_back(pw);
    }
    myfile.close();
}

void PasswordFile::addpw(std::string newuser, std::string newpassword){
    user.push_back(newuser);
    password.push_back(newpassword);

    std::ofstream myfile;
    myfile.open("password.txt");

    for(int i = 0; i < user.size(); i++){
        myfile << user[i] << " " << password[i] << std::endl;
    }
    myfile.close();
}

bool PasswordFile::checkpw(std::string usr, std::string passwd){
    for(int i = 0; i < user.size(); i++){
        if(usr == user[i]){
            std::cout << "User found.. ";
            if(passwd == password[i]){
                std::cout << "Password matched!" << std::endl;
                return true;
            }
            else{
                std::cout << "Password did not match." << std::endl;
                return false;
            }
        }
    }

    std::cout << "User did not match records" << std::endl;
    return false;
}