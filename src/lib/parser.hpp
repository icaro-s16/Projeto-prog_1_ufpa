#ifndef PARSER_HPP
#define PARSER_HPP

#include "kvector.hpp"
#include <string>
#include <cctype>
#include <stdexcept>

bool isNumeric(const std::string& s) {
    if (s.empty()) return false;
    try {
        std::stod(s); // Tenta converter para double
        return true;
    } catch (const std::invalid_argument& e) {
        return false; // Nenhuma conversão possível
    } catch (const std::out_of_range& e) {
        return false; // Valor muito grande/pequeno
    }
}

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
std::string st_to_compare(std::string st){
    std::string st_c = "";
    for (size_t i = 0 ; st[i] != '\0'; i++){
        if(st[i] != ' '){
            st_c += std::tolower(st[i]);
        }
    }
    return st_c;
}


#endif
