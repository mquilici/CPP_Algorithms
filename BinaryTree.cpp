#include "BinaryTree.h"
#include "BNode.h"
#include "Bid.h"

/**
 * Default constructor
 */
BinarySearchTree::BinarySearchTree() {
    // initialize housekeeping variables
    root = nullptr;
}

/**
 * Destructor
 */
BinarySearchTree::~BinarySearchTree() {
    // recurse from root deleting every node
    this->destroy(root);
}

// Method to recursively delete nodes from the tree
void BinarySearchTree::destroy(BNode* node) {

    // Iterate while the tree is not empty
    if (node != nullptr) {

        // If the left node is not empty, recurse on left side
        if (node->left != nullptr)
            destroy(node->left);

        // If the right node is not empty, recurse on right side
        if (node->right != nullptr)
            destroy(node->right);

        // Delete node
        delete node;
    }
}

/**
 * Traverse the tree in order
 */
void BinarySearchTree::InOrder() {
    // Call inOrder method with root parameter to iteratively search tree
    this->inOrder(root);
}

/**
 * Insert a bid
 */
void BinarySearchTree::Insert(Bid bid) {
    // If the tree is empty create new root node
    if (root == nullptr) {
        root = new BNode(bid);
    } else {
        this->addBNode(root, bid); // Call method to add the new node
    }
}

/**
 * Remove a bid
 */
void BinarySearchTree::Remove(std::string bidId) {
    this->removeBNode(root, bidId);
}

/**
 * Search for a bid
 */
Bid BinarySearchTree::Search(std::string bidId) {
    BNode* cur = root; // Start search the current node at the root

    // Traverse down the tree comparing the bidId with left and right nodes
    // If bidId is less than the current node go left otherwise go right
    while (cur != nullptr) {
        if (bidId == cur->bid.bidId) {
            return cur->bid;
        } else if (bidId < cur->bid.bidId ) {
            cur = cur->left; // Move to left child
        } else {
            cur = cur->right; // Move to right child
        }
    }

    std::cout << "No bid found " << std::endl;
    Bid bid;
    return bid;
}

/**
 * Get size of tree
 */
int BinarySearchTree::Size() {
    // Call inOrder method with root parameter to iteratively search tree
    return this->size(root);
}

/**
 * Add a bid to some node (recursive)
 *
 * @param node Current node in tree
 * @param bid Bid to be added
 */
void BinarySearchTree::addBNode(BNode* node, Bid bid) {
    // If the bidId is less than the node add the node on the left
    if (bid.bidId < node->bid.bidId) {
        // When there is an empty location, add the node
        if (node->left == nullptr) {
            node->left = new BNode(bid);
        } else {
            this->addBNode(node->left,bid); // Recurse on left side
        }
        // If the bidId is greater than the node add the node on the right
    } else {
        // When there is an empty location, add the node
        if (node->right == nullptr) {
            node->right = new BNode(bid);
        } else {
            this->addBNode(node->right,bid); // Recurse on right side
        }
    }
}

void BinarySearchTree::inOrder(BNode* node) {
    // While the node is not empty, recursively search the tree
    // and print values using LEFT-NODE-RIGHT traversal
    if (node != nullptr) {
        inOrder(node->left);
        node->bid.printBid();
        inOrder(node->right);
    }
}

BNode* BinarySearchTree::removeBNode(BNode* node, std::string bidId) {

    // If the node is empty, return
    if (node == nullptr)
        return node;

    // If the value is less than the node, call Remove() on left side
    if (bidId < node->bid.bidId)
        node->left = removeBNode(node->left, bidId);

        // If the value is greater than the node, call Remove() on right side
    else if (bidId > node->bid.bidId)
        node->right = removeBNode(node->right, bidId);

        // If the value is equal to the node, remove the node
    else {
        // If the node has one child
        // Replace node with the right child
        if (node->left == nullptr) {
            BNode *temp = node->right;
            free(node);
            return temp;
            // Replace node with the left child
        } else if (node->right == nullptr) {
            BNode *temp = node->left;
            free(node);
            return temp;
        }

        // If the node has two children
        // Replace the node with the smallest in-order successor
        BNode* min = node;

        // Find the leftmost child
        while (min && min->left != nullptr)
            min = min->left;

        // Replace the node with the smallest in-order successor
        node->bid = min->bid;

        // Call removeBNode to delete the in-order successor
        node->right = removeBNode(node->right, min->bid.bidId);
    }
    return node;
}

int BinarySearchTree::size(BNode* node) {

    if (node == NULL) {
        return 0;
    }

    return 1 + size(node->left) + size(node->right);
}