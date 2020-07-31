#include <iostream>
#include "../include/Core.h"


int main() {

    Core* core = new Core();
    core->initialize();
    core->run();
    delete (core);
    return 0;
}
