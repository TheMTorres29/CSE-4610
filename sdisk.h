#ifndef SDISK_H
#define SDISK_H
#include <string>
using namespace std;

// Class that Simulates Disk Drive
class Sdisk{
  public:
    Sdisk();
    Sdisk(string diskname, int numberofblocks, int blocksize);
    int getblock(int blocknumber, string& buffer);      // system will return 0 for FAILED, 1 for SUCCESSFUL
    int putblock(int blocknumber, string buffer);
    int getnumberofblocks();    // accessor function
    int getblocksize();       // accessor function

  private:
    string diskname;        // file name of software disk
    int numberofblocks;     // number of blocks on disk
    int blocksize;          // block size in bytes
};
#endif
