#ifndef PARSER_HPP
#define PARSER_HPP

#include "Kvector.hpp"
#include <iostream>

// Função para quebrar uma string em tokens 
Kvector<std::string> split_string(std::string st, char delimiter){
    Kvector<std::string> tokens;
    std::string aux = "";
    for(size_t i = 0; i < st.length(); i++){
        if(st[i] != delimiter){
            aux += st[i];
        }else if(aux != ""){
            tokens.push(aux);
            aux = "";
        }
    }
    return tokens;
}



#endif