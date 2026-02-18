#ifndef APP_STATE_HPP
#define APP_STATE_HPP

#include "game.hpp"

// Identifica a janela atual do app
enum Window{main_window, list_window, register_window, edit_window, help_window};

struct AppState{
    // Inicial, por padrão, na janela principal
    Window window = Window::main_window;
    // Lista de jogos
    GamesList list;
    GamesList printable_list;
    // Usado para checar as alterações
    size_t actual_size = 0;
    // Auxiliar de registro
    Game new_register_game;
    // Mensagens de erros importantes 
    std::string error_msg = "";
    // Usado para editar o valor
    int edit_index = -1;

    bool is_running = true;
};

#endif 