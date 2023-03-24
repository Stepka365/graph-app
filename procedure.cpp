#include "procedure.h"
#include <iostream>

void print_results(weight_t weight, const route_t& route) {
    std::cout << "route: ";
    for (auto elem: route){
        std::cout << elem << ' ';
    }
    std:: cout << "\nweight: " << weight;
}
