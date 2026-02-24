#ifndef COMMAND_LOGIC_HPP
#define COMMAND_LOGIC_HPP

#define PATH "data/db.csv"

#include "game_repository.hpp"
#include "app_state.hpp"
#include <string>


namespace logic{
    void main_window_logic(
        AppState& app_state, 
        Kvector<std::string> commands
    ){
        if(commands.len() != 1){
            app_state.error_msg = "Command not found!!";
            return;
        }
        if(commands[0] == "add"){
            app_state.window = register_window;
        }else if (commands[0] == "list"){
            app_state.window = list_window;
        }else if(commands[0] == "save"){
            save_games_list(app_state.list, PATH);
            app_state.actual_size = app_state.list.len();
        }else if(commands[0] == "help"){
            app_state.window = help_window;
        }else if(commands[0] == "exit"){
            app_state.is_running = false;
        }else{
            app_state.error_msg = "Command not found!!";
        }
    }

    void list_window_logic(
        AppState& app_state,
        Kvector<std::string> commands
    ){
        std::string st_with_space = "";
        if (commands.len() == 1 && commands[0] == "back"){
            app_state.window = main_window;
            app_state.printable_list = app_state.list;
        }if(commands.len() > 3 && (commands[2] != "-gt" && commands[2] != "-lt") && commands[0] == "search"){
            st_with_space.append(commands[2]);
            for(auto i = 3; i < commands.len(); i++)
                st_with_space.append(" " + commands[i]);

        }if(commands.len() == 3 || st_with_space != ""){
            if(commands[0] == "edit" && commands[1] == "-id"){
                if (!isNumeric(commands[2])){
                    app_state.error_msg = "Not a valid value!";
                    return;
                }
                int edit_id = std::stoi(commands[2]);
                int current_index = app_state.list.search_id(edit_id);
                if (current_index == -1) {
                    app_state.error_msg = "ID not found";
                }
                app_state.window = Window::edit_window;
                app_state.edit_index = current_index;
            }else if(commands[0] == "delete" && commands[1] == "-id"){
                if (!isNumeric(commands[2])){
                    app_state.error_msg = "Not a valid value!";
                    return;
                }
                int edit_id = std::stoi(commands[2]);
                int current_index = app_state.list.search_id(edit_id);
                if (current_index == -1){
                    app_state.error_msg = "ID not found";
                }else{
                    app_state.list.remove_game(current_index);
                    app_state.printable_list = app_state.list;
                }
            }else if(commands[0] == "search"){
                if(commands[1] == "-name"){
                    auto x = commands[2];
                    app_state.printable_list = app_state.list.filter([x, st_with_space](Game game){
                        if (st_with_space != "");
                            return st_to_compare(st_with_space) == st_to_compare(game.name);
                        return st_to_compare(x) == st_to_compare(game.name);
                    });
                }else if(commands[1] == "-publisher"){
                    auto x = commands[2];
                    app_state.printable_list = app_state.list.filter([x, st_with_space](Game game){
                        if (st_with_space != "")
                            return st_to_compare(st_with_space) == st_to_compare(game.publisher);
                        return st_to_compare(x) == st_to_compare(game.publisher);
                    });
                }else if(commands[1] == "-id"){
                    if (!isNumeric(commands[2])){
                        app_state.error_msg = "Not a valid value!";
                        return;
                    }
                    auto x = commands[2];
                    app_state.printable_list = app_state.list.filter([x](Game game){
                        return std::stoi(x) == game.id;
                    });
                }else if(commands[1] == "-year"){
                    if (!isNumeric(commands[2])){
                        app_state.error_msg = "Not a valid value!";
                        return;
                    }
                    auto x = commands[2];
                    app_state.printable_list = app_state.list.filter([x](Game game){
                        return std::stoi(x) == game.year;
                    });
                }else if(commands[1] == "-price"){
                    if (!isNumeric(commands[2])){
                        app_state.error_msg = "Not a valid value!";
                        return;
                    }
                    auto x = commands[2];
                    app_state.printable_list = app_state.list.filter([x](Game game){
                        float epsilon = 0.00001f;
                        return std::fabs(std::stod(x) - (game.price)) < epsilon;
                    });
                }else if(commands[1] == "-rating"){
                    if (!isNumeric(commands[2])){
                        app_state.error_msg = "Not a valid value!";
                        return;
                    }
                    auto x = commands[2];
                    app_state.printable_list = app_state.list.filter([x](Game game){
                        return std::stoi(x) == game.rating;
                    });
                }else{
                    app_state.error_msg = "Command not found!";
                }
            }else{
                app_state.error_msg = "Command not found!";
            }
        }else if(commands.len() == 4 && st_with_space == ""  && commands[0] == "search" ){
            if (!isNumeric(commands[3])){
                app_state.error_msg = "Not a valid value!";
                return;
            }
            if(commands[1] == "-price"){
                auto x = commands[3];
                if (commands[2] == "-lt")
                    app_state.printable_list = app_state.list.filter([x](Game game){
                        return std::stod(x) > game.price;
                    });
                else if (commands[2] == "-gt")
                    app_state.printable_list = app_state.list.filter([x](Game game){
                        return std::stod(x) < game.price;
                    });
                else{
                    app_state.error_msg = "Command not found!";
                    return;
                }
            }else if(commands[1] == "-year"){
                auto x = commands[3];
                if (commands[2] == "-lt")
                    app_state.printable_list = app_state.list.filter([x](Game game){
                        return std::stoi(x) > game.year;
                    });
                else if (commands[2] == "-gt")
                    app_state.printable_list = app_state.list.filter([x](Game game){
                        return std::stoi(x) < game.year;
                    });
                else{
                    app_state.error_msg = "Command not found!";
                    return;
                }
            }else if(commands[1] == "-id"){
                auto x = commands[3];
                if (commands[2] == "-lt")
                    app_state.printable_list = app_state.list.filter([x](Game game){
                        return std::stoi(x) > game.id;
                    });
                else if (commands[2] == "-gt")
                    app_state.printable_list = app_state.list.filter([x](Game game){
                        return std::stoi(x) < game.id;
                    });
                else{
                    app_state.error_msg = "Command not found!";
                    return;
                }
            }else if (commands[1] == "-rating"){
                auto x = commands[3];
                if (commands[2] == "-lt")
                    app_state.printable_list = app_state.list.filter([x](Game game){
                        return std::stoi(x) > game.rating;
                    });
                else if (commands[2] == "-gt")
                    app_state.printable_list = app_state.list.filter([x](Game game){
                        return std::stoi(x) < game.rating;
                    });
                else{
                    app_state.error_msg = "Command not found!";
                    return;
                }
            }else{
                app_state.error_msg = "Command not found!";
            }

        }
        else if (commands.len() == 2 && commands[1] == "-clean"){
            app_state.printable_list = app_state.list;
        }else{
            app_state.error_msg = "Command not found!";
        }
    }

