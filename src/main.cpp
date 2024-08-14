#include <iostream>
#include "function.h"


int main() {
    Market market;
    Basket basket;
    std::cout << "Will you fill the store's warehouse yourself, or will you entrust it to professionals? " << std::endl;
    if (market_loading()) {
        market.setHandleLoaderMarket();
    }
    else {
    market.getMarket();
    std::cout << "Greetings, dear customer, what do you want?" << std::endl;
    user_input(market, basket);
    market.getMarket();
    basket.getBasket();
    }

    return 0;
}