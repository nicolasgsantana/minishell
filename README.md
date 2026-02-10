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
## Recursos
<!-- 
listando referências clássicas relacionadas ao tópico (documentação, artigos, tutoriais, etc.), bem como uma descrição de como a IA foi usada
— especificando para quais tarefas e quais partes do projeto -->
https://pubs.opengroup.org/onlinepubs/009695399/utilities/xcu_chap02.html
https://www.cs.purdue.edu/homes/grr/SystemsProgrammingBook/Book/Chapter5-WritingYourOwnShell.pdf
https://medium.com/@laamirimarouane8/42-minishell-guide-53600f49742b
https://opensource.com/resources/what-bash

