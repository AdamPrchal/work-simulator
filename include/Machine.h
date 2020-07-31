//
// Created by Lenovo on 10.12.2019.
//

#ifndef PROJEKT_MACHINE_H
#define PROJEKT_MACHINE_H

#include <iostream>
#include <map>
#include "Product.h"

class Machine {
    static int m_idCount;
    std::string m_name;
    int m_id;
    int m_purchasePrice;
    int m_holdingTime;
    int m_availableSpace;

    
public:
    Machine();

    ~Machine();

    std::string getName();

    int getId();

    std::map<Product*, int> getQueue();
    
    int getPurchasePrice();

    int getHoldingTime();

    void increaseHoldingTime();

    int getAvailableSpace();

    int maintancePrice();


    void printInfo();

    /*TODO:
        int getPurchasePrice();
        .....
        map<Product*, int> getQueue;
        void IncreaseHoldingTime();
        void upgradeSpace(); - Zvýší availableSpace o 5000
        int maintenancePrice() - vrátí 1000
        void createProduct(Product* product, int quantity); - Přidá dvojici Product* a Int do productQueue
        printInfo() - Vypíše name, id, availableSpace, productQueue
    */
};


#endif //PROJEKT_MACHINE_H
