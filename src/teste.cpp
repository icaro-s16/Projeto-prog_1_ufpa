#include "lib/ui.hpp"
#include "lib/parser.hpp"
#include "lib/kvector.hpp"
#include "lib/result.hpp"
#include "lib/game.hpp"
#include <iostream>

int main(){
    ListGames teste_1;
    teste_1.add_game(Game("fallout 4", "bethesda", 100.00, 10, 2014, 1));
    auto t = teste_1.save_db("db.csv");
    if (t.is_ok()){
        std::cout << "tudo ok" << std::endl;
    }
    std::string s = "icaro;santos;santana";
    auto v = split_string(s, ';');
    std::cout << v[0] << std::endl;
    return 0;
}
