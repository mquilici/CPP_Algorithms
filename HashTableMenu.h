#ifndef CPP_ALGORITHMS_HASHTABLEMENU_H
#define CPP_ALGORITHMS_HASHTABLEMENU_H

#include <iostream>
#include "HashTable.h"
#include "CSVparser.h"
#include "Utilities.h"

/**
 * Load a CSV file containing bids into a container
 *
 * @param csvPath the path to the CSV file to load
 * @return a container holding all the bids read
 */
void loadBidsHT(std::string csvPath, HashTable* hashTable) {
    std::cout << "Loading CSV file " << csvPath << std::endl;

    // initialize the CSV Parser using the given path
    csv::Parser file = csv::Parser(csvPath);

    try {
        // loop to read rows of a CSV file
        for (unsigned int i = 0; i < file.rowCount(); i++) {

            // Create a data structure and add to the collection of bids
            Bid bid;
            bid.bidId = file[i][1];
            bid.title = file[i][0];
            bid.fund = file[i][8];

            std::string strAmount = file[i][4];
            strAmount.erase(remove(strAmount.begin(), strAmount.end(), '$'), strAmount.end());
            bid.amount = atof(strAmount.c_str());

            // push this bid to the end
            hashTable->Insert(bid);
        }
    } catch (csv::Error &e) {
        std::cerr << e.what() << std::endl;
    }
}

/**
 * The one and only main() method
 */
void hashTableMenu(std::string csvPath) {

    // Define a timer variable
    clock_t ticks;

    // Define a hash table to hold all the bids
    HashTable* bidTable;

    Bid bid;
    std::string bidKey;

    int choice = 0;
    while (choice != 9) {
        std::cout << "Hash Table Menu:" << std::endl;
        std::cout << "  1. Load Bids" << std::endl;
        std::cout << "  2. Display All Bids" << std::endl;
        std::cout << "  3. Find Bid" << std::endl;
        std::cout << "  4. Add a Bid" << std::endl;
        std::cout << "  5. Remove Bid" << std::endl;
        std::cout << "  9. Back" << std::endl;
        std::cout << "Enter choice: ";
        getInput(choice);

        switch (choice) {

            case 1:
                bidTable = new HashTable();
                ticks = clock(); // Initialize a timer variable before loading bids
                loadBidsHT(csvPath, bidTable);
                ticks = clock() - ticks; // current clock ticks minus starting clock ticks
                std::cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << std::endl;
                break;

            case 2:
                if (bidTable == NULL) {
                    std::cout << "No data loaded..." << std::endl;
                    break;
                }
                bidTable->PrintAll();
                break;

            case 3:
                if (bidTable == NULL) {
                    std::cout << "No data loaded..." << std::endl;
                    break;
                }

                std::cout << "Enter bid ID (0-178): ";
                std::cin >> bidKey;

                ticks = clock();
                bid = bidTable->Search(bidKey);
                ticks = clock() - ticks; // current clock ticks minus starting clock ticks
                if (!bid.bidId.empty()) {
                    bid.printBid();
                } else {
                    std::cout << "Bid Id " << bidKey << " not found." << std::endl;
                }
                std::cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << std::endl;
                break;

            case 4:
                bid = getBid();
                ticks = clock();
                bidTable->Insert(bid);
                ticks = clock() - ticks; // current clock ticks minus starting clock ticks
                bid.printBid();
                std::cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << std::endl;
                break;

            case 5:
                if (bidTable == NULL) {
                    std::cout << "No data loaded..." << std::endl;
                    break;
                }
                std::cout << "Enter bid ID (0-178): ";
                std::cin >> bidKey;
                ticks = clock();
                bidTable->Remove(bidKey);
                ticks = clock() - ticks; // current clock ticks minus starting clock ticks
                std::cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << std::endl;
                break;
        }
    }

    delete bidTable;
}

#endif //CPP_ALGORITHMS_HASHTABLEMENU_H
