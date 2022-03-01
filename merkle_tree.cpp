
#include <vector>
#include <string>
#include <iostream>




struct file_info
{
    std::string directory;
    double size;

};

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
    int hash_count = 0;

    void build_tree(std::vector<Node*> children, int BASE)
    {

        std::vector<Node*> parents;
        std::string temp;
        std::string hash;
        int displacement = 0;


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
                hash_count++;
                parents.push_back(new Node(hash));
                
                temp.clear();

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
            hash_count++;
            parents.push_back(new Node(hash));

            for(int n = 0; n < displacement; n++){
                
                parents.back()->data_ptr.push_back(children[n]);
                }
            }

            
            displacement = 0;
            temp.clear();
            children = parents;
        }
        
        
        
        this->root = parents[0];



    }

    ~merkle_tree(){
        //lol fix this
        delete root;
    }

    void destroy_tree(Node *n)
    {
        if(!n->data_ptr.empty()){
            
            for(int i = 0; i < n->data_ptr.size(); i++){
                destroy_tree(n->data_ptr[i]);
            }
            
        }

        delete n;
        
        
    }
    
    //search?
    //replace
    void print_tree(Node *n)
        {
        
        if (n)
        {
            std::cout << n->hash << std::endl;
        }
        
            
            
        
    }
    
};
