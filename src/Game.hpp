#ifndef GAME_HPP
#define GAME_HPP

#include <fstream>
#include "Kvector.hpp"
#include "Result.hpp"
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
        ListGames(){}
        void add_game(Game game){
            list.push(game);
        }
        Result<std::string, std::string> save_games(std::string file_path){
            Result<std::string, std::string> return_value;            
            std::ofstream file(file_path, std::ios::app);
            if (!file.is_open()) { // Verifica se o arquivo foi aberto corretamento
                return_value.err("Não foi possível salvar a lista");
                return return_value;
            } else {
                // Itera sobre cada posição do vetor e os salva no arquivo
                for (size_t i = 0; i < list.len(); i++) {
                    file << list[i].name << ";" 
                        << list[i].publisher << ";" 
                        << list[i].avaliation << ";" 
                        << list[i].price << ";" 
                        << list[i].year << std::endl;
                }

                file.close();
                return_value.ok("A lista foi salva com sucesso");
                return return_value;
            }
        }
    private:
        Kvector<Game> list;
};

#endif GAME_HPP