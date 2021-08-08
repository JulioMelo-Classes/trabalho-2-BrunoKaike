#include "sistema.h"
#include <iostream>
#include <sstream>
#include <algorithm>
#include <vector>
#include <iterator>
#include <map>
#include <stdio.h>
#include <time.h>

using namespace std;

/* DADOS */

int nextUserId = 1;

string Sistema::quit() {
  return "Saindo...";
}

string Sistema::create_user (const string email, const string senha, const string nome) {

  if(!this->check_duplicates_user(nome, email, senha)){

    this->usuarios.push_back(Usuario(nextUserId, nome, email, senha));
    nextUserId++;

    return "Usuário criado";

  } else {

    return "\033[1;31mUsuário já existe!\033[0m";

  }

}

string Sistema::login(const string email, const string senha) {

  int resposta = this->is_registered_user(email,senha);
  if(resposta != -1){

    this->usuariosLogados[this->usuarios[resposta].getId()] = std::make_pair("", "");
    return "Logado como " + email;

  } else {

    return "\033[1;31mSenha ou usuário inválidos!\033[0m";

  }

}

string Sistema::disconnect(int id) {

  if(this->usuariosLogados.find(id) != this->usuariosLogados.end()){
    
    this->usuariosLogados.erase(id);
    int resposta = this->is_registered_user_id(id);

    this->usuariosLogados.erase(resposta);

    return "Desconectando usuário "+this->usuarios[resposta].getEmail();

  } else {

    return "\033[1;31mUsuário não está conectado\033[0m";

  }
  
}

string Sistema::create_server(int id, const string nome) {
  
  if(this->usuariosLogados.find(id) != this->usuariosLogados.end()){

    if(this->check_duplicates_server(nome)<0){

      this->servidores.push_back(Servidor(id, nome));
      this->usuariosLogados[id] = std::make_pair(nome, "");
      this->servidores[this->servidores.size()-1].addParticipantesId(id);
      return "Servidor criado";

    } else {
      
      return "\033[1;31mServidor com esse nome já existe\033[0m";

    }

  } else {

      return "\033[1;31mUsuário não está conectado\033[0m";

  }

}

string Sistema::set_server_desc(int id, const string nome, const string descricao) {

  if(this->usuariosLogados.find(id) != this->usuariosLogados.end()){

    int resposta = this->is_registered_server(id,nome);

    if(resposta >= 0){

      this->servidores[resposta].setDescricao(descricao);
      return "Descrição do servidor \""+ nome +"\" modificada!";

    } else if(resposta == -2) {

      return "\033[1;31mServidor \""+ nome +"\" não existe\033[0m";

    } else if(resposta == -1){
      
      return "\033[1;31mVocê não pode alterar a descrição de um servidor que não foi criado por você\033[0m";

    }

  } else {

    return "\033[1;31mUsuário não está conectado\033[0m";

  }

}

string Sistema::set_server_invite_code(int id, const string nome, const string codigo) {

  if(this->usuariosLogados.find(id) != this->usuariosLogados.end()){

    int resposta = this->is_registered_server(id,nome);

    if(resposta >= 0){

      if(codigo!=""){

        this->servidores[resposta].setCodigoConvite(codigo);
        return "Código de convite do servidor \""+ nome +"\" modificado!";

      } else {

        this->servidores[resposta].setCodigoConvite(codigo);
        return "Código de convite do servidor \""+ nome +"\" removido!";

      }

    } else if(resposta == 0) {

      return "\033[1;31mServidor \""+ nome +"\" não existe\033[0m";

    } else if(resposta == -1){

      return "\033[1;31mVocê não pode alterar o código de convite de um servidor que não foi criado por você\033[0m";

    }

  } else {

    return "\033[1;31mUsuário não está conectado\033[0m";

  }

}

string Sistema::list_servers(int id) {

  if(this->usuariosLogados.find(id) != this->usuariosLogados.end()){
      string saida = this->list_servers_by_id_owner(id);

      if(!saida.empty()){

        return saida;
      
      } else {

        return "\033[1;31mNenhum servidor foi encontrado\033[0m";

      }

  } else {
    
    return "\033[1;31mUsuário não está conectado\033[0m";

  }

}

string Sistema::remove_server(int id, const string nome) {
  
  if(this->usuariosLogados.find(id) != this->usuariosLogados.end()){

    int resposta = this->is_registered_server(id, nome);

    if(resposta >= 0){

      this->remove_users_from_server_view(nome);
      this->servidores.erase(servidores.begin() + resposta);
      return "Servidor \""+ nome +"\" removido";

    } else if(resposta == -1){
      return "\033[1;31mVocê não é o dono do servidor \"" + nome + "\"\033[0m";

    } else {

      return "\033[1;31mServidor \""+ nome +"\" não encontrado\033[0m";

    }

  } else {

    return "\033[1;31mUsuário não está conectado\033[0m";

  }
  
}

