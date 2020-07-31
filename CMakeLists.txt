cmake_minimum_required(VERSION 3.15)
project(projectItem)

set(CMAKE_CXX_STANDARD 17)

add_executable(projectItem src/main.cpp src/Initialization.cpp include/Initialization.h src/Warehouse.cpp include/Warehouse.hpp src/Product.cpp include/Product.h src/Production.cpp include/Production.h src/Machine.cpp include/Machine.h src/Material.cpp include/Material.h src/Resource.cpp include/Resource.h src/Core.cpp include/Core.h src/DataLayer.cpp include/DataLayer.h src/Marketplace.cpp include/Marketplace.h src/TimeMachine.cpp include/TimeMachine.h)