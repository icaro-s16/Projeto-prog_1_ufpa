#ifndef APP_HPP
#define APP_HPP

#include "game.hpp"
#include "kvector.hpp"
#include "result.hpp"
#include "parser.hpp"
#include <iostream>

#define PATH "data/db.csv"

// Identifica a janela atual do app
enum Window{main_window, list_window, register_window, edit_window, help_window};

namespace Ui{
    // Método para limpar o terminal
    void clean(){
        #ifdef _WIN32
            std::system("cls");
        #else
            std::system("clear");
        #endif
    }
    // Desenho das telas do app
    void draw_main_window(std::string err_msg, size_t actual_size, GamesList games_list){
        std::cout<<"============================================================\n";
        std::cout<<"            🕹️  G A M E   V A U L T   v 1 . 0\n";
        std::cout<<"============================================================\n";
        std::cout<<"\n\n      [ System is ready. Waiting for commands... ]\n\n\n";
        std::cout<<"------------------------------------------------------------\n";
        std::cout<<" Commands: add | list | save | help | exit\n";
        std::string save_advice =  (actual_size == games_list.len()) ? "Your changes have been saved successfully!" : "You have unsaved changes!";
        std::cout<<" Status: "<< save_advice <<"\n";
        std::cout<<" Errors: "<<err_msg<<"\n";
        std::cout<<"------------------------------------------------------------\n";
    }


    void draw_library_window(GamesList games_list) {
        std::cout << "============================================================" << std::endl;
        std::cout << "                 📋 GAME LIBRARY" << std::endl;
        std::cout << "============================================================" << std::endl;

        for (size_t i = 0; i < games_list.len(); i++){
            std::cout << i+1 <<". [ ID: "<< games_list[i].id << " | NAME: "<< games_list[i].name <<" | DATE: "<<games_list[i].year <<" ]" << std::endl;
            std::cout << "   [ PRICE: "<< games_list[i].price <<" | RATING: "<< games_list[i].avaliation <<" | COMPANY: "<< games_list[i].publisher <<" ]" << std::endl;
        }

        std::cout << " ----------------------------------------------------------" << std::endl;
        std::cout << " [ filter SYNTAX ]" << std::endl;
        std::cout << " > filter -<field> <value>" << std::endl;
        std::cout << "   (Fields: id, name, date, price, rating, company)" << std::endl;
        std::cout << std::endl;
        
        std::cout << " [ ACTIONS ]" << std::endl;
        std::cout << " > edit -id <value> | back" << std::endl;
        std::cout << "------------------------------------------------------------" << std::endl;
    }


    void draw_new_game_window(Game new_register) {
        std::cout << "============================================================" << std::endl;
        std::cout << "               🆕 NEW GAME REGISTRATION" << std::endl;
        std::cout << "============================================================" << std::endl;
    
        std::cout << " [ ID ]        : " << new_register.id_default_template() <<std::endl;
        std::cout << " [ NAME ]      : " << new_register.name_default_template() << std::endl;
        std::cout << " [ YEAR ]      : " << new_register.year_default_template() << std::endl;
        std::cout << " [ PRICE ]     : " << new_register.price_default_template() << std::endl;
        std::cout << " [ RATING ]    : " << new_register.avaliation_default_template() << std::endl;
        std::cout << " [ COMPANY ]   : " << new_register.publisher_default_template() << std::endl;
        
        std::cout << "------------------------------------------------------------" << std::endl;
        std::cout << " [ Fields: id:<value> | name:<value> | year:<value> | price:<value> | rating:<value> | company:<value> ]" << std::endl;
        std::cout << " [ Actions: save | back ]" << std::endl;
    }

    void draw_edit_window() {
        std::cout << "============================================================" << std::endl;
        std::cout << "               📝 EDITING: [ GAME ID #" << " ]" << std::endl;
        std::cout << "============================================================" << std::endl;
        
        std::cout << " CURRENT VALUES:" << std::endl;
        std::cout << " 1. ID:        " << std::endl;
        std::cout << " 2. NAME:      " << std::endl;
        std::cout << " 3. DATE:      " <<  std::endl;
        
        // Fixed to 2 decimal places for price
        std::cout << " 4. PRICE:     "  << std::endl;
        
        // Fixed to 1 decimal place for rating
        std::cout << " 5. RATING:    " << std::endl;
        
        std::cout << " 6. COMPANY:   " << std::endl;
        
        std::cout << "------------------------------------------------------------" << std::endl;
        std::cout << " [ Change using: <field>:<value> | Ex: rating:9.5 ]" << std::endl;
        std::cout << " [ Actions: save (confirm)       | back (cancel)   ]" << std::endl;
    }

};