string Sistema::enter_server(int id, const string nome, const string codigo) {
  
  auto find = this->usuariosLogados.find(id);
  if(find != this->usuariosLogados.end()){

    int resposta = this->check_duplicates_server(nome);

    if(resposta >= 0){
      
      string codigoS = this->servidores[resposta].getCodigoConvite();

      if(codigoS == ""){

        usuariosLogados[find->first] = std::make_pair(nome,"");

        if(this->servidores[resposta].check_duplicates_participant(id) < 0){

          this->servidores[resposta].addParticipantesId(id);

        }

        return "Entrou no servidor com sucesso";

      } else {

        if(codigoS == codigo){
          
          usuariosLogados[find->first] = std::make_pair(nome,"");

          if(this->servidores[resposta].check_duplicates_participant(id) < 0){

            this->servidores[resposta].addParticipantesId(id);

          }

          return "Entrou no servidor com sucesso";

        } else if(codigo == ""){

          if(this->servidores[resposta].getUsuarioDonoId()==id){

            usuariosLogados[find->first] = std::make_pair(nome,"");
            if(this->servidores[resposta].check_duplicates_participant(id) < 0){

              this->servidores[resposta].addParticipantesId(id);

            }
            
            return "Entrou no servidor com sucesso";

          } else {

            return "\033[1;31mServidor requer código de convite\033[0m";

          }
          
        } else {

          return "\033[1;31mCódigo inválido\033[0m";

        }

      }

    } else if(resposta == -2) {

      return "\033[1;31mServidor \""+ nome +"\" não existe\033[0m";

    }

  } else {

    return "\033[1;31mUsuário não está conectado\033[0m";

  }

}

string Sistema::leave_server(int id, const string nome) {
  
  auto find = this->usuariosLogados.find(id);

  if(find != this->usuariosLogados.end()){

    int server = check_duplicates_server(nome);

    if(userOnAServer(id)==-1){

      return "\033[1;31mVocê não está em qualquer servidor\033[0m";

    } else if(server < 0) {

      return "\033[1;31mServidor não existe!\033[0m";

    } else if(server >= 0 && find->second.first != nome){

      return "\033[1;31mUsuário não está conectado no servidor informado\033[0m";
    
    } else if(server >= 0 && find->second.first == nome){

      this->usuariosLogados[find->first] = std::make_pair("","");
      this->servidores[server].remove_participant(id);
      return "Saindo do servidor \""+nome+"\"";

    }

  } else {

    return "\033[1;31mUsuário não está conectado\033[0m";

  }

}

string Sistema::list_participants(int id) {

  auto find = this->usuariosLogados.find(id);

  if(find != this->usuariosLogados.end()){

    int server = check_duplicates_server(find->second.first);

    if(server >= 0){
      
      return this->servidores[server].allParticipantsToString(this->usuarios);

    } else {

      return "\033[1;31mUsuário não está visualizando nenhum servidor!\033[0m";

    }

  } else {

    return "\033[1;31mUsuário não está conectado\033[0m";

  }

}

string Sistema::list_channels(int id) {

  if(this->list_channels_by_id_viewer(id) != ""){
    return this->list_channels_by_id_viewer(id);
  } else {

    return "O servidor visualizado não possui canais de texto!";

  }
  
}

string Sistema::create_channel(int id, const string nome) {

  auto find = this->usuariosLogados.find(id);

  if(find != this->usuariosLogados.end()){

    int server = check_duplicates_server(find->second.first);

    if(server >= 0){
      if(this->servidores[server].check_duplicates_chanel(nome) < 0){

        this->servidores[server].addCanaisTexto(CanalTexto(nome));
        this->usuariosLogados[find->first] = std::make_pair(find->second.first,nome);
        return "Canal de texto \"" + nome + "\" criado";

      } else {
        
        return "\033[1;31mCanal de texto \"" + nome + "\" já existe!\033[0m";

      }

    } else {

      return "\033[1;31mUsuário não está visualizando nenhum servidor!\033[0m";

    }

  } else {

    return "\033[1;31mUsuário não está conectado\033[0m";

  }

}

string Sistema::enter_channel(int id, const string nome) {
  auto find = this->usuariosLogados.find(id);

  if(find != this->usuariosLogados.end()){

    int server = check_duplicates_server(find->second.first);

    if(server >= 0){
      if(this->servidores[server].check_duplicates_chanel(nome) >= 0){

        this->usuariosLogados[find->first] = std::make_pair(find->second.first,nome);
        return "Entrou no canal de texto \"" + nome + "\"";

      } else {
        
        return "\033[1;31mCanal \"" + nome + "\" não existe!\033[0m";

      }

    } else {

      return "\033[1;31mUsuário não está visualizando nenhum servidor!\033[0m";

    }

  } else {

    return "\033[1;31mUsuário não está conectado\033[0m";

  }

}

