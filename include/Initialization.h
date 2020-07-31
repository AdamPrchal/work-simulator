//
// Created by adam on 12/8/19.
//

#ifndef PROJECTITEM_INITIALIZATION_H
#define PROJECTITEM_INITIALIZATION_H

#include "Production.h"
#include "DataLayer.h"

class Initialization {

   DataLayer* m_dataLayer;

public:
    Initialization();

    ~Initialization();

    MaterialsVector createMaterialsVector();
    ProductCluster createProductsMap(MaterialsVector materials);
    MaterialsCluster createMaterialsMap(MaterialsVector materials);
    ProductsVector createProductsVector(ProductCluster productCluster);


    void printVector(resourceVector array);                                // Prints vector made by load() - primarily made for testing

};


#endif //PROJECTITEM_INITIALIZATION_H
