#include "LinkedList.h"

#include <algorithm>
#include <iostream>
#include "Bid.h"
#include "Node.h"

using namespace std;

/**
 * Default constructor
 */
LinkedList::LinkedList() {
    head = nullptr; // Initialize head to nullptr
    tail = nullptr; // Initialize tail to nullptr
    size = 0;       // Initialize size of list to 0
}

/**
 * Destructor
 */
LinkedList::~LinkedList() {
    Node *cur = head;
    Node *prev = nullptr;
    while (cur) {
        prev = cur;
        cur = cur->next;
        delete prev;
    }
}

/**
 * Append a new bid to the end of the list
 */
void LinkedList::Append(Bid bid) {
    Node* newNode = new Node(bid); // Pointer to a new node using bid argument

    // If the list is empty, assign the head to the new node
    // Otherwise set the tail to point to the new node
    if (head == nullptr) {
        head = newNode;       // Assign head to new node
        tail = newNode;       // Assign tail to new node
    } else {
        tail->next = newNode; // Move new node after tail
        tail = newNode;       // Assign tail to new node
    }
    size++;                   // Increment size by one
}

/**
 * Prepend a new bid to the start of the list
 */
void LinkedList::Prepend(Bid bid) {
    Node* newNode = new Node(bid); // Pointer to a new node using bid argument

    // If the list is empty assign the head and tail to the new node
    // Otherwise, move the head after the new node using the next pointer
    if (head == nullptr) {
        head = newNode;       // Assign head to new node
        tail = newNode;       // Assign tail to new node
    } else {
        newNode->next = head; // Move head after new node
        head = newNode;       // Assign head to new node
    }
    size ++;                  // Increment size by one
}

/**
 * Simple output of all bids in the list
 */
void LinkedList::PrintList() {
    Node* current = head; // Pointer to a new node using bid argument

    // If the list is empty, print an error
    if (head == nullptr) {
        cout << "The list is empty." << endl;
    }

    // Loop through nodes and print bid info until we reach the end (nullptr)
    while (current != nullptr) {
        current->data.printBid();
        current = current->next; // Set to the next node and repeat
    }
}

/**
 * Remove a specified bid
 *
 * @param bidId The bid id to remove from the list
 */
void LinkedList::Remove(string bidId) {
    // If the list is not empty, proceed
    if(head != nullptr) {

        bool headMatch = !head->data.bidId.compare(bidId); // true if head matches bidId

        // If the first node matches
        if (headMatch) {
            // If the list contains only the head node, remove the head and tail nodes
            if (head->next == nullptr) {
                head = nullptr; // Delete head
                tail = nullptr; // Delete tail
                size = 0;       // Assign size to zero
                return;
            }
                // If the list contains more than one node, remove only the head node
            else {
                Node* tempNode = head->next; // Save next node
                delete head;                 // Delete head node
                head = tempNode;             // Assign head node to saved node
                size--;                      // Decrement size by one
                return;
            }
        }

        Node* current = head; // Current node used to iterate through list

        // Loop over all of the nodes
        while (current->next != nullptr) {

            bool nextMatch = !current->next->data.bidId.compare(bidId); // True if next node matches

            // If the next node matches and is the last node, remove the next node
            if (current->next->next == nullptr && nextMatch) {
                current->next = nullptr; // Delete pointer to the next node
                tail = current;          // Assign tail to current node
                size--;                  // Decrement size by one
                return;
            }

            // If the next node matches and is not the last node, remove the next node
            if (current->next->next != nullptr && nextMatch) {
                Node* tempNode = current->next; // Save the next node
                current->next = tempNode->next; // Point current node to one after the saved node
                delete tempNode;                // Delete the saved node
                size--;                         // Decrement size by one
                return;
            }

            current = current->next; // Set to the next node and repeat
        }
    }
}

/**
 * Search for the specified bidId
 *
 * @param bidId The bid id to search for
 */
Bid LinkedList::Search(string bidId) {
    Node* current = head; // Pointer to a new node using bid argument

    // Loop over nodes until we the end (nullptr)
    // If bidId is found, return the matching bid
    while (current != nullptr) {
        if (current->data.bidId.compare(bidId) == 0) {
            return current->data;
        }
        current = current->next; // Set to the next node and repeat
    }

    // If no match is found, return an empty bid
    Bid nullBid;
    std::cout << "No bid found " << std::endl;
    return nullBid;
}

/**
 * Returns the current size (number of elements) in the list
 */
int LinkedList::Size() {
    return size;
}
