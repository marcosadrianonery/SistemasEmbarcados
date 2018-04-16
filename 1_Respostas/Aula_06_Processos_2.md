
1. Crie um código em C para gerar três processos-filho usando o `fork()`.
```bash
marcosadriano@marcosadriano:~/Área de trabalho/Aula_06/Questão_01$ ./bib_arqs
Pid pai antes do primeiro Fork() -  4601
Pid filho 1 -  4602
Pid pai antes do segundo Fork(), o primeiro filho foi criado-  4601
Pid filho 2 - 4603
Pid pai  antes do terceiro Fork(), o segundo filho foi criado-  4601
Pid filho 3 - 4604
Pid pai  depois do terceiro Fork(), o terceiro filho já foi criado-  4601
```
```C
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/signal.h>
#include <errno.h>


int main(void) {
int pid_filho_1, pid_filho_2, pid_filho_3,  pid_pai;

printf("Pid pai antes do primeiro Fork() -  %d\n", getpid());

pid_filho_1 = fork();

if (pid_filho_1 == 0)
	{
		printf("Pid filho 1 -  %d\n", getpid());
	}
else{
		sleep(1);
		printf("Pid pai antes do segundo Fork(), o primeiro filho foi criado-  %d\n", getpid());

		pid_filho_2 = fork();

		if (pid_filho_2 == 0)
			{
				printf("Pid filho 2 - %d\n", getpid());
			}
			else{
				sleep(1);
				printf("Pid pai  antes do terceiro Fork(), o segundo filho foi criado-  %d\n", getpid());			

				pid_filho_3 = fork();
				
				if (pid_filho_3 == 0)
				{
					printf("Pid filho 3 - %d\n", getpid());
				}
				else{
				sleep(1);
				printf("Pid pai  depois do terceiro Fork(), o terceiro filho já foi criado-  %d\n", getpid());
				}
			} 
	}

}
```
2. Crie um código em C que recebe o nome de diversos comandos pelos argumentos de entrada (`argc` e `*argv[]`), e executa cada um sequencialmente usando `system()`. Por exemplo, considerando que o código criado recebeu o nome de 'serial_system', e que ele foi executado na pasta '/Sistemas_Embarcados/Code/06_Processos', que contem diversos arquivos:

```bash
$ ./serial_system pwd echo ls echo cal
$ ~/Sistemas_Embarcados/Code/06_Processos
$
$ Ex1.c    Ex2b.c   Ex4.c   Ex6.c
$ Ex2a.c   Ex3.c    Ex5.c   serial_system
$
$     Março 2017
$ Do Se Te Qu Qu Se Sá
$           1  2  3  4
$  5  6  7  8  9 10 11
$ 12 13 14 15 16 17 18
$ 19 20 21 22 23 24 25
$ 26 27 28 29 30 31


marcosadriano@marcosadriano:~/Área de trabalho/Aula_06/Questão_02$ ./bib_arqs pwd echo ls echo cal
/home/marcosadriano/Área de trabalho/Aula_06/Questão_02

bib_arqs  bib_arqs.c  bib_arqs.h  bib_arqs.o  main.c  main.o  Makefile	Nome.txt  README.md

     Abril 2018       
do se te qu qu se sá  
 1  2  3  4  5  6  7  
 8  9 10 11 12 13 14  
15 16 17 18 19 20 21  
22 23 24 25 26 27 28  
29 30 
```

```C
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/signal.h>
#include <errno.h>
#include <string.h>
int main(int argc, const char * argv[]) {
int n;
char entrada[20];
	for(n = 1; n < argc; n ++)
	{
		strcpy (entrada, argv[n]);
		system(entrada);
	}
}
```

3. Crie um código em C que recebe o nome de diversos comandos pelos argumentos de entrada (`argc` e `*argv[]`), e executa cada um usando `fork()` e `exec()`.
```C
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/wait.h>

int main(int argc, const char *argv[])
{
	int i;
	char *lista[2] = {NULL, NULL};
	for(i=1;i<argc;i++)
	{
        lista[0] = (char* )argv[i];
        execvp(lista[0],lista);
    }	
    
	return 0;
}

```


4. Crie um código em C que gera três processos-filho usando o `fork()`, e que cada processo-filho chama a seguinte função uma vez:

