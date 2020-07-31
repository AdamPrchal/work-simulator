//
// Created by Jacob Derynk on 01/01/2020.
//

#ifndef PROJECTITEM_MARKETPLACE_H
#define PROJECTITEM_MARKETPLACE_H

#include <iostream>
#include <array>
#include <random>
#include "Production.h"
#include "Material.h"
#include "Warehouse.hpp"

class Marketplace {

    MaterialsVector m_materialsVector;
    ProductsVector m_productsVector;

    std::map<std::string, int> m_materialsQueue;
    int m_queueCost;

public:
    Marketplace(MaterialsVector materials, ProductsVector products);

    ~Marketplace();

    int BuyMaterial(std::string material, int amount, int cash, Warehouse* at_warehouse);

    void priceGen();

    int orderProduct(int id, int amount, Warehouse* at_warehouse, Production* at_production);

    void killAll();

    void initiateMaterialsQueue(Warehouse* at_Warehouse);

    void printQueue();

    void resetRound();

    Product* getProductPointer(int name);

private:

    void addToQueue(std::string material, int amount);

    int SellProduct(int ID, int amount, Warehouse* at_warehouse);

    void assignJob(Product *product, int quaintity, Warehouse *ware, Production *production);
};


#endif //PROJECTITEM_MARKETPLACE_H
