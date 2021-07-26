#include "sistema.h"
#include <iostream>
#include <sstream>
#include <algorithm>
#include <vector>
#include <iterator>
#include <map>

using namespace std;

#include "../include/usuario.h"
#include "../include/servidor.h"

/* DADOS */

int nextUserId = 1;

string Sistema::quit() {
  return "Saindo...";
}

string Sistema::create_user (const string email, const string senha, const string nome) {

  if(!this->check_duplicates_user(nome, email, senha)){
    
    if(this->usuarios.size()== 0){

      this->usuarios.push_back(Usuario(0,"","",""));

    }

    Usuario new_user(nextUserId, nome, email, senha);
    this->usuarios.push_back(new_user);
    nextUserId++;

    return "Usuário criado";

  } else {

    return "Usuário já existe!";

  }

}

string Sistema::login(const string email, const string senha) {

  int resposta = this->is_registered_user(email,senha);
  if(resposta != 0){

    this->usuariosLogados[this->usuarios[resposta].getId()] = std::make_pair("", "");
    return "Logado como " + email;

  } else {

    return "Senha ou usuário inválidos!";

  }

}

string Sistema::disconnect(int id) {

  if(this->usuariosLogados.find(id) != this->usuariosLogados.end()){
    
    this->usuariosLogados.erase(id);
    int resposta = this->is_registered_user_id(id);

    this->usuariosLogados.erase(resposta);

    return "Desconectando usuário "+this->usuarios[resposta].getEmail();

  } else {

    return "Usuário não está conectado";

  }
  
}

string Sistema::create_server(int id, const string nome) {
  
  if(this->usuariosLogados.find(id) != this->usuariosLogados.end()){

    if(!this->check_duplicates_server(nome)){

      if(this->servidores.size()== 0){

        this->servidores.push_back(Servidor(0,""));

      }

      Servidor new_server(id, nome);
      this->servidores.push_back(new_server);
      this->usuariosLogados[id] = std::make_pair(nome, "");

      return "Servidor criado";

    } else {

      return "Servidor com esse nome já existe";

    }

  } else {

      return "Usuário não está conectado";

  }

}

string Sistema::set_server_desc(int id, const string nome, const string descricao) {

  if(this->usuariosLogados.find(id) != this->usuariosLogados.end()){

    int resposta = this->is_registered_server(id,nome);

    if(resposta > 0){

      this->servidores[resposta].setDescricao(descricao);
      return "Descrição do servidor \""+ nome +"\" modificada!";

    } else if(resposta == 0) {

      return "Servidor \""+ nome +"\" não existe";

    } else if(resposta == -1){

      return "Você não pode alterar a descrição de um servidor que não foi criado por você";

    }

  } else {

    return "Usuário não está conectado";

  }

}

string Sistema::set_server_invite_code(int id, const string nome, const string codigo) {

  if(this->usuariosLogados.find(id) != this->usuariosLogados.end()){

    int resposta = this->is_registered_server(id,nome);

    if(resposta > 0){

      if(codigo!=""){

        this->servidores[resposta].setCodigoConvite(codigo);
        return "Código de convite do servidor \""+ nome +"\" modificado!";

      } else {

        this->servidores[resposta].setCodigoConvite(codigo);
        return "Código de convite do servidor \""+ nome +"\" removido!";

      }

    } else if(resposta == 0) {

      return "Servidor \""+ nome +"\" não existe";

    } else if(resposta == -1){

      return "Você não pode alterar o código de convite de um servidor que não foi criado por você";

    }

  } else {

    return "Usuário não está conectado";

  }

}

string Sistema::list_servers(int id) {

  if(this->usuariosLogados.find(id) != this->usuariosLogados.end()){
    string saida = this->list_servers_by_id_owner(id);

    if(!saida.empty()){

      return saida;
    
    } else {

      return "Nenhum servidor foi encontrado!";

    }

  } else {
    
    return "Usuário não está conectado";

  }

}

