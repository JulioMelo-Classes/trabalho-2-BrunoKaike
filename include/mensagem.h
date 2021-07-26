#ifndef MENSAGEM_H
#define MENSAGEM_H

class Mensagem{
	/*
		TODO implementação dos atributos e métodos
	*/
  private:

    std::string dataHora;
    int enviadaPor;
    std::string conteudo;

  public:

    //Constructor
    
    Mensagem(std::string dataHora, int enviadaPor, std::string conteudo){

      this->dataHora = dataHora;
      this->enviadaPor = enviadaPor;
      this->conteudo = conteudo;

    }

};

#endif
