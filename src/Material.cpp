//
// Created by adam on 12/11/19.
//

#include "../include/Material.h"

Material::Material(int id, std::string name, int price) : Resource(name, id) {
    m_price = price;
};

Material::~Material() = default;


int Material::getPrice() {
    return m_price;
}

void Material::setPrice(int price) {    //called form marketplace to change materials price during the game :--)
    m_price = price;
}
