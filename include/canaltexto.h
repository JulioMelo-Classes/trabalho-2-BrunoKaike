#ifndef CANALTEXTO_H
#define CANALTEXTO_H

#include "../include/mensagem.h"

class CanalTexto{
	/*
		TODO implementação dos atributos e métodos
	*/
  private:

    std::string nome;
    std::vector<Mensagem> mensagens;

  public:

    //Constructor

    CanalTexto(std::string nome){

      this->nome = nome;

    }

    //Adder

    void addMensagens(Mensagem m){

      this->mensagens.push_back(m);

    }


};

#endif
