#include <iostream>
#include "HashTableMenu.h"
#include "LinkedListMenu.h"
#include "BinaryTreeMenu.h"
using namespace std;

const string csvPath = "bid_data.csv";

int main() {

    int choice = 0;
    while (choice != 9) {
        cout << "Select Data Structure:" << endl;
        cout << "  1. Hash Table" << endl;
        cout << "  2. Linked List" << endl;
        cout << "  3. Binary Tree" << endl;
        cout << "  9. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

        switch (choice) {
            case 1:
                hashTableMenu(csvPath);
                break;
            case 2:
                linkedListMenu(csvPath);
                break;
            case 3:
                binaryTreeMenu(csvPath);
                break;
        }
    }

    cout << "Exiting...";

    return 0;
}