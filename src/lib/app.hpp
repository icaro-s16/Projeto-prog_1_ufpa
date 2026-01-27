#ifndef APP_HPP
#define APP_HPP

#include "kvector.hpp"
#include "result.hpp"
#include "ui.hpp"
#include <iostream>

// Identifica a janela atual do app
enum Window{main_window, list_window, register_window, edit_window, notice_window};

class App{
    public:
        App(){}
        
        void run(){
            Ui::clean();
            while(true){
                switch (window){
                case main_window:
                    break;
                case list_window:
                    break;
                case register_window:
                    break;
                case edit_window:
                    break;
                case notice_window:
                    break;
                default:
                    break;
                }

            }
        }

    private :
    // Inicial, por padrão, na janela principal
    Window window = Window::main_window;
};


#endif APP_HPP