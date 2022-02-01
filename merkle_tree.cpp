
#include <vector>
#include <string>
#include <iostream>

struct Node {
    std::string hash;
    Node *left;
    Node *right;

    Node(std::string data){
        hash = data;
    }
};

struct merkle_tree {

    Node* root;
    Keccak keccak;

    merkle_tree(std::vector<Node*> data) {

        std::vector<Node*> nodes;

        while (data.size() != 1) 
        {

            for (unsigned int l = 0, n = 0; l < data.size(); l = l + 2, n++) 
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

    void print_tree(Node *n)
        {
        if (n) {
            if (n->left) {
                print_tree(n->left);
                std::cout << std::endl;
            }
            if (n->right) {
                print_tree(n->right);
                std::cout << std::endl;
            }

            std::cout << n->hash << "\n";
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