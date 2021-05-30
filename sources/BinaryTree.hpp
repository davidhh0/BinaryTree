#include <iostream>
#include <cfloat>
#include <string>
#include <iostream>
#include <vector>
#include <time.h>

#include <queue>
#include <fstream>
#include <sstream>
#include <set>
#include <algorithm>
#include <cstdlib>
#include <functional>
#include <map>
#include <memory>
#include <string>
#include <vector>
using namespace std;
namespace ariel {
    template<typename T>
    class BinaryTree {

    private:
        struct Node {
            T value;
            Node *left = nullptr;
            Node *right = nullptr;

            Node(T val) : value(val) {}
            Node(const Node &n){
                if (left != nullptr){
                    delete left;
                }
                if (right != nullptr){
                    delete right;
                }
                left=n.left; right=n.right;
            }
            Node &operator=(Node from) {
            if (this != &from) {
                if (left != nullptr){
                    delete left;
                }
                if (right != nullptr){
                    delete right;
                }
                right = from.right; left = from.left;
            }
            return *this;
        }
            Node &operator=(Node &&from) noexcept{
                if(left!=nullptr){
                    delete left;
                }
                if(right!=nullptr){
                    delete right;
                }
                left = from.left; right=from.right;
                from.left=nullptr; from.right=nullptr;
            }
            Node(Node&& other) noexcept:value(other.value) {
            left = other.left; right=other.right;
            other.left=nullptr; other.right=nullptr;
            }
            ~Node() {
                if (left != NULL) {
                    delete left;
                }
                if (right != NULL) {
                    delete right;
                }
            }
        };

        enum class traversal {
            inorder,
            preorder,
            postorder
        };

    public:
        Node *root = nullptr;
        int numberOfLeafs=0;
        BinaryTree() {
        }

        Node* copyTree(const Node *source)
        {
            if(source == nullptr)
            {
                return nullptr;
            }
            Node* result = new Node(source->value);
            result->left = copyTree(source->left);
            result->right = copyTree(source->right);
            return result;
        }

        BinaryTree(const BinaryTree &rhs)
                : root(copyTree(rhs.root)){}


        BinaryTree &add_root(T val) {
            if(root==nullptr){
            root = new Node(val);
            numberOfLeafs++;
            }
            else{
                root->value = val;
            }
            return *this;
        }

        Node *findInTree(Node *node, T val) {
            if (node == nullptr) {
                return nullptr;
            }
            if (node->value == val) {
                return node;
            }
            Node *LEFT = findInTree(node->left, val);
            if (LEFT != nullptr) {
                return LEFT;
            }
            Node *RIGHT = findInTree(node->right, val);
            return RIGHT;
        }



        class iterator {
        public:
            std::queue<Node*> iteratorQ;
            iterator(Node* node,traversal trav){
                if(node!=nullptr){
                    switch (trav)
                    {
                        case traversal::inorder:
                            createInOrder(node);
                            break;
                        case traversal::postorder:
                            createPostOrder(node);
                            break;
                        case traversal::preorder:
                            createPreOrder(node);
                            break;
                        default:
                            break;
                    }
                }
            }
            iterator(const iterator &source): iteratorQ(source.iteratorQ){
            }
            ~iterator(){
                // while(!iteratorQ.empty()){
                //     iteratorQ.pop();
               // }
            }
            iterator(iterator&& other) noexcept :iteratorQ(other.iteratorQ) {

            }

            iterator& operator=(iterator&& other)noexcept{
                iteratorQ = other.iteratorQ;
                return *this;
            }
            iterator& operator=(const iterator& other){
                if(this == &other){
                    return *this;
                }
                iteratorQ = other.iteratorQ;
                return *this;
            }

            bool operator!=(const iterator &other)  {
                if( (!iteratorQ.empty() && other.iteratorQ.empty())){
                    return true;
                }
                if( iteratorQ.empty() && !other.iteratorQ.empty()){
                    return true;
                }
                if(iteratorQ.empty() && other.iteratorQ.empty()){
                    return false;
                }

                return iteratorQ.front() != other.iteratorQ.front();
            }

