#include "../include/canaltexto.h"
#include <iostream>
#include <sstream>
#include <algorithm>
#include <vector>
#include <iterator>

using namespace std;

    CanalTexto::CanalTexto(std::string nome){

      this->nome = nome;

    }

    //Adder

    void CanalTexto::addMensagens(Mensagem m){

      this->mensagens.push_back(m);

    }

    string CanalTexto::getNome(void) const{

      return this->nome;

    }

    //To string

    std::string CanalTexto::messagesToString(std::vector<Usuario> users){

      std::string ts;

      for(int x = 0; x < this->mensagens.size(); x++){

        for(int y = 0; y < users.size();y++){

          if(this->mensagens[x].getEnviadoPor()==users[y].getId()){
            
            if(ts == ""){

              ts += "\033[1;32m"+users[y].getNome()+"\033[0m" + this->mensagens[x].getData() + ":" + this->mensagens[x].getConteudo();

            } else {
              
              ts += "\n\033[1;32m"+users[y].getNome()+"\033[0m" + this->mensagens[x].getData() + ":" + this->mensagens[x].getConteudo();;

            }

            break;

          }

        }

      }

      return ts;

    }