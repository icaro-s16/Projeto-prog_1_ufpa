#ifndef KVECTOR_HPP
#define KVECTOR_HPP


template<typename T>
class Kvector{
    public:
        // Constructor Default
        Kvector();
        // Construtor de cópias (deep copy)
        Kvector(const Kvector<T>& other);
        // Constructor de inicialização apartir de literais
        Kvector(std::initializer_list<T> init_vec);
        // Destructor 
        ~Kvector();
    
        void push(T value);// Função para alocar e adicionar o valor de parâmetro

        void remove(const size_t index); // Remove um item de uma posição especificada pelo index
        
        void pop(); // Função para excluir o último item adicionado no vetor
        
        size_t len(); // Retorna a quantidade de itens alocados

        T* operator[](const size_t index);  

        // Operador de atribuição para gerenciamento das cópias 
        Kvector<T>& operator=(const Kvector<T>& other);

    private:
        T *vec = nullptr;
        // Tamanho correspondente a quantidade de itens
        size_t size = 0;
        // Tamanho correspondente a capacidade total do vetor
        size_t capactiy = 0;
        
        void alloc(size_t size); // Alocação padrão
};

// Implementação das funções de gerenciamento de cópias junto de operadores

template<typename T> Kvector<T>::Kvector(){
    vec = nullptr;
    size = 0;
    capactiy = 0;
}

template<typename T> Kvector<T>::Kvector(std::initializer_list<T> init_vec){
    if (init_vec.size() > 0){
        alloc(init_vec.size());
        std::copy(init_vec.begin(), init_vec.end(), vec);
        size = init_vec.size();
        capactiy = 0;
    }
}

template<typename T> Kvector<T>::Kvector(const Kvector<T>& other){
    vec = new T[other.size];
    for (size_t i = 0; i < other.size ; i ++){
        vec[i] = other.vec[i];
    }
    capactiy = other.capactiy;
    size = other.size;
}

template<typename T> Kvector<T>::~Kvector(){
    size = 0;
    capactiy = 0;
    delete[] vec;
    vec = nullptr;
}

template<typename T> Kvector<T>& Kvector<T>::operator=(const Kvector<T>& other){
    if (this != &other){
        delete[] vec;
        size = other.size;
        capactiy = other.capactiy;
        vec = new T[other.size];
        for (unsigned i = 0; i < size; i++){
            vec[i] = other.vec[i];
        }
    }
    return *this;
}

template<typename T> T* Kvector<T>::operator[](const size_t index){
    return vec + index;
}

// Implementação dos métodos

template<typename T> void Kvector<T>::push(T value){ 
    if (capactiy == size){
        if (capactiy == 0){ capactiy++; }
        alloc( capactiy * 2);    
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
            T aux = vec[i + 1];
            vec[i + 1] = vec[i];
            vec[i] = aux;
        }
        size--;
    }
}

template<typename T> size_t Kvector<T>::len(){
    return size;
}



template<typename T>void Kvector<T>::alloc(size_t new_size){
    
    T* aux = new T[new_size]; // Aloca um novo espaço de acordo com o tamanho passado
    capactiy = new_size;
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