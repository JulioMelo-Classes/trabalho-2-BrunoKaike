#ifndef MENSAGEM_H
#define MENSAGEM_H

#include <string>

/*
Ok

Documentação 0 - Faltou a documentação!
*/
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
    
    Mensagem(std::string dataHora, int enviadaPor, std::string conteudo);

    //Getter
    int getEnviadoPor();

    std::string getData();

    std::string getConteudo();

};

#endif
