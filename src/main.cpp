#include <iostream>
#include "function.h"


int main() {
    Market market;
    Basket basket;
    market.getMarket();
    std::cout << "Greetings, dear customer, what do you want?" << std::endl;
    user_input(market, basket);
    market.getMarket();
    basket.getBasket();
   

    return 0;
}