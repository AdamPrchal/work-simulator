//
// Created by Lenovo on 10.12.2019.
//

#ifndef PROJEKT_PRODUCTION_H
#define PROJEKT_PRODUCTION_H
#include <iostream>
#include <vector>
#include "Machine.h"
#include "Product.h"

class Production {
    std::vector<Machine*> m_machines;
    std::map<Product*, int> m_productQueue;
public:
    Production();
    ~Production();
    int buyMachine();
    int sellMachine(int id);
    void printInfo();
    std::map<Product*, int> getFinishedProducts();
    void clearQueue();
    void printMachines();
    void createProduct(Product* product, int quantity);
    void printProductReq(Product* product, int quantity);
private:
    bool checkCapacity(int newProductTime);
    bool checkDoubleEntry(int id);
};


#endif //PROJEKT_PRODUCTION_H