    void register_window_logic(
        AppState& app_stats,
        Kvector<std::string> commands
    ){
        if(commands.len() != 1){
            Kvector<std::string> fields = split_string(commands[0], ':');
            if ((fields[0] != "name" || fields[0] != "publisher") && fields.len() != 2){
                app_stats.error_msg = "Command not found!";
                return;
            }
            std::string field = "";
            field += fields[1];
            for(size_t i = 1; i < commands.len(); i ++){
                field += " " + commands[i];
            }
            if (fields[0] == "name"){
                auto valid_name = app_stats.list.valid_name(field);
                if (valid_name.is_ok()){
                    app_stats.new_register_game.name = field;
                }else{
                    app_stats.error_msg = *valid_name.get_err();
                }
            }else{
                app_stats.new_register_game.publisher = field;
            }
            return;
        }
        if (commands[0] == "save" && !app_stats.new_register_game.is_default()){
            app_stats.list.add_game(app_stats.new_register_game);
            app_stats.printable_list = app_stats.list;            
            app_stats.new_register_game.clean();
        }else if(commands[0] == "back"){
            app_stats.window = main_window;
            app_stats.new_register_game.clean();
        }else{
            Kvector<std::string> fields = split_string(commands[0], ':');
            if (fields.len() != 2){
                app_stats.error_msg = "Command not found!";
                return;
            }
            if (fields[0] == "id"){
                if (!isNumeric(fields[1])){
                    app_stats.error_msg = "Not a valid value!";
                    return;
                }
                auto valid_id = app_stats.list.valid_id(std::stoi(fields[1]));
                if (valid_id.is_ok()){
                    app_stats.new_register_game.id = std::stoi(fields[1]);
                }else{
                    app_stats.error_msg = *valid_id.get_err();
                    return;
                }
            }else if(fields[0] == "year"){
                if (!isNumeric(fields[1])){
                    app_stats.error_msg = "Not a valid value!";
                    return;
                }
                app_stats.new_register_game.year = std::stoi(fields[1]);
            }else if(fields[0] == "price"){
                if (!isNumeric(fields[1])){
                    app_stats.error_msg = "Not a valid value!";
                    return;
                }
                app_stats.new_register_game.price = std::stof(fields[1]);
            }else if(fields[0] == "rating"){
                if (!isNumeric(fields[1])){
                    app_stats.error_msg = "Not a valid value!";
                    return;
                }
                app_stats.new_register_game.rating = std::stoi(fields[1]);
            }else if(fields[0] == "name"){
                auto valid_name = app_stats.list.valid_name(fields[1]);
                if (valid_name.is_ok()){
                    app_stats.new_register_game.name = fields[1];
                }else{
                    app_stats.error_msg = *valid_name.get_err();
                    return;
                }   
            }else if(fields[0] == "publisher"){
                app_stats.new_register_game.publisher = fields[1];
            }else{
                app_stats.error_msg = "Command not found!";
                return;
            }
        }
    }

