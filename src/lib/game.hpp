#ifndef GAME_HPP
#define GAME_HPP

#include <fstream>
#include "kvector.hpp"
#include "result.hpp"
#include <string>
#include "parser.hpp"
#include <cmath>


struct Game
{
    std::string name = "";
    std::string publisher = "";
    float price = 0.0;
    int avaliation = -1 ;
    int year = 0;
    int id = 0;

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

    std::string name_default_template(){
        return (name == "") ? "(empty)" : name;
    }

    std::string id_default_template(){
        return (id == 0) ? "(empty)" : std::to_string(id);
    }

    std::string publisher_default_template(){
        return (publisher == "" ) ? "(empty)" : publisher;
    }
    std::string year_default_template(){
        return (year == 0) ? "(empty)" : std::to_string(year);
    }
    std::string price_default_template(){
        float epsilon = 0.00001f;
        return (std::fabs(price - 0.00) < epsilon) ? "(empty)" : std::to_string(price);
    }
    std::string avaliation_default_template(){
        return (avaliation == -1) ? "(empty)" : std::to_string(avaliation);
    }

    bool can_be_saved(){
        float epsilon = 0.00001f;
        return name != "" && publisher != "" && (std::fabs(price - 0.00) > epsilon) && avaliation != -1 && year != 0 && id != 0;
    }

    void clean(){
        name = "";
        publisher = "";
        price = 0.0;
        avaliation = -1 ;
        year = 0;
        id = 0;        
    }

    bool operator==(Game rhs){
        return this->id == rhs.id || this->name == rhs.name;
    }
    bool operator!=(Game rhs){
        return this->id != rhs.id && this->name != rhs.name;
    }
};

std::string format_game_st(Game game){
    std::string price = std::to_string(game.price);
    std::string avaliation = std::to_string(game.avaliation);
    std::string year = std::to_string(game.year);
    std::string id = std::to_string(game.id);
    return game.name + ";" + game.publisher + ";" + price + ";" + avaliation + ";" + year + ";" + id + "\n";
}



class GamesList{
    public:
        GamesList(){};
        Result<std::string, std::string> init_games_list(std::string path){
            Result<std::string, std::string> status; 
            std::ifstream file(path);
            std::string buffer;
            if (file.bad()){
                file.close();
                status.err("Error type bad file!");
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
                    list.push(game);
                }
            }   
            status.ok("initialization completed!");
            file.close();
            return status;
        }
        Result<std::string, std::string> save_games_list(std::string path){
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

        void add_game(Game game){
            list.push(game);
        }
        void remove_game(size_t index){
            list.remove(index);
        }
        Game& operator[](size_t index){
            return list[index];
        }
        size_t len(){
            return list.len();
        }

    private:
        Kvector<Game> list;
};




#endif 
