#include "Bid.h"

Bid::Bid() {
    amount = 0.0;
}

Bid::Bid(std::string bidId,std::string title,std::string fund,double amount) {
    this->bidId = bidId;
    this->title = title;
    this->fund = fund;
    this->amount = amount;
}

void Bid::printBid() {
    std::cout << bidId << ": " << title << " | " << amount << " | " << fund << std::endl;
}