// https://en.wikipedia.org/wiki/AVL_tree
// 28/06/2019

#include <iostream>
#include <math.h>

class Node {

    private:
        int key, height;
        Node *left, *right;
        Node * add_node(int);
        Node * left_rotation();
        Node * right_rotation();
        Node * self_balance(int, int);
        std::pair<bool, Node *> predecessor(int);
        std::pair<bool, Node *> successor(int);
        void printAll();
        friend class AVLTree;
    public:
        Node(int);
        ~Node();
        int Key();
        friend int getHeight(Node *);
        friend int differ_height_of_childs(Node *);
};

class AVLTree {
    private:
        Node *root;
        int *amoutOfNode;
    public:
        AVLTree();
        ~AVLTree();
        std::pair<bool, Node *> Search(int);
        void Insert(int);
        void Traversal();
        std::pair<bool, Node *> find_predecessor(int);
        std::pair<bool, Node *> find_successor(int);
};

//---------------------------------------------------------------------------------------------------------------------------------------------------------------
// Main function
int getHeight(Node *node) {
    if (node)
        return node->height;
    return 0;
}

int differ_height_of_childs(Node *node) {
    return getHeight(node->left) - getHeight(node->right);
}

int main() {
    AVLTree *tree = new AVLTree();
    tree->Traversal();
    int choice, value;
    while (1) {
        std::cout <<"\n1 + x: Get predecessor of(x)\n2 + x: Get Successor of (x)\n0: End game\n";
        std::cin >> choice;
        if (choice) {
            std::pair<bool, Node *> finding;
            std::cin >> value;
            if (choice == 1) {
                finding = tree->find_predecessor(value);
                if (!finding.first)
                    std::cout <<"\nNo Predecessor of " << value;
                else 
                    std::cout << "\nPredecessor of " << value <<" is " << finding.second->Key();
            }
            else {
                finding = tree->find_successor(value);
                if (!finding.first)
                    std::cout <<"\nNo Successor of " << value;
                else 
                    std::cout << "\nSuccessor of " << value <<" is " << finding.second->Key();
            }
        }
        else {
            std::cout <<"\nEnd game";
            return 0;
        }
    }

}

//-----------------------------------------------------------------------------------------------------------------------------------------------------
// Node member Method, function
Node::Node(int key) {
    this->key = key, this->height = 1;
    this->left = this->right = NULL;
}

int Node::Key() {return this->key;}

Node::~Node() {
    delete this->left, this->right;
}

Node * Node::left_rotation() {
    Node *rightNode = this->left->right;
    Node *leftNode = this->left;
    leftNode->right = this;
    this->left = rightNode;
    this->height = 1 + std::max(getHeight(this->left), getHeight(this->right));
    leftNode->height = 1 + std::max(getHeight(leftNode->left), getHeight(leftNode->right));
    return leftNode;
}

Node * Node::right_rotation() {
    Node *rightNode = this->right;
    Node *leftNode = this->right->left;
    this->right = leftNode;
    rightNode->left = this;
    this->height = 1 + std::max(getHeight(this->left), getHeight(this->right));
    rightNode->height = 1 + std::max(getHeight(rightNode->left), getHeight(rightNode->right));
    return rightNode;
}

Node * Node::self_balance(int value, int differ) {
    if (differ > 1) {
        if (value < this->left->key)
            return this->left_rotation();
        this->left = this->left->right_rotation();
        return this->left_rotation();
    }
    else 
        if (differ < -1) {
            if (value > this->right->key)
                return this->right_rotation();
            this->right = this->right->left_rotation();
            return this->right_rotation();
        }
    return this;
}

Node * Node::add_node(int value) {
    if (this) {
        if (this->key == value)
            return this;
        if (this->key > value)
            this->left = this->left->add_node(value);
        else
            this->right = this->right->add_node(value);
        this->height = 1 + std::max(getHeight(this->left), getHeight(this->right));
        int differ = differ_height_of_childs(this);
        return this->self_balance(value, differ);
    }
    else 
        return (new Node(value));
}

std::pair<bool, Node *> Node::predecessor(int value) {  
    std::pair<bool, Node *> result;
    result.first = false, result.second = this;
    Node * temp = this;
    while (temp) 
        if (temp->key < value) {
            result.first = true;
            result.second = temp;
            if (temp->right) {
                auto another = temp->right->predecessor(value);
                if (another.first)
                    return another;
            }   
            return result;
        }
        else 
            temp = temp->left;
    return result;
}

std::pair<bool, Node *> Node::successor(int value) {
    std::pair<bool, Node *> result;
    result.first = false, result.second = this;
    Node * temp = this;
    while (temp) 
        if (temp->key > value) {
            result.first = true;
            result.second = temp;
            if (temp->left) {
                auto another = temp->left->successor(value);
                if (another.first)
                    return another;
            }   
            return result;
        }
        else 
            temp = temp->right;
    return result;
}

void Node::printAll() {
    if (this) {
        this->left->printAll();
        std::cout <<" " << this->key;
        this->right->printAll();
    }
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------
// AVL tree member Method and function
std::pair<bool, Node *> AVLTree::Search(int value) {
    std::pair<bool, Node *> result;
    result.first = false, result.second = this->root;
    if (this->root) {
        Node *temp = this->root;
        while (temp) {
            result.second = temp;
            if (temp->key == value) {
                result.first = true;
                break;
            }
            else 
                if (temp->key > value)
                    temp = temp->left;
                else
                    temp = temp->right;
        }
    }
    return result;
}

void AVLTree::Insert(int value) {
    if (this->root) 
        this->root = this->root->add_node(value);
    else 
        this->root = new Node(value);
}

void AVLTree::Traversal() {
    if (this->root)
        this->root->printAll();
}

AVLTree::AVLTree() {
    std::cout <<"Input\n";
    int key;
    this->amoutOfNode = new int(0);
    this->root = NULL;
    while (std::cin >> key) {
        if (!key)
            break;
        this->Insert(key);
        *(this->amoutOfNode) += 1;
    }
}

std::pair<bool, Node *> AVLTree::find_predecessor(int value) {
    std::pair<bool, Node *> result;
    result.first = false, result.second = this->root;
    if (this->root) 
        result = this->root->predecessor(value);
    return result;
}

std::pair<bool, Node *> AVLTree::find_successor(int value) {
    std::pair<bool, Node *> result;
    result.first = false, result.second = this->root;
    if (this->root) 
        result = this->root->successor(value);
    return result;
}


AVLTree::~AVLTree() {
    delete this->root;
}
