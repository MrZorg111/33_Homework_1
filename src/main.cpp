#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>
#include <map>
#include <string>

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

    void getMap() {
        std::cout << "Products in the store: " << std::endl;
        for(std::map<std::string, int> :: iterator it = data_base.begin(); it != data_base.end(); it++) {
            std::cout << "Articulate " << it->first << "\t" << " Volume " << it->second << std::endl;
        }
    }
    void setRemoveVolumeMarket(std::string basket_art, int basket_vol) {
        data_base.find(basket_art)->second -= basket_vol;
    }
};

class Basket {
    std::map<std::string, int> basket_buyer;
public:
    void putInBasket(std::string input_art, int input_vol) {
        basket_buyer.insert(std::pair<std::string, int> (input_art, input_vol));
    }

    void takeFromBasket();

};

void user_input (Market _market, Basket _basket) {
    std::string articule("I");
    int volume(0);
    std::cout << "������� ������� � �������� ���������� ������: " << std::endl;
    std::cin >> articule >> volume;
    _basket.putInBasket(articule, volume);
    _market.setRemoveVolumeMarket(articule, volume);
}

int main() {
    Market market;
    Basket basket;
    market.getMap();
    std::cout << "������������ ���, ������� ����������, ���� �������?" << std::endl;
    user_input(mar);
    market.getMap();
   


}
/*
��� ����� �������

���������� ������� � ���������� ������ ������ ������� ������-��������.

� ������ ��������� �� ���������� ���� ������ ������ �������� ����� ����������� �������. 
������ ������� ���� ���� ������ ������� �� ���� ����������� � �������� � ���������� ����.
������� ������ ������������ ��������� ��������: ���������� ������ � ��������� ��� ����������� � add, �������� ������ � ��������� ����������� � remove.
��� �������� ��������� ������� ������ � ���� ������ � ���������� � ���� ������ �����.
��� ����� ���������� � ��������� ������ �������������� �� ���������. 
������� ������ ���� � ���� ������ ��������, ���������� �� ������ ��������� ���������� ���������� �������� �� ������ (��� �������� � � �������).

ww������������

� �������� ���������� ��� ���� ������ � ����� ������� ������ ������������ std::map.

���� ������������ ��� ������������ ����������, �� ����� ��������� std::invalid_argument, � ������ ������� � runtime_error. 

*/