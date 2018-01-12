//
// Created by ermakoy on 21.09.17.
//

#include "exeptions.h"

std::string exc_io::what() {
    return "I can't find file";
}

std::string exc_param::what() {
    return "Invalid pair of Name-Parametr";
}
