#ifndef FILESYS_H
#define FILESYS_H
#include "sdisk.h"
#include <string>
#include <vector>
using namespace std;

// File System that will handle dynamic file management
// system will return 0 for FAILED, 1 for SUCCESSFUL
class Filesys : public Sdisk
{
  public:
    Filesys(string diskname, int numberofblocks, int blocksize);
    int fsclose();
    int newfile(string file);
    int rmfile(string file);
    int getfirstblock(string file);
    int addblock(string file, string block);
    int delblock(string file, int blocknumber);
    int readblock(string file, int blocknumber, string& buffer);
    int writeblock(string file, int blocknumber, string buffer);
    int nextblock(string file, int blocknumber);
    vector<string> ls();

  private:
    int rootsize;         // maximum number of entries in ROOT
    int fatsize;          // number of blocks occupied by FAT
    vector<string> filename;      // filenames in ROOT
    vector<int> firstblock;       // firstblocks in ROOT
    vector<int> fat;      // FAT
    void buildfs();        // builds the file system
    void readfs();         // reads the file system
    void fssynch();        // writes the FAT and ROOT to the sdisk
    bool checkblock(string file, int blocknumber);
};
#endif
