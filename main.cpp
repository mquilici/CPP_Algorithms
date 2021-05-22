#include <iostream>
#include "HashTableMenu.h"
#include "LinkedListMenu.h"
#include "BinaryTreeMenu.h"
#include "VectorMenu.h"
using namespace std;

const string csvPath = "bid_data.csv";

int main() {

    int choice = 0;
    while (choice != 9) {
        cout << "Select Data Structure:" << endl;
        cout << "  1. Vector" << endl;
        cout << "  2. Hash Table" << endl;
        cout << "  3. Linked List" << endl;
        cout << "  4. Binary Tree" << endl;
        cout << "  9. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

        switch (choice) {
            case 1:
                vectorMenu(csvPath);
                break;
            case 2:
                hashTableMenu(csvPath);
                break;
            case 3:
                linkedListMenu(csvPath);
                break;
            case 4:
                binaryTreeMenu(csvPath);
                break;
        }
    }

    cout << "Exiting...";

    return 0;
}