//
// Created by adamp on 05.01.20.
//

#ifndef PROJECTITEM_TIMEMACHINE_H
#define PROJECTITEM_TIMEMACHINE_H

#include <vector>
#include <iostream>
#include <iomanip>


class TimeMachine {
   static TimeMachine* s_instance;
   std::vector<int> m_revenue;
   std::vector<int> m_costs;
   std::vector<int> m_cash;
   int m_turn;

public:
    static TimeMachine* getTimeMachine();
    ~TimeMachine();
    void addToRevenue(int price);
    void addToCosts(int price);
    void addToCash(int price);

    void nextTurn();
    void printInfo();

private:
    TimeMachine();

};

#endif //PROJECTITEM_TIMEMACHINE_H
