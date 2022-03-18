#include "keccak.cpp"

#include <vector>
#include <fstream>
#include <iostream>
#include <string>
#include <regex>

void print_hash(std::vector<std::string> p){

    for(int i = 0; i < p.size(); i++){
        std::cout << p[i]; 
    }

    std::cout<<std::endl;
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

int main(void){

    Keccak keccak;
    
    std::string buffer;
    std::ifstream in("hash.txt");

    std::smatch index;//holds index row,column
    std::smatch hash;//holds the hash
    std::vector<std::string> coordinates;
 
    std::vector<std::string> hashes;

    std::string directory;
    std::ifstream in_first_file("first_file");
    in_first_file >> directory;
    in_first_file.close();
    std::ifstream in_first(directory);
    
    std::string first_file = files_to_hash(directory);
    std::string hash_file = files_to_hash("Id_file");



    


    
    while(!in.eof()){
        std::getline(in, buffer);
        if(std::regex_search(buffer, index, std::regex("[0-9]*,1\\)"))){
            std::cout << index[0] << std::endl;
            coordinates.push_back(index[0]);


            if(std::regex_search(buffer, hash, std::regex(" [0-9a-z]*"))){

            std::string s_hash = hash[0];
            s_hash = s_hash.substr(1,s_hash.length());
            std::cout << s_hash << std::endl;
            hashes.push_back(s_hash);

            }   

 
        }

       
    }

    int hash_comps = 1;
    std::string next = keccak(hash_file + first_file);;
    for(int i = 0; i < hashes.size(); i++){
        
        std::string temp = hashes[i];

        next = keccak(next + temp);
        hash_comps++;
    }

    std::cout << hash_comps << std::endl;
    std::cout << next << std::endl;

    

}