#include <iostream>
#include "KVector.hpp"
using namespace std;



int main(){
    KVector<double> my_vector;
    my_vector.append(2.5);
    my_vector.append(10.0);
    cout << *my_vector.get_index(0) << endl;
    cout << *my_vector.get_index(1) << endl;
    *my_vector.get_index(0) += 10.0;
    cout << *my_vector.get_index(0) << endl;
    return 0;
}