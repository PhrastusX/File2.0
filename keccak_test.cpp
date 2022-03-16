#include "keccak.cpp"
#include "merkle_tree.cpp"
#include <iostream>
#include <vector>

#include <fstream>
#include <string>

int main()
{
    Keccak keccak;

    std::string hash = keccak("d161f2301a6bcba459ca903c70e767895ccd4715ba228824410e2145293667a954a8c0ab653c15bfb48b47fd011ba2b9617af01cb45cab344acd57c924d56798");

    std::cout << hash << std::endl;



}