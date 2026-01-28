#ifndef COMMAND_LOGIC_HPP
#define COMMAND_LOGIC_HPP

#define PATH "data/db.csv"

#include "app_state.hpp"
#include <string>

namespace logic{
    void main_window_logic(
        AppState& app_state, 
        Kvector<std::string> commands,
        bool& is_running
    ){
        if(commands.len() != 1){
            app_state.error_msg = "Command not found!";
            return;
        }
        if(commands[0] == "add"){
            app_state.window = register_window;
        }else if (commands[0] == "list"){
            app_state.window = list_window;
        }else if(commands[0] == "save"){
            app_state.list.save_games_list(PATH);
            app_state.actual_size = app_state.list.len();
        }else if(commands[0] == "help"){
            app_state.window = help_window;
        }else if(commands[0] == "exit"){
            is_running = false;
        }else{
            app_state.error_msg = "command not found!";
        }
    }

    void list_window_logic(
        AppState& app_state,
        Kvector<std::string> commands
    ){
        if (commands.len() == 1 && commands[0] == "back"){
            app_state.window = main_window;
        }else if(commands.len() == 3){
            if(commands[0] == "edit"){

            }else if(commands[0] == "filter"){

            }
        }else{
            app_state.error_msg = "Command not found";
        }
    }

    void register_window_logic(
        AppState& var,
        Kvector<std::string> commands
    ){
        if(commands.len() != 1){
            Kvector<std::string> fields = split_string(commands[0], ':');
            if ((fields[0] != "name" || fields[0] != "company") && fields.len() != 2){
                var.error_msg = "Command not found";
                return;
            }
            std::string field = "";
            field += fields[1];
            for(size_t i = 1; i < commands.len(); i ++){
                field += " " + commands[i];
            }
            if (fields[0] == "name"){
                var.new_register_game.name = field;
            }else{
                var.new_register_game.publisher = field;
            }
            return;
        }
        if (commands[0] == "save" && var.new_register_game.can_be_saved()){
            var.list.add_game(var.new_register_game);
            var.new_register_game.clean();
        }else if(commands[0] == "back"){
            var.window = main_window;
            var.new_register_game.clean();
        }else{
            Kvector<std::string> fields = split_string(commands[0], ':');
            if (fields.len() != 2){
                var.error_msg = "Command not found";
                return;
            }
            if (fields[0] == "id"){
                var.new_register_game.id = std::stoi(fields[1]);
            }else if(fields[0] == "year"){
                var.new_register_game.year = std::stoi(fields[1]);
            }else if(fields[0] == "price"){
                var.new_register_game.price = std::stof(fields[1]);
            }else if(fields[0] == "rating"){
                var.new_register_game.avaliation = std::stoi(fields[1]);
            }else if(fields[0] == "name"){
                var.new_register_game.name = fields[1];   
            }else if(fields[0] == "company"){
                var.new_register_game.publisher = fields[1];
            }else{
                var.error_msg = "Command not found";
            }
        }
    }

    void edit_window_logic(AppState& app_state){

    }

    void help_window_logic(AppState& app_state){

    }

    void window_logic(
        AppState& app_state, 
        Kvector<std::string> commands,
        bool& is_running
    ){
        switch(app_state.window){
            case main_window:
                main_window_logic(
                    app_state, 
                    commands, 
                    is_running
                );
                break;
            case list_window:
                list_window_logic(
                    app_state,
                    commands
                );
                break;
            case register_window:
                register_window_logic(
                    app_state, 
                    commands
                );
                break;
            case edit_window:
                edit_window_logic(
                    app_state
                );
                break;
            case help_window:
                help_window_logic(
                    app_state
                );
                break;
            default:
                break;
        }
    }
}


#endif