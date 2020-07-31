//
//  Warehouse.hpp
//  item_myprivate
//
//  Created by Jacob Derynk on 08/12/2019.
//  Copyright © 2019 Jacob. All rights reserved.
//

#ifndef Warehouse_hpp
#define Warehouse_hpp

#include <iostream>
#include <vector>
#include <map>
#include "Material.h"
#include "Product.h"

// ############### helpers begin here ##############################

typedef std::vector<Product*> ProductsVector;
typedef std::vector<Resource*> resourceVector;
typedef std::map<Material*, int> MaterialsCluster;
typedef std::map<Product*, int> ProductCluster;         //TODO: FACEPALM

// ############### helpers end here ##############################

class Warehouse {
private:

    int m_spaceLimit; //TODO: max warehouse capacity
    MaterialsCluster m_materialsCluster;
    ProductCluster m_productsCluster;

public:
    Warehouse(int tier, MaterialsCluster materialsMap, ProductCluster productsMap);    //FEATURE: according to the tier, specific no. of slots (space limit) would generate

    ~Warehouse();

    int getMaterialAmount(std::string which);

    int getProductAmount(int ID);

    int getSpaceLimit();

    void buyMaterial(int quantity, std::string material);

    int StorageFee();   // calculates ant returns storage fee

    void upgradeSpace();

    void addToMaterialsCluster(std::string what, int amount);

    void addToProductsCluster(int ID, int amount);

    void removeFromMaterialsCluster(std::string what, int amount);

    void removeFromProductsCluster(int ID, int amount);

    void printMaterialCluster();

    void printProductCluster();

    bool checkMaterial(std::string what);

    int getMaterialPrice(std::string what);

    int getProductPrice(int ID);

    bool checkProduct(int ID);

    void setMaterialAmount(std::string what, int count);

    std::string getProductsName(int productsID);

    void killAll();

    void tommode();
};

#endif /* Warehouse_hpp */
