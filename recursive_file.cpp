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

std::vector<file_info *> fill_files(std::string directory)
{
    std::vector<file_info*> files; //keeping track of the file paths
    
    
    std::string directory_path;
    double file_size;
  
    for ( filesys::recursive_directory_iterator end, dir(directory); 
    dir != end; dir++ ) {


        directory_path = dir->path().string();

        if(checkIfFile(directory_path)){

            filesys::path pathObj(directory_path);
            
            

            files.push_back(new(file_info));

            files.back()->size = filesys::file_size(pathObj);
            files.back()->directory = directory_path;


        }
    
    }
    return files;
}

int partition(std::vector<file_info *> &sorting_file, int start, int end)
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


void q_sort(std::vector<file_info *> &sorting_file, int start, int end)
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
    
    
    std::string bin_file_rep(file.begin(), file.end());
            
    return bin_file_rep;

}

std::vector<Node *> hash_file(std::vector<file_info *> files, int BASE, int key, int position, int &count)
{
    //std::vector<std::string> file_name; //keeping track of file names
    //std::vector<unsigned char> file_rep; //file is stored in this vector
    std::vector<Node *> leaves; //leaves for the merkle tree
    std::string  temp, directory_path;
    std::string file_rep;
    Keccak keccak;
    int displacement = files.size() % BASE;
    
    
    

    for ( int i = 0; i < files.size() - BASE; i+= BASE ) 
    {

        

        for(int j = 0; j < BASE; j++)
        
        {
            if (i+j == position -1){

                file_rep += std::to_string(key);
            }

            file_rep += files_to_hash(files[i+j]->directory);
        
        }

        temp = keccak(file_rep);
        
        count++;
  

        leaves.push_back(new Node(temp));
        temp.clear();
        file_rep.clear();
        
        
    }//for
    if(displacement != 0)
            {
                for(int n = files.size() - displacement; n != files.size(); n++){
                
                file_rep += files_to_hash(files[n]->directory);
                }

            
            temp = keccak(file_rep);
            leaves.push_back(new Node(temp));
            count++;

            }

    return leaves;

}



int main (int argc, char* argv[]) {

    int size = 0;
    int key = 12345678;
    int position = 100;
    int num_of_hashes = 0;

    auto start = chrono::high_resolution_clock::now();
    //read files
    auto start_read_file = chrono::high_resolution_clock::now();
    std::vector<file_info *> files = fill_files(argv[1]);
    auto end_read_files = chrono::high_resolution_clock::now();

    size = files.size();
    //sort files
    auto start_sort = chrono::high_resolution_clock::now();
    q_sort(files, 0, files.size()-1);
    auto end_sort = chrono::high_resolution_clock::now();
    
    //hash files
    auto start_read_hash_files = chrono::high_resolution_clock::now();
    std::vector<Node *> leaves = hash_file(files, std::stoi(argv[2]), key, position, num_of_hashes);
    auto end_read_hash_files = chrono::high_resolution_clock::now();


    merkle_tree tree = merkle_tree();
    
    //build tree
    auto start_build_tree = chrono::high_resolution_clock::now();
    tree.build_tree(leaves, std::stoi(argv[2]));
    auto end_build_tree = chrono::high_resolution_clock::now();

    
    auto end = chrono::high_resolution_clock::now();
    
    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
    auto duration_files = chrono::duration_cast<chrono::milliseconds>(end_read_files - start_read_file);
    auto duration_sort = chrono::duration_cast<chrono::milliseconds>(end_sort - start_sort);
    auto duration_build_tree = chrono::duration_cast<chrono::microseconds>(end_build_tree - start_build_tree);
    auto duration_hash = chrono::duration_cast<chrono::milliseconds>(end_read_hash_files - start_read_hash_files);
    

    tree.print_tree(tree.root);

    std::cout << duration.count() << "ms total" << std::endl;
    std::cout << duration_sort.count() << "ms sorting" << std::endl;
    std::cout << duration_files.count() << "ms find all files" << std::endl;
    
    std::cout << duration_hash.count() << "ms read and hash files" << std::endl;
    std::cout << duration_build_tree.count() << "us build tree" << std::endl;

    std::cout << "Number of hashes at base: " << num_of_hashes << " Number of hashes in tree: "<< tree.hash_count << std::endl;
    std::cout << "Total: " << num_of_hashes + tree.hash_count << std::endl;
    

    return 0;
}