string Sistema::remove_server(int id, const string nome) {
  
  if(this->usuariosLogados.find(id) != this->usuariosLogados.end()){

    int resposta = this->is_registered_server(id, nome);

    if(resposta > 0){

      this->remove_users_from_server_view(nome);
      this->servidores.erase(servidores.begin() + resposta);
      return "Servidor \""+ nome +"\" removido";

    } else if(resposta == 0){

      return "Servidor \""+ nome +"\" não encontrado";

    } else {

      return "Você não é o dono do servidor \"" + nome + "\"";

    }

  } else {

    return "Usuário não está conectado";

  }
  
  return "remove_server NÃO IMPLEMENTADO";
}

string Sistema::enter_server(int id, const string nome, const string codigo) {
  return "enter_server NÃO IMPLEMENTADO";
}

string Sistema::leave_server(int id, const string nome) {
  return "leave_server NÃO IMPLEMENTADO";
}

string Sistema::list_participants(int id) {
  return "list_participants NÃO IMPLEMENTADO";
}

string Sistema::list_channels(int id) {
  return "list_channels NÃO IMPLEMENTADO";
}

string Sistema::create_channel(int id, const string nome) {
  return "create_channel NÃO IMPLEMENTADO";
}

string Sistema::enter_channel(int id, const string nome) {
  return "enter_channel NÃO IMPLEMENTADO";
}

string Sistema::leave_channel(int id) {
  return "leave_channel NÃO IMPLEMENTADO";
}

string Sistema::send_message(int id, const string mensagem) {
  return "send_message NÃO IMPLEMENTADO";
}

string Sistema::list_messages(int id) {
  return "list_messages NÃO IMPLEMENTADO";
}

/* IMPLEMENTAR MÉTODOS PARA OS COMANDOS RESTANTES */

int Sistema::is_registered_server(int id, const std::string nome){

  for(int x = 1; x < this->servidores.size(); x++){
    
    if(this->servidores[x].getUsuarioDonoId()==id && this->servidores[x].getNome()==nome){
      return x;

    } else if(this->servidores[x].getUsuarioDonoId()!=id && this->servidores[x].getNome()==nome){
      
      return -1;

    }

  }

  return 0;

}

int Sistema::is_registered_user_id(int id){

  for(int x = 1; x < this->usuarios.size(); x++){
    
    if(this->usuarios[x].getId()==id){
      return x;

    }

  }

  return 0;

}

int Sistema::is_registered_user(const string email, const string senha){

  for(int x = 1; x < this->usuarios.size(); x++){

    if(this->usuarios[x].getEmail()==email && this->usuarios[x].getSenha()==senha){
      return x;

    }

  }

  return 0;

}

bool Sistema::check_duplicates_user(const std::string nome, const std::string email, const std::string senha){

  for(int x = 1; x < this->usuarios.size(); x++){

    if(this->usuarios[x].getNome()==nome && this->usuarios[x].getEmail()==email && this->usuarios[x].getSenha()==senha){

      return true;

    }

  }

  return false;

}

bool Sistema::check_duplicates_server(const std::string nome){

  for(int x = 0; x < this->servidores.size(); x++){

    if(this->servidores[x].getNome()==nome){

      return true;

    }

  }

  return false;

}

string Sistema::list_servers_by_id_owner(int id){

  string saida;

  for(int x = 1; x < this->servidores.size(); x++){
    
    if(this->servidores[x].getUsuarioDonoId()==id){
      
      if(x==1){
        saida+= this->servidores[x].getNome();
      } else {
        
        saida+= '\n'+this->servidores[x].getNome();

      }
      
    }

  }

  return saida;

}

void Sistema::remove_users_from_server_view(string nome){

  int count = 0;
  for(auto x = this->usuariosLogados.begin(); x != this->usuariosLogados.end();x++){

    if(x->second.first == nome){

      usuariosLogados[x->first] = std::make_pair("","");

    }

    count++;

  }

}