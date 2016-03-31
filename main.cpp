#include <iostream>
#include <cassert>
#include <cstring>

#include "leveldb/db.h"

int main(int argc, char** argv){

  // create the database for storing synset information
  leveldb::DB* db;
  leveldb::Options options;
  options.create_if_missing = true;
  options.error_if_exists = true;
  leveldb::Status s = leveldb::DB::Open(options, "./synsetDB", &db);
  if(!s.ok()){
    std::cerr << s.ToString() << std::endl;
  }
  
  // open word synset file
  std::string file_path = argv[1]
  

  // Write the key-value pair
  db->Put(leveldb::WriteOptions(), key_write, value_write);

  // Read the value by 'key'
  std::string key_read = "this is key";
  std::string value_read;

  s = db->Get(leveldb::ReadOptions(), key_read, &value_read);
  if(s.ok()){
    std::cout << s.ToString() << std::endl;
    std::cout << "The value to '" << key_read << "'is " << value_read << std::endl;
  }

  // iterate over the each item in the database
  leveldb::Iterator* iter = db->NewIterator( leveldb::ReadOptions() ); 
  for(iter->SeekToFirst(); iter->Valid(); iter->Next()){
    std::cout << iter->key().ToString() << ": " << iter->value().ToString() << std::endl; 
  }


  // release the memory
  delete iter;
  delete db;
  
  return 0;
}
