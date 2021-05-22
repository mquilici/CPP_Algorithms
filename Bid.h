#ifndef CPP_ALGORITHMS_BID_H
#define CPP_ALGORITHMS_BID_H

#include <iostream>

// define a structure to hold bid information
struct Bid {
    std::string bidId; // unique identifier
    std::string title;
    std::string fund;
    double amount;
    Bid();
    Bid(std::string,std::string,std::string,double);
    void printBid();
};

#endif //CPP_ALGORITHMS_BID_H
