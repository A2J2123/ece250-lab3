#include "tokenize.h"
#include <iostream>
#include <fstream>
#include <sstream>

// Constructor for the TwoWayDictionary class.
TwoWayDictionary::TwoWayDictionary(int new_size) {
    table_size = new_size;
    nodes = 0; 
    hash_table = new HashNode*[table_size];
    // Initialize hash table with nullptrs.
    for (int i = 0; i < table_size; ++i) {
        hash_table[i] = nullptr;
    }
}

// Destructor for the TwoWayDictionary class.
TwoWayDictionary::~TwoWayDictionary() {
    // Delete all nodes in the hash table.
    for (int i = 0; i < table_size; ++i) {
        HashNode* current = hash_table[i];
        while (current != nullptr) {
            HashNode* next = current->get_next();
            delete current;
            current = next;
        }
    }
    delete[] hash_table; // Delete the hash table array.
}

// Function to insert a word into the dictionary.
bool TwoWayDictionary::insert(const std::string& word) {
    unsigned index = hash(word); // Get the hash index for the word.
    HashNode* current = hash_table[index]; // Get the node at the hash index.

    // Check if the word contains only alphabetic characters.
    for(char ch : word){
        if (!isalpha(ch)){
            return false; 
        }
    }

    // Check if the word already exists in the dictionary.
    while (current != nullptr) {
        if (current->get_word() == word) {
            return false;
        }
        current = current->get_next();
    }

    // Create a new node for the word and add it to the hash table.
    nodes++;
    HashNode* newNode = new HashNode();
    newNode->set_word(word);
    newNode->set_token(nodes);
    newNode->set_next(hash_table[index]);
    hash_table[index] = newNode;
    word_vector.push_back(word); 

    // Check if the load factor exceeds 0.8, and resize if necessary.
    if(double(nodes)/table_size >= 0.8){
        resize();
    }

    return true;
}

// Function to load words from a file into the dictionary.
bool TwoWayDictionary::load(const std::string& filename) {
    std::ifstream file(filename);

    bool check = false; // Flag to indicate if any word was inserted.
    std::string word;
    int token = 0;

    // Read words from the file and insert them into the dictionary.
    while (file >> word) {
        if (insert(word)) {
            check = true;
            ++token;
        }
    }

    file.close(); // Good convention to close the file.

    return check; // Return true if at least one word was inserted.
}

// Function to get the token of a word.
int TwoWayDictionary::tok(const std::string& word) {
    unsigned hashValue = hash(word); // Get the hash value for the word.
    HashNode* current = hash_table[hashValue]; // Get the node at the hash index.
    // Traverse the linked list at the hash index to find the word.
    while (current != nullptr) {
        if (current->get_word() == word) {
            return current->get_token(); // Return the token if found.
        }
        current = current->get_next();
    }
    return -1; // Return -1 if word not found.
}

// Function to get the word associated with a token.
std::string TwoWayDictionary::ret(int token) {
    // Check if the token is valid.
    if (token <= 0 || token > word_vector.size()) {
        return "N/A";
    }
    return word_vector[token - 1]; // Return the word corresponding to the token.
}

// Function to resize the hash table when the load factor exceeds 0.8.
void TwoWayDictionary::resize(){
    int old_table_size = table_size; // Store the old table size.
    table_size *= 2; // Double the table size.
    HashNode** new_table = new HashNode*[table_size](); // Create a new hash table.

    // Rehash all the nodes into the new hash table.
    for (int i = 0; i < old_table_size; i++) {
        HashNode* current = hash_table[i];
        while (current != nullptr) {
            HashNode* next = current->get_next();
            unsigned new_index = hash(current->get_word());
            current->set_next(new_table[new_index]);
            new_table[new_index] = current;
            current = next;
        }
    }

    delete[] hash_table; // Delete the old hash table.
    hash_table = new_table; // Update the hash table pointer.
}

// Function to print words stored at a specific hash table index.
void TwoWayDictionary::print(int k) {
    if (k < 0 || k >= table_size) {
        return; // Return if the index is out of range.
    }
    
    std::string keys = "";
    HashNode* curr = hash_table[k]; // Get the node at the given index.
    if (curr == nullptr) return; // Return if no node exists at the index.
    // Concatenate all words stored at the index.
    while(curr != nullptr){
        keys = curr->get_word() + " " + keys;
        curr = curr->get_next();
    }
    std::cout << keys << std::endl; // Print the concatenated words.
}

// Function to compute the hash value for a word.
unsigned TwoWayDictionary::hash(const std::string & word) {
    unsigned ans = 0;
    // Compute the hash value using the polynomial rolling hash function.
    for(auto it = word.begin(); it != word.end(); ++it)
        ans = ans * 29 + *it;
    return ans % table_size; // Return the hash value modulo table size.
}

// Constructor for the HashNode class.
HashNode::HashNode() {
    next = nullptr;
}

// Destructor for the HashNode class.
HashNode::~HashNode() {

}

// Getter function for the next pointer.
HashNode* HashNode::get_next() {
    return next;
}

// Getter function for the token.
int HashNode::get_token() {
    return token;
}

// Getter function for the word.
std::string HashNode::get_word() {
    return word;
}

// Setter function for the next pointer.
void HashNode::set_next(HashNode* new_next) {
    next = new_next;
}

// Setter function for the token.
void HashNode::set_token(int new_token) {
    token = new_token;
}

// Setter function for the word.
void HashNode::set_word(const std::string& new_word) {
    word = new_word;
}
