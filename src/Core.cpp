//
// Created by Lenovo on 11.12.2019.
//

#include "../include/Core.h"


Core::Core() {
    m_cashflow = 100000;
    m_running = true;
    m_turn = 1;
    m_warehouse = nullptr;
    m_timeMachine = TimeMachine::getTimeMachine();
    m_marketplace = nullptr;
    m_production = nullptr;
    m_deathRow = 0;
}

Core::~Core() {
}

void Core::dashBoard(int type) {
    if(type == 0){
        std::cout << std::endl;
        std::cout << "Welcome to the game! We hope that you will enjoy this game made by Item corporation." << std::endl;
        std::cout << std::endl;
        std::cout << "  **   **********   ********   ****     ****   Corporation." << std::endl;
        std::cout << " /**  /////**///   /**/////   /**/**   **/**   " << std::endl;
        std::cout << " /**      /**      /**        /**//** ** /**   Vinc, Jacob and CC" << std::endl;
        std::cout << " /**      /**      /*******   /** //***  /**   (c) 2019-2020" << std::endl;
        std::cout << " /**      /**      /**////    /**  //*   /**   " << std::endl;
        std::cout << " /**      /**      /**        /**   /    /**   " << std::endl;
        std::cout << " /**      /**      /********  /**        /**   " << std::endl;
        std::cout << " //       //       ////////   //         //    " << std::endl;
        std::cout << std::endl;
        std::cout << "\033[33mYou can use \"help\" command to see list of commands.\033[0m" << std::endl;
    }else if(type == 1){
        std::cout << "Welcome to the next round! You can use \"help\" command to see list of commands." << std::endl;
        std::cout << std::endl;
    }
}

void Core::nextTurn() {
    transferProducts();
    m_production->clearQueue();

    m_marketplace->initiateMaterialsQueue(m_warehouse);
    m_marketplace->priceGen();
    dashBoard(1);

    m_timeMachine->addToCash(m_cashflow);
    m_timeMachine->nextTurn();

// ============================================ dont put any code under this line (in this method of course) ============================================
    setCashFlow(getCashFlow() - m_warehouse->StorageFee());
    if(m_cashflow < 0) {
        m_deathRow++;
        if (m_deathRow == 1) {
            std::cout << "\033[91mWatch out! You are starting this round with negative budget!" << std::endl
                      << "Make sure to end this round with positive amount of cash or the Game is over!\033[0m"
                      << std::endl;
        }
    }

    if (m_deathRow > 1){
        gameOver();
    } else if (m_deathRow == 1 and m_cashflow > 0){
        m_deathRow = 0;
        std::cout   << "\033[34mYou have managed to overcome your bankruptcy! Well played." << std::endl
                    << "Better watch out next time!\033[0m" << std::endl;
    }
}

int Core::Commands(std::string input) {
    m_commands.insert(std::pair<std::string, int>("listMaterials", 1));
    m_commands.insert(std::pair<std::string, int>("listProducts", 2));
    m_commands.insert(std::pair<std::string, int>("buyMaterials", 3));
    m_commands.insert(std::pair<std::string, int>("sellProducts", 4));
    m_commands.insert(std::pair<std::string, int>("cash", 5)); //
    m_commands.insert(std::pair<std::string, int>("help", 6));

    m_commands.insert(std::pair<std::string, int>("next", 7));
    m_commands.insert(std::pair<std::string, int>("resetRound", 8));
    m_commands.insert(std::pair<std::string, int>("listq", 9));
    m_commands.insert(std::pair<std::string, int>("stats", 10));
    m_commands.insert(std::pair<std::string, int>("createProducts", 11));
    m_commands.insert(std::pair<std::string, int>("motivation", 13));
    m_commands.insert(std::pair<std::string, int>("productr", 14));
    m_commands.insert(std::pair<std::string, int>("buyMachine", 15));
    m_commands.insert(std::pair<std::string, int>("sellMachine", 16));
    m_commands.insert(std::pair<std::string, int>("showMachine", 17));
    



    m_commands.insert(std::pair<std::string, int>("tommode", 200));
    m_commands.insert(std::pair<std::string, int>("hobomode", 404));
    m_commands.insert(std::pair<std::string, int>("exit", 100));

    m_input = input;
    std::map<std::string, int>::iterator itr;
    for (auto itr = m_commands.find(m_input); itr == m_commands.find(m_input);) {
        if (itr == m_commands.find(m_input)) {
            return itr->second;
        } else {
            return 0;
        }
    }
    return (-1);
}

