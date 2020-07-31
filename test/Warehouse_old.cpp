//
// Created by Jacob Derynk on 17/12/2019.
//

/// This file only contains initialization of materials and products cluster that had been used in Warehouse.cpp before it was moved to Initialization.cpp



/// Warehouse.hpp

//    static materialsVector materialsVectorInitialization();     //static bc why not.. like what if we need that damn vector before Warehouse init?
//
//    void materialsClusterInitialization();
//
//    static productsVector productsVectorInitialization();       //static bc why not.. like what if we need that damn vector before Warehouse init?
//
//    void productsClusterInitialization();



/// Warehouse constructor:

//    materialsVectorInitialization();    //creating vector of materials here
//    materialsClusterInitialization();   //creating map of materials /w amount here
//
//    productsVectorInitialization();     //creating vector of products here
//    productsClusterInitialization();    //creating map of products /w amount here



//materialsVector Warehouse::materialsVectorInitialization() {    // creating vector of Materials using initialization of globalResources vector
//
//    materialsVector materialVectorInit;
//    Initialization* init = new Initialization();
//    resourceVector globalMaterials = init ->loadVector("materials");   // loading materials from *.ini file to global vector
//
//    for(int i = 0; i < globalMaterials.size(); i++){
//        materialVectorInit.push_back((Material*)globalMaterials.at(i));     // loading materials from global vector to vector of materials
//    }
//
//    delete init;
//    return materialVectorInit;
//}
//
//productsVector Warehouse::productsVectorInitialization() {  // creating vector of Products using initialization of globalResources vector --same as Materials--
//
//    productsVector productVectorInit;
//    Initialization* init = new Initialization();
//    resourceVector globalMaterials = init ->loadVector("products");
//
//    for(int i = 0; i < globalMaterials.size(); i++){
//        productVectorInit.push_back((Product*)globalMaterials.at(i));
//    }
//
//    delete init;
//    return productVectorInit;
//}
//
//void Warehouse::materialsClusterInitialization() {      // creating map of Materials here
//
//    materialsVector vector = materialsVectorInitialization();   // calling above methods
//    for (int i = 0; i < vector.size();){
//        for (auto const &x : vector) {      //for whole vector of Materials
//            Material* material_temp = vector.at(i);     // temporary holding Material here
//            m_materialsCluster.insert(std::pair<Material*, int> (material_temp, 69));       // inserting material with generated amount into map
//            i++;                                                                                    //TODO: generating rand nu. or 0
//        }
//    };
//}
//
//void Warehouse::productsClusterInitialization() {   // creating map of Products here --same as Materials--
//
//    productsVector vector = productsVectorInitialization();
//    for (int i = 0; i < vector.size();){
//        for (auto const &x : vector) {
//            Product* product_temp = vector.at(i);
//            m_productsCluster.insert(std::pair<Product*, int> (product_temp, 1));
//            i++;
//        }
//    };
//}

