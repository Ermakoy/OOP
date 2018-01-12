//
// Created by ermakoy on 21.09.17.
//

#ifndef UNTITLED_EXEPTIONS_H
#define UNTITLED_EXEPTIONS_H

#include "string"
#include <exception>
using namespace std;

class exc_io : public exception {
public:
    string what();
};

class exc_param : public exception {
public:
    string what();
};

#endif //UNTITLED_EXEPTIONS_H
