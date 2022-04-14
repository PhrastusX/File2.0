#include "keccak.cpp"
#include "merkle_tree.h"
#include "recursive_file.h"



#include <vector>
#include <fstream>
#include <iostream>
#include <string>

void compare(std::vector<Node*> c, std::vector<Node*>n){

    int size = c.size();
    std::string file_rep_c;
    std::string file_rep_n;
    for (int i = 0; i < size; i ++){
        file_rep_c = files_to_hash(c[i]->directory);
        file_rep_n = files_to_hash(n[i]->directory);

        //if the files are the same continue
        if(files_to_hash(c[i]->directory).compare(files_to_hash(n[i]->directory)) == 0){
            continue;
        }
        else{
            n[i]->changes = true;
            //std::cout << file_rep_n << "\n\n" << file_rep_c << std::endl;
        }
    }

}

int main(int argc, char* argv[])
{


    std::vector<Node*> current_version; //represents the leaves in the current version
    std::vector<Node*> new_version; //represents the leaves in the new version

    //get the directories from the command line
    std::string current_version_directory = argv[1];
    std::string new_version_directory = argv[2];

    add_Id(current_version);
    add_Id(new_version);

    //fill the vectors with the appropriate directories.
    fill_files(current_version_directory, current_version);
    fill_files(new_version_directory, new_version);

    std::cout << "Current version size " << current_version.size() << std::endl;
    std::cout << "New version size "<<new_version.size() << std::endl;

    q_sort(current_version, 1, current_version.size()-1);
    q_sort(new_version, 1, new_version.size()-1);

    int size = current_version.size();

    balance_leaves(current_version);
    balance_leaves(new_version);

  

    std::cout << current_version.size() << std::endl;
    std::cout << new_version.size() << std::endl;

    size = current_version.size();

    compare(current_version, new_version);
    int count = 0;

    for(int i = 0; i < size; i ++){
        if(new_version[i]->changes)
            {count++;}
    }



    std::cout<< count << std::endl;


}
