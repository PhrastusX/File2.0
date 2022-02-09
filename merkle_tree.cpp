
#include <vector>
#include <string>
#include <iostream>


#define BASE 12
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
        std::string hash = keccak(temp);
        int displacement = 0;
        int toggle       = 1; //toggle add key 

        while(children.size() != 1){

            displacement = children.size() % BASE;

            parents.clear();

            for(int i = 0; i < children.size() - displacement; i+=BASE)
            {
                for(int j = i; j < BASE + i; j++)
                {
                    temp = temp + children[j]->hash;
                }

                hash = keccak(temp);
                parents.push_back(new Node(hash));
                
                //add the key or not
                if(toggle == 1)
                    {temp = std::to_string(KEY);}

                else 
                    {temp.clear();}

                for(int k = i; k < BASE + i; k++)
                {
                    parents.back()->data_ptr.push_back(children[k]);
                }

            }

            
            if(displacement != 0)
            {
                for(int n = children.size() - displacement; n != children.size(); n++){
                
                temp = temp + children[n]->hash;
                }

            
            hash = keccak(temp);
            parents.push_back(new Node(hash));

            for(int n = 0; n < displacement; n++){
                
                parents.back()->data_ptr.push_back(children[n]);
                }
            }

            
            displacement = 0;
            toggle = 0;
            temp.clear();
            children = parents;
        }
        
        
        
        this->root = parents[0];



    }
    

    void print_tree(Node *n)
        {
        
        if (n)
        {
            std::cout << n->hash << std::endl;
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