//
// Created by adam on 12/8/19.
//

#include "../include/Initialization.h"

Initialization::Initialization(){
    m_dataLayer = new DataLayer();
};

Initialization::~Initialization() = default;

void Initialization::printVector(resourceVector array) {
    if (!array.empty()) {
        std::cout << std::endl << "Init resources" << std::endl;
        std::cout << "----------------------" << std::endl;

        for (auto const &x : array) { // Projde každý prvek v poli
            std::cout << x->getName() << std::endl;
        }
    } else {
        std::cerr << std::endl << "Nebylo mozne vypsat obsah prazdneho vektoru" << std::endl;
    }

}

MaterialsVector Initialization::createMaterialsVector() {
    parametersVector materialsList = m_dataLayer->load("materials");
    MaterialsVector createdVector;
    for (auto it : materialsList) {
        createdVector.push_back(new Material(it.id, it.name, it.price));
    }
    return createdVector;
}

MaterialsCluster Initialization::createMaterialsMap(MaterialsVector materials) {
    MaterialsCluster createdMap;
    for (auto it : materials) {
        createdMap.insert(std::make_pair(it, 10));
    }
    return createdMap;
}

ProductCluster Initialization::createProductsMap(MaterialsVector materials) {
    parametersVector productsList = m_dataLayer->load("products");
    ProductCluster createdMap;
    for (auto it : productsList) {
        createdMap.insert(std::make_pair(Product::createProduct(it.id, it.name, it.timeRequirement, it.materialRequirements, materials), 0));
    }
    return createdMap;
}

ProductsVector Initialization::createProductsVector(ProductCluster productCluster) {
    ProductsVector productsVector;
    for (auto it : productCluster) {
        productsVector.push_back(it.first);
    }
    return productsVector;
}

