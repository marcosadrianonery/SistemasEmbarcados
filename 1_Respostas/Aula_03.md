Para todas as questões, compile-as com o gcc e execute-as via terminal.

1. Crie um "Olá mundo!" em C.
```C
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
	 printf("Olá mundo!");
	return 0;
}
```

2. Crie um código em C que pergunta ao usuário o seu nome, e imprime no terminal "Ola " e o nome do usuário. Por exemplo, considerando que o código criado recebeu o nome de 'ola_usuario_1':

```C
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{

	char nome[128];
	printf("Qual é o seu nome? ");
	scanf("%s", nome);
	printf("Olá %s. \n", nome);
	return 0;
}
```

3. Apresente os comportamentos do código anterior nos seguintes casos:

(a) Se o usuário insere mais de um nome.
```bash
$ ./ola_usuario_1
$ Digite o seu nome: Eu Mesmo

alunos@LAB-SS-PC:~/Área de Trabalho/Aula_03$ ./reciprocal
Qual é o seu nome? Marcos Adriano
Olá Marcos.
```

(b) Se o usuário insere mais de um nome entre aspas duplas. Por exemplo:
```bash
$ ./ola_usuario_1
$ Digite o seu nome: "Eu Mesmo"

alunos@LAB-SS-PC:~/Área de Trabalho/Aula_03$ ./reciprocal
Qual é o seu nome? "Marcos Adriano"    
Olá "Marcos. 
```

(c) Se é usado um pipe. Por exemplo:
```bash
$ echo Eu | ./ola_usuario_1

alunos@LAB-SS-PC:~/Área de Trabalho/Aula_03$ echo Marcos | ./reciprocal
Qual é o seu nome? Olá Marcos. 
```

(d) Se é usado um pipe com mais de um nome. Por exemplo:
```bash
$ echo Eu Mesmo | ./ola_usuario_1

alunos@LAB-SS-PC:~/Área de Trabalho/Aula_03$ echo Marcos Adriano | ./reciprocal
Qual é o seu nome? Olá Marcos.  
```

(e) Se é usado um pipe com mais de um nome entre aspas duplas. Por exemplo:
```bash
$ echo "Eu Mesmo" | ./ola_usuario_1

alunos@LAB-SS-PC:~/Área de Trabalho/Aula_03$ echo "Marcos Adriano" | ./reciprocal
Qual é o seu nome? Olá Marcos. 

```

(f) Se é usado o redirecionamento de arquivo. Por exemplo:
```bash
$ echo Ola mundo cruel! > ola.txt
$ ./ola_usuario_1 < ola.txt

alunos@LAB-SS-PC:~/Área de Trabalho/Aula_03$ echo Ola mundo cruel! > ola.txt
alunos@LAB-SS-PC:~/Área de Trabalho/Aula_03$ ./reciprocal < ola.txt
Qual é o seu nome? Olá Ola. 

```

4. Crie um código em C que recebe o nome do usuário como um argumento de entrada (usando as variáveis argc e *argv[]), e imprime no terminal "Ola " e o nome do usuário. Por exemplo, considerando que o código criado recebeu o nome de 'ola_usuario_2':

```bash
$ ./ola_usuario_2 Eu
$ Ola Eu
```
```C
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
	printf("Olá, %s. \n", argv[1]);
	return 0;
}
```

5. Apresente os comportamentos do código anterior nos seguintes casos:

(a) Se o usuário insere mais de um nome.
```bash
$ ./ola_usuario_2 Eu Mesmo

drico@drico-VirtualBox:~/Área de Trabalho/Sistemas_Embarcados/Aula_03/CODIGO_Arg
umento_ArgcEargv$ ./reciprocal Marcos Adriano
Olá, Marcos. 
```

(b) Se o usuário insere mais de um nome entre aspas duplas. Por exemplo:
```bash
$ ./ola_usuario_2 "Eu Mesmo"

drico@drico-VirtualBox:~/Área de Trabalho/Sistemas_Embarcados/Aula_03/CODIGO_Arg
umento_ArgcEargv$ ./reciprocal "Marcos Adriano"
Olá, Marcos Adriano. 
```

(c) Se é usado um pipe. Por exemplo:
```bash
$ echo Eu | ./ola_usuario_2

drico@drico-VirtualBox:~/Área de Trabalho/Sistemas_Embarcados/Aula_03/CODIGO_Arg
umento_ArgcEargv$ echo Marcos | ./reciprocal
Olá, (null).

```

(d) Se é usado um pipe com mais de um nome. Por exemplo:
```bash
$ echo Eu Mesmo | ./ola_usuario_2

drico@drico-VirtualBox:~/Área de Trabalho/Sistemas_Embarcados/Aula_03/CODIGO_Arg
umento_ArgcEargv$ echo Marcos Adriano | ./reciprocal
Olá, (null). 

```

(e) Se é usado um pipe com mais de um nome entre aspas duplas. Por exemplo:
```bash
$ echo Eu Mesmo | ./ola_usuario_2

drico@drico-VirtualBox:~/Área de Trabalho/Sistemas_Embarcados/Aula_03/CODIGO_Arg
umento_ArgcEargv$ echo "Marcos Adriano |" ./reciprocal
Marcos Adriano | ./reciprocal

```

