#ifndef APP_HPP
#define APP_HPP

#include "game.hpp"
#include "kvector.hpp"
#include "result.hpp"
#include "ui.hpp"
#include "parser.hpp"
#include <iostream>

#define PATH "data/db.csv"

// Identifica a janela atual do app
enum Window{main_window, list_window, register_window, edit_window, help_window};

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
            }
            while(is_running){
                Ui::clean();
                switch (window){
                    case main_window:
                        Ui::draw_main_window();
                        break;
                    case list_window:
                        break;
                    case register_window:
                        break;
                    case edit_window:
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
        // Mensagens de erros importantes 
        std::string error_msg = "";
        // Status do app
        bool is_running = true;
        bool is_saved = false;

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
                            is_saved = true;
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
                    break;
                case register_window:
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