string Sistema::leave_channel(int id) {

  auto find = this->usuariosLogados.find(id);

  if(find != this->usuariosLogados.end()){

    int server = check_duplicates_server(find->second.first);

    if(server >= 0){

      if(this->servidores[server].check_duplicates_chanel(find->second.second) >= 0){

          this->usuariosLogados[find->first] = std::make_pair(find->second.first,"");
          return "Saindo do canal";

      } else {

          return "\033[1;31mUsuário não está visualizando nenhum canal!\033[0m";

      }

    } else {

      return "\033[1;31mUsuário não está visualizando nenhum servidor!\033[0m";

    }

  } else {

    return "\033[1;31mUsuário não está conectado\033[0m";

  }

}

string Sistema::send_message(int id, const string mensagem) {

  auto find = this->usuariosLogados.find(id);

  if(find != this->usuariosLogados.end()){

    int server = check_duplicates_server(find->second.first);

    if(server >= 0){

      int chanel = this->servidores[server].check_duplicates_chanel(find->second.second);
      if(chanel >= 0){

          std::string data = this->currentDateTime();
          this->servidores[server].addMensagens(chanel, Mensagem(data, id, mensagem));
          return "Mensagem enviada!";

      } else {

          return "\033[1;31mUsuário não está visualizando nenhum canal!\033[0m";

      }

    } else {

      return "\033[1;31mUsuário não está visualizando nenhum servidor!\033[0m";

    }

  } else {

    return "\033[1;31mUsuário não está conectado\033[0m";

  }
  
}

string Sistema::list_messages(int id) {

  auto find = this->usuariosLogados.find(id);

  if(find != this->usuariosLogados.end()){

    int server = check_duplicates_server(find->second.first);

    if(server >= 0){

      int chanel = this->servidores[server].check_duplicates_chanel(find->second.second);
      if(chanel >= 0){

          std::string saida = this->servidores[server].allMessagesToString(this->usuarios, chanel);

          if(saida != ""){

            return saida;

          } else {

            return "Sem mensagens para exibir";

          }

      } else {

          return "\033[1;31mUsuário não está visualizando nenhum canal!\033[0m";

      }

    } else {

      return "\033[1;31mUsuário não está visualizando nenhum servidor!\033[0m";

    }

  } else {

    return "\033[1;31mUsuário não está conectado\033[0m";

  }

}

/* IMPLEMENTAR MÉTODOS PARA OS COMANDOS RESTANTES */

int Sistema::is_registered_server(int id, const std::string nome){

  for(int x = 0; x < this->servidores.size(); x++){
    
    if(this->servidores[x].getUsuarioDonoId()==id && this->servidores[x].getNome()==nome){
      return x;

    } else if(this->servidores[x].getUsuarioDonoId()!=id && this->servidores[x].getNome()==nome){
      
      return -1;

    }

  }

  return -2;

}

int Sistema::is_registered_user_id(int id){

  for(int x = 0; x < this->usuarios.size(); x++){
    
    if(this->usuarios[x].getId()==id){
      return x;

    }

  }

  return -1;

}

int Sistema::is_registered_user(const string email, const string senha){

  for(int x = 0; x < this->usuarios.size(); x++){

    if(this->usuarios[x].getEmail()==email && this->usuarios[x].getSenha()==senha){
      return x;

    }

  }

  return -1;

}

bool Sistema::check_duplicates_user(const std::string nome, const std::string email, const std::string senha){

  for(int x = 0; x < this->usuarios.size(); x++){

    if(this->usuarios[x].getNome()==nome && this->usuarios[x].getEmail()==email && this->usuarios[x].getSenha()==senha){

      return true;

    }

  }

  return false;

}

int Sistema::check_duplicates_server(const std::string nome){

  for(int x = 0; x < this->servidores.size(); x++){

    if(this->servidores[x].getNome()==nome){

      return x;

    }

  }

  return -1;

}

string Sistema::list_servers_by_id_owner(int id){

  string saida;

  for(int x = 0; x < this->servidores.size(); x++){
    
    if(this->servidores[x].getUsuarioDonoId()==id){
      
      if(x==0){
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

string Sistema::list_channels_by_id_viewer(int id){

  auto find = this->usuariosLogados.find(id);

  string saida;

  for(int x = 0; x < this->servidores.size(); x++){
    
    if(this->servidores[x].getNome() == find->second.first){
      
      int servidor = this->check_duplicates_server(find->second.first);
      
      return servidores[servidor].allChannelsToString();
      
    }

  }

  return "Servidor não encontrado";

}

int Sistema::userOnAServer(int id){

  for(int x = 0; x < this->servidores.size(); x++){

    return this->servidores[x].check_duplicates_participant(id);

    }

  return -1;

}

string Sistema::currentDateTime() {
    setlocale(LC_ALL,NULL);

    time_t now = time(0);
    struct tm tstruct;
    char buf[80];
    tstruct = *localtime(&now);
    
    strftime(buf, sizeof(buf), "<%Y-%m-%d - %X>", &tstruct);

    return buf;
}
