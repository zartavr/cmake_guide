#include "lib.h"
#include "config.h"

#include <iostream>

namespace lib {

    int makeSomeSuperJob() {
        std::cout << "Hello from lib!" << std::endl;
        return 42;
    }
    
    int sum(int a, int b){
        return a + b;
    }

    int getVersion() {
        return (PROJECT_VERSION);
    }

}