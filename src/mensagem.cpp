#include "../include/mensagem.h"
#include <iostream>
#include <sstream>
#include <algorithm>

using namespace std;

    Mensagem::Mensagem(std::string dataHora, int enviadaPor, std::string conteudo){

      this->dataHora = dataHora;
      this->enviadaPor = enviadaPor;
      this->conteudo = conteudo;

    }

    int Mensagem::getEnviadoPor(){

      return this->enviadaPor;

    }

    std::string Mensagem::getData(){

      return this->dataHora;

    }

    std::string Mensagem::getConteudo(){

      return this->conteudo;

    }