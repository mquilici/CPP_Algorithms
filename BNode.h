#ifndef CPP_ALGORITHMS_BNODE_H
#define CPP_ALGORITHMS_BNODE_H

#include "Bid.h"

struct BNode {
    BNode* left;  // Left child node pointer
    BNode* right; // Right child node pointer
    Bid bid;      // Bid at node

    // Default constructor
    BNode() {
        left = nullptr;
        right = nullptr;
        bid = Bid();
    }

    // Overloaded default constructor - takes bid
    BNode(Bid abid) : BNode() {
        bid = abid;
    }
};

#endif //CPP_ALGORITHMS_BNODE_H
