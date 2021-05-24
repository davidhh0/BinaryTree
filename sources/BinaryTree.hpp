#include <iostream>
using namespace std;
#include <cfloat>
#include <string>
#include <iostream>
#include <vector>
#include <queue>
#include <fstream>
#include <sstream>
#include <set>

namespace ariel{
template <typename T>
class BinaryTree{

private:
    struct Node{
        T value;
        bool empty=false;
        Node* left=nullptr;
        Node* right=nullptr;
        Node(){}
        Node(int indicator,bool isEmpty):empty(isEmpty){}
        Node(T val): value(val){}
        ~Node(){
            if(left!=NULL){
                delete left;
            }
            if(right!=NULL){
                delete right;
            }
        }
    };
    


public:
    Node* root;
    BinaryTree(){
        root = new Node;
        
    }
    BinaryTree& add_root(T val){
        root->value = val;
        return *this;
   }

public:
    class iterator{
        public:
        
        Node* baseIterator;
        queue<Node*> treeQ;
        iterator(Node* node,int what){
            while(!treeQ.empty()){
                treeQ.pop();
            }
            if(node == nullptr){
                return;
            }
            switch (what)
            {
            case 1:
                createInOrder(node);
                break;
            case 2:
                createPreOrder(node);
                break;
            case 3:
                createPostOrder(node);
                break;        
            default:
                break;
            }

        }
        void createPostOrder(Node* node)
        {
            if (node == NULL)
                return;
            createPostOrder(node->left);
            createPostOrder(node->right);
            treeQ.push(node);
        }


        void createPreOrder(Node* node)
        {
            if (node == NULL)
                return;
            treeQ.push(node);    
            createPreOrder(node->left);
            createPreOrder(node->right);
        }
        void createInOrder(Node* node){
        if (node == NULL)
            return;
        createInOrder(node->left);
        treeQ.push(node);
        createInOrder(node->right);
        }

        
        
        public:


            bool operator!=(const iterator& other) const{
                bool isOtherEmpty = other.treeQ.empty();
                if((isOtherEmpty&&!treeQ.empty()) || (!isOtherEmpty&&treeQ.empty())){
                    return true;
                }
                return isOtherEmpty&&treeQ.empty()?false: (treeQ.front()!=other.treeQ.front());
            }
            iterator& operator++(){
                treeQ.pop();
                return *this;
            }
            T& operator*() const {
                return treeQ.front()->value;
            }   
            T* operator->() const{
                return &(treeQ.front()->value);
            }
            bool operator==(const iterator& rhs) const {
			    return treeQ.front() == rhs.treeQ.front();
		    }


    };
       friend class iterator;
    iterator begin(){
        return iterator{root,1};
    }
    iterator end(){
        return iterator{nullptr,1};
    }

    iterator begin_preorder(){
        return iterator{root,2};
    }
    iterator end_preorder(){
        return iterator{nullptr,2};
    }
    iterator begin_postorder(){
        return iterator{root,3};
    }
    iterator end_postorder(){
        return iterator{nullptr,3};
    }
    iterator begin_inorder(){
        return iterator{root,1};
    }
    iterator end_inorder(){
        return iterator{nullptr,1};
    }



    BinaryTree& add_left(const T& exists ,const T& add){    
    bool wasFound=false;
    iterator it = iterator{root,1};
    queue<Node*> runningQueue = it.treeQ;

    while(!runningQueue.empty()){
        
        Node* temp = runningQueue.front();
        if(temp->value == exists){
            
            wasFound=true;
            if(temp->left == NULL){
                
                Node* tempNode = new Node(add);
                temp->left = tempNode;
            }
            else{
                temp->left->value = add;
            }
            break;
        }
        runningQueue.pop();
    }
    
    if(!wasFound){
        throw::invalid_argument("Not found in the tree!");
    }
    return *this;
}
     BinaryTree& add_right(const T& exists ,const T& add){

    bool wasFound=false;
   
    iterator it = iterator{root,1};
    
    while(!it.treeQ.empty()){
        
        Node* temp = it.treeQ.front();
        if(temp->value == exists){
            wasFound=true;
            if(temp->right == NULL){
                
                Node* tempNode = new Node(add);
                temp->right = tempNode;
            }
            else{
                temp->right->value = add;
            }
            break;
        }
        it.treeQ.pop();
    }
    if(!wasFound){
        throw::invalid_argument("Not found in the tree!");
    }
    return *this;
}

    void deleteTree(Node* node){
        if(root==nullptr){
            return;
        }
        deleteTree(node->left);
        deleteTree(node->right);
        delete node;
        //node=NULL;
    }
    ~BinaryTree(){
        if(root!=NULL){
            delete root;
        }
    }
    
    


public:
    friend ostream& operator<<(ostream& os,BinaryTree& tree) {
    vector<vector<Node*>> treeLayers;
    Node* emptySpace =new Node(1,true);
    queue<Node*> Q;
    Q.push(tree.root);
    int counterForQ = 1;
    while(counterForQ>=0){
        int level = Q.size();
        vector<Node*> tempQueue;
        for(unsigned int i=0;i<level;i++){
            Node* node = Q.front(); Q.pop(); counterForQ--;
            tempQueue.push_back(node);
            if(node->left!=NULL){
                Q.push(node->left);
                counterForQ++;
            }
            else
                Q.push(emptySpace);     
            if(node->right != NULL){ 
                Q.push(node->right);
                counterForQ++;
            }
            else
                Q.push(emptySpace);          
        } treeLayers.push_back(tempQueue);

    }
    delete emptySpace;
    std::string::size_type treeLevel = treeLayers.size();
    std::string::size_type countForSpacesDividing = treeLevel;
    os<<string(treeLevel,' ');
    for(std::string::size_type i=0;i<treeLevel;i++){
        os<<string((treeLevel - i),' ');
        for(std::string::size_type j=0;j<treeLayers.at(i).size();j++){

            if((j) == treeLayers.at(i).size()/2 && i!=0 && i!=treeLevel-1) {
                os<<string(2*(countForSpacesDividing--)+1,' ');
                //cout<<"Bitch"<<countForSpacesDividing++<<"    ";
            }
            else if((j) == treeLayers.at(i).size()/2 && i==treeLevel-1) {
                os<<string(i-1,' ');
            }
            
            if(!treeLayers.at(i).at(j)->empty)
                os<<treeLayers.at(i).at(j)->value<< " ";
            else
                os<<"X ";    
        }
        os<<endl;
    }

    
    os << "Tree";
    return os;
    }
};
};