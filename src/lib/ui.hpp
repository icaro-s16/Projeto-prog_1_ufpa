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
            std::cout << i+1 <<". [ ID: "<< games_list[i].id << " | NAME: "<< games_list[i].name <<" | YEAR: "<<games_list[i].year <<" ]" << std::endl;
            std::cout << "   [ PRICE: "<< "R$ " + formated_price.str() <<" | RATING: "<< games_list[i].rating <<" | PUBLISHER: "<< games_list[i].publisher <<" ]\n" << std::endl;
        }

        std::cout << " ----------------------------------------------------------" << std::endl;
        std::cout << " [ search SYNTAX ]" << std::endl;
        std::cout << " > search -<field> <value>              : Search for exact match or text." << std::endl;
        std::cout << " > search -<field> -gt/-lt <value>      : Search using comparison (Greater Than / Less Than)." << std::endl;
        std::cout << "   * Comparison applies only to: id, price, year, rating." << std::endl;
        std::cout << " > search -clean                        : Clear all active filters." << std::endl;
                
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
        std::string price = new_register.price_default_template();
        std::ostringstream formated_price;
        
        std::cout << " [ PRICE ]     : " << new_register.price_default_template() << std::endl;
        std::cout << " [ RATING ]    : " << new_register.rating_default_template() << std::endl;
        std::cout << " [ PUBLISHER ]   : " << new_register.publisher_default_template() << std::endl;
        
        std::cout << "------------------------------------------------------------" << std::endl;
        std::cout << " [ Change using: <field>:<value> | Ex: rating:9.5 ]" << std::endl;
        std::cout << " [ Actions: save (confirm)       | back (cancel)  ]" << std::endl;
        std::cout<<"------------------------------------------------------------\n";
        std::cout<<" Errors: "<<err_msg<<"\n";
        std::cout<<"------------------------------------------------------------" << std::endl;
    }

    void draw_edit_window(std::string err_msg, Game new_register, GamesList games_list, int current_index) {
        std::cout << "============================================================" << std::endl;
        std::cout << "                 EDITING: [ GAME ID #" << games_list[current_index].id << " ]" << std::endl;
        std::cout << "============================================================" << std::endl;
        
        std::string name = (new_register.field_is_default("name")) ? games_list[current_index].name : new_register.name;
        int year = (new_register.field_is_default("year")) ? games_list[current_index].year : new_register.year;
        double price = (new_register.field_is_default("price")) ? games_list[current_index].price : new_register.price;
        int rating = (new_register.field_is_default("rating")) ? games_list[current_index].rating : new_register.rating;
        std::string publisher = (new_register.field_is_default("publisher")) ? games_list[current_index].publisher : new_register.publisher;

        std::cout << " [ NAME ]      : " << name<< std::endl;
        std::cout << " [ YEAR ]      : " << year << std::endl;
        std::ostringstream formated_price;
        formated_price << std::fixed << std::setprecision(2) << price;
        std::cout << " [ PRICE ]     : " << "R$ " + formated_price.str() << std::endl;
        std::cout << " [ RATING ]    : " << rating << std::endl;
        std::cout << " [ PUBLISHER ]   : " << publisher << std::endl;
        
        std::cout << "------------------------------------------------------------" << std::endl;
        std::cout << " [ Change using: <field>:<value> | Ex: rating:9.5 ]" << std::endl;
        std::cout << " [ Actions: save (confirm)       | back (cancel)   ]" << std::endl;
        std::cout<<"------------------------------------------------------------\n";
        std::cout<<" Errors: "<<err_msg<<"\n";
        std::cout << "------------------------------------------------------------" << std::endl;
    }

    void draw_help_window(std::string err_msg) {
        std::cout << "============================================================" << std::endl;
        std::cout << "                    HELP & INSTRUCTIONS" << std::endl;
        std::cout << "============================================================" << std::endl;

        std::cout << " [ MAIN NAVIGATION ]" << std::endl;
        std::cout << " > add   : Register a new game." << std::endl;
        std::cout << " > list  : View library and search games." << std::endl;
        // Atualizado aqui para indicar o Status
        std::cout << " > save  : Persist changes (Check 'Status' field)." << std::endl; 
        std::cout << " > exit  : Close the application." << std::endl;

        std::cout << " ------------------------------------------------------------" << std::endl;
        std::cout << " [ LIBRARY SEARCH SYNTAX ]" << std::endl;
        std::cout << " > search -clean           : Clear filters." << std::endl;
        std::cout << " > search -<field> <val>   : Exact match." << std::endl;
        std::cout << "   Fields: name, publisher, id, year, price, rating." << std::endl;
        std::cout << " > search -<field> -gt/-lt <val> : Comparison search." << std::endl;
        std::cout << "   Fields: id, year, price, rating." << std::endl;
        std::cout << "   Flags : -gt (Greater Than), -lt (Less Than)." << std::endl;

        std::cout << " ------------------------------------------------------------" << std::endl;
        std::cout << " [ EDITING & REGISTRATION ]" << std::endl;
        std::cout << " > <field>:<value> : Set field value." << std::endl;
        std::cout << "   Ex: name:God of War | price:49.90 | year:2018" << std::endl;
        std::cout << " > edit -id <id>   : Enter edit mode for a game ID." << std::endl;
        std::cout << " > save / back     : Confirm or Cancel actions." << std::endl;

        std::cout << "------------------------------------------------------------" << std::endl;
        std::cout << " [ Type 'back' to return to Main Menu ]" << std::endl;
        std::cout << "------------------------------------------------------------" << std::endl;
        std::cout << " Errors: " << err_msg << "\n";
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
                    app_state.printable_list
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
                    app_state.error_msg,
                    app_state.new_register_game,
                    app_state.list,
                    app_state.edit_index
                );
                break;
            case help_window:
                draw_help_window(
                    app_state.error_msg
                );
                break;
            default:
                break;
        }
    }
};




#endif