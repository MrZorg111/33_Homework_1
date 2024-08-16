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
       market.AutoLoadingMarket();
    }
    
    std::cout << "These products are in the store's warehouse: " << std::endl;
    market.getMarket();

    std::cout << "\n\n\nTo select the desired product, enter its article and quantity!" << std::endl;
    std::string input_articule;
    int input_volume;
    bool stop_buy(true);

    while (stop_buy){
        try {
            std::cout << "Articule - ";
            std::cin >> input_articule;
            std::cout << "Volume - ";
            std::cin >> input_volume;
            //check_user_input(input_articule, input_volume);
        }
        catch(std::invalid_argument& x) {
            std::cerr << "Invalid argument " << x.what() << std::endl;
        }

    }
    


    return 0;
}