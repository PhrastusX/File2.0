
#include <vector>
#include <string>
#include <iostream>

#define BASE 2

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

    merkle_tree(std::vector<Node*> data) {

        std::vector<Node*> nodes;
        std::vector<Node*> inner_nodes;
        

        while (data.size() != 1) 
        {

            for (unsigned int l = 0, n = 0; l < data.size(); l = l + BASE, n++) 
            {
                if (l != data.size() - 1) 
                {

                        nodes.push_back(new Node(keccak(data[l]->hash + data[l+1]->hash))); 

                        nodes[n]->left = data[l]; 
                        nodes[n]->right = data[l+1];

                    


                }
            
                else 
                {
                    nodes.push_back(data[l]);
                }
            }
            data = nodes;
            nodes.clear();

        }
        this->root = data[0];
    }

    void build_tree(std::vector<Node*> data)
    {
        std::vector<Node*> node;

        if(data.size() != 1 ){
            for (int i = 0, n = 0; i < data.size(); i += BASE, n += BASE ){

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