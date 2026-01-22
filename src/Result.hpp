#ifndef RESULT_HPP
#define RESULT_HPP
#include <memory>


template<typename T, typename U>
class Result{
    public:
        Result() : ok_content(nullptr), err_content(nullptr) {} // Função para inicialização padrão
        void ok(T value); // Método para retorno em caso de sucesso
        void err(U value); // Método para retorno em caso de erro

        // Métodos para verificação do tipo de resultados
        bool is_ok();
        bool is_err();
        
        // Métodos para pegar os itens contidos na classe
        T* get_ok();
        U* get_err();
    private:
        std::unique_ptr<T> ok_content;
        std::unique_ptr<U> err_content;
};

template<typename T, typename U> void Result<T, U>::ok(T value){
    if (ok_content == nullptr && err_content == nullptr) {    
        ok_content = std::make_unique<T>(value);
        err_content = nullptr;
    }
}

template<typename T, typename U> void Result<T, U>::err(U value){
    if (ok_content == nullptr && err_content == nullptr){
        err_content = std::make_unique<U>(value);
        ok_content = nullptr;
    }
}

template<typename T, typename U> bool Result<T, U>::is_ok(){
    return ok_content != nullptr;
}

template<typename T, typename U> bool Result<T, U>::is_err(){
    return err_content != nullptr;
}

template<typename T, typename U> T* Result<T, U>::get_ok(){
    return ok_content.get();
}

template<typename T, typename U> U* Result<T, U>::get_err(){
    return err_content.get();
}


#endif