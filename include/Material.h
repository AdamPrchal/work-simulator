//
// Created by adam on 12/11/19.
//

#ifndef PROJECTITEM_MATERIAL_H
#define PROJECTITEM_MATERIAL_H

#include <iostream>
#include <vector>
#include "Resource.h"

class Material : public Resource {
    int m_price;

public:
    Material(int id, std::string name, int price);
    ~Material();
    int getPrice() override;
    void setPrice(int price);
};

#endif //PROJECTITEM_MATERIAL_H
