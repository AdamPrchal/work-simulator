//
// Created by Lenovo on 10.12.2019.
//

#include "../include/Production.h"




/*TODO: Prevest vyrobni seznam na Production
 * - budeme snaz kontrolovat dostupnou kapacitu vyroby
 * - mnohem snaz vyresime odebirani veci z vyrobniho seznamu
 * - snazsi udrzba a prace s prvky
 * */

Production::Production() {

    m_machines = {};
    m_machines.push_back(new Machine());
    m_productQueue = {};
}

Production::~Production() {}

int Production::buyMachine() {
    Machine *newMachine = new Machine();
    m_machines.push_back(newMachine);
    std::cout << std::endl << "Machine was succesfully bought." <<std::endl;
    return newMachine->getPurchasePrice();
}

int Production::sellMachine(int id) {

    bool found = false;
    int position = 0;
    while (!found && position < m_machines.size()) {
        if (m_machines[position]->getId() == id) {
            found = true;
        } else {
            position++;
        }
    }
    if(found){
        int price = m_machines[position]->getPurchasePrice();
        m_machines.erase(m_machines.begin() + position);
        return price;
    }
    else{
        std::cout << std::endl << "Machine " << id <<" does not exists." << std::endl;
        return 0;
    }
}

void Production::createProduct(Product* product, int quantity) {
    int fullTimeReq = product->getTimeRequirements() * quantity;
    if(checkCapacity(fullTimeReq)){
        if(checkDoubleEntry(product->getId())){
            for(const auto& productInQ: m_productQueue){
                if(productInQ.first->getId() == product->getId()){
                    m_productQueue.at(productInQ.first) += quantity;
                }
            }
        }else{
            m_productQueue.insert(std::make_pair(product,quantity));
        }

        std::cout << "You have successfully added \033[93m"<< quantity << "x\033[0m of \033[93m" << product->getName()
                  << "\033[0m to production queue." << std::endl;
    }
    else{
        std::cout << "You can't create that much or you reached maximum production capacity." << std::endl;
    }
}


void Production::printInfo() {
    std::cout << std::endl;
    std::cout<<"------------------------------------------"<<std::endl;
    std::cout<<"Printing production Queue:: "<<std::endl;
    std::cout<<"------------------------------------------"<<std::endl;
    for (const auto &key : m_productQueue) {     // look at each key-value pair
        std::cout << key.first->getName() << ": ";
        std::cout << key.second << std::endl;
    }
    std::cout << std::endl;
}

std::map<Product *, int> Production::getFinishedProducts() {
    return m_productQueue;}

void Production::printMachines() {
    for (int i = 0; i < m_machines.size(); i++) {
        std::cout << "Machine: " << m_machines[i]->getName() << std::endl;
    }
    std::cout << "-------------------------" << std::endl;

}

void Production::clearQueue() {
    m_productQueue = {};
}

bool Production::checkCapacity(int newProductTime) {
    int actualFreeTime = 0;
    int thisProductTime= 0;

    for(int i = 0; i < m_machines.size(); i++){
        actualFreeTime += m_machines[i]->getAvailableSpace();
    }

    for(const auto product:m_productQueue){
        thisProductTime= product.first->getTimeRequirements() * product.second;
        actualFreeTime -= thisProductTime;
    }

    if (actualFreeTime >= newProductTime){
        return true;
    }
        return false;

}

bool Production::checkDoubleEntry(int id) {
    bool found = false;
    for(const auto product:m_productQueue){
        if(product.first->getId() == id){
            found = true;
        }
    }
    return found;
}

void Production::printProductReq(Product* product, int quantity) {
    std::cout<<"------------------------------------------"<<std::endl;
    std::cout << product->getName() <<" requirements:: "<<std::endl;
    std::cout<<"------------------------------------------"<<std::endl;
    std::string unit;

    for (const auto& key : product->getMaterialRequirements()){
        if(key.second * quantity > 1){unit = " units";}
        else {unit = " unit";}
        std::cout << key.first->getName() << " : " << key.second * quantity  << unit << std::endl;
    }
}




