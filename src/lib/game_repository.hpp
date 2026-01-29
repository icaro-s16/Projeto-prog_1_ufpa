#ifndef GAME_REPOSITORY_HPP
#define GAME_REPOSITORY_HPP

#include "kvector.hpp"
#include "result.hpp"
#include "game.hpp"
#include "parser.hpp"
#include <fstream>
#include <string>



Result<GamesList, std::string> init_games_list(std::string path){
    Result<GamesList, std::string> status; 
    GamesList list;
    std::ifstream file(path);
    std::string buffer;
    if (!file.is_open()){
        file.close();
        status.err("Fail to open the file!");
        return status;
    }
    // Descarta o header csv do arquivo
    std::getline(file, buffer);
    buffer = "";
    while(std::getline(file, buffer)){
        Kvector<std::string> tokens;
        tokens = split_string(buffer, ';');
        if (tokens.len() == 6){
            Game game(
                tokens[0],
                tokens[1],
                std::stof(tokens[2]),
                std::stoi(tokens[3]),
                std::stoi(tokens[4]),
                std::stoi(tokens[5])
            );
            list.add_game(game);
        }
    }   
    status.ok(list);
    file.close();
    return status;
}
Result<std::string, std::string> save_games_list(GamesList list, std::string path){
    Result<std::string, std::string> status;
    std::ofstream file(path);
    std::string header = "# name;publisher;price;avaliation;year;id\n";
    if (file.bad()){
        status.err("Error type bad file!");
        file.close();
        return status;
    }
    file << header;
    for(size_t i = 0; i < list.len(); i++){
        file << format_game_st(list[i]);
    }
    status.ok("save completed!");
    return status;
}

#endif