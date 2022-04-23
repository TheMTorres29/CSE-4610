#include "filesys.h"
#include "block.h"
#include <iostream>
#include <sstream>
using namespace std;

Filesys::Filesys(string diskname, int numberofblocks, int blocksize) : Sdisk(diskname, numberofblocks, blocksize){
  string buffer;
  int code = getblock(0, buffer);
  if(code == 0){
    cout << "Bad device..." << endl;
    return;
  }

  rootsize = getblocksize()/12;
  fatsize = ((getnumberofblocks()*6)/getblocksize())+1;

  code = getblock(1, buffer);
  if(buffer[0] == '#'){
    // No File System exists
    buildfs();
  }
  else{
    // File System exists
    readfs();
  }
  fssynch();
}

void Filesys::buildfs(){
  // Write ROOT to Sdisk in block 1
  ostringstream ostream;
  for(int i = 0; i < rootsize; i++){
      filename.push_back("XXXXX");
      firstblock.push_back(0);
      ostream << "XXXXX" << " " << 0 << " ";
  }

  string buffer = ostream.str();
  vector<string> blocks = block(buffer, getblocksize());
  putblock(1, blocks[0]);

  // Write FAT to Sdisk in block 2
  ostringstream ostream2;
  fat.push_back(fatsize + 2);
  fat.push_back(1);
  for(int i = 0; i < fatsize; i++){
    fat.push_back(-1);
  }

  for(int i = fatsize + 2; i < getnumberofblocks(); i++){
      fat.push_back(i + 1);
  }

  fat[fat.size() - 1] = 0;
  for(int i = 0; i < fat.size(); i++){
      ostream2 << fat[i] << " ";
  }

  string buffer2 = ostream2.str();
  vector<string> blocks2 = block(buffer2, getblocksize());
  for(int i = 0; i < blocks2.size(); i++){
      putblock(2 + i, blocks2[i]);
  }
}

void Filesys::readfs(){
  // Read in ROOT
  istringstream istream;
  string buffer;
  getblock(1, buffer);

  istream.str(buffer);
  for(int i = 0; i < rootsize; i++){
      string s;
      int t;
      istream >> s;
      istream >> t;
      filename.push_back(s);
      firstblock.push_back(t);
  }

  // Read in FAT
  istringstream istream2;
  string buffer2;
  for(int i = 0; i < fatsize; i++){
      string b;
      getblock(i + 2, b);
      buffer2 += b;
  }
  istream2.str(buffer2);
  for(int i = 0; i < getnumberofblocks(); i++){
      int t;
      istream2 >> t;
      fat.push_back(t);
  }
}

void Filesys::fssynch(){
  // Write root and fat to disk
  ostringstream ostream;
  for(int i = 0; i < rootsize; i++){
    ostream << filename[i] << " " << firstblock[i] << " ";
  }
  string buffer = ostream.str();
  vector<string> blocks = block(buffer, getblocksize());
  putblock(1, blocks[0]);

  ostringstream ostream2;
  for(int i = 0; i < fat.size(); i++){
    ostream2 << fat[i] << " ";
  }
  string buffer2 = ostream2.str();
  vector<string> blocks2 = block(buffer2, getblocksize());
  for(int i = 0; i < blocks2.size(); i++){
    putblock(2 + i, blocks2[i]);
  }
}

int Filesys::fsclose(){
  fssynch();
  return 0;
}

int Filesys::newfile(string file){
  for(int i = 0; i < filename.size(); i++){
    if(filename[i] == file){
      cout << "File " << file << " exists" << endl;
      return 0;
    }
  }

  for(int i = 0; i < filename.size(); i++){
    if(filename[i] == "XXXXX"){
      cout << "Creating file: " << file << endl;
      filename[i] = file;
      firstblock[i] = 0;
      fssynch();
      return 1;
    }
  }
  cout << "No room in ROOT" << endl;
  return 0;
}

int Filesys::rmfile(string file){
  for(int i = 0; i < filename.size(); i++){
    if(filename[i] == file && firstblock[i] == 0){
      filename[i] = "XXXXX";
      firstblock[i] = 0;
      fssynch();
      return 1;
    }
  }
  return 1;
}

int Filesys::getfirstblock(string file)
{
  // returns firstblock of file or
  // returns 0 if file is empty or doesnt exist
  for(int i = 0; i < filename.size(); i++)
  {
    if(filename[i] == file)
    {
      cout << "returning first block..." << endl;
      return firstblock[i];
    }
  }
  cout << "No such file..(getfirstblock)" << endl;
  return -1;
}

int Filesys::addblock(string file, string block)
{
  // return allocated block number
  int first = getfirstblock(file);
  if(first == -1)
  {
    cout << "No such file..(addblock)" << endl;
    return 0;
  }

  int allocate = fat[0];
  if(allocate == 0)
  {
    cout << "no space in disk" << endl;
    return 0;
  }



  fat[0] = fat[fat[0]];
  fat[allocate] = 0;

  if(first == 0)
  {
    for(int i = 0; i < rootsize; i++)
    {
      if(filename[i] == file)
      {
        firstblock[i] = allocate;
      }
    }
  }
  else
  {
    int b = first;
    while(fat[b] != 0)
    {
      b = fat[b];
    }
    fat[b] = allocate;
  }
  putblock(allocate, block);
  fssynch();
  return allocate;
}

int Filesys::delblock(string file, int blocknumber){
  if(!checkblock(file, blocknumber))
  {
    return 0;
  }
  int b = getfirstblock(file);
  if(blocknumber == b)
  {
    for(int i = 0; i < filename.size(); i++)
    {
      if(filename[i] == file)
      {
        firstblock[i] = fat[blocknumber];
        break;
      }
    }
  }
  else
  {
    while(fat[b] != blocknumber)
    {
      b = fat[b];
    }
    fat[b] = fat[blocknumber];
  }
  // Update free list
  fat[blocknumber] = fat[0];
  fat[0] = blocknumber;
  fssynch();
}

int Filesys::readblock(string file, int blocknumber, string& buffer){
  if(checkblock(file, blocknumber)){
    getblock(blocknumber, buffer);
    return 1;
  }
  else{
    return 0;
  }
}

int Filesys::writeblock(string file, int blocknumber, string buffer){
  if(checkblock(file, blocknumber)){
    putblock(blocknumber, buffer);
    return 1;
  }
  else{
    return 0;
  }
}

int Filesys::nextblock(string file, int blocknumber){
  if(checkblock(file, blocknumber)){
    return fat[blocknumber];
  }
  else{
    return 0;
  }
}

bool Filesys::checkblock(string file, int blocknumber){
  // return false if block doesnt exist
  // return true if block exists
  int b = getfirstblock(file);
  if(b == -1)
  {
    return false;
  }
  // if(b == blocknumber)
  // {
  //   return true;
  // }
  while(b != 0)
  {
    if(b == blocknumber)
    {
      return true;
    }
    b = fat[b];
  }
  return false;
}

// Added ls() from shell lab
vector<string> Filesys::ls()
{
  vector<string> flist;
  for(int i=0; i<filename.size(); i++)
  {
    if(filename[i] != "XXXXX")
    {
      flist.push_back(filename[i]);
    }
  }
  return flist;
}
