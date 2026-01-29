#ifndef GAME_HPP
#define GAME_HPP

#include "kvector.hpp"
#include "result.hpp"
#include "parser.hpp"
#include <string>
#include <cmath>
#include <iomanip>


struct Game
{
    std::string name = "";
    std::string publisher = "";
    float price = -1.0;
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
        std::ostringstream formated_price;
        formated_price << std::fixed << std::setprecision(2) << price; 
        return (std::fabs(price - (-1.00)) < epsilon) ? "(empty)" : "R$ " + formated_price.str();
    }
    std::string avaliation_default_template(){
        return (avaliation == -1) ? "(empty)" : std::to_string(avaliation);
    }

    bool is_default(){
            float epsilon = 0.00001f;
            return name == "" &&
                publisher == "" && 
                (std::fabs(price - (-1.00)) < epsilon) && 
                avaliation == -1 && 
                year == 0 && 
                id == 0;
    }

    void clean(){
        name = "";
        publisher = "";
        price = -1.0;
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
        GamesList():list(Kvector<Game>()){};


        Result<std::string, std::string> valid_id(int id){
            Result<std::string, std::string> result;
            for(size_t i = 0; i < list.len(); i++){
                if (list[i].id == id){
                    result.err("ID already registered");
                    return result;
                }
            }
            
            result.ok("Valid field");
            return result;
        }
        Result<std::string, std::string> valid_name(std::string name){
            Result<std::string, std::string> result;
            for(size_t i = 0; i < list.len(); i++){
                if (st_to_lower(list[i].name) == st_to_lower(name)){
                    result.err("Name already registered");
                    return result;
                }
            }
            
            result.ok("Valid field");
            return result;
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
