//
// Created by Lenovo on 10.12.2019.
//

#include "../include/Product.h"


Product::Product(int id, std::string name, int timeRequirement, materialReqList materialRequirements) : Resource(name, id) {
    m_timeRequirement = timeRequirement;
    m_materialRequirements = materialRequirements;
}

Product::~Product() = default;

Product * Product::createProduct(int id, std::string name, int timeRequirement, parsedMaterialsReq materialRequirements, MaterialsVector materials) {
    materialReqList completeList = {};
    Material* matchingInstance;
    for (auto token : materialRequirements) {
        for (auto &it : materials) {
            if(std::stoi(token[0]) == it->getId()){
                matchingInstance = it;
            }
        }
        completeList.insert(std::make_pair(matchingInstance,std::stoi(token[1])));
    }

    Product* newProduct = new Product(id, name, timeRequirement, completeList);
    return newProduct;
}

int Product::getPrice() {       //TODO - Calculate price based on material requirements
    int sum = 0;
    for (const auto& key : m_materialRequirements){
        sum += key.first->getPrice();
    }
    float profitPrice = float(sum) * 1.21;
    return int(profitPrice);
}

int Product::getTimeRequirements() {
    return m_timeRequirement;
}

materialReqList Product::getMaterialRequirements() {
    return m_materialRequirements;
}
