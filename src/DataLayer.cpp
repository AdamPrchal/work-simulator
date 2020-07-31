//
// Created by adam on 12/22/19.
//

#include "../include/DataLayer.h"

DataLayer::DataLayer() = default;

DataLayer::~DataLayer() = default;

parametersVector DataLayer::load(std::string fileName) {
    if (fileName == "materials" || fileName == "products") {
        parametersVector vectorContainer;
        parametersContainer container;
        std::string line;
        std::ifstream file("../spike/" + fileName + ".ini");        // Find file from which data will be loaded
        if (file.is_open()) {
            while (getline(file, line)) {
                std::vector<std::string> tokens = parseLine(line,'|');
                container = packageParameters(fileName,tokens);
                vectorContainer.push_back(container);
            }
            file.close();
        } else {
            std::cerr << "Unable to open file" << std::endl;
        }

        return vectorContainer;
    } else {
        std::cerr << "Soubor \"" << fileName << "\" nelze nacist. Lze nacist pouze \"materials\" a \"products\""
                  << std::endl;
        return {};
    }
}

std::vector<std::string> DataLayer::parseLine(std::string activeLine, char delimiter) {


    std::vector<std::string> tokens;        // Vector of string to save tokens

    std::stringstream buffer(activeLine);       // Stringstream class used for operating with string

    std::string intermediate;   // String variable used for storing each token at the time and passing it to vector

    while (getline(buffer, intermediate,
                   delimiter)) {        // Tokenizing - getline(whole string , where to put save token , delimiter)
        tokens.push_back(intermediate);
    }
    return tokens;
}

parametersContainer DataLayer::packageParameters(std::string type, std::vector<std::string> it) {
    parametersContainer container;
    if(type == "materials"){
            container.id = std::stoi(it[0]);
            container.name = it[1];
            container.price = std::stoi(it[2]);
    }
    else {
            parsedMaterialsReq materialRequirements = parseMaterialReq(it[3]);
            container.id = std::stoi(it[0]);
            container.name = it[1];
            container.timeRequirement = std::stoi(it[2]);
            container.materialRequirements = materialRequirements;

    }
    return container;
}

parsedMaterialsReq DataLayer::parseMaterialReq(std::string materialReq) {
    parsedMaterialsReq completeList;
    std::vector<std::string> tokensBig = parseLine(materialReq,',');
    for (auto token : tokensBig) {
        std::vector<std::string> tokensSmall = parseLine(token,':');
        completeList.push_back(tokensSmall);
    }
    return completeList;
}