//
// Created by loumtechnologies on 4/24/2024.
//

#include "API.h"
#include <print>
#include <iostream>

namespace API {
    void sendEvent(std::string str) {
        std::print("{0}", str);
        std::flush(std::cout);
    }
}