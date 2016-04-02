#include <iostream>
#include <fstream>
#include <sstream>
#include <streambuf>
#include <vector>

#include <cassert>
#include <cstring>

#include "leveldb/db.h"
#include "leveldb/write_batch.h"
#include "boost/algorithm/string.hpp"

using namespace std;

string load_file_toString(char const * filepath)
{
  ifstream src(filepath);
  if(!src.is_open()){
    cerr << "File not open: unkown reason" << endl;
  }
  
  stringstream buf;
  buf << src.rdbuf();
  return buf.str();
}

int main(int argc, char** argv){

  /* create the database for storing synset information */
  leveldb::DB* db;
  leveldb::Options options;
  options.create_if_missing = true;
  leveldb::Status s = leveldb::DB::Open(options, "./synsetDB", &db);
  if(!s.ok()){
    std::cerr << s.ToString() << std::endl;
  }
  
  /* open file */
  string file_path = argv[1];
  string file_content = load_file_toString(file_path.c_str());
  vector<string> lines;
  boost::split(lines, file_content, boost::is_any_of("\n"));

  
  /* Write the key-value pair */
  leveldb::WriteBatch batch;
  int key = 0;
  for(vector<string>::iterator iter=lines.begin(); iter!=lines.end(); iter++){
    key++;
    batch.Put(to_string(key), *iter);
  }
  db->Write(leveldb::WriteOptions(), &batch);


  
  /* Read the value by 'key' */
  std::string key_read = "400";
  std::string value_read;
  
  s = db->Get(leveldb::ReadOptions(), key_read, &value_read);
  if(s.ok()){
    std::cout << s.ToString() << std::endl;
    std::cout << "The value to '" << key_read << "'is " << value_read << std::endl;
  }  

  
  /* iterate over the each item in the database
  leveldb::Iterator* iter = db->NewIterator( leveldb::ReadOptions() ); 
  for(iter->SeekToFirst(); iter->Valid(); iter->Next()){
    std::cout << iter->key().ToString() << ": " << iter->value().ToString() << std::endl; 
  }
  delete iter;
  */


  /* release the memory */
  delete db;
  
  return 0;
}
