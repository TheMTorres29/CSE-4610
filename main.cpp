#include <iostream>
#include "sdisk.h"
#include "filesys.h"
#include "block.h"
#include "shell.h"
#include "table.h"
using namespace std;

int main(){
  // Test for SDisk
  /*Sdisk disk1("newdisk1", 16, 32);
  string block1, block2, block3, block4;

  for(int i = 1; i <= 32; i++){
    block1=block1+"1";
  }
  for(int i = 1; i <= 32; i++){
    block2=block2+"2";
  }

  disk1.putblock(4, block1);
  disk1.getblock(4, block3);
  cout << "Should be 32 1s : ";
  cout << block3 << endl;

  disk1.putblock(8, block2);
  disk1.getblock(8, block4);
  cout << "Should be 32 2s : ";
  cout << block4 << endl;*/

  // Test for Filesys
  /*Sdisk disk1("disk1",256,128);
  Filesys fsys("disk1",256,128);
  fsys.newfile("file1");
  fsys.newfile("file2");

  string bfile1;
  string bfile2;

  for(int i=1; i<=1024; i++){
    bfile1+="1";
  }

  vector<string> blocks = block(bfile1,128);

  int blocknumber=0;

  for(int i=0; i < blocks.size(); i++){
    blocknumber=fsys.addblock("file1",blocks[i]);
  }

  cout << "DEBUG: Del File1: " << endl;
  fsys.delblock("file1",fsys.getfirstblock("file1"));

  cout << "DEBUG: File2: " << endl;

  for(int i=1; i<=2048; i++){
    bfile2+="2";
  }

  blocks = block(bfile2,128);

  for(int i=0; i < blocks.size(); i++){
    blocknumber=fsys.addblock("file2",blocks[i]);
  }

  cout << "DEBUG: Del File2: " << endl;
  fsys.delblock("file2",blocknumber);*/

  // Test for Shell
  /*string s;
  string command="go";
  string op1,op2;

  Shell* shell = new Shell ("disk1", 256, 128);

  while (command != "quit")
  {
    command.clear();
    op1.clear();
    op2.clear();
    cout << "$";
    getline(cin,s);

    int firstblank=s.find(' ');
    if (firstblank < s.length())
      s[firstblank]='#';

    int secondblank=s.find(' ');
    command=s.substr(0,firstblank);

    if (firstblank < s.length())
      op1=s.substr(firstblank+1,secondblank-firstblank-1);
    if (secondblank < s.length())
      op2=s.substr(secondblank+1);
    if (command=="dir")
    {
      // use the ls function
      shell->dir();
    }
    if (command=="add")
    {
      // The variable op1 is the new file and op2 is the file data
      shell->add(op1, op2);
    }
    if (command=="del")
    {
      // The variable op1 is the file
      shell->del(op1);
    }
    if (command=="type")
    {
      // The variable op1 is the file
      shell->type(op1);
    }
    if (command=="copy")
    {
      // The variable op1 is the source file and the variable op2 is the destination file.
      shell->copy(op1, op2);
    }
    if (command=="search")
    {
      // This is the command for Project 4
      // The variable op1 is the date
    }

  }
  return 0;*/

  // Test for Table
  Sdisk sdisk = Sdisk("sdisk.txt",256,128);
  Filesys fsys = Filesys("sdisk.txt",256,128);
  Shell shell = Shell("sdisk.txt",256,128);
  Table table = Table("sdisk.txt",256,128,"flatfile","indexfile");
  table.Build_Table("data.txt");

  string s;
  string command = "go";
  string op1, op2;

  while (command != "quit")
  {
    command.clear();
    op1.clear();
    op2.clear();
    cout << "$";
    getline(cin,s);
    int firstblank = s.find(' ');
    if(firstblank < s.length())
    {
      s[firstblank] = '#';
    }

    int secondblank = s.find(' ');
    command = s.substr(0,firstblank);
    if (firstblank < s.length())
      op1 = s.substr(firstblank+1,secondblank-firstblank-1);
    if (secondblank < s.length())
      op2 = s.substr(secondblank+1);
    if (command == "dir")
    {
      shell.dir();    // use the ls function
    }
    if (command == "search")
    {
      table.Search(op1);    // The variable op1 is the date
    }
    if (command == "add")
    {
      shell.add(op1, op2);   // The variable op1 is the new file
    }
    if (command == "del")
    {
      shell.del(op1);   // The variable op1 is the file
    }
    if (command == "type")
    {
      shell.type(op1);    // The variable op1 is the file
    }
    if (command == "copy")
    {
      shell.copy(op1, op2);   // The variable op1 is the source file and the variable op2 is the destination file.
    }
  }
  return 0;
}


/*=============== How to make compress and make tar ===============*/
// tar -cf migueltorresCSE4610.tar
//    -czf                    .tgz

// How to uncompress and open
// tar -xf migueltorresCSE4610.tar