(f) Se é usado o redirecionamento de arquivo. Por exemplo:
```bash
$ echo Ola mundo cruel! > ola.txt
$ ./ola_usuario_2 < ola.txt

drico@drico-VirtualBox:~/Área de Trabalho/Sistemas_Embarcados/Aula_03/CODIGO_Arg
umento_ArgcEargv$ echo Ola mundo cruel! > ola.txt
drico@drico-VirtualBox:~/Área de Trabalho/Sistemas_Embarcados/Aula_03/CODIGO_Arg
umento_ArgcEargv$ ./reciprocal < ola.txt
Olá, (null). 
```

6. Crie um código em C que faz o mesmo que o código da questão 4, e em seguida imprime no terminal quantos valores de entrada foram fornecidos pelo usuário. Por exemplo, considerando que o código criado recebeu o nome de 'ola_usuario_3':

```bash
$ ./ola_usuario_3 Eu
$ Ola Eu
$ Numero de entradas = 2
```
```C
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
	printf("Olá, %s. \n", argv[1]);
	printf("Numero de entradas =  %d.", argc);
	return 0;
}

```

```bash
### Saida
drico@drico-VirtualBox:~/Área de Trabalho/Sistemas_Embarcados/Aula_03/Questão_0
6$ ./reciprocal Marcos
Olá, Marcos. 
Numero de entradas =  2.
```
7. Crie um código em C que imprime todos os argumentos de entrada fornecidos pelo usuário. Por exemplo, considerando que o código criado recebeu o nome de 'ola_argumentos':

```bash
$ ./ola_argumentos Eu Mesmo e Minha Pessoa
$ Argumentos: Eu Mesmo e Minha Pessoa
```

```C
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
	int n=1;

	printf("Argumentos: ");	
	for(1; n < argc; n++)
	{
	printf("%s ", argv[n]);
	}
	return 0;
}221
```


8. Crie uma função que retorna a quantidade de caracteres em uma string, usando o seguinte protótipo:
`int Num_Caracs(char *string);` Salve-a em um arquivo separado chamado 'num_caracs.c'. Salve o protótipo em um arquivo chamado 'num_caracs.h'. Compile 'num_caracs.c' para gerar o objeto 'num_caracs.o'.
```C
//MAIN
#include <stdio.h>
#include <stdlib.h>
#include "num_caracs.h"

int main(int argc, char **argv)
{
	int tamanho;
	char numero[100];
	gets(numero);
	tamanho = Num_Caracs(numero);
	printf("Tamanho: %d ", tamanho);
	return 0;
}

//num_caracs.h
int Num_Caracs(char *string);

//num_caracs.c
#include "num_caracs.h"

int Num_Caracs(char *string)
{
	int tamanho;	
	tamanho = strlen(string);
	return tamanho;
}


```
```bash
drico@drico-VirtualBox:~/Área de Trabalho/Sistemas_Embarcados/Aula_03/Ques
tão_08$ ./num_caracs
Marcos
Tamanho: 6
```

9. Re-utilize o objeto criado na questão 8 para criar um código que imprime cada argumento de entrada e a quantidade de caracteres de cada um desses argumentos. Por exemplo, considerando que o código criado recebeu o nome de 'ola_num_caracs_1':

```bash
$ ./ola_num_caracs_1 Eu Mesmo
$ Argumento: ./ola_num_caracs_1 / Numero de caracteres: 18
$ Argumento: Eu / Numero de caracteres: 2
$ Argumento: Mesmo / Numero de caracteres: 5
```
```bash
drico@drico-VirtualBox:~/Área de Trabalho/Sistemas_Embarcados/Aula_03/Questão_0
9$ ./num_caracs
Marcos Adriano Nery de Abrantes
Argumento: Marcos / Numero de caracteres: 6.
Argumento: Adriano / Numero de caracteres: 7.
Argumento: Nery / Numero de caracteres: 4.
Argumento: de / Numero de caracteres: 2.
Argumento: Abrantes / Numero de caracteres: 8.
```

```C
// MAIN
#include <stdio.h>
#include <stdlib.h>
#include "num_caracs.h"

int main(int argc, char **argv)
{
	char numero[100];
	gets(numero);	
	Num_Caracs(numero);
	return 0;
}

// NUM_CARACS.c
#include "num_caracs.h"

int Num_Caracs(char *string)
{
	int tamanho = 0, tamanho_total, aux = 0, n;
	char temporaria[50];	
	tamanho_total = strlen(string);
	
	for (n = 0; n <= tamanho_total ; n++)
	{		
	
		temporaria[aux] = string[n];	
	
			if((string[n] == ' ') || (string[n] == '\n')|| (n == tamanho_total)) {
			temporaria[aux] = '\0';
			tamanho = strlen(temporaria);
			printf("Argumento: %s / Numero de caracteres: %d.\n", temporaria, tamanho);
			aux = -1;
			}
		aux++;
	}
	return 0;
}

//NUM_CARACS.h
int Num_Caracs(char *string);

```
10. Crie um Makefile para a questão anterior.

11. Re-utilize o objeto criado na questão 8 para criar um código que imprime o total de caracteres nos argumentos de entrada. Por exemplo, considerando que o código criado recebeu o nome de 'ola_num_caracs_2':

```bash
$ ./ola_num_caracs_2 Eu Mesmo
$ Total de caracteres de entrada: 25
```

12. Crie um Makefile para a questão anterior.
