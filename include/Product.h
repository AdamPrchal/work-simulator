//
// Created by Lenovo on 10.12.2019.
//

#ifndef PROJEKT_PRODUCT_H
#define PROJEKT_PRODUCT_H

#include <iostream>
#include <map>
#include "Resource.h"
#include "Material.h"

typedef std::vector<Material*> MaterialsVector;
typedef std::map<Material*, int> materialReqList;
typedef std::vector<std::vector<std::string>> parsedMaterialsReq;


class Product : public Resource {
    int m_timeRequirement;
    materialReqList m_materialRequirements;
public:
    static Product* createProduct(int id, std::string name, int timeRequirement, parsedMaterialsReq materialRequirements, MaterialsVector materials);

    ~Product();

    int getPrice() override;

    int getTimeRequirements();

    materialReqList getMaterialRequirements();
private:
    Product(int id, std::string name, int timeRequirement, materialReqList materialRequirements);

};


#endif //PROJEKT_PRODUCT_H
