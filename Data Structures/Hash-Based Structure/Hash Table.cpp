// Collision resolution with Separate Chaining and Talbe doubling
#include <iostream>
#define ull unsigned long long


class Node {
    private:
        ull key;
        Node *next, *pre;
        friend class doublyLinkedList;
    public:
        Node(ull, Node *, Node *);
        ~Node();
        friend class hashTable;
};

class doublyLinkedList {
    private:
        Node *head, *tail;
    public:
        doublyLinkedList();
        ~doublyLinkedList();
        bool Insert(ull);
        std::pair<bool, Node *> Search(ull);
        bool Delete(ull);
        friend class hashTable;
};

class hashTable {
    private:
        doublyLinkedList ** table;
        ull capacity, size;
        void UpSize();
        void DownSize();
        ull hash(ull, ull);
    public:
        hashTable();
        ~hashTable();
        void Insert(ull);
        void Delete(ull);
        std::pair<bool, Node *> Search(ull);
};

int main() {    
    int value;
    hashTable *arr = new hashTable();
    while(std::cin >> value) {
        if (value == 0)
            break;
        arr->Insert(value);
    }
}


// -----------------------------------------

Node::Node(ull key, Node *pre = NULL, Node *next = NULL) {
    this->key = key;
    this->pre = pre, this->next = next;
}

Node::~Node() {
    this->pre = this->next = NULL;
}

// ---------------------------------------------

doublyLinkedList::doublyLinkedList() {
    this->head = this->tail = NULL;
}

doublyLinkedList::~doublyLinkedList() {
    Node *move = NULL;
    while (this->head) {
        move = this->head;
        this->head = this->head->next;
        delete move;
    }
    this->tail = NULL;
}

bool doublyLinkedList::Insert(ull value) {
    if (this->head) {
        Node *temp = this->head;
        while (temp != NULL) {
            if (temp->key == value)
                return false;
            temp = temp->next;
        }
        this->tail = new Node(value, this->tail);
    }   
    else 
        this->head = this->tail = new Node(value);
    return true;
}

std::pair<bool, Node *> doublyLinkedList::Search(ull value) {
    std::pair<bool, Node *> result;
    result.first = false, result.second = NULL;
    if (this->head != NULL) {   
        Node *temp = this->head;
        while (temp != NULL) {
            if (temp->key == value) {
                result.first = true;
                result.second = temp;
                break;
            }
            temp = temp->next;
        }
    }
    return result;
}

bool doublyLinkedList::Delete(ull value) {
    auto search = this->Search(value);
    if (search.first == false)
        return false;   
    if (search.second->pre != NULL) {
            search.second->pre->next = search.second->next;
            if (search.second->next == NULL)
                this->tail = search.second->pre;
    }
    else {
        this->head = search.second->next;
        if (search.second->next == NULL)
            this->tail = NULL;
    }
    delete search.second;
}

//-------------------------------------

ull hashTable::hash(ull value, ull capacity) {
    return (value % capacity);
}

hashTable::hashTable() {
    this->size = 0;
    this->capacity = 10;
    this->table = new doublyLinkedList*[capacity];
}

hashTable::~hashTable() {
    for (int i = 0; i < this->capacity; i++)
        delete table[i];
    this->size = this->capacity = 0;
}


void hashTable::Insert(ull value) {
    ull position = this->hash(value, this->capacity);   
    if (this->table[position] == NULL)
        this->table[position] = new doublyLinkedList();
    if (this->table[position]->Insert(value))
        this->size++;
    if (this->size == capacity)
        this->UpSize();
}

void hashTable::Delete(ull value) {
    ull position = this->hash(value, this->capacity);
    if (this->table[position] != NULL) 
        if (this->table[position]->Delete(value))
            this->size--;
    if (this->size <= this->capacity / 4)
        this->DownSize();
}

void hashTable::UpSize() {
    doublyLinkedList ** newTable = new doublyLinkedList*[this->capacity * 2];
    Node *temp = NULL;
    for (int i = 0; i < this->capacity; i++)
        if (this->table[i] != NULL) 
            while(this->table[i]->head != NULL) {
                temp = this->table[i]->head;
                this->table[i]->head = temp->next;
                ull pos = this->hash(temp->key, this->capacity * 2);
                if (newTable[pos] == NULL)
                    newTable[pos] = new doublyLinkedList();
                newTable[pos]->Insert(temp->key);
                delete temp;
            }
    this->capacity *= 2;
    delete this->table;
    this->table = newTable;
}

void hashTable::DownSize() {
    doublyLinkedList ** newTable = new doublyLinkedList*[this->capacity / 2];
    Node *temp = NULL;
    for (int i = 0; i < this->capacity; i++) 
        if (this->table[i] != NULL) 
            while (this->table[i]->head != NULL) {
                temp = this->table[i]->head;
                this->table[i]->head = temp->next;
                ull pos = this->hash(temp->key, this->capacity / 2);
                if (newTable[pos] == NULL)
                    newTable[pos] = new doublyLinkedList();
                newTable[pos]->Insert(temp->key);
                delete temp;               
            }
    this->capacity /= 2;
    delete this->table;
    this->table = newTable;
}