    void edit_window_logic(
        AppState& app_stats, 
        Kvector<std::string> commands
    ){
        if(commands.len() != 1){
            Kvector<std::string> fields = split_string(commands[0], ':');
            if ((fields[0] != "name" || fields[0] != "publisher") && fields.len() != 2){
                app_stats.error_msg = "Command not found!";
                return;
            }
            std::string field = "";
            field += fields[1];
            for(size_t i = 1; i < commands.len(); i ++){
                field += " " + commands[i];
            }
            if (fields[0] == "name"){
                auto valid_name = app_stats.list.valid_name(field);
                if (valid_name.is_ok() || st_to_compare(field) == st_to_compare(app_stats.list[app_stats.edit_index].name)){
                    app_stats.new_register_game.name = field;
                }else{
                    app_stats.error_msg = *valid_name.get_err();
                }
            }else{
                app_stats.new_register_game.publisher = field;
            }
            return;
        }
        if (commands[0] == "save"){
            app_stats.window = list_window;
            app_stats.list[app_stats.edit_index].rating = (app_stats.new_register_game.field_is_default("rating")) ? app_stats.list[app_stats.edit_index].rating : app_stats.new_register_game.rating;
            app_stats.list[app_stats.edit_index].name = (app_stats.new_register_game.field_is_default("name")) ? app_stats.list[app_stats.edit_index].name : app_stats.new_register_game.name;
             app_stats.list[app_stats.edit_index].year = (app_stats.new_register_game.field_is_default("year")) ? app_stats.list[app_stats.edit_index].year : app_stats.new_register_game.year;
            app_stats.list[app_stats.edit_index].price = (app_stats.new_register_game.field_is_default("price")) ? app_stats.list[app_stats.edit_index].price : app_stats.new_register_game.price;
            app_stats.list[app_stats.edit_index].publisher = (app_stats.new_register_game.field_is_default("publisher")) ? app_stats.list[app_stats.edit_index].publisher : app_stats.new_register_game.publisher;
            app_stats.edit_index = -1;
            app_stats.new_register_game.clean();
        }else if(commands[0] == "back"){
            app_stats.window = list_window;
            app_stats.edit_index = -1;
            app_stats.new_register_game.clean();
        }else{
            Kvector<std::string> fields = split_string(commands[0], ':');
            if (fields.len() != 2){
                app_stats.error_msg = "Command not found!";
                return;
            }else if(fields[0] == "year"){
                if (!isNumeric(fields[1])){
                    app_stats.error_msg = "Not a valid value!";
                    return;
                }
                app_stats.new_register_game.year = std::stoi(fields[1]);
            }else if(fields[0] == "price"){
                if (!isNumeric(fields[1])){
                    app_stats.error_msg = "Not a valid value!";
                    return;
                }
                app_stats.new_register_game.price = std::stof(fields[1]);
            }else if(fields[0] == "rating"){
                if (!isNumeric(fields[1])){
                    app_stats.error_msg = "Not a valid value!";
                    return;
                }
                app_stats.new_register_game.rating = std::stoi(fields[1]);
            }else if(fields[0] == "name"){
                auto valid_name = app_stats.list.valid_name(fields[1]);
                if (valid_name.is_ok() || st_to_compare(fields[1]) == st_to_compare(app_stats.list[app_stats.edit_index].name)){
                    app_stats.new_register_game.name = fields[1];
                }else{
                    app_stats.error_msg = *valid_name.get_err();
                    return;
                }   
            }else if(fields[0] == "publisher"){
                app_stats.new_register_game.publisher = fields[1];
            }else{
                app_stats.error_msg = "Command not found!";
                return;
            }
        }
    }

    void help_window_logic(AppState& app_state, Kvector<std::string> commands){
        if(commands.len() == 1 && commands[0] == "back"){
            app_state.window = Window::main_window;
        }else{
            app_state.error_msg = "Command not found!";
        }
    }

    void window_logic(
        AppState& app_state, 
        Kvector<std::string> commands
    ){
        app_state.error_msg = "";
        switch(app_state.window){
        case main_window:
            main_window_logic(
                app_state, 
                commands
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
                app_state,
                commands
            );
            break;
        case help_window:
            help_window_logic(
                app_state,
                commands
            );
            break;
        default:
            break;
        }
    }
}


#endif