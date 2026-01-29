#ifndef APP_HPP
#define APP_HPP

#include "game.hpp"
#include "kvector.hpp"
#include "result.hpp"
#include "parser.hpp"
#include "ui.hpp"
#include "app_state.hpp"
#include "command_logic.hpp"
#include "game_repository.hpp"




class App{
    public:
        App(){}
        
        void run(){
            std::string buffer;
            Kvector<std::string> commands;
            // Inicia a lista de jogos e checa possíveis erros
            Result<GamesList, std::string> result = init_games_list(PATH);
            if (result.is_err()){
                app_state.error_msg = *result.get_err();
            }else{
                app_state.list = *result.get_ok();
            }
            while(is_running){
                Ui::draw_window(app_state);
                std::cout<<">>";
                std::getline(std::cin, buffer);
                commands = split_string(buffer, ' ');
                logic::window_logic(
                    app_state, 
                    commands, 
                    is_running
                );
            };
        }

    private :
        AppState app_state;
        // Status do app
        bool is_running = true;
};


#endif
