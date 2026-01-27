#include "lib/ui.hpp"
#include "lib/parser.hpp"
#include "lib/kvector.hpp"
#include <iostream>

int main(){
    std::string s = "icaro;santos;santana";
    auto v = split_string(s, ';');
    std::cout << v[0] << std::endl;
    return 0;
}