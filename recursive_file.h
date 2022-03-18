#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include <string>
#include <filesystem>
#include <chrono>
#include <cmath>

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


void fill_files(std::string directory, std::vector<Node *> &files)
{
    
    std::string directory_path;
    double file_size;
  
    for ( filesys::recursive_directory_iterator end, dir(directory); 
    dir != end; dir++ ) {


        directory_path = dir->path().string();

        if(checkIfFile(directory_path)){

            filesys::path pathObj(directory_path);
            
            files.push_back(new Node());

            files.back()->size = filesys::file_size(pathObj);
            files.back()->directory = directory_path;


        }
    
    }
    
}


int partition(std::vector<Node *> &sorting_file, int start, int end)
{
    int pivot = sorting_file.at(start)->size;

    int count = 0;
    for(int i = start + 1; i <= end; i++)
    {
        if(sorting_file.at(i)->size <= pivot){
            count++;
        }
    }
    
    int pivot_index = start + count;
    std::swap(sorting_file.at(start), sorting_file.at(pivot_index));

    int i = start, j = end;
 
    while (i < pivot_index && j > pivot_index) {
 
        while (sorting_file[i]->size <= pivot) {
            i++;
        }
 
        while (sorting_file[j]->size > pivot) {
            j--;
        }
        if (i < pivot_index && j > pivot_index) {
            std::swap(sorting_file[i++], sorting_file[j--]);
        }
    }
 
    return pivot_index;
}


void q_sort(std::vector<Node *> &sorting_file, int start, int end)
{
    // base case
    if (start >= end)
        return;
 
    // partitioning the array
    int p = partition(sorting_file, start, end);
 
    // Sorting the left part
    q_sort(sorting_file, start, p - 1);
 
    // Sorting the right part
    q_sort(sorting_file, p + 1, end);
}


std::string files_to_hash(std::string directory_path)
{
    std::vector<char> file;
    
    char c;


    std::ifstream in_file(directory_path, std::ifstream::binary);

    while(!in_file.eof())
    {
        in_file >> c;
        file.push_back(c);
    }
    
    
    std::string bin_file_rep(file.begin(), file.end()-1);
            
    return bin_file_rep;

}


std::vector<Node *> hash_file(std::vector<Node *> files, int BASE, int &count)
{
    //std::vector<std::string> file_name; //keeping track of file names
    //std::vector<unsigned char> file_rep; //file is stored in this vector
    std::vector<Node *> leaves; //leaves for the merkle tree
    std::string  temp, directory_path;
    std::string file_rep;
    std::vector<char> key_value;
    Keccak keccak;
    char c;


    for ( int i = 0; i < files.size(); i+= BASE ) 
    {

        

        for(int j = 0; j < BASE; j++)
        
        {
  

            file_rep += files_to_hash(files[i+j]->directory);
        
        }

        temp = keccak(file_rep);
        
        count++;
  

        leaves.push_back(new Node(temp));
        temp.clear();
        file_rep.clear();
        
        
    }//for
   

    return leaves;

}
