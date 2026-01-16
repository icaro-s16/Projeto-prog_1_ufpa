#ifndef K_VECTOR_HPP
#define K_VECTOR_HPP


template<typename T>
class KVector{
    public:
        // Constructor Default
        KVector();
        // Destructor Default
        ~KVector();
    
        // Função para alocar e adicionar o valor de parâmetro
        void append(T value);
        // Retorna o ponteiro do indice passado como argumento
        T* get_index(unsigned index);
        // Função para excluir o último item adicionado no vetor
        void pop();
        // Retorna o tamanho atual do vetor
        unsigned len();
        

    private:
        // Para iniciar apontando para o nada
        T *vec;
        unsigned size;
        
        // Alocação padrão
        void alloc(unsigned size);
};

template<typename T> void KVector<T>::append(T value){ 
    size += 1;
    alloc(size);
    *(vec + (size - 1)) = value;
}

template<typename T> T* KVector<T>::get_index(unsigned index){
    if(index < size){
        return vec + index;       
    }else{
        return nullptr;
    }
}

template<typename T> void KVector<T>::pop(){
    T *aux = new T[ --size ];
    for (unsigned i = 0; i < size; i ++){
        *(aux + i) = *(vec + i);
    }
    delete[] vec;
    vec = aux;
}

template<typename T> unsigned KVector<T>::len(){
    return size;
}

template<typename T> KVector<T>::KVector(){
    vec = nullptr;
    size = 0;
}

template<typename T> KVector<T>::~KVector(){
    size = 0;
    delete[] vec;
    vec = nullptr;
}


template<typename T>void KVector<T>::alloc(unsigned new_size){
    
    T* aux = new T[new_size];

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

#endif