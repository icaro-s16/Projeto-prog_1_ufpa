#include <iostream>
#include <fstream>
#include "lib/kvector.hpp"
#include "lib/result.hpp"
#include <memory>
#include <string>
using namespace std;


struct Game
{
    std::string name;
    std::string publisher;
    float price;
    int avaliation;
    int year;
    int id;
    // Constructor Default
    Game(){}
    // Constructor Preenchido, 
    Game(
        string new_name, 
        string new_publisher, 
        float new_price,
        int new_avaliation,
        int new_year,
        int new_id
    ) : 
    name(new_name), 
    publisher(new_publisher), 
    price(new_price),
    avaliation(new_avaliation),
    year(new_year),
    id(new_id){}
};

class ListGames{
    public:
        ListGames(){}

        void add_game(Game game){
            list.push(game);
        }
        void save_games(string file_path){
            ofstream file(file_path, ios::app);
            if (!file.is_open()) { // Verifica se o arquivo foi aberto corretamento
                cout << "Erro ao abrir arquivo para registrar os jogos";

                return;
            } else {
                // Itera sobre cada posição do vetor e os salva no arquivo
                for (size_t i = 0; i < list.len(); i++) {
                    file << list[i].name << ";" 
                        << list[i].publisher << ";" 
                        << list[i].avaliation << ";" 
                        << list[i].price << ";" 
                        << list[i].year << endl;
                }

                file.close();
            }
        }
    private:
        Kvector<Game> list;
};


void addGame(Kvector<Game>& list, Game game) {
    list.push(game);
}

// Cria o arquivo caso já não exista e o cabeçalho do CSV
Result<string, string> initDB(string file_path) {
    ifstream test(file_path);
    Result<string, string> return_value;

    if (!test.good()) {
        ofstream file(file_path);
        if (!file.is_open()) { // Verifica se o arquivo foi aberto corretamento
            return_value.err("Erro ao abrir o arquivo");
            return return_value;
        } else {
            file << "# name" << ";" 
                << "publisher" << ";" 
                << "avaliation" << ";" 
                << "price" << ";" 
                << "year" << endl;

            file.close();
        }
    }
    return_value.ok("Iniciação do DB concluída");
    return return_value;
}


// Salva todos os registros do vetor em um arquivo
void saveGames(Kvector<Game>& game_list, string file_path) {
    ofstream file(file_path, ios::app);

    if (!file.is_open()) { // Verifica se o arquivo foi aberto corretamento
        cout << "Erro ao abrir arquivo para registrar os jogos";

        return;
    } else {
        // Itera sobre cada posição do vetor e os salva no arquivo
        for (size_t i = 0; i < game_list.len(); i++) {
            file << game_list[i].name << ";" 
                << game_list[i].publisher << ";" 
                << game_list[i].avaliation << ";" 
                << game_list[i].price << ";" 
                << game_list[i].year << endl;
        }

        file.close();
    }
}


int main() {
    const string FILE_PATH = "db.csv";
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