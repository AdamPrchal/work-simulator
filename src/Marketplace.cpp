//
// Created by Jacob Derynk on 01/01/2020.
//

#include "../include/Marketplace.h"

Marketplace::Marketplace(MaterialsVector materials, ProductsVector products){
    m_materialsVector = materials;
    m_productsVector = products;
    m_materialsQueue = {};
    m_queueCost = 0;
}

Marketplace:: ~Marketplace(){

}

void Marketplace::killAll() {
    m_materialsQueue = {};
    m_productsVector = {};
    m_materialsVector = {};
}

int Marketplace::orderProduct(int id, int amount, Warehouse* at_warehouse, Production* at_production){
    std::string order;
    int bill = 0;

    if (at_warehouse->checkProduct(id)) {

        if (amount > 0) {

            if (at_warehouse->getProductAmount(id) >= amount){
                //mam produkt

                bill = SellProduct(id, amount, at_warehouse);
                return bill;

            } else {
                std::cout   << "\033[91mWe are sorry, but we don't have enough number of " << at_warehouse->getProductsName(id)
                            << " on stock\033[0m" << std::endl
                            << "Do you want to order it? (y/n) ";

                getline(std::cin, order);

                if (order == "y"){
                    // send to order

                    amount = amount  -  at_warehouse->getProductAmount(id);
                    std::cout << amount <<" of products are about to be ordered" << std::endl;

                    assignJob(getProductPointer(id),amount,at_warehouse,at_production);


                    return 0;
                } else {
                    std::cout << "Products was not ordered" << std::endl;
                    return 0;
                }
            }

        }
        else { std::cout << "Can't sell this amount" << std::endl;}

    } else {
        std::cout << "Product with ID: " << id
                  << " does not exist. Write \"listProducts\" command to see list of products."
                  << std::endl;
        }

    return 0;
}

int Marketplace::SellProduct(int id, int amount, Warehouse* at_warehouse) {
    int bill = 0;

    bill = at_warehouse->getProductPrice(id) * amount;   // calculates price to be paid
    at_warehouse->removeFromProductsCluster(id, amount);

    std::cout       << "You have successfully sold \033[93m"<< amount << "\033[0m of \033[93m\"" << at_warehouse->getProductsName(id)
                    << "\"\033[0m for \033[93m$" << bill << "\033[0m" << std::endl;
    return bill;

}

int Marketplace::BuyMaterial(std::string material, int amount, int cash, Warehouse* at_warehouse) {
    int bill = 0;

    if (at_warehouse->checkMaterial(material)) {

        if (amount > 0) {
            bill = amount * at_warehouse->getMaterialPrice(material);   //calculates bill
            if (cash >= bill) {

                addToQueue(material, amount);
                m_queueCost += bill;

                std::cout       << "You have successfully added \033[93m"<< amount << "\033[0m of \033[93m\"" << material
                                << "\"\033[0m to checklist for \033[93m$" << bill << "\033[0m" << std::endl;

                return bill;    // if everything is ok, method ends
            } else {
                std::cout << "You do not have enough money." << std::endl;
                bill = 0;
            }
        } else {
            std::cout << "Amount cannot be negative." << std::endl;
        }
    } else {
        std::cout << "Material " << material
                  << " does not exist. Write \"listMaterials\" command to see list of materials."
                  << std::endl;
    }

    return 0;
}

void Marketplace::priceGen() {
    float quocient = 0;
    int newPrice = 0;

    std::random_device rd;  // random no gen
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(-45, 55);   // probability of result

    for (int i = 0; i < m_materialsVector.size(); i++){
        //quocient = rand() % 100 + (-45);      // old algorithm
        quocient = dist(mt);    // saving generated no.
        newPrice = m_materialsVector.at(i)->getPrice() * (1 + (quocient/1000));     // calculating value change to material
        m_materialsVector.at(i)->setPrice(newPrice);    // applying change to material
    }
}

void Marketplace::addToQueue(std::string material, int amount) {

    if(m_materialsQueue.empty()) {m_materialsQueue.insert(std::make_pair(material, amount));}
    else{
        for (auto& key : m_materialsQueue){
            if(key.first == material){
                key.second += amount;
                break;
            }
        }
        m_materialsQueue.insert(std::make_pair(material, amount));
    }
}

void Marketplace::printQueue() {
    std::cout<<"------------------------------------------"<<std::endl;
    std::cout<<"Printing materials checklist:: "<<std::endl;
    std::cout<<"------------------------------------------"<<std::endl;
    std::string unit;

    for (const auto& key : m_materialsQueue){
        if(key.second > 1){unit = " units";}
        else {unit = " unit";}
        std::cout << key.first << " : " << key.second << unit << std::endl;
    }
    std::cout << "\nTotal bill is: \033[93m$" << m_queueCost << "\033[0m" << std::endl;
}

void Marketplace::initiateMaterialsQueue(Warehouse *at_warehouse) {    // buys material in queue

    if (!m_materialsQueue.empty()){
        for (const auto& key : m_materialsQueue){       //materialsQueue has at .first name of Material, at .second amount to be bought
            at_warehouse->buyMaterial(key.second, key.first);
        }

        std::string type;
        if(m_materialsQueue.size() > 1){type = " types";}
        else {type = " type";}

        std::cout   << "You have successfully bought\033[93m " << m_materialsQueue.size() << "\033[0m"<< type << " of material " << std::endl
                    << "with total of \033[93m$" << m_queueCost << "\033[0m" << std::endl;
    }

    resetRound();
}

void Marketplace::resetRound() {
    m_materialsQueue = {};
    m_queueCost = 0;
}


Product * Marketplace::getProductPointer(int id) {
    for(int i = 0; i < m_productsVector.size(); i++){
        if(m_productsVector[i]->getId() == id){
            return m_productsVector[i];
        }
    }
    return nullptr;
}

void Marketplace::assignJob(Product *product, int quaintity, Warehouse *ware, Production *production) {

    materialReqList materialList = product->getMaterialRequirements();
    int reqMaterialCount = 0;
    int canAssing = 0;

    for(const auto material : materialList){
        std::string materialName = material.first->getName();
        if(ware->checkMaterial(materialName)){
            if(ware->getMaterialAmount(materialName) >= material.second * quaintity){
                canAssing++;
            }
        }
        reqMaterialCount++;
    }

    if(reqMaterialCount == canAssing) {
        production->createProduct(product,quaintity);

        for(const auto material : materialList){
            std::string materialName = material.first->getName();
            ware->setMaterialAmount(materialName,material.second * quaintity);
        }
    }else{
        std::cout << "\033[31mYou don't meet material requirements for this job.\033[0m" << std::endl;
        production->printProductReq(product, quaintity);
    }
}