#ifndef CPP_ALGORITHMS_NODE_H
#define CPP_ALGORITHMS_NODE_H

#include "Bid.h"

struct Node {
    Bid data;   // Bid data for current node
    Node* next; // Reference to next node

    // Default constructor for node data structure
    Node() {
        next = nullptr;
    }

    // Overloaded constructor that includes a Bid argument
    Node(Bid bid) {
        data = bid;
        next = nullptr;
    }
};

#endif //CPP_ALGORITHMS_NODE_H
