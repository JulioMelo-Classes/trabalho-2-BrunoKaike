# Concordo

Concordo é um projeto simplificado do Discord baseado na entrada de dados pelo console ou arquivos de texto.

## Objetivos

Projeto desenvolvido e apresentado ao curso de Tecnologia da Informação da Universidade Federal do Rio Grande do Norte, como requisito parcial para obtenção de nota na disciplina de Linguagem de Programação I, ministrada pelo professor Julio Cesar Paulino de Melo(*<julio.melo@imd.ufrn.br>*).

## O que é o Discord?

O Discord é um software gratuito de mensagens instantâneas que permite que as pessoas conversem pela Internet . Ele foi originalmente criado para pessoas que jogam videogame , mas agora é usado por outras pessoas.

## Sobre o projeto
<center>
<img src="img/logo.png">
</center>

O projeto KenoBot foi desenvolvido utilizando da linguagem C++ e do gerador de sistema de compilação Cmake.

## Para compilar

Cmake:
```console
mkdir build
cd build
cmake ..
cmake --build .
```

## Para executar
Você pode rodar o sistema e em logo depois digitar os comandos seguidos de ENTER
```console
./concordo
```

Ou pode criar um arquivo de texto com uma lista de comandos (um por linha) e executar o sistema redirecionando esse arquivo como entrada padrão:

Teste 1 (Fornecido pelo professor)
```console
./concordo < ../data/script_comandos.txt

```

<details>
<summary>Testes de funcionalidade</summary>


<p>Criar usuário</p>

```console
./concordo < ../data/functional/teste1.txt

```

<p>Login</p>

```console
./concordo < ../data/functional/teste2.txt

```

<p>Logout</p>

```console
./concordo < ../data/functional/teste3.txt

```

<p>Criar servidor</p>

```console
./concordo < ../data/functional/teste4.txt

```

<p>Modificar descrição do servidor</p>

```console
./concordo < ../data/functional/teste5.txt

```

<p>Inserir código de convite do servidor</p>

```console
./concordo < ../data/functional/teste6.txt

```

<p>Remover código de convite do servidor</p>

```console
./concordo < ../data/functional/teste7.txt

```

<p>Listar servidores criados por um determinado usuário</p>

```console
./concordo < ../data/functional/teste8.txt

```

<p>Remover servidor</p>

```console
./concordo < ../data/functional/teste9.txt

```

<p>Entrar em servidor</p>

```console
./concordo < ../data/functional/teste10.txt

```

<p>Entrar em servidor com código de convite</p>

```console
./concordo < ../data/functional/teste11.txt

```

<p>Sair de servidor</p>

```console
./concordo < ../data/functional/teste12.txt

```

<p>Listar participantes de um servidor que está sendo visualizado por um determinado usuário</p>

```console
./concordo < ../data/functional/teste13.txt

```

<p>Listar canais de texto de um servidor que está sendo visualizado por um determinado usuário</p>

```console
./concordo < ../data/functional/teste14.txt

```

<p>Criar canal de texto em um servidor que está sendo visualizado por um determinado usuário</p>

```console
./concordo < ../data/functional/teste15.txt

```

<p>Entrar em um canal de um servidor que está sendo visualizado por um determinado usuário</p>

```console
./concordo < ../data/functional/teste16.txt

```

<p>Sair de um canal de um servidor que está sendo visualizado por um determinado usuário</p>

```console
./concordo < ../data/functional/teste17.txt

```

<p>Enviar mensagem em um canal de texto</p>

```console
./concordo < ../data/functional/teste18.txt

```

<p>Visualizar mensagens de um canal de texto em que um usuário está conectado</p>

```console
./concordo < ../data/functional/teste19.txt

```

</details>

<details>
<summary>Testes de Erro</summary>


<p>Não foi possível criar usuário (Usuário já existe)</p>

```console
./concordo < ../data/error/teste1.txt

```

<p>Não foi possível logar (Usuário ou senha inválidos)</p>

```console
./concordo < ../data/error/teste5.txt

```

<p>Não foi possível interagir com o servidor (Usuário não está logado)</p>

```console
./concordo < ../data/error/teste6.txt

```

<p>Não foi possível criar sevidor (Servidor já existe)</p>

```console
./concordo < ../data/error/teste2.txt

```

<p>Não foi possível modificar descrição (Servidor não existe)</p>

```console
./concordo < ../data/error/teste3.txt

```

<p>Não foi possível modificar descrição (Você não é o dono do servidor)</p>

```console
./concordo < ../data/error/teste7.txt

```

<p>Não foi possível entrar em servidor (Requer código de convite)</p>

```console
./concordo < ../data/error/teste4.txt

```

<p>Não foi possível remover servidor (Você não é o dono do servidor)</p>

```console
./concordo < ../data/error/teste11.txt

```

<p>Não foi possível sair do servidor (Usuário não está participando de nenhum servidor)</p>

```console
./concordo < ../data/error/teste8.txt

```

<p>Não foi possível sair do servidor (Usuário não está conectado no servidor informado)</p>

```console
./concordo < ../data/error/teste10.txt

```

<p>Não foi possível criar canal de texto (Canal de texto já existe)</p>

```console
./concordo < ../data/error/teste9.txt

```

<p>Não foi possível sair do canal de texto (Usuário não está visualizando nenhum canal)</p>

```console
./concordo < ../data/error/teste12.txt

```

</details>

## Contato

Bruno Kaike do Nascimento Batista -
*<brunokaike@ufrn.edu.br>*

Link do projeto: [https://github.com/JulioMelo-Classes/trabalho-2-BrunoKaike.git](https://github.com/JulioMelo-Classes/trabalho-2-BrunoKaike.git)
