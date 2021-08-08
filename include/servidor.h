#ifndef SERVIDOR_H
#define SERVIDOR_H

#include "../include/canaltexto.h"
#include "../include/usuario.h"

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

    Servidor(int usuarioDonoId, std::string nome);

    //Setters

    void setDescricao(std::string descricao);

    void setCodigoConvite(std::string codigoConvite);

    //adders

    void addCanaisTexto(CanalTexto c);

    void addParticipantesId(int id);

    //getters

    int getUsuarioDonoId();

    std::string getNome();

    std::string getDescricao();

    std::string getCodigoConvite();

    // operations

    int check_duplicates_chanel(std::string);

    int check_duplicates_participant(int id);

    void remove_participant(int id);

    void addMensagens(int id, Mensagem s);

    //toStrings

    std::string allParticipantsToString(std::vector<Usuario> users);
    
    std::string allChannelsToString();

    std::string allMessagesToString(std::vector<Usuario> users, int chanel);
    

};

#endif
