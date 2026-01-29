#ifndef PARSER_HPP
#define PARSER_HPP

#include "kvector.hpp"
#include <string>
#include <cctype>

// Função para quebrar uma string em tokens 
Kvector<std::string> split_string(std::string st, char delimiter){
    Kvector<std::string> tokens;
    std::string aux = "";
    for(size_t i = 0; st[i] != '\0'; i++){
        if(st[i] != delimiter){
            aux += st[i];
        }else if(aux != ""){
            tokens.push(aux);
            aux = "";
        }
    }
    if (aux != ""){
        tokens.push(aux);
    }
    return tokens;
}

//Função para retornar a string em caixa baixa para quesito de comparação
std::string st_to_lower(std::string st){
    for (size_t i = 0; st[i] != '\0'; i++){
        if(st[i] != ' '){
            st[i] = std::tolower(st[i]);
        }
    }
    return st;
}


#endif
