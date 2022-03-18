#include "keccak.cpp"
#include "merkle_tree.h"
#include <iostream>
#include <vector>

#include <fstream>
#include <string>
#include <chrono>

namespace chrono = std::chrono;
int main()
{
    Keccak keccak;

    auto start_read_hash_files = chrono::high_resolution_clock::now();

   for(int i = 0; i < 10000; i ++){
    std::string hash = keccak("d161f2301a6bcba459ca903c70e767895ccd4715ba228824410e2145293667a954a8c0ab653c15bfb48b47fd011ba2b9617af01cb45cab344acd57c924d56798");
    }
   
    auto end_read_hash_files = chrono::high_resolution_clock::now();

    auto duration_hash = chrono::duration_cast<chrono::microseconds>(end_read_hash_files - start_read_hash_files);

    std::cout << duration_hash.count() << "us" << std::endl;



}