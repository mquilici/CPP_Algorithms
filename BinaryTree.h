#ifndef CPP_ALGORITHMS_BINARYTREE_H
#define CPP_ALGORITHMS_BINARYTREE_H

#include <iostream>
#include "BNode.h"
#include "Bid.h"

// Binary Search Tree class
/**
 * Define a class containing data members and methods to
 * implement a binary search tree
 */
class BinarySearchTree {
private:
    BNode* root;
    void addBNode(BNode* node, Bid bid);
    void inOrder(BNode* node);
    int size(BNode* node);
    BNode* removeBNode(BNode* node, std::string bidId);
    void destroy(BNode* node); // Method to recursively delete tree

public:
    BinarySearchTree();
    virtual ~BinarySearchTree();
    void InOrder();
    int Size();
    void Insert(Bid bid);
    void Remove(std::string bidId);
    Bid Search(std::string bidId);
};

#endif //CPP_ALGORITHMS_BINARYTREE_H