            iterator &operator++() {
                iteratorQ.pop();
                return *this;
            }
            iterator operator++(int dummy){
                iterator temp = *this;
                if(iteratorQ.empty()){
                    return temp;
                }
                this->iteratorQ.pop();
                return temp;
            }

            T &operator*() const {
                return iteratorQ.front()->value;
            }

            T *operator->() const {
                return &(iteratorQ.front()->value);
            }


            bool operator==(const iterator &rhs) const {
                if(iteratorQ.empty() && !rhs.iteratorQ.empty()){
                    return false;
                }
                if(!iteratorQ.empty() && rhs.iteratorQ.empty()){
                    return false;
                }
                return (iteratorQ.empty()&&rhs.iteratorQ.empty())?true:iteratorQ.front()==rhs.iteratorQ.front();
            }

            void createInOrder(Node* node){
                if (node == NULL){
                    return;
                }
                createInOrder(node->left);
                iteratorQ.push(node);
                createInOrder(node->right);
            }
            void createPreOrder(Node* node)
            {
                if (node == NULL){
                    return;
                }
                iteratorQ.push(node);
                createPreOrder(node->left);
                createPreOrder(node->right);
            }
            void createPostOrder(Node* node)
            {
                if (node == NULL){
                    return;
                }
                createPostOrder(node->left);
                createPostOrder(node->right);
                iteratorQ.push(node);
            }



        };


        iterator begin() {
            return begin_inorder();
        }

        iterator end() {
            return end_inorder();
        }
//
        iterator begin_preorder() {
            iterator it = iterator(root,traversal::preorder);
            return it;

        }

        iterator end_preorder() {
            return iterator(nullptr,traversal::preorder);
        }

        iterator begin_postorder() {
            iterator it = iterator(root,traversal::postorder);
            return it;

        }

        iterator end_postorder() {
            return iterator(nullptr,traversal::postorder);
        }

        iterator begin_inorder() {
            iterator it = iterator(root,traversal::inorder);
            return it;

        }

        iterator end_inorder() {
            return iterator(nullptr,traversal::inorder);
        }



        BinaryTree &add_left(const T &exists, const T &add) {
            if (root == NULL) {
                throw std::invalid_argument("The tree wasn't initialized!");
            }
            Node *found = findInTree(root, exists);
            if (found == nullptr) {
                throw ::invalid_argument("Not found in the tree!");
            }
            if (found->left != nullptr) {
                found->left->value = add;
            } else {
                found->left = new Node(add);
                numberOfLeafs++;
            }
            return *this;
        }

        BinaryTree &add_right(const T &exists, const T &add) {
            if (root == NULL) {
                throw std::invalid_argument("The tree wasn't initialized!");
            }
            Node *found = findInTree(root, exists);
            if (found == nullptr) {
                throw ::invalid_argument("Not found in the tree!");
            }
            if (found->right != nullptr) {
                found->right->value = add;
            } else {
                numberOfLeafs++;
                found->right = new Node(add);
            }
            return *this;
        }

        ~BinaryTree() {
            if (root != NULL) {
                delete root;
            }
        }



        void printTree(ostream &os, Node *node, unsigned long counter) {
            if (node == nullptr) {
                return;
            }
            printTree(os, node->right, counter + 1);
            if (node) {
                os << string(4 * counter, ' ') << " -> " << node->value << endl;
            }
            printTree(os, node->left, counter + 1);

        }


        friend ostream &operator<<(ostream &os, BinaryTree &tree) {
            os << "";
            tree.printTree(os, tree.root, 0);
            return os;
        }

        BinaryTree &operator=(BinaryTree from) {
            if (this != &from) {
                if (root != nullptr){
                    delete root;
                }
                root = copyTree(from.root);
            }
            return *this;
        }
        BinaryTree &operator=(BinaryTree &&from) noexcept{
            cout<<"Constructr HERE !!#!@ !"<<endl;
            if (root != nullptr){
                delete root;
            }
            root = from.root;
            from.root = nullptr;

            return *this;
        }

        BinaryTree(BinaryTree&& other) noexcept{
            cout<<"Constructr !"<<endl;
            root  = other.root;
            other.root = nullptr;
        }

    };
};