//
// Created by Lenovo on 11.12.2019.
//

#ifndef PROJEKT_CORE_H
#define PROJEKT_CORE_H

#include <iostream>
#include <vector>
#include <map>
#include <cctype>
#include <string>
#include <algorithm>
#include <iomanip>
#include "Initialization.h"
#include "Marketplace.h"
#include "Production.h"
#include "TimeMachine.h"

class Core {
    int m_cashflow;
    int m_turn;
    std::string m_input;
    bool m_running;
    std::map<std::string, int> m_commands;
    Marketplace* m_marketplace;
    Production* m_production;
    Warehouse* m_warehouse;
    TimeMachine* m_timeMachine;
    int m_deathRow;
public:
    Core();
    ~Core();
    int Commands(std::string m_input);
    void run();
    void removeWarehouse();
    void removeMarketplace();
    void removeProduction();
    void initialize();
    std::vector<std::string> parseCommand(std::string activeCommand);
    int getCashFlow();
    void setCashFlow(int cashflow);
    void helpDesk();
    void dashBoard(int type);
    //int getTurnsNo();     //FEATURE: depending on no. of turns, game gets harder (stock, random events, etc.)

    //Handling product creating
    void assignJob(Product* product, int quantity);
private:
    void setWarehouse(Warehouse* newWarehouse);
    void printProductRequirements(int id);
    void resetRound();
    void nextTurn();
    void gameOver();
    void endGame();
    void transferProducts();
};


#endif //PROJEKT_CORE_H
