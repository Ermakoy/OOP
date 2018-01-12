#include <iostream>
#include <fstream>
#include <thread>
#include "Reader.h"
#include "Factorisator.h"
// I have some struggles with next function. Because reader.threadedFactorise don't want to take native function from class
// ¯\_(ツ)_/¯
std::string threadFunc(uint64_t num){
    Factorisator factorisator;
    return factorisator.factorisationFunction(num);
};

int main() {
    Factorisator factorisator;
    Reader<uint64_t > reader;

    std::string inputFile = "input.txt",
                outputFile = "output.txt";

    int threadsCount = 1;

    reader.threadedFactorise(inputFile,outputFile,threadFunc,threadsCount);
    return 0;
}