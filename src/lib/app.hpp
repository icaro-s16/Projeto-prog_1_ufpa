#ifndef APP_HPP
#define APP_HPP

#include "game.hpp"
#include "kvector.hpp"
#include "result.hpp"
#include "parser.hpp"
#include "ui.hpp"
#include "app_state.hpp"
#include "command_logic.hpp"


#define PATH "data/db.csv"



class App{
    public:
        App(){}
        
        void run(){
            std::string buffer;
            Kvector<std::string> commands;
            // Inicia a lista de jogos e checa possíveis erros
            Result<std::string, std::string> result = variables.list.init_games_list(PATH);
            if (result.is_err()){
                variables.error_msg = *result.get_err();
            }else{
                variables.actual_size = variables.list.len();
            }
            while(is_running){
                Ui::draw_window(variables);
                std::cout<<">>";
                std::getline(std::cin, buffer);
                commands = split_string(buffer, ' ');
                logic::window_logic(
                    variables, 
                    commands, 
                    is_running
                );
                
            };
        }

    private :
        AppState variables;
        // Status do app
        bool is_running = true;
};


#endif
