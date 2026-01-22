#ifndef KVECTOR_HPP
#define KVECTOR_HPP


template<typename T>
class KVector{
    public:
        // Constructor Default
        KVector();
        // Destructor Default
        ~KVector();
    
        void push(T value);// Função para alocar e adicionar o valor de parâmetro

        void remove(unsigned index); // Remove um item de uma posição especificada pelo index
        
        void pop(); // Função para excluir o último item adicionado no vetor
        
        unsigned len(); // Retorna o tamanho atual do vetor

        T* operator[](const unsigned index);  
        

    private:
        T *vec;
        unsigned size;
        
        void alloc(unsigned size); // Alocação padrão
};


template<typename T> void KVector<T>::push(T value){ 
    alloc(++size);
    *(vec + (size - 1)) = value;
}

template<typename T> T* KVector<T>::operator[](const unsigned index){
    return vec + index;
}

template<typename T> void KVector<T>::pop(){ 
    T *aux = new T[ --size ];
    for (unsigned i = 0; i < size; i ++){
        *(aux + i) = *(vec + i);
    }
    delete[] vec;
    vec = aux;
    
}

template<typename T> void KVector<T>::remove(unsigned index){
    T* aux = new T[ size - 1 ];
    for(unsigned i = 0, j = 0; i < size; i++){
        if ( i != index ){
            *(aux + (j++)) = *(vec + i);
        }
    }
    size--;
    delete vec;
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