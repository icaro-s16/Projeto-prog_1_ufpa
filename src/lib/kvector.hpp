#ifndef KVECTOR_HPP
#define KVECTOR_HPP

#include <cstddef>

template<typename T>
class Kvector{
    public:
        // Constructor Default
        Kvector();
        // Construtor de cópias (deep copy)
        Kvector(const Kvector<T>& other);
        // Constructor de inicialização a partir de literais
        Kvector(std::initializer_list<T> init_vec);
        // Destructor 
        ~Kvector();
    
        void push(T value);// Função para alocar e adicionar o valor de parâmetro

        void remove(const size_t index); // Remove um item de uma posição especificada pelo index
        
        void pop(); // Função para excluir o último item adicionado no vetor
        
        size_t len(); // Retorna a quantidade de itens alocados

        T& operator[](const size_t index);  

        // Operador de atribuição para gerenciamento das cópias 
        Kvector<T>& operator=(const Kvector<T>& other);

    private:
        T *vec = nullptr;
        // Tamanho correspondente a quantidade de itens
        size_t size = 0;
        // Tamanho correspondente a capacidade total do vetor
        size_t capacity = 0;
        
        void alloc(size_t size); // Alocação padrão
};

// Implementação das funções de gerenciamento de cópias junto de operadores
template<typename T> Kvector<T>::Kvector(){
    vec = nullptr;
    size = 0;
    capacity = 0;
}

template<typename T> Kvector<T>::Kvector(std::initializer_list<T> init_vec){
    if (init_vec.size() > 0){
        // Inicia o vetor com 40 espaços ou
        // um valor > 40 e múltiplo de 10
        if (init_vec.size() < 40){    
            capacity = 40;
            alloc(capacity);
        }else if (init_vec.size() % 10 != 0){
            capacity = init_vec.size() + (10 - (init_vec.size() % 10));
            alloc(capacity);
        }else{
            capacity = init_vec.size();
            alloc(capacity);
        }
        std::copy(init_vec.begin(), init_vec.end(), vec);
        size = init_vec.size();
    }
}

template<typename T> Kvector<T>::Kvector(const Kvector<T>& other){
    vec = new T[other.capacity];
    for (size_t i = 0; i < other.size ; i ++){
        vec[i] = other.vec[i];
    }
    capacity = other.capacity;
    size = other.size;
}

template<typename T> Kvector<T>::~Kvector(){
    size = 0;
    capacity = 0;
    delete[] vec;
    vec = nullptr;
}

template<typename T> Kvector<T>& Kvector<T>::operator=(const Kvector<T>& other){
    if (this != &other){
        delete[] vec;
        size = other.size;
        capacity = other.capacity;
        vec = new T[other.capacity];
        for (unsigned i = 0; i < size; i++){
            vec[i] = other.vec[i];
        }
    }
    return *this;
}

template<typename T> T& Kvector<T>::operator[](const size_t index){
    return vec[index];
}

// Implementação dos métodos

template<typename T> void Kvector<T>::push(T value){ 
    if (capacity == size){
        if (capacity == 0){
            capacity = 40;
            alloc(capacity);
        }else{
            alloc( capacity + 10);    
        }
    }
    size++;
    vec[ size - 1 ] = value;
    
}

template<typename T> void Kvector<T>::pop(){ 
    if (size > 0) {
        size--;
    }
    
}

template<typename T> void Kvector<T>::remove(const size_t index){
    if (index < size){
        for(size_t i = index; i < size - 1; i++){
            vec[i] = vec[i+1];
        }
        size--;
    }
}

template<typename T> size_t Kvector<T>::len(){
    return size;
}



template<typename T>void Kvector<T>::alloc(size_t new_size){
    T* aux = new T[new_size];
    capacity = new_size;
    // caso o vetor possua itens eles serão passados para esse novo espaço alocado
    if (size > 0){
        for (size_t i = 0; i < size; i++){
            aux[i] = vec[i];
        }
        delete[] vec;
        vec = aux;
    }else{
        vec = aux;
    }
}

#endif