```C
int v_global = 0; // Variavel global para este exemplo
void Incrementa_Variavel_Global(pid_t id_atual)
{
	v_global++;
	printf("ID do processo que executou esta funcao = %d\n", id_atual);
	printf("v_global = %d\n", v_global);
}

////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////	CODIGO	///////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/signal.h>
#include <errno.h>




int v_global = 0; // Variavel global para este exemplo
void Incrementa_Variavel_Global(pid_t id_atual)
{
	v_global++;
	printf("ID do processo que executou esta funcao = %d\n", id_atual);
	printf("v_global = %d\n", v_global);
}



int main(void) {
int pid_filho_1, pid_filho_2, pid_filho_3,  pid_pai;
printf("Pid pai antes do primeiro Fork() -  %d\n", getpid());
pid_filho_1 = fork();

if (pid_filho_1 == 0)
	{
		Incrementa_Variavel_Global(getpid());
	}
else{
		sleep(1);
		pid_filho_2 = fork();

		if (pid_filho_2 == 0)
			{
				Incrementa_Variavel_Global(getpid());
			}
			else{
				sleep(1);
				pid_filho_3 = fork();
				
				if (pid_filho_3 == 0)
				{
					Incrementa_Variavel_Global(getpid());
				}
				else{
				sleep(1);
				printf("Pid pai  depois do terceiro Fork(), o terceiro filho já foi criado-  %d\n", getpid());
				}
			} 
	}

}

```
```BASH
marcosadriano@marcosadriano:~/Área de trabalho/Aula_06/Questão_04$ ./bib_arqs
Pid pai antes do primeiro Fork() -  3674
ID do processo que executou esta funcao = 3675
v_global = 1
ID do processo que executou esta funcao = 3676
v_global = 1
ID do processo que executou esta funcao = 3677
v_global = 1
Pid pai  depois do terceiro Fork(), o terceiro filho já foi criado-  3674
```
(Repare que a função `Incrementa_Variavel_Global()` recebe como entrada o ID do processo que a chamou.) Responda: a variável global `v_global` foi compartilhada por todos os processos-filho, ou cada processo enxergou um valor diferente para esta variável? Todos receberam um mesmo valor, enxergaram o valor presente no processo Pai.

5. Repita a questão anterior, mas desta vez faça com que o processo-pai também chame a função `Incrementa_Variavel_Global()`. Responda: a variável global `v_global` foi compartilhada por todos os processos-filho e o processo-pai, ou cada processo enxergou um valor diferente para esta variável?
```bash
marcosadriano@marcosadriano:~/Área de trabalho/Aula_06/Questão_04$ ./bib_arqs
Pid pai antes do primeiro Fork() -  3960
ID do processo que executou esta funcao = 3960
v_global = 1
ID do processo que executou esta funcao = 3961
v_global = 1
ID do processo que executou esta funcao = 3962
v_global = 2
ID do processo que executou esta funcao = 3960
v_global = 2
ID do processo que executou esta funcao = 3963
v_global = 3
ID do processo que executou esta funcao = 3960
v_global = 3
Pid pai  depois do terceiro Fork(), o terceiro filho já foi criado-  3960
```
```C
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/signal.h>
#include <errno.h>
int v_global = 0; // Variavel global para este exemplo
void Incrementa_Variavel_Global(pid_t id_atual)
{
	v_global++;
	printf("ID do processo que executou esta funcao = %d\n", id_atual);
	printf("v_global = %d\n", v_global);
}
int main(void) {
int pid_filho_1, pid_filho_2, pid_filho_3,  pid_pai;
printf("Pid pai antes do primeiro Fork() -  %d\n", getpid());
pid_filho_1 = fork();

if (pid_filho_1 == 0)
	{
		Incrementa_Variavel_Global(getpid());
	}
else{
		Incrementa_Variavel_Global(getpid());

		sleep(1);
		pid_filho_2 = fork();

		if (pid_filho_2 == 0)
			{
				Incrementa_Variavel_Global(getpid());
			}
			else{
				sleep(1);
				Incrementa_Variavel_Global(getpid());
				pid_filho_3 = fork();
				if (pid_filho_3 == 0)
				{
				Incrementa_Variavel_Global(getpid());
				}
				else{
				sleep(1);
				Incrementa_Variavel_Global(getpid());
				printf("Pid pai  depois do terceiro Fork(), o terceiro filho já foi criado-  %d\n", getpid());
				}
			} 
	}

}
```


