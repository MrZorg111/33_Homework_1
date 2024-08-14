#pragma once
#include <iostream>
#include <fstream>
#include <map>
#include <nlohmann/json.hpp>
#include <string>
#include <exception>

bool stop_input() {
    std::string stop_word;
    std::cout << "To stop filling, enter ""stop""." << std::endl;
    std::cin >> stop_word;

    if (stop_word == "stop") {
        return false;
    } 
    else {
        return true;
    }
}

bool market_loading() {
    std::string answer;
    std::cout << " Enter yes/no: " << std::endl;
    std::cin >> answer;
    if (answer == "yes") {
        return true;
    }
    else {
         return false;
    }
}

class Market {
    std::map<std::string, int> data_base;
public:
    Market() {
        std::ifstream data_market;
    data_market.open("data_market.json");
    nlohmann::json dict;
    data_market >> dict;
    
    if(!dict.empty()) {
        data_base = dict;
    }
    else {
        std::cout << "Dict empty!" << std::endl;
    }
    }

    void setHandleLoaderMarket() {
        std::string articule;
        int volume;
        bool handle_input = true;
        std::cout << "Enter the article and the desired quantity of the product: " << std::endl;
        
        while(handle_input) { 
            std::cout << "Articule - ";
            std::cin >> articule;
            std::cout << "Volume - ";
            std::cin >> volume;

            data_base.insert(std::pair<std::string, int> (articule, volume));
            handle_input = stop_input();
        }
    }
    void getMarket() {
        std::cout << "Products in the store: " << std::endl;
        for(std::map<std::string, int> :: iterator it = data_base.begin(); it != data_base.end(); it++) {
            std::cout << "Articulate " << it->first << "\t" << " Volume " << it->second << std::endl;
        }
    }
    void setRemoveVolumeMarket(std::string basket_art, int basket_vol) {
        auto it = data_base.find(basket_art);
        data_base.insert(std::pair<std::string, int> (it->first, (it->second -= basket_vol)));
    }
};
class Basket {
    std::map<std::string, int> basket_buyer;
public:
    void getBasket() {
        if(!basket_buyer.empty()) {
            std::cout << "\n\nBasket-Buyer: " << std::endl;
            
            for(std::map<std::string, int> :: iterator it = basket_buyer.begin(); it != basket_buyer.end(); it++) {
                std::cout << "Articulate " << it->first << "\t" << " Volume " << it->second << std::endl;
            }
        }
        else{
            std::cout << "Basket-Buyer Empty! " << std::endl;
        }
    }

    void PutInBasket(std::string input_art, int input_vol) {
        basket_buyer.insert(std::pair<std::string, int> (input_art, input_vol));
    }
    
    void RemoveFromBasket(std::string _art, int _vol) {
        basket_buyer.find(_art)->second -= _vol;
            if(basket_buyer.find(_art) ->second == 0) {
                basket_buyer.erase(_art);
            }
    }
    
};

void user_input (Market& _market, Basket& _basket) {
    std::string articule("I");
    int volume(0);
    bool use_input = true;
    std::cout << "Enter the article and the desired quantity of the product: " << std::endl;
    
    while(use_input) {
        std::cout << "Articule - ";
        std::cin >> articule;
        std::cout << "Volume - ";
        std::cin >> volume;
        _basket.PutInBasket(articule, volume);
        _market.setRemoveVolumeMarket(articule, volume);
        use_input = stop_input();
    }
}