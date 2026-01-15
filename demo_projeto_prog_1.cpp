#include <iostream>
using namespace std;

class Vector{
    public:
        Vector(){
            vec = nullptr;
            size = 0;
        }
        Vector(unsigned size){
            size = size;
            alloc(size);
        }
        Vector(int new_vec[], unsigned size){
            size = size;
            alloc(size);
            for(unsigned i = 0; i < size ; i ++){
                *(vec + i) = *(new_vec + i);
            }
        }
        void append(int value){ 
            size += 1;
            alloc(size);
            *(vec + (size - 1)) = value;
        }
        int* get_index(unsigned index){
            if(index < size){
                return vec + index;       
            }else{
                return nullptr;
            }
        }
        void delete_vec(){
            delete[] vec;
            vec = nullptr;
            size = 0;
        }

    private:
        int *vec;
        unsigned size;
        
        void alloc(unsigned size){
            int* aux = new int[size];
            if ((vec != nullptr) && (size > 0)){
                for (unsigned i = 0; i < size - 1; i++){
                    *aux = *(vec + i);
                }
                delete[] vec;
                vec = aux;
            }else{
                vec = aux;
            }
        }
};



int main(){
    int aux[] = {1,2,3,4,5};
    Vector my_vector(aux, 5);
    cout << *(my_vector.get_index(0)) << endl;
    cout << *(my_vector.get_index(1)) << endl;
    my_vector.delete_vec();
    return 0;
}