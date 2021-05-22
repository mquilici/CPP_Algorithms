//
// Created by quilici on 5/22/21.
//

#ifndef CPP_ALGORITHMS_VECTORMENU_H
#define CPP_ALGORITHMS_VECTORMENU_H

#include <iostream>
#include <vector>

/**
 * Load a CSV file containing bids into a container
 *
 * @param csvPath the path to the CSV file to load
 * @return a container holding all the bids read
 */
std::vector<Bid> loadBidsVC(std::string csvPath) {
    std::cout << "Loading CSV file " << csvPath << std::endl;

    // Define a vector data structure to hold a collection of bids.
    std::vector<Bid> bids;

    // initialize the CSV Parser using the given path
    csv::Parser file = csv::Parser(csvPath);

    try {
        // loop to read rows of a CSV file
        for (int i = 0; i < file.rowCount(); i++) {

            // Create a data structure and add to the collection of bids
            Bid bid;
            bid.bidId = file[i][1];
            bid.title = file[i][0];
            bid.fund = file[i][8];
            std::string strAmount = file[i][4];
            strAmount.erase(remove(strAmount.begin(), strAmount.end(), '$'), strAmount.end());
            bid.amount = atof(strAmount.c_str());

            //std::cout << "Item: " << bid.title << ", Fund: " << bid.fund << ", Amount: " << bid.amount << std::endl;

            // push this bid to the end
            bids.push_back(bid);
        }
    } catch (csv::Error &e) {
        std::cerr << e.what() << std::endl;
    }
    return bids;
}

/**
 * Partition the vector of bids into two parts, low and high
 *
 * @param bids Address of the vector<Bid> instance to be partitioned
 * @param begin Beginning index to partition
 * @param end Ending index to partition
 */
int partition(std::vector<Bid>& bids, int begin, int end) {
    int l = begin; // Starting index in partition
    int h = end;   // Ending index in partition

    // Pick midpoint as pivot
    //int p = (l + h)/2;

    // Pick random element as pivot (this can be faster)
    int p = l + rand() % (h-l);

    // Store pivot value (bid title)
    // Note: Use pivot value not index because array changes within loop
    std::string pivot = bids[p].title;

    while (l <= h) {

        // Increment low index l while low value < pivot
        // Note: Must use < not <= or l overshoot pivot when incremented
        while (bids[l].title < pivot) {
            ++l;
        }

        // Decrement high index h while high value > pivot
        // Note: Must use > not >= or h will drop below pivot when decremented
        while (bids[h].title > pivot) {
            --h;
        }

        // Swap bids[l] and bids[h], update l and h
        // Note: Must use <= not < because l = h will occur above
        if (l <= h) {
            Bid temp = bids[l];
            bids[l] = bids[h];
            bids[h] = temp;
            ++l;
            --h;
        }
    }

    // return low index as partition index
    return l;
}

/**
 * Perform a quick sort on bid title
 * Average performance: O(n log(n))
 * Worst case performance O(n^2))
 *
 * @param bids address of the vector<Bid> instance to be sorted
 * @param begin the beginning index to sort on
 * @param end the ending index to sort on
 */
void quickSort(std::vector<Bid>& bids, int begin, int end) {

    // Only sort when the low index is less than the high index
    if (begin < end) {
        int part = partition(bids, begin, end);	// Use the partition() method to get the pivot index
        quickSort(bids, begin, part - 1);       // Recursive call to sort the lower portion
        quickSort(bids, part, end);             // Recursive call to sort the upper portion
    }
    return;
}

/**
 * Perform a selection sort on bid title
 * Average performance: O(n^2))
 * Worst case performance O(n^2))
 *
 * @param bid address of the vector<Bid>
 *            instance to be sorted
 */
