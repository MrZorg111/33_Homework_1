#pragma once
#include <iostream>
#include <fstream>
#include <map>
#include <nlohmann/json.hpp>
#include <string>
#include <exception>

//########################################---MARKET---######################################################################
//Checking the correctness of the entry of the article and the quantity of the product
void check_load_market(std::string _articule, int _volume) {
    if(_articule.size() <= 0 || _articule.size() > 3 || _volume <= 0 || _volume > 999) {
        throw std::invalid_argument(_articule.size() <= 0 || _articule.size() > 3 ? "Articule" : "Volume");
    }
}
//Safe word 
bool stop_input() {
    for(;;) {
        std::string stop_word;
        std::cout << "To stop filling, enter (""stop""/""go"")." << std::endl;
        std::cin >> stop_word;

        if (stop_word == "go") {
            return false;
        } 
        else if (stop_word == "stop") {
            return true;
        }
        else {
            std::cout << "Input error! Repeat the input!" << std::endl;
            continue;
        }
    }
}
//Choosing the type of store filling
bool market_loading() {
    std::string answer;
    std::cout << "yes/no" << std::endl;
    std::cin >> answer;
    if (answer == "yes") {
        return true;
    }
    else {
        return false;
    }
}
//Shop
class Market {
    std::map<std::string, int> data_base;
public:
    //Filling the store with goods (Auto/manual)
    void AutoLoadingMarket() {
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
        std::cout << "Enter the article and the desired quantity of the product: " << std::endl;
        
        do { 
            try {    
                std::cout << "Articule - ";
                std::cin >> articule;
                std::cout << "Volume - ";
                std::cin >> volume;
                check_load_market(articule, volume);
                
                data_base.insert(std::pair<std::string, int> (articule, volume));
            }
            catch(std::invalid_argument(check_load_market)) {
                std::cerr << "Invalid argument: " << check_load_market.what() << std::endl;
                std::cout << "Enter the data again, be careful when entering!" << std::endl;
                continue;
            }
        }while(!stop_input());
    }
    //Product demonstration
    void getMarket() {
        for(std::map<std::string, int> :: iterator it = data_base.begin(); it != data_base.end(); it++) {
            std::cout << "\tArticulate - " << it->first << "\t" << " Volume - " << it->second << std::endl;
        }
    }
    //Sale
    void setRemoveVolumeMarket(std::string basket_art, int basket_vol) {
        auto it = data_base.find(basket_art);
        data_base.insert(std::pair<std::string, int> (it->first, (it->second -= basket_vol)));
    }
    //Refund
    void setReturnProduct(std::string _art, int _vol) {
        data_base.insert(std::pair<std::string, int> (_art, _vol));
    }
    //Checking the availability of the product and matching its quantity when selling
    void check_market(std::string _key, int _volume) {
        if(!data_base.count(_key) || _key.size() != 3) {
            throw std::invalid_argument("Articule");
        }
        else if ((data_base.find(_key)->second - _volume) < 0) {
            throw std::invalid_argument("Volume");
        }
    }
};



//########################################---BASKET---######################################################################

//Basket
class Basket {
    std::map<std::string, int> basket_buyer;
public:
    //Product demonstration in the shopping cart
    void getBasket() {
        if(!basket_buyer.empty()) {
            std::cout << "Basket-buyer! To be paid:" << std::endl;
            
            for(std::map<std::string, int> :: iterator it = basket_buyer.begin(); it != basket_buyer.end(); it++) {
                std::cout << "\tArticulate " << it->first << "\t" << " Volume " << it->second << std::endl;
            }
        }
        else{
            std::cout << "Basket-Buyer Empty! " << std::endl;
        }
    }
    //Purchase of goods
    void PutInBasket(std::string input_art, int input_vol) {
        basket_buyer.insert(std::pair<std::string, int> (input_art, input_vol));
    }
    //Return of the product
    void RemoveFromBasket(std::string _art, int _vol) {
        if(!basket_buyer.count(_art) || basket_buyer.find(_art)->second < _vol) {
            throw std::invalid_argument(!basket_buyer.count(_art) ? "Articule" : "Volume");
        }
        else {
            basket_buyer.find(_art)->second -= _vol;
                if(basket_buyer.find(_art) ->second == 0) {
                    basket_buyer.erase(_art);
                }
        }
    }
};
//Return of the product to the shelf
void remove_basket(Market& _market, Basket& _basket) {
    int volume(0);
    std::string articule("I"), answer("I");
    std::cout << "Would you like to put something out of the basket and put it back on the shelf? yes/no" << std::endl;
    std::cin >> answer;

    if(answer == "yes") {
        std::cout << "Enter the article and quantity of the product. " << std::endl;
        do {
            std::cout << "Articule - ";
            std::cin >> articule;
            std::cout << "Volume - ";
            std::cin >> volume;
            try {
                _basket.RemoveFromBasket(articule, volume);
                _market.setReturnProduct(articule, volume);
            }
            catch (std::invalid_argument(RemoveFromBasket)) {
                std::cerr << "Invalid argument " << RemoveFromBasket.what() << std::endl;
                std::cout << "Input error, enter this again, be careful!" << std::endl;
            }
        }while(!stop_input());
        _basket.getBasket();
    }
    else {
        _basket.getBasket();
    }
}
//Choosing an item to buy
void user_input (Market& _market, Basket& _basket) {
    std::string articule("I");
    int volume(0);
    
    do {
        try{
            std::cout << "Articule - ";
            std::cin >> articule;
            std::cout << "Volume - ";
            std::cin >> volume;
            _market.check_market(articule, volume);

            _basket.PutInBasket(articule, volume);
            _market.setRemoveVolumeMarket(articule, volume);
        }
        catch (std::invalid_argument(check_market)){
            std::cerr << "Invalid argument: " << check_market.what() << std::endl;
            std::cout << "Input error, enter this again, be careful!" << std::endl;
            continue;
        }
    } while(!stop_input());
}