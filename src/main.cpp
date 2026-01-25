#include <iostream>
#include <fstream>
#include "Kvector.hpp"
#include "Result.hpp"
#include <memory>
#include <string>
using namespace std;


struct Game
{
    std::string name;
    std::string publisher;
    float price;
    float avaliation;
    int year;

};


void addGame(Kvector<Game>& list, Game game) {
    list.push(game);
}

// Cria o arquivo caso já não exista e o cabeçalho do CSV
void initDB(string file_path) {
    ifstream test(file_path);

    if (!test.good()) {
        ofstream file(file_path);

        if (!file.is_open()) { // Verifica se o arquivo foi aberto corretamento
            cout << "Erro ao abrir o arquivo para criar o cabeçalho";
            
            return;
        } else {
            file << "name" << "," 
                << "publisher" << "," 
                << "avaliation" << "," 
                << "price" << "," 
                << "year" << endl;

            file.close();
        }
    }
}


// Salva todos os registros do vetor em um arquivo
void saveGames(Kvector<Game>& game_list, string file_path) {
    ofstream file(file_path, ios::app);

    if (!file.is_open()) { // Verifica se o arquivo foi aberto corretamento
        cout << "Erro ao abrir arquivo para registrar os jogos";

        return;
    } else {
        // Itera sobre cada posição do vetor e os salva no arquivo
        for (int i = 0; i < game_list.len(); i++) {
            file << game_list[i].name << "," 
                << game_list[i].publisher << "," 
                << game_list[i].avaliation << "," 
                << game_list[i].price << "," 
                << game_list[i].year << endl;
        }

        file.close();
    }
}


int main() {
    const string FILE_PATH = "db.txt";
    Game game;
    Kvector<Game> game_list;
    string n;

    initDB(FILE_PATH);

    while (n != "N") {
        cout << "Digite o nome do jogo: ";
        cin >> game.name;
        cout << "Digite a publisher do jogo: ";
        cin >> game.publisher;
        cout << "Digite o price do jogo: ";
        cin >> game.price;
        cout << "Digite o avaliation do jogo: ";
        cin >> game.avaliation;
        cout << "Digite o year do jogo: ";
        cin >> game.year;

        addGame(game_list, game);

        cout << "Você quer continuar [S/N]: ";
        cin >> n;
    }

    saveGames(game_list, FILE_PATH);

    return 0;
}