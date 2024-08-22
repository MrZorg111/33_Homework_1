#pragma once
#include <iostream>
#include <fstream>
#include <map>
#include <nlohmann/json.hpp>
#include <string>
#include <exception>

//########################################---MARKET---######################################################################

void check_load_market(std::string _articule, int _volume) {
    if(_articule.size() <= 0 || _articule.size() > 3 || _volume <= 0 || _volume > 999) {
        throw std::invalid_argument(_articule.size() <= 0 || _articule.size() > 3 ? "Articule" : "Volume");
    }
}

bool market_loading() {
    std::string answer;
    std::cout << "Enter yes/no: " << std::endl;
    std::cin >> answer;
    if (answer == "yes") {
        return true;
    }
    else {
         return false;
    }
}

bool stop_input() {
    std::string stop_word;
    std::cout << "To stop filling, enter ""stop"" or ""go""." << std::endl;
    std::cin >> stop_word;

    if (stop_word == "stop") {
        return true;
    } 
    else {
        return false;
    }
}

class Market {
    std::map<std::string, int> data_base;
public:
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
        bool handle_input = true;
        std::cout << "Enter the article and the desired quantity of the product: " << std::endl;
        
        while(handle_input) { 
            try {    
                std::cout << "Articule - ";
                std::cin >> articule;
                std::cout << "Volume - ";
                std::cin >> volume;
                check_load_market(articule, volume);
                
                data_base.insert(std::pair<std::string, int> (articule, volume));
                handle_input = stop_input();
            }
            catch(std::invalid_argument(check_load_market)) {
                std::cerr << "Invalid argument: " << check_load_market.what() << std::endl;
                std::cout << "Enter the data again, be careful when entering!" << std::endl;
                continue;
            }
        }
    }
    void getMarket() {
        std::cout << "Products in the store: " << std::endl;
        for(std::map<std::string, int> :: iterator it = data_base.begin(); it != data_base.end(); it++) {
            std::cout << "\tArticulate - " << it->first << "\t" << " Volume - " << it->second << std::endl;
        }
    }
    void setRemoveVolumeMarket(std::string basket_art, int basket_vol) {
        auto it = data_base.find(basket_art);
        data_base.insert(std::pair<std::string, int> (it->first, (it->second -= basket_vol)));
    }
    void check_market_key(std::string _key) {
        if(!data_base.count(_key) || _key.size() != 3) {
            throw std::invalid_argument("Articule");
        }
    }
};



//########################################---BASKET---######################################################################

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

void user_input (Market _market, Basket _basket) {
    std::string articule("I");
    int volume(0);
    
    do {
        try{
            std::cout << "Articule - ";
            std::cin >> articule;
            _market.check_market_key(articule);
            std::cout << "Volume - ";
            std::cin >> volume;
            _basket.PutInBasket(articule, volume);
            _market.setRemoveVolumeMarket(articule, volume);
        }
        catch (std::invalid_argument(check_market_key)){
            std::cerr << "Invalid argument: Articul" << std::endl;
            std::cout << "This product is not available in the store, enter the request again!" << std::endl;
            continue;
        }
    } while(!stop_input());
}