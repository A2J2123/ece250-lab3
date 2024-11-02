#ifndef TOKENIZE_H
#define TOKENIZE_H

#include <string>
#include <vector>

// Forward declaration
class HashNode;

class TwoWayDictionary {
public:
    TwoWayDictionary(int new_size);
    ~TwoWayDictionary();

    bool insert(const std::string& word);
    bool load(const std::string& filename);
    int tok(const std::string& word);
    std::string ret(int token);
    void print(int k);
    
private:
    unsigned hash(const std::string & word);
    void resize(); 
    std::vector<std::string> word_vector;
    int table_size;
    int nodes;
    HashNode** hash_table;
};

class HashNode {
    public:
        HashNode();
        ~HashNode();
        
        HashNode* get_next();
        int get_token();
        std::string get_word();

        void set_next(HashNode* new_next);
        void set_token(int new_token);
        void set_word(const std::string& new_word);

    private:
        HashNode* next;
        int token;
        std::string word;
};

#endif // TOKENIZE_H