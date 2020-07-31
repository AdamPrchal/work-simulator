//
// Created by adam on 12/12/19.
//

#ifndef PROJECTITEM_RESOURCE_H
#define PROJECTITEM_RESOURCE_H

#include <iostream>

class Resource {
protected:
    std::string m_name;
    int m_id;
public:
    Resource(std::string name, int id);

    virtual ~Resource();

    virtual int getPrice() = 0;

    virtual std::string getName();

    int getId();
};


#endif //PROJECTITEM_RESOURCE_H
