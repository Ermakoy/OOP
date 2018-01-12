#include <iostream>
#include "Vector.h"
int main() {
    Vector<int> vector(1,123);
    Vector<int> v2(vector);
    std::cout<<vector[0];
    return 0;
}