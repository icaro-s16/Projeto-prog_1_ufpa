#ifndef GAME_HPP
#define GAME_HPP

#include <fstream>
#include "kvector.hpp"
#include "result.hpp"
#include <string>

struct Game
{
    std::string name;
    std::string publisher;
    float price;
    int avaliation;
    int year;
    int id;
    // Constructor Default
    Game(){}
    // Constructor Preenchido, 
    Game(
        std::string new_name, 
        std::string new_publisher, 
        float new_price,
        int new_avaliation,
        int new_year,
        int new_id
    ) : 
    name(new_name), 
    publisher(new_publisher), 
    price(new_price),
    avaliation(new_avaliation),
    year(new_year),
    id(new_id){}
};

class ListGames{
    public:
        ListGames(){};

        void add_game(Game game){
            list.push(game);
        }

    private:
        Kvector<Game> list;
};

#endif GAME_HPP