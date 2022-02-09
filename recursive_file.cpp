#include "keccak.cpp"
#include "merkle_tree.cpp"
#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include <string>
#include <filesystem>
#include <chrono>




namespace filesys = std::filesystem;
namespace chrono = std::chrono;

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

    auto start = chrono::high_resolution_clock::now();

    std::vector<std::string> file_name; //keeping track of file names
    std::vector<unsigned char> bin_file_rep; //file is stored in this vector
    std::vector<Node*> leaves; //leaves for the merkle tree
    std::string  temp, directory_path;
    Keccak keccak;
    unsigned char c;
    int count = 0;
  
  

    
    for ( filesys::recursive_directory_iterator end, dir("/home/theo/Desktop"); 
    dir != end; dir++ ) {

        
        temp.clear();
        bin_file_rep.clear();

        directory_path = dir->path().string();

        if(checkIfFile(directory_path)){
            count++;
            

            std::ifstream in_file(directory_path, std::ifstream::binary);

            while(!in_file.eof()){

                in_file >> c;

                bin_file_rep.push_back(c);


                

            }//while
      
            std::string ss(bin_file_rep.begin(), bin_file_rep.end() - 1);

            std::cout << directory_path << std::endl;

            temp = keccak(ss);

            leaves.push_back(new Node(temp));
            leaves.back()->file_directory = directory_path;
            leaves.back()->count = count;

            file_name.push_back(directory_path);

            in_file.close();

    
        }

        

        
        
      
        
    }//for
    merkle_tree tree = merkle_tree();
    tree.build_tree(leaves);
    tree.print_tree(tree.root);

    return 0;
}