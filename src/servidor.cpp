#include "../include/servidor.h"
#include <iostream>
#include <sstream>
#include <algorithm>
#include <vector>
#include <iterator>

#include "../include/usuario.h"

using namespace std;

    Servidor::Servidor(int usuarioDonoId, std::string nome){

      this->usuarioDonoId = usuarioDonoId;
      this->nome = nome;

    }

    //Setters

    void Servidor::setDescricao(std::string descricao){

      this->descricao = descricao;

    }

    void Servidor::setCodigoConvite(std::string codigoConvite){

      this->codigoConvite = codigoConvite;

    }

    //adders

    void Servidor::addCanaisTexto(CanalTexto c){
      
      this->canaisTexto.push_back(c);

    }

    void Servidor::addParticipantesId(int id){
      
      this->participantesIDs.push_back(id);

    }

    //getters

    int Servidor::getUsuarioDonoId(){

      return this->usuarioDonoId;

    }

    std::string Servidor::getNome(){

      return this->nome;

    }

    std::string Servidor::getDescricao(){

      return this->descricao;

    }

    std::string Servidor::getCodigoConvite(){

      return this->codigoConvite;
    }

    std::string Servidor::allChannelsToString(){

      std::string ts = "";

      for(int x = 0; x < this->canaisTexto.size(); x++){
        if(x==0){
          ts+= this->canaisTexto[x].getNome();
        } else {
        
          ts+= '\n'+this->canaisTexto[x].getNome();

        }
      
      }

      return ts;

    }

    std::string Servidor::allMessagesToString(std::vector<Usuario> users, int chanel){

      return this->canaisTexto[chanel].messagesToString(users);

    }

    int Servidor::check_duplicates_chanel(std::string nome){

      for(int x = 0; x < this->canaisTexto.size(); x++){
          
        if(this->canaisTexto[x].getNome() == nome){

          return x;

        }
      
      }

      return -1;

    }

    int Servidor::check_duplicates_participant(int id){

      for(int x = 0; x < this->participantesIDs.size(); x++){
          
        if(this->participantesIDs[x] == id){

          return x;

        }
      
      }

      return -1;

    }

    void Servidor::remove_participant(int id){

      for(int x = 0; x < this->participantesIDs.size(); x++){
          
        if(this->participantesIDs[x] == id){
          
          this->participantesIDs.erase(this->participantesIDs.begin()+x);
          break;

        }
      
      }

    }

    std::string Servidor::allParticipantsToString(std::vector<Usuario> users){

      std::string ts = "";

      for(int x = 0; x < this->participantesIDs.size(); x++){
        
        for(int y = 0; y < users.size();){

          if(users[y].getId()==this->participantesIDs[x]){
            
            if(ts == ""){

              ts += users[y].getNome();

            } else {
              
              ts += "\n" + users[y].getNome();

            }

            users.erase(users.begin() + y);
            break;

          } else {
            
            y++;
            
          }

        }
      
      }

      return ts;

    }

    void Servidor::addMensagens(int id, Mensagem s){
    
      this->canaisTexto[id].addMensagens(s);

    }