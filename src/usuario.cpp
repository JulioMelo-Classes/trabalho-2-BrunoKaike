#include "../include/usuario.h"
#include <iostream>
#include <sstream>
#include <algorithm>
#include <vector>
#include <iterator>

using namespace std;

    Usuario::Usuario(int id, std::string nome, std::string email, std::string senha){
      this->id = id;
      this->nome = nome;
      this->email = email;
      this->senha = senha;

    }

    string Usuario::getNome(){

      return this->nome;
    }

    string Usuario::getEmail(){

      return this->email;
    }

    string Usuario::getSenha(){

      return this->senha;
    }

    int Usuario::getId(){

      return this->id;

    }