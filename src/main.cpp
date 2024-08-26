#include <iostream>
#include "market.h"



int main() {
    Market market;
    Basket basket;
    std::cout << "Will you fill the store's warehouse yourself, or will you entrust it to professionals? " << std::endl;
    if (market_loading()) {
        market.setHandleLoaderMarket();
    }
    else {
       market.AutoLoadingMarket();
    }
    
    std::cout << "These products are in the store's warehouse: " << std::endl;
    market.getMarket();

    std::cout << "Enter the article and the desired quantity of the product: " << std::endl;
    user_input(market, basket);
    remove_basket(market, basket);

    market.getMarket();
    basket.getBasket();
    return 0;
}