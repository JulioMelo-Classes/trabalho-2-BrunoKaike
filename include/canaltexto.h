#ifndef CANALTEXTO_H
#define CANALTEXTO_H

#include <vector>
#include <string>

#include "../include/mensagem.h"
#include "../include/usuario.h"

class CanalTexto{
	/*
		TODO implementação dos atributos e métodos
	*/
  private:

    std::string nome;
    std::vector<Mensagem> mensagens;

  public:

    //Constructor

    CanalTexto(std::string nome);

    //Adder

    void addMensagens(Mensagem m);

    //Getter
    std::string getNome(void) const;

    //ToString
    std::string messagesToString(std::vector<Usuario> users);

};

#endif
