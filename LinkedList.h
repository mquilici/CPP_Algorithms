#ifndef CPP_ALGORITHMS_LINKEDLIST_H
#define CPP_ALGORITHMS_LINKEDLIST_H

#include <iostream>
#include "Node.h"
#include "Bid.h"

class LinkedList {

private:
    Node* head; // Pointer to head node of linked list
    Node* tail; // Pointer to tail node of linked list
    int size;   // Size of linked list

public:
    LinkedList();
    virtual ~LinkedList();
    void Append(Bid bid);
    void Prepend(Bid bid);
    void PrintList();
    void Remove(std::string bidId);
    Bid Search(std::string bidId);
    int Size();
};

#endif //CPP_ALGORITHMS_LINKEDLIST_H