void Core::setCashFlow(int cashflow) {
    m_cashflow = cashflow;
}

int Core::getCashFlow() {
    return m_cashflow;
}

void Core::run() {
    int amount = 0;
    int price = 0;
    int id = 0;
    dashBoard(0);
    while (m_running) {
        std::string input;
        std::cout << std::endl;
        std::cout << "Enter command: ";
        getline(std::cin, input);
        std::vector<std::string> parsedCommand = parseCommand(input);
        switch (Commands(parsedCommand[0])) {
            case 1:
                m_warehouse->printMaterialCluster();
                break;
            case 2:
                m_warehouse->printProductCluster();
                break;
            case 3:
                if (parsedCommand.size() == 3 &&
                    std::all_of(parsedCommand[2].begin(), parsedCommand[2].end(), ::isdigit)) {
                    parsedCommand[1][0] = toupper(parsedCommand[1][0]);

                    amount = std::stoi(parsedCommand[2]);
                    std::string what = parsedCommand[1];
                    int bill = 0;
                    bill = m_marketplace->BuyMaterial(what, amount, getCashFlow(), m_warehouse);        //buyMaterial returns amount that we pay - stored in bill

                    setCashFlow(getCashFlow() - bill);
                    m_timeMachine -> addToCosts(bill);

                } else {
                    std::cout << "Wrong command parameters. eg. \"buyMaterials <name> <amount>\"" << std::endl;
                }
                break;



            case 4:
                if (parsedCommand.size() == 3 &&
                    std::all_of(parsedCommand[1].begin(), parsedCommand[1].end(), ::isdigit) &&
                    std::all_of(parsedCommand[2].begin(), parsedCommand[2].end(), ::isdigit)) {

                    id = std::stoi(parsedCommand[1]);
                    amount = std::stoi(parsedCommand[2]);

                    price = m_marketplace->orderProduct(id, amount, m_warehouse, m_production);        //sellProducts returns amount that we gain - stored in price
                    if (price > 0){
                        setCashFlow(getCashFlow() + price);
                    }

                    m_timeMachine -> addToRevenue(price);

                } else{ std::cout << "Wrong command parameters. eg. \"sellProducts <id> <amount>\"" << std::endl;}
                break;



            case 5:
                std::cout << "Cashflow: " << getCashFlow() << std::endl;
                break;



            case 6:
                helpDesk();
                break;



            case 7:
                nextTurn();
                break;



            case 8:
                resetRound();
                break;



            case 9:
                m_marketplace->printQueue();
                m_production->printInfo();
                break;

            case 10:
                m_timeMachine->printInfo();
                break;

            case 11:
                if (parsedCommand.size() == 3 &&
                std::all_of(parsedCommand[1].begin(), parsedCommand[1].end(), ::isdigit) &&
                std::all_of(parsedCommand[2].begin(), parsedCommand[2].end(), ::isdigit)){
                    id = std::stoi(parsedCommand[1]);
                    amount = std::stoi(parsedCommand[2]);
                    assignJob(m_marketplace->getProductPointer(id),amount);
                } else{
                    std::cout << "Wrong command parameters. eg. \"createProducts <id> <amount>\"" << std::endl;
                }
                break;


            case 13:
                std::cout << "##    # ###### #    # ###### #####      ####  # #    # ######    #    # #####"
                          << std::endl;
                std::cout << "# #   # #      #    # #      #    #    #    # # #    # #         #    # #    #"
                          << std::endl;
                std::cout << "#  #  # #####  #    # #####  #    #    #      # #    # #####     #    # #    # "
                          << std::endl;
                std::cout << "#   # # #      #    # #      #####     #  ### # #    # #         #    # ##### "
                          << std::endl;
                std::cout << "#    ## #       #  #  #      #   #     #    # #  #  #  #         #    # #"
                          << std::endl;
                std::cout << "#     # ######   ##   ###### #    #     ####  #   ##   ######     ####  #"
                          << std::endl;
                break;


            case 14:
                if (parsedCommand.size() == 2 && std::all_of(parsedCommand[1].begin(), parsedCommand[1].end(), ::isdigit)){
                    id = std::stoi(parsedCommand[1]);

                    // TODO: m_production-> requirements

                    Product* selectedProduct = m_marketplace->getProductPointer(id);
                    m_production->printProductReq(selectedProduct, 1);


                } else{ std::cout << "Wrong command parameters. eg. \"productr <id>\"" << std::endl;}
                break;


            case 15:
                if(getCashFlow() >= 10000){
                    setCashFlow(getCashFlow() - m_production->buyMachine());
                } else{
                    std::cout << std::endl << "You dont have enough money" <<std::endl;
                }


                break;

            case 16:
                if (parsedCommand.size() == 2 && std::all_of(parsedCommand[1].begin(), parsedCommand[1].end(), ::isdigit)){
                    id = std::stoi(parsedCommand[1]);
                setCashFlow(getCashFlow() + m_production->sellMachine(id));}
                else{ std::cout << "Wrong command parameters. eg. \"sellMachine <id>\"" << std::endl;}
                break;

            case 17:
                m_production->printMachines();

                break;



            case 100:
                std::cout << "You have left the game." << std::endl;
                m_timeMachine->printInfo();
                endGame();

                break;

            case 200:   //tom mode
                setCashFlow(999999);
                m_warehouse->tommode();


                break;
            case 404:   //hobo mode
                setCashFlow(0);
                break;

            default:
                std::cout << parsedCommand[0]
                          << " command does not exist. Write \"help\" command to see list of commands." << std::endl;
        }
    }
}

