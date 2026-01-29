#ifndef UI_HPP
#define UI_HPP

#include "game.hpp"
#include "app_state.hpp"
#include <iostream>
#include <iomanip>

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
        std::cout<<"               G A M E   V A U L T   v 1 . 0\n";
        std::cout<<"============================================================\n";
        std::cout<<"\n\n      [ System is ready. Waiting for commands... ]\n\n\n";
        std::cout<<"------------------------------------------------------------\n";
        std::cout<<" Commands: [ add | list | save | help | exit ]\n";
        std::string save_advice =  (actual_size == games_list.len()) ? "Your changes have been saved successfully!" : "You have unsaved changes!";
        std::cout<<"------------------------------------------------------------\n";
        std::cout<<" Status: "<< save_advice <<"\n";
        std::cout<<" Errors: "<<err_msg<<"\n";
        std::cout<<"------------------------------------------------------------\n";
    }


    void draw_library_window(std::string err_msg, GamesList games_list) {
        std::cout << "============================================================" << std::endl;
        std::cout << "                   GAME LIBRARY" << std::endl;
        std::cout << "============================================================" << std::endl;

        for (size_t i = 0; i < games_list.len(); i++){
            std::ostringstream formated_price;
            formated_price << std::fixed << std::setprecision(2) << games_list[i].price;
            std::cout << i+1 <<". [ ID: "<< games_list[i].id << " | NAME: "<< games_list[i].name <<" | DATE: "<<games_list[i].year <<" ]" << std::endl;
            std::cout << "   [ PRICE: "<< "R$ " + formated_price.str() <<" | RATING: "<< games_list[i].avaliation <<" | COMPANY: "<< games_list[i].publisher <<" ]\n" << std::endl;
        }

        std::cout << " ----------------------------------------------------------" << std::endl;
        std::cout << " [ filter SYNTAX ]" << std::endl;
        std::cout << " > filter -<field> <value>" << std::endl;
        std::cout << "   (Fields: id, name, date, price, rating, company)" << std::endl;
        std::cout << std::endl;
        
        std::cout << " [ ACTIONS ]" << std::endl;
        std::cout << " > edit -id <value> | back" << std::endl;
        std::cout<<"------------------------------------------------------------" << std::endl;
        std::cout<<" Errors: "<<err_msg<<"\n";
        std::cout<<"------------------------------------------------------------" << std::endl;
    }


    void draw_new_game_window(Game new_register, std::string err_msg) {
        std::cout << "============================================================" << std::endl;
        std::cout << "                 NEW GAME REGISTRATION" << std::endl;
        std::cout << "============================================================" << std::endl;
    
        std::cout << " [ ID ]        : " << new_register.id_default_template() <<std::endl;
        std::cout << " [ NAME ]      : " << new_register.name_default_template() << std::endl;
        std::cout << " [ YEAR ]      : " << new_register.year_default_template() << std::endl;
        std::cout << " [ PRICE ]     : " << new_register.price_default_template() << std::endl;
        std::cout << " [ RATING ]    : " << new_register.avaliation_default_template() << std::endl;
        std::cout << " [ COMPANY ]   : " << new_register.publisher_default_template() << std::endl;
        
        std::cout << "------------------------------------------------------------" << std::endl;
        std::cout << " [ Change using: <field>:<value> | Ex: rating:9.5 ]" << std::endl;
        std::cout << " [ Actions: save (confirm)       | back (cancel)  ]" << std::endl;
        std::cout<<"------------------------------------------------------------\n";
        std::cout<<" Errors: "<<err_msg<<"\n";
        std::cout<<"------------------------------------------------------------" << std::endl;
    }

    void draw_edit_window(std::string err_msg) {
        std::cout << "============================================================" << std::endl;
        std::cout << "                 EDITING: [ GAME ID #" << " ]" << std::endl;
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
        std::cout<<"------------------------------------------------------------\n";
        std::cout<<" Errors: "<<err_msg<<"\n";
        std::cout << "------------------------------------------------------------" << std::endl;
    }

    void draw_window(AppState& app_state){
        clean();
        switch (app_state.window)
        {
            case main_window:
                Ui::draw_main_window(
                    app_state.error_msg,
                    app_state.actual_size,
                    app_state.list
                );
                break;
            case list_window:
                Ui::draw_library_window(
                    app_state.error_msg,
                    app_state.list
                );
                break;
            case register_window:
                Ui::draw_new_game_window(
                    app_state.new_register_game,
                    app_state.error_msg
                );
                break;
            case edit_window:
                Ui::draw_edit_window(
                    app_state.error_msg
                );
                break;
            case help_window:
                break;
            default:
                break;
        }
    }
};




#endif