> *Este projeto foi criado como parte do currículo da 42 por **kqueiroz** e **nde-sant***

---

## Descrição
Neste projeto temos o objetivo de construir um pequeno shell funcional. Um shell é um 
interpretador de comandos que atua como uma ponte entre o usuário e o sistema operacional. 
As etapas de um programa shell são basicamente ler um comando, interpretar e executar.
Para esta implementação nos baseamos no funcionamento do [bash](https://www.gnu.org/savannah-checkouts/gnu/bash/manual/) 
como referência.

## Funcionalidades Disponíveis
- Redirecionamentos (<, >, <<, >>);
- Pipes;
- Variáveis de ambiente
- $?
- Builtins:
  - echo com flag `-n`
  - cd
  - pwd
  - export
  - unset
  - env
  - exit

## Instruções
Clone o repositório e entre na pasta:
``` bash
git clone https://github.com/nicolasgsantana/minishell.git
cd minishell
```
Compile e execute o programa:
``` bash
make
./minishell
```
### Teste livremente!
Alguns exemplos:
```bash
ls -la
```
```bash
echo "Hello, Shell!"
```
```bash
cat < test.txt | grep morning > result.txt
```
```bash
export NEW_VAR=value
```
Para sair digite `exit` ou `Ctrl + d`

## Recursos
Referências utilizadas durante o desenvolvimento:

- [O que é Bash?](https://opensource.com/resources/what-bash);
- [Guia Minishell](https://medium.com/@laamirimarouane8/42-minishell-guide-53600f49742b);
- [Documentação Open Group](https://pubs.opengroup.org/onlinepubs/009695399/utilities/xcu_chap02.html);
- [Introduction to Systems Programming: a Hands-on Approach by Gustavo A. Junipero Rodriguez-Rivera and Justin Ennen - cap. 5](https://www.cs.purdue.edu/homes/grr/SystemsProgrammingBook/Book/Chapter5-WritingYourOwnShell.pdf);
- [The Architecture of Open Source Applications (Volume 1) The Bourne-Again Shell](https://aosabook.org/en/v1/bash.html);
- [Military Grade C/C++ Lexer from Scratch - Tsoding](https://youtu.be/AqyZztKlSGQ?si=cJEnBszUpOx-J1P2);
- [The Bash Parser](https://mywiki.wooledge.org/BashParser);
- [Bash Features Chapter 3.1.1](https://www.gnu.org/software/bash/manual/html_node/Shell-Operation.html);
- A IA foi utilizada para:
  - Fazer testes isolados de algumas funcionalidades na execução de funções builtins e nativas;
  - Pesquisas rápidas de conceitos;

*Português* | [English](https://github.com/nicolasgsantana/minishell/blob/main/README_en.md)
