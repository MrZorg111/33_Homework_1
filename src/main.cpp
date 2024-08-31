#include <iostream>
#include "market.h"



int main() {
    Market market;
    Basket basket;
    bool stop_load_market = false;
    std::string answer("I");
    //##########################################################---MARKET---##########################################################################
    
    while(!stop_load_market) {
        std::cout << "Dear store owner, how do you want to fill the warehouse with goods yourself, or entrust it to a commodity expert? (self/prof)" << std::endl;
        std::cin >> answer;

        if (answer == "self") {
            market.setHandleLoaderMarket();
            stop_load_market = true;
        }
        else if (answer == "prof") {
            market.AutoLoadingMarket();
            stop_load_market = true;
        }
        else {
            std::cout << "Input error! Repeat the input!" << std::endl;
            continue;
        }
    }
    
    std::cout << "The product presented in the store: " << std::endl;
    market.getMarket();

    //###########################################################---Basket---###########################################################################

    std::cout << "Welcome dear customer, what do you want? " << std::endl;
    user_input(market, basket);
<<<<<<< HEAD
    std::cout << "The products are selected: " << std::endl;
    basket.getBasket();
    remove_basket(market, basket);
=======
    remove_basket(market, basket);
    
>>>>>>> origin/main
    return 0;
}