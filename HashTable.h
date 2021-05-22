#ifndef CPP_ALGORITHMS_HASHTABLE_H
#define CPP_ALGORITHMS_HASHTABLE_H

#include <iostream>
#include <vector>
#include "Node.h"
#include "Bid.h"

class HashTable {

private:

    // Node data structure to implement linked list
    struct Node {
        unsigned key; // Stores key
        Bid data;     // Stores bid data
        Node* next;   // Pointer to next node

        // Default constructor
        Node() {
            key = UINT_MAX; // UINT_MAX indicates key is not yet assigned
            next = nullptr;
        };

        // Overloaded constructor with Bid parameter
        Node(Bid abid) : Node() {
            data = abid;
        }

        // Overloaded constructor with bid and key arguments
        Node(Bid abid, unsigned akey) : Node(abid) {
            key = akey;
        }
    };

    std::vector<Node> hashTable; // Hash table vector
    unsigned hash(int key); // Hash function

public:
    HashTable();
    virtual ~HashTable();
    void Insert(Bid bid);
    void PrintAll();
    void Remove(std::string bidId);
    Bid Search(std::string bidId);
};


#endif //CPP_ALGORITHMS_HASHTABLE_H
