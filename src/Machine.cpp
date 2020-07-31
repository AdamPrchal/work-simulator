//
// Created by Lenovo on 10.12.2019.
//

#include <map>
#include "../include/Machine.h"


Machine::Machine() {
    m_name = "Machine no." + std::to_string(m_idCount);
    m_availableSpace = 5000000;
    m_holdingTime = 0;
    m_purchasePrice = 10000;
    m_id = m_idCount;
    m_idCount++;
}

Machine::~Machine() {
}

std::string Machine::getName() {
    return m_name;
}

int Machine::getId(){
    return m_id;
}

int Machine::getPurchasePrice() {
    return m_purchasePrice;
}

int Machine::getHoldingTime() {
    return m_holdingTime;
}


int Machine::maintancePrice() {
    return 1000;
}



int Machine::getAvailableSpace() {
    return m_availableSpace;
}

void Machine::printInfo() {
    std::cout << "Name: " << getName() << std::endl;
    std::cout << "ID: " << getId() << std::endl;
    std::cout << "Available space: " << getAvailableSpace() << std::endl;

}


int Machine::m_idCount = 0;

