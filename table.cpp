#include "table.h"
#include "block.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

// GOOD, he did switch blocksize and numberofblocks tho
Table::Table(string diskname, int blocksize, int numberofblocks, string flatfile, string indexfile) : Filesys(diskname, numberofblocks, blocksize){
  this->indexfile = indexfile;
  this->flatfile = flatfile;
  newfile(flatfile);
  newfile(indexfile);
  cout << "Table created successfully!" << endl;
}

// int Table::Build_Table(string input_file){
//   ifstream infile;
//   infile.open(input_file.c_str());
//
// 	vector<string> tKey;
//   vector<int> tBlock;
//   string record;
//   getline(infile, record);
//   int number = 0;
//
//   while(infile.good()){
//   	string primeKey = record.substr(0,5);
//   	vector<string> blocks = block(record, getblocksize());
//   	int blockid = addblock(flatfile, blocks[0]);
//   	tKey.push_back(primeKey);
//   	tBlock.push_back(blockid);
//   	getline(infile, record);
//   	if(infile.bad() && tKey.size()>0){
//   		ostringstream tBuffer;
//   		tBuffer << tKey.size() << " ";
//   		for(int i = 0; i < tKey.size(); i++){
//   			tBuffer << tKey[i] << " " << tBlock[i] << " ";
//   		}
//   		string buffer = tBuffer.str();
//   		vector<string> blocks2 = block(buffer, getblocksize());
//   		int error = addblock(indexfile, blocks2[0]);
//   		tKey.clear();
//   		tBlock.clear();
//   	}
//   }
// }

// REMADE FROM class
int Table::Build_Table(string input_file){
  int code = newfile(indexfile);
  code = newfile(flatfile);

  ostringstream ostream;  // create indexfile
  ifstream infile;
  infile.open(input_file.c_str());
  string inputline;
  getline(infile, inputline);

  while(infile.good()){
    string key = inputline.substr(0, 5);  // grabs first 5 char
    string rest = inputline.substr(5);  // grabs rest of the line

    vector<string> blocks = block(inputline, getblocksize());
    int blockid = addblock(flatfile, blocks[0]); // make an int? instead if string

    ostream << key << " " << blockid << " ";
    getline(infile, inputline);
  }
  ostream << "XXXXX" << " " << 0 << " ";
  string buffer = ostream.str();
  vector<string> iblocks = block(buffer, getblocksize());

  // create indexfile
  for(int i = 0; i < iblocks.size(); i++){
    addblock(indexfile, iblocks[i]);
  }
  return 1;
}

int Table::Search(string value){
  int b = IndexSearch(value);
  if(b <= 0){
  	cout << "Record doesnt exist" << endl;
    return 0;
  }
  else{
  	string buffer;
  	readblock(flatfile, b, buffer);
  	cout << buffer << endl;
  }
  return 1;
}

int Table::IndexSearch(string value){
  istringstream instream;
  int b = getfirstblock(indexfile);
  while(b != 0){
    string buffer;
    readblock(indexfile, b, buffer);

    string key;
    int block;

    instream.str(buffer);

    for(int i = 1; i <= 4; i++){
      instream >> key >> block;
      if(value == key){
        return block;
      }
    }
    b = nextblock(indexfile, b);
  }
  return 1;
}
