#include <iostream>
#include <vector>
#include "Kvector.hpp"
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
    Kvector<int> my_vector;
    Kvector<double> m = {1.1,1.2,3.4};
    my_vector.push(10);
    cout << my_vector[0] << endl;
    my_vector.push(1);
    cout << my_vector[1] << endl;
    Kvector<int> teste = {1,2,3,4,5};
    cout << teste[0] << endl;
    teste.push(10);
    cout << teste[teste.len() - 1] << endl;
    Kvector<int> p = teste;
    cout << p[0] << endl;
    p[0] = 100;
    cout << p[0] << endl;
    return 0;
}