std::vector<std::string> Core::parseCommand(std::string activeCommand) {
    std::vector<std::string> tokens;        // Vector of string to save tokens
    std::stringstream buffer(activeCommand);       // Stringstream class used for operating with string
    std::string intermediate;   // String variable used for storing each token at the time and passing it to vector
    while (getline(buffer, intermediate,
                   ' ')) {        // Tokenizing - getline(whole string , where to put save token , delimiter)
        tokens.push_back(intermediate);
    }
    return tokens;
}

void Core::removeWarehouse(){
    delete m_warehouse;
    m_warehouse = nullptr;
}

void Core::removeMarketplace(){
    delete m_marketplace;
    m_marketplace = nullptr;
}

void Core::removeProduction() {
    delete m_production;
    m_production = nullptr;
}

void Core::endGame() {
    m_running = false;

    m_warehouse->killAll();
    m_marketplace->killAll();
    // KILL ALL

    removeWarehouse();
    removeMarketplace();
    removeProduction();
}

void Core::initialize() {
    Initialization *init = new Initialization();

    MaterialsVector allMaterials = init->createMaterialsVector();
    MaterialsCluster materialsWarehouse = init->createMaterialsMap(allMaterials);   //map
    ProductCluster productsWarehouse = init->createProductsMap(allMaterials);       //map
    ProductsVector allProducts = init->createProductsVector(productsWarehouse);

    Warehouse *warehouse = new Warehouse(1, materialsWarehouse, productsWarehouse);             //  THIS
    setWarehouse(warehouse);


    Marketplace *marketplace = new Marketplace(allMaterials, allProducts);      //FIXME: predavam bez pointeru (lebo to nejde) ale i tak zmena cen funguje ??? wtf
    m_marketplace = marketplace;

    Production *production = new Production();
    m_production = production;

    delete (init);
}

void Core::setWarehouse(Warehouse *newWarehouse) {
    m_warehouse = newWarehouse;
}

void Core::resetRound() {
    m_marketplace->resetRound();

    std::cout << "Round was restarted, queues are now empty." << std::endl;
}

