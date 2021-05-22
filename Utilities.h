#ifndef CPP_ALGORITHMS_UTILITIES_H
#define CPP_ALGORITHMS_UTILITIES_H

#include <iostream>
#include "Bid.h"

bool getInput(int &input){
    int choice;
    std::cin >> input;
    if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return false;
    }
    return true;
}

Bid getBid() {

    Bid bid;

    std::cout << "Enter Id: ";
    std::cin.ignore();
    std::string bidId;
    getline(std::cin, bidId);
    bid.bidId = bidId;

    std::cout << "Enter title: ";
    std::string title;
    getline(std::cin, title);
    bid.title = title;

    std::cout << "Enter fund: ";
    std::string fund;
    std::cin >> fund;
    bid.fund = fund;

    std::cout << "Enter amount: ";
    std::cin.ignore();
    std::string strAmount;
    getline(std::cin, strAmount);
    strAmount.erase(remove(strAmount.begin(), strAmount.end(), '$'), strAmount.end());
    bid.amount = atof(strAmount.c_str());

    return bid;
}

#endif //CPP_ALGORITHMS_UTILITIES_H
