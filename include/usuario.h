#ifndef USUARIO_H
#define USUARIO_H

#include <string>

class Usuario{
	/*
		TODO implementação dos atributos e métodos
	*/
  private:

    int id; //Identificador único para o usuário
    std::string nome; //O nome cadastrado pelo usuário
    std::string email; //O email cadastrado pelo usuário
    std::string senha; //A senha cadastrada pelo usuário

  public:

    //Constructor

    Usuario(int id, std::string nome, std::string email, std::string senha){
      this->id = id;
      this->nome = nome;
      this->email = email;
      this->senha = senha;

    }

    // Getters
    
    std::string getNome(){

      return this->nome;
    }

    std::string getEmail(){

      return this->email;
    }

    std::string getSenha(){

      return this->senha;
    }

    int getId(){

      return this->id;

    }

};

#endif
