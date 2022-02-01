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

int main (int argc, char* argv[]) {

    std::vector<std::string> files;
    std::vector<std::string> file_name;
    std::vector<unsigned char> bin_file_rep;
    std::vector<Node*> leaves;
    std::string  temp, h;
    Keccak keccak;
    unsigned char c;
  
  

    
    for ( filesys::recursive_directory_iterator end, dir("/home/theo/Desktop/Keccak/XKCP"); 
    dir != end; dir++ ) {

        
        temp.clear();
        bin_file_rep.clear();

        h = dir->path().string();

        if(checkIfFile(h)){
            
            

            std::ifstream in_file(h, std::ifstream::binary);

            while(!in_file.eof()){

                in_file >> c;

                bin_file_rep.push_back(c);


                

            }//while
      
            std::string ss(bin_file_rep.begin(), bin_file_rep.end() - 1);

            std::cout << h << std::endl;

            temp = keccak(ss);

            leaves.push_back(new Node(temp));
            leaves.back()->left = NULL;
            leaves.back()->right = NULL;

            file_name.push_back(h);

            in_file.close();

            
            
        }
      
        
  }//for

    

 

    merkle_tree *hash_tree = new merkle_tree(leaves);


    
    hash_tree->print_tree(hash_tree->root);


    return 0;

  
  
}