#pragma once

#include "fsm.hpp"
#include <string>
#include <iostream>
#include <fstream>

namespace fsm_export {

template<typename T>
void to_ppm(const FSM<T>& fsm, const std::string& filename) {
    if (!fsm.is_valid()) {
        std::cerr << "not a valid FSM" << std::endl;
        return;
    }

    std::ofstream file(filename + ".ppm", std::ofstream::binary);
    if (!file.is_open()) {
        std::cerr << "cannot open the file: " << filename << ".ppm" << std::endl;
        return;
    }

    file << "P3" << std::endl;
    file << "500 500" << std::endl;
    file.close();
}

}