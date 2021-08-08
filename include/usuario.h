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

    Usuario(int id, std::string nome, std::string email, std::string senha);

    // Getters
    
    std::string getNome();

    std::string getEmail();

    std::string getSenha();

    int getId();

};

#endif
