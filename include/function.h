#pragma once
#include <iostream>
#include <fstream>
#include <map>
#include <nlohmann/json.hpp>
#include <string>
#include <exception>

class UncorrectInputVolume: public std::exception {
    const char* what() const noexcept override {
        std::cout << "Error! Uncorrect volume!" << std::endl;
    }
};
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
    
    bool CheckArticuleInBasket(std::string _art) {
        return basket_buyer.count(_art);
    }

    bool CheckVolumeinBasket(std::string _art, int _vol) {
        if (basket_buyer.find(_art)->second >= _vol) {
            return true;
        }
        else {
             return false;
        }
    }
    
    void PutInBasket(std::string input_art, int input_vol) {
        basket_buyer.insert(std::pair<std::string, int> (input_art, input_vol));
    }
    
    void RemoveFromBasket(std::string _art, int _vol) {
        if (CheckVolumeinBasket(_art, _vol)) {
            basket_buyer.find(_art)->second -= _vol;
            if(basket_buyer.find(_art) ->second == 0) {
                basket_buyer.erase(_art);
            }
        }
        else {
            throw UncorrectInputVolume();
        }
    }
    
};

void user_input (Market& _market, Basket& _basket) {
    std::string articule("I");
    int volume(0);
    bool use_input = true;
    std::cout << "Enter the article and the desired quantity of the product: " << std::endl;
    
    while(use_input) {
        std::cin >> articule >> volume;
        _basket.PutInBasket(articule, volume);
        _market.setRemoveVolumeMarket(articule, volume);
    }
}