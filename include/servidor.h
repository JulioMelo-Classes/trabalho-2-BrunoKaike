#ifndef SERVIDOR_H
#define SERVIDOR_H

#include "../include/canaltexto.h"
#include "../include/usuario.h"

/*
Ok

Documentação 0 - Faltou a documentação!
*/
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

    /*! Verifica se um canal está cadastrado em um servidor e retorna sua posição no vetor de canais de texto.
    		@param nome uma string contendo o nome do canal informado.
    		@return um int com a posição do canal encontrado no vetor, sendo -1 um valor inválido.
    */
    int check_duplicates_chanel(std::string nome);

    /*! Verifica se um usuário está participando de um servidor e retorna sua posição no vetor de participantes.
    		@param id um int contendo o id de usuário informado.
    		@return um int com a posição do usuário encontrado no vetor, sendo -1 um valor inválido.
    */
    int check_duplicates_participant(int id);
	
    /*! Percorre o vetor de participantes de um servidor e verifica se um usuário está participando do mesmo, caso esteja ele é removido do vetor.
    		@param id um int contendo o id de usuário informado.
    */
    void remove_participant(int id);

    /*! Chama a função addMensagens() do objeto canal de texto e envia o id do canal recebido por parâmetro.
    		@param id um int contendo o id do canal informado no vetor de canais de texto do servidor.
    */	
    void addMensagens(int id, Mensagem s);

    //toStrings

    std::string allParticipantsToString(std::vector<Usuario> users);
    
    std::string allChannelsToString();

    std::string allMessagesToString(std::vector<Usuario> users, int chanel);
    

};

#endif
