#include <iostream>
#include <vector>
#include "KVector.hpp"
#include "Result.hpp"
#include <memory>
using namespace std;

Result<int, string> teste(int x){
    Result<int, string> valor_de_retorno;
    if (x < 0){
        valor_de_retorno.err("O valor está muito baixo");
        return valor_de_retorno;
    }
    valor_de_retorno.ok(x);
    return valor_de_retorno;
}



int main(){
    vector<int> p = {1, 2, 3};
    cout << p[0] << endl;
    p[0] = 10;
    cout << p[0] << endl;
    KVector<int> my_vector;
    my_vector.push(10);
    my_vector.push(9);
    cout << my_vector.len() << endl;
    cout << *my_vector[0] << endl;
    my_vector.remove(0);
    cout << *my_vector[0] << endl;
    *my_vector[0] = 100;
    cout << *my_vector[0] << endl;
    return 0;
}