void Core::gameOver(){
    std::cout   << "\033[31mOh no! Your budget was below zero two times in a row." << std::endl
                << "I'm gonna stop you right there. (read as: GAME OVER)\033[0m" << std::endl;

    m_timeMachine->printInfo();
    endGame();
}

void Core::helpDesk(){
    const char separator = ' ';
    const int nameWidth = 55;
    const int secondNameWidth = 34;

    std::cout << std::left << std::setw(secondNameWidth-9) << std::setfill(separator) << "Command:";
    std::cout << std::left << std::setw(nameWidth) << std::setfill(separator) << "Action:";
    std::cout << std::left << std::setw(nameWidth) << std::setfill(separator) << "Example:";
    std::cout << std::endl;
    std::cout << "-----------------------------------------------------------------------------------------------------------------" << std::endl;
    std::cout << std::left << std::setw(secondNameWidth) << std::setfill(separator) << "\033[34mhelp\033[0m";
    std::cout << std::left << std::setw(nameWidth) << std::setfill(separator) << "Prints available commands";
    std::cout << std::left << std::setw(nameWidth) << std::setfill(separator) << "\033[34mhelp\033[0m";
    std::cout << std::endl;
    std::cout << std::left << std::setw(secondNameWidth) << std::setfill(separator) << "\033[34mmotivation\033[0m";
    std::cout << std::left << std::setw(nameWidth) << std::setfill(separator) << "Prints ASCII art to motivate your comrades in arms";
    std::cout << std::left << std::setw(nameWidth) << std::setfill(separator) << "\033[34mmotivation\033[0m";
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::left << std::setw(secondNameWidth) << std::setfill(separator) << "\033[34mcash\033[0m";
    std::cout << std::left << std::setw(nameWidth) << std::setfill(separator) << "Prints cash";
    std::cout << std::left << std::setw(nameWidth) << std::setfill(separator) << "\033[34mcash\033[0m";
    std::cout << std::endl;
    std::cout << std::left << std::setw(secondNameWidth) << std::setfill(separator) << "\033[34mlistMaterials\033[0m";
    std::cout << std::left << std::setw(nameWidth) << std::setfill(separator) << "Prints list of materials";
    std::cout << std::left << std::setw(nameWidth) << std::setfill(separator) << "\033[34mlistMaterials\033[0m";
    std::cout << std::endl;
    std::cout << std::left << std::setw(secondNameWidth) << std::setfill(separator) << "\033[34mlistProducts\033[0m";
    std::cout << std::left << std::setw(nameWidth) << std::setfill(separator) << "Prints list of products";
    std::cout << std::left << std::setw(nameWidth) << std::setfill(separator) << "\033[34mlistProducts\033[0m";
    std::cout << std::endl;
    std::cout << std::left << std::setw(secondNameWidth) << std::setfill(separator) << "\033[34mlistq\033[0m";
    std::cout << std::left << std::setw(nameWidth) << std::setfill(separator) << "Prints all tasks scheduled";
    std::cout << std::left << std::setw(nameWidth) << std::setfill(separator) << "\033[34mlistq\033[0m";
    std::cout << std::endl;
    std::cout << std::left << std::setw(secondNameWidth) << std::setfill(separator) << "\033[34mstats\033[0m";
    std::cout << std::left << std::setw(nameWidth) << std::setfill(separator) << "Prints history \"calls\"";
    std::cout << std::left << std::setw(nameWidth) << std::setfill(separator) << "\033[34mstats\033[0m";
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::left << std::setw(secondNameWidth) << std::setfill(separator) << "\033[34mbuyMaterials\033[0m";
    std::cout << std::left << std::setw(nameWidth) << std::setfill(separator) << "Buys amount of certain material";
    std::cout << std::left << std::setw(nameWidth) << std::setfill(separator) << "\033[34mbuyMaterials <name of material> <amount>\033[0m";
    std::cout << std::endl;
    std::cout << std::left << std::setw(secondNameWidth) << std::setfill(separator) << "\033[34msellProducts\033[0m";
    std::cout << std::left << std::setw(nameWidth) << std::setfill(separator) << "Sells amount of certain product";
    std::cout << std::left << std::setw(nameWidth) << std::setfill(separator) << "\033[34msellProducts <ID of the product> <amount>\033[0m";
    std::cout << std::endl;
    std::cout << std::left << std::setw(secondNameWidth) << std::setfill(separator) << "\033[34mnext\033[0m";
    std::cout << std::left << std::setw(nameWidth) << std::setfill(separator) << "New round (pays bill, starts production etc.)";
    std::cout << std::left << std::setw(nameWidth) << std::setfill(separator) << "\033[34mnext\033[0m";
    std::cout << std::endl;
    std::cout << std::left << std::setw(secondNameWidth) << std::setfill(separator) << "\033[34mresetRound\033[0m";
    std::cout << std::left << std::setw(nameWidth) << std::setfill(separator) << "Starts current round again";
    std::cout << std::left << std::setw(nameWidth) << std::setfill(separator) << "\033[34mresetRound\033[0m";
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::left << std::setw(secondNameWidth) << std::setfill(separator) << "\033[34mcreateProducts\033[0m"; // sell machine chce id stroje
    std::cout << std::left << std::setw(nameWidth) << std::setfill(separator) << "sets products to production";
    std::cout << std::left << std::setw(nameWidth) << std::setfill(separator) << "\033[34mcreateProducts <id> <amount>\033[0m";
    std::cout << std::endl;
    std::cout << std::left << std::setw(secondNameWidth) << std::setfill(separator) << "\033[34mproductr\033[0m";
    std::cout << std::left << std::setw(nameWidth) << std::setfill(separator) << "Shows products requirements";
    std::cout << std::left << std::setw(nameWidth) << std::setfill(separator) << "\033[34mproductr <id>\033[0m";
    std::cout << std::endl;
    std::cout << std::left << std::setw(secondNameWidth) << std::setfill(separator) << "\033[34mbuyMachine\033[0m";
    std::cout << std::left << std::setw(nameWidth) << std::setfill(separator) << "Buys new machine";
    std::cout << std::left << std::setw(nameWidth) << std::setfill(separator) << "\033[34mbuyMachine\033[0m";
    std::cout << std::endl;
    std::cout << std::left << std::setw(secondNameWidth) << std::setfill(separator) << "\033[34msellMachine\033[0m";
    std::cout << std::left << std::setw(nameWidth) << std::setfill(separator) << "Sells machine with id";
    std::cout << std::left << std::setw(nameWidth) << std::setfill(separator) << "\033[34msellMachine <id>\033[0m";
    std::cout << std::endl;
    std::cout << std::left << std::setw(secondNameWidth) << std::setfill(separator) << "\033[34mshowMachine\033[0m";
    std::cout << std::left << std::setw(nameWidth) << std::setfill(separator) << "Prints info about machines";
    std::cout << std::left << std::setw(nameWidth) << std::setfill(separator) << "\033[34mshowMachine\033[0m";
}

void Core::assignJob(Product *product, int quantity) {
    materialReqList materialList = product->getMaterialRequirements();
    int reqMaterialCount = 0;
    int canAssing = 0;

    for(const auto material : materialList){
        std::string materialName = material.first->getName();
        if(m_warehouse->checkMaterial(materialName)){
            if(m_warehouse->getMaterialAmount(materialName) >= material.second * quantity){
                canAssing++;
            }
        }
        reqMaterialCount++;
    }

    if(reqMaterialCount == canAssing) {
        m_production->createProduct(product,quantity);

        for(const auto material : materialList){
            std::string materialName = material.first->getName();
                m_warehouse->setMaterialAmount(materialName,material.second * quantity);
        }
    }else{
        std::cout << "\033[31mYou don't meet material requirements for this job.\033[0m" << std::endl;
        m_production->printProductReq(product, quantity);
    }
}

void Core::transferProducts() {
    std::map<Product*, int> products = m_production->getFinishedProducts();
    for(const auto product:products){
        m_warehouse->addToProductsCluster(product.first->getId(),product.second);
    }
}
