//
//  Warehouse.cpp
//  project_item
//
//  Created by Jacob Derynk on 08/12/2019.
//  Copyright © 2019 Jacob. All rights reserved.
//

// colors std::cout << "\033[31m red \033[0m";
// 033 ASCII esc, 31 is color id (red in this case), m is probably end symbol?

#include "../include/Warehouse.hpp"

Warehouse::Warehouse(int tier, MaterialsCluster materialsMap, ProductCluster productsMap){
    switch (tier) {
        case 1:
            m_spaceLimit = 20;
            break;
            
        case 2:
            m_spaceLimit = 10;
            break;
            
        case 3:
            m_spaceLimit = 5;
        
      default:
            std::cerr << "There has been an error joining selected tier." << std::endl;
            m_spaceLimit = 20;
            break;
    }

    m_materialsCluster = materialsMap; // the map is already created in Init
    m_productsCluster = productsMap;   // same here
}

Warehouse::~Warehouse(){
}

int Warehouse::getSpaceLimit(){
    return m_spaceLimit;
}

int Warehouse::StorageFee(){
    int productsNo = 0;
    int materialsNo = 0;

    for (const auto& key : m_productsCluster){  // calculating no of products on stock
        productsNo += key.second;
    }

    for (const auto& key : m_materialsCluster){     // calculating no of material on stock
        materialsNo += key.second;
    }

    int foo = (materialsNo + (productsNo * 2)) * 0.5704012;           // fee calculation

    std::cout << "You paid the storage fee:\033[93m $" << foo << "\033[0m" << std::endl;
    std::cout << "  - You have \033[93m" << productsNo << "\033[0m products and\033[93m " << materialsNo << "\033[0m material in stock" << std::endl;

    return foo;
}

void Warehouse::upgradeSpace(){
    m_spaceLimit += 5;
    std::cout << "Storage limit was upgraded" << std::endl;
}

int Warehouse::getMaterialAmount(std::string which){

    for (const auto& key : m_materialsCluster){     // look at each key-value pair
        if (key.first->getName() == which){         // if the value is same as input
            return key.second;                      // returns second in map
        }
    }

    std::cout<<"key miss"<<std::endl;
    std::cerr<<"no such Material //at Warehouse::getMaterialAmount"<<std::endl;   // if someone cant write, return error value

    return (-1);
}

void Warehouse::buyMaterial(int quantity, std::string material){
    Warehouse::addToMaterialsCluster(material, quantity);
}

void Warehouse::addToMaterialsCluster(std::string what, int amount){

    int total = getMaterialAmount(what) + amount;

    for (const auto& key : m_materialsCluster){     // look at each key-value pair
        if (key.first->getName() == what){         // if the value is same as input
            //std::cout<<"key hit"<<std::endl;
            m_materialsCluster.at(key.first) = total;       // adds previous amount of material in stock plus amount wanted
            break;      // if found, function ends
        }
    }
}

bool Warehouse::checkMaterial(std::string what) {
    for (const auto& key : m_materialsCluster){     // look at each key-value pair
        if (key.first->getName() == what){         // if the value is same as input
            return true;
        }
    }
    return false;
}

int Warehouse::getMaterialPrice(std::string what) {
    for (const auto& key : m_materialsCluster){     // look at each key-value pair
        if (key.first->getName() == what){         // if the value is same as input
            return key.first->getPrice();
        }
    }
    return 0;
}

void Warehouse::removeFromMaterialsCluster(std::string what, int amount){
    int total = getMaterialAmount(what) - amount;     // total of Material (previous - amount wanted)

    if (total < 0){  //negative amount check
        std::cerr << "You can't remove " << amount << " of " << what << ". Amount would be negative" << std::endl;
    }
    else{
        for (const auto& key : m_materialsCluster){
            if (key.first->getName() == what){
                m_materialsCluster.at(key.first) = total;
                break;
            }
        }
    }
}

void Warehouse::printMaterialCluster() {

    std::cout<<"------------------------------------------"<<std::endl;
    std::cout<<"Printing Materials in stock: "<<std::endl;
    std::cout<<"------------------------------------------"<<std::endl;
    for (const auto& key : m_materialsCluster){
        std::cout << key.first->getName();
        std::cout << ": " << key.second;
        std::cout << "  - \033[93m$" << key.first->getPrice() << "/pc\033[0m";
        std::cout << std::endl;
    }
}

// ================================================================== zde konci material ==================================================================

void Warehouse::printProductCluster() {

    std::cout<<"------------------------------------------"<<std::endl;
    std::cout<<"Printing Products in stock: "<<std::endl;
    std::cout<<"------------------------------------------"<<std::endl;
    for (const auto& key : m_productsCluster){
        std::cout << key.first->getId() << " | ";
        std::cout << key.first->getName();
        std::cout << ": " << key.second;
        std::cout << "  - \033[93m$" << key.first->getPrice() << "/pc\033[0m";
        std::cout << std::endl;
    }
}

int Warehouse::getProductAmount(int ID){

    for (const auto& key : m_productsCluster){
        if (key.first->getId() == ID){
            return key.second;
        }
    }

    std::cout<<"key miss"<<std::endl;
    std::cerr<<"no such Product //at Warehouse::getProduct"<<std::endl;

    return (-1);    // returns error value
}

void Warehouse::addToProductsCluster(int ID, int amount){
    int total = getProductAmount(ID) + amount;

    for (const auto& key : m_productsCluster){     // look at each key-value pair
        if (key.first->getId() == ID){         // if the value is same as input
            m_productsCluster.at(key.first) = total;
            break;
        }
    }
}

void Warehouse::removeFromProductsCluster(int ID, int amount){
    int total = getProductAmount(ID) - amount;

    if (total < 0){   //negative amount check
        std::cerr << "You can't remove " << amount << " of product with ID:  " <<  ID << ". Amount would be negative" << std::endl;
    }
    else{

        for (const auto& key : m_productsCluster){
            if (key.first->getId() == ID){
                m_productsCluster.at(key.first) = total;
                break;
            }
        }
    }
}

int Warehouse::getProductPrice(int ID) {
    for (const auto& key : m_productsCluster){
        if (key.first->getId() == ID){
            return key.first->getPrice();
        }
    }
    return 0;
}

bool Warehouse::checkProduct(int what) {
    for (const auto& key : m_productsCluster){
        if (key.first->getId() == what){
            return true;
        }
    }
    return false;
}

std::string Warehouse::getProductsName(int productsID) {
    for (const auto& key : m_productsCluster){
        if (key.first->getId() == productsID){
            return (key.first->getName());
        }
    }
    return ("NULL");
}

void Warehouse::killAll() {
    for (const auto& key : m_productsCluster){
        delete key.first;
    }

    for (const auto& key : m_materialsCluster){
        delete key.first;
    }

    m_materialsCluster = {};
    m_productsCluster = {};
}

void Warehouse::setMaterialAmount(std::string what,int count) {
    for (std::pair<Material *const, int> &key : m_materialsCluster){     // look at each key-value pair
        if (key.first->getName() == what){         // if the value is same as input
            key.second = getMaterialAmount(what) - count;
        }
    }
}

void Warehouse::tommode() {
    for (std::pair<Material *const, int> &key : m_materialsCluster){
        key.second = 500;
    }
}