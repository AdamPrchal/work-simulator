//
// Created by adam on 12/22/19.
//

#ifndef PROJECTITEM_DATALAYER_H
#define PROJECTITEM_DATALAYER_H

#include <iostream>
#include <cstdlib>
#include <sstream>
#include <fstream>
#include <vector>
#include <string>
#include "Warehouse.hpp"
#include "Material.h"
#include "Product.h"


struct parametersContainer {
    int id;
    std::string name;
    int price;
    int timeRequirement;
    parsedMaterialsReq materialRequirements;
};

typedef std::vector<parametersContainer> parametersVector;


class DataLayer {
    parametersContainer packageParameters(std::string type, std::vector<std::string> tokens);
public:
    DataLayer();
    ~DataLayer();
    parametersVector load(std::string fileName);                // Returns vector with instances of Material or Product depending of what filename you call
private:
    parsedMaterialsReq parseMaterialReq(std::string materialReq);
    std::vector<std::string> parseLine(std::string activeLine, char delimiter);     // Parses entered string
};


#endif //PROJECTITEM_DATALAYER_H
