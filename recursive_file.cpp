#include "keccak.h"
#include "merkle_tree.h"
#include "recursive_file.h"


int main (int argc, char* argv[]) {

    int size = 0; //starts at one to account for the key getting inserted into the tree
    int displacement;
    char c;
    int num_of_hashes = 0;
    double check;
    int additional_files;
    std::vector<char> key_value;
    std::vector<Node*> leaves;
    std::vector<Node*> files;//files do not become part of tree


    

    files.push_back(new Node());
    files.back()->directory = "key_file";

    auto start = chrono::high_resolution_clock::now();
    //read files
    auto start_read_file = chrono::high_resolution_clock::now();
    fill_files( argv[1], files);
    auto end_read_files = chrono::high_resolution_clock::now();

    size = files.size();

    //sort files
    auto start_sort = chrono::high_resolution_clock::now();
    q_sort(files, 0, files.size()-1);
    auto end_sort = chrono::high_resolution_clock::now();


    //this little bit fills the rest of the tree with hashes.
    check = std::ceil(std::log2(size));

    additional_files = pow(2,check) - size;

    for(int i = 1; i <= additional_files; i++){
        files.push_back(files[i]);
    }

    size = files.size();

    
 
    //hash files
    auto start_read_hash_files = chrono::high_resolution_clock::now();

   
    leaves = hash_file(files, std::stoi(argv[2]), num_of_hashes);
    
   
   
    auto end_read_hash_files = chrono::high_resolution_clock::now();

    


    merkle_tree tree = merkle_tree();
    
    //build tree

    auto start_build_tree = chrono::high_resolution_clock::now();
    //for(int i = 0; i < 10000; i ++){
        tree.build_tree(leaves, std::stoi(argv[2]));
    //}
    auto end_build_tree = chrono::high_resolution_clock::now();

    
    auto end = chrono::high_resolution_clock::now();
    
    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
    auto duration_files = chrono::duration_cast<chrono::milliseconds>(end_read_files - start_read_file);
    auto duration_sort = chrono::duration_cast<chrono::milliseconds>(end_sort - start_sort);
    auto duration_build_tree = chrono::duration_cast<chrono::microseconds>(end_build_tree - start_build_tree);
    auto duration_hash = chrono::duration_cast<chrono::milliseconds>(end_read_hash_files - start_read_hash_files);
    

    tree.print_tree(tree.root);

    std::cout << "Files: "<< size << std::endl;
    std::cout << duration.count() << "ms total" << std::endl;
    std::cout << duration_sort.count() << "ms sorting" << std::endl;
    std::cout << duration_files.count() << "ms find all files" << std::endl;
    
    std::cout << duration_hash.count() << "ms read and hash files" << std::endl;
    std::cout << duration_build_tree.count() << "us build tree" << std::endl;

    std::cout << "Number of hashes at base: " << num_of_hashes << " Number of hashes in tree: "<< tree.hash_count << std::endl;
    std::cout << "Total: " << num_of_hashes + tree.hash_count << std::endl;
    

    return 0;
}