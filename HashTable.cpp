#include "HashTable.h"
#include <climits>
#include <iostream>

const unsigned int DEFAULT_SIZE = 179;

/**
 * Default constructor
 */
HashTable::HashTable() {
    hashTable.resize(DEFAULT_SIZE); // Resize hash table to global DEFAULT_SIZE
}

/**
 * Destructor
 */
HashTable::~HashTable() {
    hashTable.erase(hashTable.begin()); // Erase hash table vector
}

/**
 * Calculate the hash value of a given key.
 * Note that key is specifically defined as
 * unsigned int to prevent undefined results
 * of a negative list index.
 *
 * @param key The key to hash
 * @return The calculated hash
 */
unsigned int HashTable::hash(int key) {
    return key % DEFAULT_SIZE;
}

/**
 * Insert a bid
 *
 * @param bid The bid to insert
 */
void HashTable::Insert(Bid bid) {
    unsigned key = hash(stoi(bid.bidId)); // Hash table key
    Node* oldNode = &(hashTable.at(key)); // Node in linked list at key

    // If the node at the key does not exist
    // Create a now node with the bid and key
    // Insert new node into
    if (oldNode == nullptr) {
        Node* newNode = new Node(bid,key);
        hashTable.insert(hashTable.begin() + key, (*newNode));

        // If the fist node at the key is empty
        // Update key, data and next pointer
    } else if (oldNode->key == UINT_MAX) {
        oldNode->key = key;
        oldNode->data = bid;
        oldNode->next = nullptr;

        // If the fist node at the key is not empty
        // Insert new node at end of linked list
    } else {

        // Go to end of linked list
        while (oldNode->next != nullptr) {
            oldNode = oldNode->next;
        }

        // Insert new node at end of linked list
        oldNode->next = new Node(bid,key);
    }
}

/**
 * Print all bids
 */
void HashTable::PrintAll() {
    // Loop through all elements in hash table
    for (int i=0; i<DEFAULT_SIZE; ++i) {

        // Node in hash table at key i
        Node* node = &(hashTable.at(i));

        // Loop all nodes in linked list
        while(node != nullptr && node->key!=UINT_MAX) {

            // Print bid info at node i
            node->data.printBid();

            // Move to next node
            node = node->next;
        }
    }
}

/**
 * Remove a bid
 *
 * @param bidId The bid id to search for
 */
void HashTable::Remove(std::string bidId) {
    unsigned key = hash(stoi(bidId));
    Node* node = &(hashTable.at(key));

    // If the first node matches
    if (node != nullptr && node->key != UINT_MAX && node->data.bidId == bidId) {

        // If the list contains only the head node, remove the first node
        if (node->next == nullptr) {
            Bid emptyBid;
            node->key = UINT_MAX;
            node->next = nullptr;
            node->data = emptyBid;
            return;

        // If the list contains more than one node, remove the first node
        } else {
            hashTable.at(key) = *(node->next);
            return;
        }
    }

    Node* current = node; // Current node used to move through linked list

    // Loop over all of the nodes
    while (current->next != nullptr) {

        // If the next node matches and is the last node, remove the next node
        if (current->next->next == nullptr && current->next->data.bidId == bidId) {
            current->next = nullptr; // Delete pointer to the next node
            return;
        }

        // If the next node matches and is not the last node, remove the next node
        if (current->next->next != nullptr && current->next->data.bidId == bidId) {
            Node* tempNode = current->next; // Save the next node
            current->next = tempNode->next; // Point current node to one after the saved node
            delete tempNode;                // Delete the saved node
            return;
        }

        current = current->next; // Set to the next node and repeat
    }

    // Bid ID not found in list
    std::cout << "Bid ID " + bidId + " not found." << std::endl;

}

/**
 * Search for the specified bidId
 *
 * @param bidId The bid id to search for
 */
Bid HashTable::Search(std::string bidId) {
    Bid bid;

    unsigned key = hash(stoi(bidId));  // hash key
    Node* node = &(hashTable.at(key)); // node in hash table at key

    // If the node at the key is empty, return an empty bid
    if (node == nullptr || node->key == UINT_MAX) {
        return bid;
    }

    // If the node at the key matches the bid ID return matching bid
    if (node->data.bidId == bidId) {
        return node->data;
    }

    // Loop though linked list
    while(node != nullptr) {

        // If the bid ID is in the linked list, return matching bid
        if (node->key != UINT_MAX && node->data.bidId == bidId) {
            return node->data;
        }

        // Move to next node in linked list
        node = node->next;
    }

    std::cout << "No bid found " << std::endl;
    return bid;
}