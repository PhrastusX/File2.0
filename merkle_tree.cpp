
#include <vector>
#include <string>
#include <iostream>

#define BASE 2
#define KEY 123456789

struct Node {
    int count;
    std::string hash;
    std::string file_directory;
    Node *left;
    Node *right;
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
        std::string temp; //holds all the concatinated hashes
        int displacement = children.size() % BASE;

        for(int i = 0; i < children.size(); i+=BASE)
        {
            for(int j = i; j < BASE+i; j++)
            {
                temp = temp + children[j]->hash;
            }

            std::string hash = keccak(temp);
            parents.push_back(new Node(hash));

            for(int k = i; k < BASE + i; k++)
            {
                parents.back()->data_ptr.push_back(children[k]);
            }
            
        }



    }
    

    void print_tree(Node *n)
        {
        
        if (n) {
            if (n->left) {
                print_tree(n->left);
            }
            if (n->right) {
                print_tree(n->right);               
            }
            if(n->left || n->right){
                std::cout <<"Node hash: " <<  n->hash << "\n"  << "Left hash: " << n->left->hash  << "\n" << "Right Hash: " << n->right->hash<< "\n" << std::endl;
            }
            else{
            
                std::cout << "Node number: " << n->count <<"\n"+ n->hash << "\n" << n->file_directory << "\n\n";
            }
        
            
            
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