> *This project was created as part of the 42 curriculum by **kqueiroz** and **nde-sant***.

---

## Description
In this project, our goal is to build a small functional shell. A shell is a 
command interpreter that acts as a bridge between the user and the operating system. 
The steps of a shell program are basically reading a command, interpreting it, and executing it.
For this implementation, we based ourselves on the functioning of [bash](https://www.gnu.org/savannah-checkouts/gnu/bash/manual/) 
as a reference.

## Features
- Redirections (<, >, <<, >>);
- Pipes;
- Environment variables
- $?
- Builtins:
  - echo with flag `-n`
  - cd
  - pwd
  - export
  - unset
  - env
  - exit

 ## Instructions
Clone the repository and enter the folder:
```bash
git clone https://github.com/nicolasgsantana/minishell.git
cd minishell
```
Compile and run the program:
```bash
make
./minishell
```
### Feel free to test it!
Some examples:
```bash
ls -la
```
```bash
echo “Hello, Shell!”
```
```bash
cat < test.txt | grep morning > result.txt
```
```bash
export NEW_VAR=value
```
To exit, type `exit` or `Ctrl + d`

## Resources
References used during development:

- [What is Bash?](https://opensource.com/resources/what-bash);
- [Minishell Guide](https://medium.com/@laamirimarouane8/42-minishell-guide-53600f49742b);
- [Open Group Documentation](https://pubs.opengroup.org/onlinepubs/009695399/utilities/xcu_chap02.html);
- [Introduction to Systems Programming: a Hands-on Approach by Gustavo A. Junipero Rodriguez-Rivera and Justin Ennen - chap. 5](https://www.cs.purdue.edu/homes/grr/SystemsProgrammingBook/Book/Chapter5-WritingYourOwnShell.pdf);
- [The Architecture of Open Source Applications (Volume 1) The Bourne-Again Shell](https://aosabook.org/en/v1/bash.html);
- [Military Grade C/C++ Lexer from Scratch - Tsoding](https://youtu.be/AqyZztKlSGQ?si=cJEnBszUpOx-J1P2);
- [The Bash Parser](https://mywiki.wooledge.org/BashParser);
- [Bash Features Capítulo 3.1.1](https://www.gnu.org/software/bash/manual/html_node/Shell-Operation.html);
- AI was used to:
  - Perform isolated tests of some functionalities in the execution of built-in and native functions;
  - Quick searches for concepts;

 [Português](https://github.com/nicolasgsantana/minishell/blob/main/README.md) | *English*
