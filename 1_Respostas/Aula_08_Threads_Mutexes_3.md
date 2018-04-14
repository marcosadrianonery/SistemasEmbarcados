1. Apresente as características e utilidades das seguintes funções:

(a) `popen()`

popen - initiate pipe streams to or from a process

## synopsis

```C
	#include <stdio.h>
	FILE *popen(const char *command, const char *mode);
```

## Description

The **popen()** function shall execute the command specified by the string **command**.
It shall create a pipe between the calling program and the executed command, and shall 
return a pointer to a stream that can be used to either read from or write to the pipe.

The environment of the executed command shall be as if a child process were created 
within the **popen()** call using the **fork()** function, and the child invoked
the **sh** utility using the call:

```
execl(shell path, "sh", "-c", command, (char*));

```
where **shell** is an unspecified pathname for the **sh** utility.

the **popen()** function shall ensure that any streams from previous **popen()** calls 
that remain open in the parent process are closed in the new child process.

the **mode** argument to **popen()** is a string that specifies I/O mode:

1. If **mode** is **r**, when the child process is started, its file descriptor STDOUT_FILENO 
shall be the writable end of the pipe, and the file descriptor **fileno(stream)** in the 
calling process, where **stream** is the stream pointer returned by **popen()**, shall be 
the readable end of the pipe.

2. If **mode** is **w**, when the child process is started, its file descriptor STDIN_FILENO 
shall be the readable end of the pipe, and the file descriptor **fileno(stram)** in the 
calling process, where **stream** pointer returned by **popen()**, shall be the writable 
end of the pipe.

3. If **mode** is any other value, the result is undefined. 

## Return Value

Upon sucessful completion, **popen()** shall return a pointer to an open stram that can be used 
to read or write to the pipe. Otherwise, it shall return a null pointer and may set **errno** to 
indicate the error.

(b) `pclose()`

pclose - close a pipe stram to or from a process

## Synopsis

```C
	#include <stdio.h>
	int pclose(FILE *stream);
```
## Description

The **pclose()** function shall close a stream that was opened by **popen()**, wait for the command
to terminate, and return the termination status of the process that was running the command language
interpreter. However, if a call caused the termination status to be unavailable to **pclose()**, then 
**pclose()** shall return -1 with **errno** set to [ECHILD] to report this situation.

## Return Value

Upon successful return, **pclose()** shall return the termination status of the command language
interpreter. Otherwise, **pclose()** shall return -1 and set ***errno** to indicate the error.

(c) `fileno()`

"stands for: file number"

fileno - map a stram pointer to a file descriptor

## Synopsis

```C
	#include <stdio.h>
	int fileno(FILE *stram);
```
## Description 

The *fileno()* function shall return the integer file descriptor associated with the stram ponted to by *stream*.

## Return Value

Upon succesful completion, *fileno()* shall return the integer value of the file descriptor associated 
with *stream*. Otherwise, the value -1 shall be returned and *errno* set to indicate the error.

## ERRORS

The *fileno()* function may fail if:

The *stream* argument is not a valid stream.

2. Quais são as vantagens e desvantagens em utilizar:

(a) `popen()?`

Vantagens:

- Com esta função, o novo processo criado executa somente o comando que está dentro do argumento da função 
popen(), sendo possível executar a expansão de caracteres em uma string só ( ex.: "ls -l", 
ao invês de "ls","-l" em exec()), já que um shell é criado para isto;

Desvantagens:

- Perde-se a funcionalidade do fork(), pois o processo criado só executa o programa, não cria uma cópia 

(b) `exec()?`

Vantagens:

- Após o fork() ser realizado, é possível realizar diversas tarefas ainda dentro do processo filho e 
só depois usar exec();

Desvantagens:

- A sintaxe para usar a função exec() é um pouco mais trabalhosa que para popen();
