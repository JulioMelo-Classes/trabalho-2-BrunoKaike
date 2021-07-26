#ifndef SERVIDOR_H
#define SERVIDOR_H

#include "../include/canaltexto.h"

class Servidor{
	/*
		TODO implementação dos atributos e métodos
	*/
  private:

    int usuarioDonoId;
    std::string nome;
    std::string descricao;
    std::string codigoConvite;
    std::vector<CanalTexto> canaisTexto;
    std::vector<int> participantesIDs; 

  public:

    //Constructor

    Servidor(int usuarioDonoId, std::string nome){

      this->usuarioDonoId = usuarioDonoId;
      this->nome = nome;

    }

    //Setters

    void setDescricao(std::string descricao){

      this->descricao = descricao;

    }

    void setCodigoConvite(std::string codigoConvite){

      this->codigoConvite = codigoConvite;

    }

    //adders

    void addCanaisTexto(CanalTexto c){
      
      this->canaisTexto.push_back(c);

    }

    void addParticipantesId(int id){
      
      this->participantesIDs.push_back(id);

    }

    //getters

    int getUsuarioDonoId(){

      return this->usuarioDonoId;

    }

    std::string getNome(){

      return this->nome;

    }

    std::string getDescricao(){

      return this->descricao;

    }

};

#endif