void selectionSort(std::vector<Bid>& bids) {

    // Loop through each element
    for (int i=0; i<bids.size()-1; ++i) {
        int smallestIndex = i;   // Temporary variable for swap

        // Find index of smallest remaining element
        for (int j=i+1; j<bids.size(); ++j) {
            if (bids[j].title < bids[smallestIndex].title) {
                smallestIndex = j;
            }
        }

        // Swap bids[i] and bids[indexSmallest]
        Bid temp = bids[i];
        bids[i] = bids[smallestIndex];
        bids[smallestIndex] = temp;
    }
    return;
}

/**
 * The one and only main() method
 */
void vectorMenu(const std::string &csvPath) {

    // Define a vector to hold all the bids
    std::vector<Bid> bids;

    // Define a timer variable
    clock_t ticks;

    Bid bid;
    std::string bidKey;
    bool flag = false;

    int choice = 0;
    while (choice != 9) {
        std::cout << "Menu:" << std::endl;
        std::cout << "  1. Load Bids" << std::endl;
        std::cout << "  2. Display All Bids" << std::endl;
        std::cout << "  3. Find Bid" << std::endl;
        std::cout << "  4. Add a Bid" << std::endl;
        std::cout << "  5. Remove Bid" << std::endl;
        std::cout << "  6. Selection Sort All Bids" << std::endl;
        std::cout << "  7. Quick Sort All Bids" << std::endl;
        std::cout << "  9. Exit" << std::endl;
        std::cout << "Enter choice: ";
        getInput(choice);

        switch (choice) {

            case 1:
                ticks = clock();
                bids = loadBidsVC(csvPath);
                std::cout << bids.size() << " bids read" << std::endl;
                ticks = clock() - ticks; // current clock ticks minus starting clock ticks
                std::cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << std::endl;
                break;

            case 2:
                if (bids.size() == 0) {
                    std::cout << "No data loaded..." << std::endl;
                    break;
                }
                for (int i = 0; i < bids.size(); ++i) {
                    bids[i].printBid();
                }
                std::cout << std::endl;
                break;

            case 3:
                if (bids.size() == 0) {
                    std::cout << "No data loaded..." << std::endl;
                    break;
                }
                std::cout << "Enter bid ID (0-178): ";
                std::cin >> bidKey;
                flag = false;
                for (int i=0 ;i<bids.size(); i++) {
                    if (bids[i].bidId.compare(bidKey) == 0) {
                        bids[i].printBid();
                        flag = true;
                        break;
                    }
                }
                if (!flag) std::cout << "Bid Id " << bidKey << " not found." << std::endl;
                break;

            case 4:
                bid = getBid();
                bids.push_back(bid);

            case 5:
                if (bids.size() == 0) {
                    std::cout << "No data loaded..." << std::endl;
                    break;
                }
                //Remove
                std::cout << "Enter bid ID (0-178): ";
                std::cin >> bidKey;
                flag = false;
                for (int i=0 ;i<bids.size(); i++) {
                    if (bids[i].bidId.compare(bidKey) == 0) {
                        bids.erase (bids.begin()+i);
                        flag = true;
                        break;
                    }
                }
                if (!flag) std::cout << "Bid Id " << bidKey << " not found." << std::endl;
                break;

            case 6:
                if (bids.size() == 0) {
                    std::cout << "No data loaded..." << std::endl;
                    break;
                }
                ticks = clock();
                selectionSort(bids);
                ticks = clock() - ticks; // current clock ticks minus starting clock ticks
                std::cout << bids.size() << " bids sorted" << std::endl;
                std::cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << std::endl;
                break;

            case 7:
                if (bids.size() == 0) {
                    std::cout << "No data loaded..." << std::endl;
                    break;
                }
                ticks = clock(); // Initialize a timer variable before loading bids
                quickSort(bids,0,bids.size()); // Use quicksort to sort bids
                ticks = clock() - ticks; // Time elapsed since quickSort was called
                std::cout << bids.size() << " bids sorted" << std::endl; // Display size of array
                std::cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << std::endl; // Display time elapsed
                break;
        }
    }
}

#endif //CPP_ALGORITHMS_VECTORMENU_H
