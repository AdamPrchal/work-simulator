//
// Created by adam on 12/12/19.
//

#include "../include/Resource.h"

Resource::Resource(std::string name, int id) {
    m_name = name;
    m_id = id;
}

Resource::~Resource() = default;

std::string Resource::getName() {
    return m_name;
}

int Resource::getId() {
    return m_id;
}
