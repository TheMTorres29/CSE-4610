#ifndef SHELL_H
#define SHELL_H
#include <string>
#include "filesys.h"

class Shell : public Filesys{
    public:
        Shell(std::string filename, int numberofblocks, int blocksize);
        int dir(); // lists all files
        int add(std::string file, std::string buffer); // add a new file using input from the keyboard
        int del(std::string file); // deletes the file
        int type(std::string file); // lists the contents of file
        int copy(std::string file1, std::string file2); // copies file1 to file2
};
#endif
