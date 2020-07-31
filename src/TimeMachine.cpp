//
// Created by adamp on 05.01.20.
//

#include "../include/TimeMachine.h"

TimeMachine* TimeMachine::s_instance = nullptr;

TimeMachine::TimeMachine() {
    m_turn = 0;
    m_costs = {0};
    m_revenue= {0};
    m_cash= {0};
}

TimeMachine::~TimeMachine() = default;

TimeMachine *TimeMachine::getTimeMachine() {
    if (s_instance == nullptr) {
        s_instance = new TimeMachine();
        return s_instance;
    } else {
        return s_instance;
    }
}

void TimeMachine::addToCosts(int price) {
    m_costs.at(m_turn) += price;
}

void TimeMachine::addToRevenue(int price) {
    m_revenue.at(m_turn) += price;
}

void TimeMachine::addToCash(int price) {
    m_cash.at(m_turn) += price;
}

void TimeMachine::nextTurn() {
    m_turn += 1;
    m_costs.push_back(0);
    m_revenue.push_back(0);
    m_cash.push_back(0);
}

void TimeMachine::printInfo() {
    std::cout << std::endl;
    int turns = m_turn + 1;
    std::cout << "Active turn: " << turns << std::endl;
    std::cout << std::setw(5) << "\033[4m Turn" << " | " << std::setw(16) << "Costs" << " | " << std::setw(16) << "Revenue" << " | "  << std::setw(16) << "Cash at the end \033[0m" << std::endl;
    for (int i = 0; i < turns; i++) {
        std::cout << std::setw(5) << i + 1 << " " << std::setw(16) << m_costs.at(i) << " " << std::setw(16) << m_revenue.at(i)  << " " << std::setw(16) << m_cash.at(i) <<  std::endl;
    }
}