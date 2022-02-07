#include "keccak.cpp"
#include "merkle_tree.cpp"
#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include <string>
#include <filesystem>

namespace filesys = std::filesystem;

bool checkIfFile(std::string filePath)
{
    t
    try {
        // Create a Path object from given path string
        filesys::path pathObj(filePath);
        // Check if path exists and is of a regular file
        if (filesys::exists(pathObj) && filesys::is_regular_file(pathObj))
            return true;
    }
    catch (filesys::filesystem_error & e)
    {
        std::cerr << e.what() << std::endl;
    }
    return false;
}
bool checkIfDirectory(std::string filePath)
{
    try {
        // Create a Path object from given path string
        filesys::path pathObj(filePath);
        // Check if path exists and is of a regular file
        if (filesys::exists(pathObj) && filesys::is_directory(pathObj))
            return true;
    }
    catch (filesys::filesystem_error & e)
    {
        std::cerr << e.what() << std::endl;
    }
    return false;
}

void recursiveFile(std::string h)
{

    std::vector<std::string> in_order_files;
    for ( filesys::directory_iterator end, dir(h); 
    dir != end; dir++ ) {
    
        std::string temp = dir->path().string();

        if(checkIfDirectory(temp)){

            recursiveFile(temp);
        }



        
        std::cout << temp << std::endl;
      
        
    }//for
}

int main (int argc, char* argv[]) {

    std::vector<std::string> file_name; //keeping track of file names
    std::vector<unsigned char> bin_file_rep; //file is stored in this vector
    std::vector<Node*> leaves; //leaves for the merkle tree
    std::string  temp, h;
    Keccak keccak;
    unsigned char c;
  
  

    
    recursiveFile("/home/theo/file_test");




    return 0;

  
  
}