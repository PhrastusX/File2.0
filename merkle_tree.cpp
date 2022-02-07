
#include <vector>
#include <string>
#include <iostream>


#define BASE 2
#define KEY 123456789

struct Node {
    int count;
    std::string hash;
    std::string file_directory;
    std::vector<Node*> data_ptr;

    Node(std::string data){
        hash = data;
        
    }
};

struct merkle_tree {

    Node* root;
    Keccak keccak;

    void build_tree(std::vector<Node*> children)
    {
        std::vector<Node*> parents;
        std::string temp = std::to_string(KEY); //holds all the concatinated hashes
        int displacement = children.size() % BASE;

        while(children.size() != 1){
            parents.clear();
        for(int i = 0; i < children.size(); i+=BASE)
        {
            for(int j = i; j < BASE+i; j++)
            {
                temp = temp + children[j]->hash;
            }

            std::string hash = keccak(temp);
            parents.push_back(new Node(hash));

            temp = std::to_string(KEY);

            for(int k = i; k < BASE + i; k++)
            {
                parents.back()->data_ptr.push_back(children[k]);
            }

       
            
        }
        children = parents;
        }
        
        
        
        this->root = parents[0];



    }
    

    void print_tree(Node *n)
        {
        
        if (n)
        {
            std::cout << n->data_ptr[0]->hash << std::endl;
        }
        
            
            
        
    }
    
};
/*
int main() {

    std::vector<Node*> leaves;
    Keccak keccak;

    leaves.push_back(new Node(keccak("somedata")));
    leaves.push_back(new Node(keccak("somedata")));
    leaves.push_back(new Node(keccak("somedata")));
    leaves.push_back(new Node(keccak("somedata")));
    leaves.push_back(new Node(keccak("somedata")));

    // initialize leaves
    for (unsigned int i = 0; i < leaves.size(); i++) {
        leaves[i]->left = NULL;
        leaves[i]->right = NULL;
    }

    merkle_tree *hashTree = new merkle_tree(leaves);


    
    hashTree->print_tree(hashTree->root);
    

    return 0;
}*/