#include "ui.hpp"
#include "parser.hpp"
#include "Kvector.hpp"
#include <iostream>

int main(){
    std::string s = "icaro  santos santana";
    auto v = split_string(s, ' ');
    std::cout << v[1] << std::endl;
    return 0;
}