#ifndef UI_HPP
#define UI_HPP

#include <iostream>
#include <cstdlib>

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
    void draw_main_window(){
        std::cout<<"============================================================\n";
        std::cout<<"            🕹️  G A M E   V A U L T   v 1 . 0\n";
        std::cout<<"============================================================\n";
        std::cout<<"\n\n      [ System is ready. Waiting for commands... ]\n\n\n";
        std::cout<<"------------------------------------------------------------\n";
        std::cout<<" Commands: add | list | save | help | exit\n";
        std::cout<<" Status: ( ! ) Pending changes\n";
        std::cout<<" Errors: \n";
        std::cout<<"------------------------------------------------------------\n";
    }

    void draw_edit_window(){
        std::cout<<"============================================================\n";
        std::cout<<"             📝 Edit Mode: [ GAME ID #010 ]\n";
        std::cout<<"============================================================\n";
        std::cout<<" CURRENT VALUES:\n";
        std::cout<<" 1. ID:        010\n";
        std::cout<<" 2. NAME:      Elden Ring\n";
        std::cout<<" 3. YEAR:      2022\n";
        std::cout<<" 4. PRICE:     249.90\n";
        std::cout<<" 5. RATING: 9.8\n";
        std::cout<<" 6. COMPANY:   FromSoftware\n";
        std::cout<<"------------------------------------------------------------\n";
        std::cout<<" [ Change Using: <field>:<value> | Ex: rating:9.5 ]\n";
        std::cout<<" [ Actions: save (confirm)        | back (cancel) ]\n";
    }

};

#endif