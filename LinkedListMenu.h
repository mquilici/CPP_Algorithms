#ifndef CPP_ALGORITHMS_LINKEDLISTMENU_H
#define CPP_ALGORITHMS_LINKEDLISTMENU_H

#include <iostream>
#include "LinkedList.h"
#include "CSVparser.h"
#include "Utilities.h"

/**
 * Load a CSV file containing bids into a LinkedList
 *
 * @return a LinkedList containing all the bids read
 */
void loadBidsLL(std::string csvPath, LinkedList *list) {
    std::cout << "Loading CSV file " << csvPath << std::endl;

    // initialize the CSV Parser
    csv::Parser file = csv::Parser(csvPath);

    try {
        // loop to read rows of a CSV file
        for (int i = 0; i < file.rowCount(); i++) {

            // initialize a bid using data from current row (i)
            Bid bid;
            bid.bidId = file[i][1];
            bid.title = file[i][0];
            bid.fund = file[i][8];

            std::string strAmount = file[i][4];
            strAmount.erase(remove(strAmount.begin(), strAmount.end(), '$'), strAmount.end());
            bid.amount = atof(strAmount.c_str());

            // add this bid to the end
            list->Append(bid);
        }
    } catch (csv::Error &e) {
        std::cerr << e.what() << std::endl;
    }
}

/**
 * The one and only main() method
 *
 * @param arg[1] path to CSV file to load from (optional)
 * @param arg[2] the bid Id to use when searching the list (optional)
 */
void linkedListMenu(const std::string &csvPath) {

    // Define a timer variable
    clock_t ticks;

    // Define a linked list to hold all the bids
    LinkedList bidList;

    Bid bid;
    std::string bidKey;

    int choice = 0;
    while (choice != 9) {
        std::cout << "Linked List Menu:" << std::endl;
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
                ticks = clock();
                loadBidsLL(csvPath, &bidList);
                ticks = clock() - ticks;
                std::cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << std::endl;
                std::cout << bidList.Size() << " bids read" << std::endl;
                break;

            case 2:
                if (bidList.Size() == 0) {
                    std::cout << "No data loaded..." << std::endl;
                    break;
                }
                bidList.PrintList();
                break;

            case 3:
                if (bidList.Size() == 0) {
                    std::cout << "No data loaded..." << std::endl;
                    break;
                }
                std::cout << "Enter bid ID (0-178): ";
                std::cin >> bidKey;
                ticks = clock();
                bid = bidList.Search(bidKey);
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
                bidList.Append(bid);
                ticks = clock() - ticks; // current clock ticks minus starting clock ticks
                bid.printBid();
                std::cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << std::endl;
                break;

            case 5:
                if (bidList.Size() == 0) {
                    std::cout << "No data loaded..." << std::endl;
                    break;
                }
                std::cout << "Enter bid ID (0-178): ";
                std::cin >> bidKey;
                ticks = clock();
                bidList.Remove(bidKey);
                ticks = clock() - ticks; // current clock ticks minus starting clock ticks
                std::cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << std::endl;
                break;
        }
    }
}

#endif //CPP_ALGORITHMS_LINKEDLISTMENU_H