class App{
    public:
        App(){}
        
        void run(){
            std::string buffer;
            Kvector<std::string> commands;
            // Inicia a lista de jogos e checa possíveis erros
            Result<std::string, std::string> result = list.init_games_list(PATH);
            if (result.is_err()){
                error_msg = *result.get_err();
            }else{
                actual_size = list.len();
            }
            while(is_running){
                Ui::clean();
                switch (window){
                    case main_window:
                        Ui::draw_main_window(error_msg, actual_size, list);
                        break;
                    case list_window:
                        Ui::draw_library_window(list);
                        break;
                    case register_window:
                        Ui::draw_new_game_window(new_register_game);
                        break;
                    case edit_window:
                        Ui::draw_edit_window();
                        break;
                    case help_window:
                        break;
                    default:
                        break;
                }
                std::cout<<">>";
                std::getline(std::cin, buffer);
                commands = split_string(buffer, ' ');
                use_commands(commands);
                
            };
        }

    private :
        // Inicial, por padrão, na janela principal
        Window window = Window::main_window;
        // Lista de jogos
        GamesList list;
        // Usado para checar as alterações
        size_t actual_size = 0;
        // Auxiliar de registro
        Game new_register_game;
        // Mensagens de erros importantes 
        std::string error_msg = "";
        // Status do app
        bool is_running = true;


        void use_commands(Kvector<std::string> commands){
            switch(window){
                case main_window:
                    if(commands.len() == 1){
                        if(commands[0] == "add"){
                            window = register_window;
                        }else if (commands[0] == "list"){
                            window = list_window;
                        }else if(commands[0] == "save"){
                            list.save_games_list(PATH);
                            actual_size = list.len();
                        }else if(commands[0] == "help"){
                            window = help_window;
                        }else if(commands[0] == "exit"){
                            is_running = false;
                        }else{
                            error_msg = "command not found!";
                        }
                    }else{
                        error_msg = "Command not found!";
                    }
                    
                    break;
                case list_window:
                    if (commands.len() == 1 && commands[0] == "back"){
                        window = main_window;
                    }else if(commands.len() == 3){
                        if(commands[0] == "edit"){

                        }else if(commands[0] == "filter"){

                        }
                    }else{
                        error_msg = "Command not found";
                    }
                    break;
                case register_window:
                    if (commands.len() == 1){
                        if (commands[0] == "save" && new_register_game.can_be_saved()){
                            list.add_game(new_register_game);
                            new_register_game.clean();
                        }else if(commands[0] == "back"){
                            window = main_window;
                            new_register_game.clean();
                        }else{
                            Kvector<std::string> fields = split_string(commands[0], ':');
                            if (fields.len() == 2){
                                if (fields[0] == "id"){
                                    new_register_game.id = std::stoi(fields[1]);
                                }else if(fields[0] == "year"){
                                    new_register_game.year = std::stoi(fields[1]);
                                }else if(fields[0] == "price"){
                                    new_register_game.price = std::stof(fields[1]);
                                }else if(fields[0] == "rating"){
                                    new_register_game.avaliation = std::stoi(fields[1]);
                                }else if(fields[0] == "name"){
                                    new_register_game.name = fields[1];   
                                }else if(fields[0] == "company"){
                                    new_register_game.publisher = fields[1];
                                }else{
                                    error_msg = "Command not found";
                                }
                            }else{
                                error_msg = "Command not found";
                            }
                        }
                    }else{
                        Kvector<std::string> fields = split_string(commands[0], ':');
                        if ((fields[0] == "name" || fields[0] == "company") && fields.len() == 2){
                            std::string field = "";
                            field += fields[1];
                            for(size_t i = 1; i < commands.len(); i ++){
                                field += " " + commands[i];
                            }
                            if (fields[0] == "name"){
                                new_register_game.name = field;
                            }else{
                                new_register_game.publisher = field;
                            }
                        }else{ 
                            error_msg = "Command not found";
                        }
                    }
                    break;
                case edit_window:
                    break;
                case help_window:
                    break;
                default:
                    break;
            }
        }
};


#endif
