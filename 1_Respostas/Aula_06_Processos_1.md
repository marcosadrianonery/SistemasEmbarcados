1. Como se utiliza o comando `ps` para:

(a) Mostrar todos os processos rodando na máquina?

```bash
ps -aux

```

(b) Mostrar os processos de um usuário?

```bash

ps -u username

```

(c) Ordenar todos os processos de acordo com o uso da CPU?

```bash
ps aux --sort=-pcpu

```

(d) Mostrar a quanto tempo cada processo está rodando?

```bash
ps -ef --sort=start_time

```


2. De onde vem o nome `fork()`?

- Fork vem de bifurcação, onde de um ponto/segmento derivam-se vários. No caso dos processos, um processo se divide em vários.

3. Quais são as vantagens e desvantagens em utilizar:

(a) `system()`?

- A função system() permite executar um comando dentro do programa, criando um sub-processo (processo-filho). Sua saída é retornada no shell. Sua vantagem é a execução simples. As desvantagens são que esta executa comandos para uma plataforma específica e abre brecha para falhas.

(b) `fork()` e `exec()`?

- fork()

 A função fork() é usada para criar um novo processo duplicando o processo existente do ponto onde a função foi chamada. O processo do qual a função foi chamada se chama processo-pai e o novo processo criado, processo-filho. O processo filho é uma cópia duplicada do processo pai. 

 O processo filho possui um PID como qualquer outro processo rodando no sistema operacional.

A função fork() retorna:

- No processo-pai, o PID do processo do filho.

- No processo-filho, retorna 0;

Quando um filho é criado, os valores das variáveis, e atribuições realizadas são passadas para o filho, mas após a criação do processo-filho, tudo o que ocorre no novo processo não se relaciona com o pai.

A comunicação dos dois processos é feito por meio de pipe, ou sinais.

- exec()

 As primitivas exec() constituem na verdade uma família de funções (execl, execlp, execle, execv, execvp) que permitem o lançamento da execução de um programa externo ao processo. Não existe a criação efetiva de um novo processo, mas simplesmente uma substituição do programa de execução. 

  Na chamada de uma função exec(), existe um recobrimento do segmento de instruções do processo que chama a função. Desta forma, não existe retorno de um exec() cuja execução seja correta (o endereço de retorno desaparece). Em outras palavras, o processo que chama a função exec() morre. 

4. É possível utilizar o `exec()` sem executar o `fork()` antes?

É possível, mas tudo que estiver abaixo do função exec() não será executado, pois depois de realizar o comando, a execução do processo termina. 

5. Quais são as características básicas das seguintes funções:

(a) `execlp()`?

int execlp(const char *file, const char *arg,.../*(char *)NULL */)

**file**: filename associated with the file being executed

**const char *arg and ellipses**: describe a list of one more pointers to null-terminated strings that represent the argument list available to the executed program. 

(b) `execv()`?

```
int execv(const char *path, char *const argv[])
```
**path**: should point to the path of the file being executed.

**argv[]**: is a null terminated array of character pointers.

(c) `exece()`?

The  `execle()`  and `execvpe()` functions allow the caller to specify the environment of the executed program via the argument envp.  The envp argument is an array of pointers to null-terminated strings and must be terminated  by  a null pointer.  The other functions take the environment for the new process image from the external variable environ in the calling process.


(d) `execvp()`?

- Sintax:

```
int execvp(const char *file, char *const argv[]);
```
**file**: points to the fine name associated with the file being executed. The file could be in the current path.

**argv**: is a null terminated array of character pointers. 


(e) `execve()`?

```
int execve(const char *filename, char *const argv[], char *const envp[]);
```

**execve()**: executes the program pointed to by filename must be either a binary executable, or a script starting with a line of the form:

#! interpreter [optional-arg]

**argv** is an array of argument strings passed to the new program. By convention, the first of these strings (i.e, argv[0]) should contain the filename associated with the file being executed. 

**envp** is an array of strings, conventionally of the form **key=value**, which are passed as environment to the new program. The argv and envp arrays must each include a null pointer at the end of the array.

The argument vector and environment can be accessed by the called  program's main function, when it is defined as:

```
int main(int argc, char *argv[], char *envp[])
```

Note, however, that the use of a third argument to the main function is not specified in POSIX.1; according to POSIX.1, the environment  should be accessed via the external variable environ(7).


(f) `execle()`?

```
int execle(const char *path, const char *arg, .../*, (char *) NULL, char * const envp[] */);
```
**char * const envp[]**: allow the caller to specify the environment of the executed program via the argument envp.

**envp**: This argument is an array of pointers to null-terminated strings and must be terminated by a null pointer. The other functions take the environment for the new process image from the external variable environ in the calling process.
