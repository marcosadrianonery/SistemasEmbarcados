1. Crie um programa em C que cria um processo-filho e um pipe de comunicação. Faça com que o processo-pai envie os valores 1, 2, 3, 4, 5, 6, 7, 8, 9 e 10 para o processo-filho, com intervalos de 1 segundo entre cada envio. Depois de o processo-pai enviar o número 10, ele aguarda 1 segundo e termina a execução. O processo-filho escreve na tela cada valor recebido, e quando ele receber o valor 10, ele termina a execução.
```bash
marcosadriano@marcosadriano:~/Área de trabalho/Aula_07/Questão_01$ ./bib_arqs
Pai vai escrever no pipe
Pai espera 1 seg
Filho espera o Pai.
Pai espera 1 seg
Pai espera 1 seg
Pai espera 1 seg
Pai espera 1 seg
Pai espera 1 seg
Pai espera 1 seg
Pai espera 1 seg
Pai espera 1 seg
Pai espera 1 seg
Pai se encerra.
marcosadriano@marcosadriano:~/Área de trabalho/Aula_07/Questão_01$ Filho leu: 1
Filho leu: 2
Filho leu: 3
Filho leu: 4
Filho leu: 5
Filho leu: 6
Filho leu: 7
Filho leu: 8
Filho leu: 9
Filho leu: 10
Filho se encerra.
```
```C
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/signal.h>
#include <errno.h>
int main(void) {
	int pid_filho_1, pid_filho_2, pid_filho_3,  pid;	// PIDs dos processos
	int fd[2];	// Descritores do pipe
	int i;
	// Cria o pipe
	pipe(fd);
	// Cria o processo
	pid = fork();
	// Codigo do filho
	if(pid == 0)
	{	
		printf("Filho espera o Pai.\n");
		sleep(11);		
		for(int n=1; n<=10; n++)
		{		
			if (read(fd[0], &i,  sizeof(int)) < 0)
				printf("Erro na escrita do pipe\n");
			else
				printf("Filho leu: %d\n", i);
		}
		printf("Filho se encerra.\n");		

	}
	// Codigo do pai
	else
	{
		printf("Pai vai escrever no pipe\n");
		for(int n=1; n<=10; n++)
		{		
		if (write(fd[1], &n, sizeof(n)) < 0)
			printf("Erro na escrita do pipe\n");
		printf("Pai espera 1 seg\n");
		sleep(1);
		}
		printf("Pai se encerra.\n");		
	}
	return 0;
}
```


2. Crie um programa em C que cria um processo-filho e um pipe de comunicação. Utilize o pipe para executar a seguinte conversa entre processos:

```
FILHO: Pai, qual é a verdadeira essência da sabedoria?
PAI: Não façais nada violento, praticai somente aquilo que é justo e equilibrado.
FILHO: Mas até uma criança de três anos sabe disso!
PAI: Sim, mas é uma coisa difícil de ser praticada até mesmo por um velho como eu...
```
```C
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/signal.h>
#include <errno.h>


int main() {
	int pid_filho_1, pid_filho_2, pid_filho_3,  pid;	// PIDs dos processos
	int fd[2];	// Descritores do pipe

	int i;
	char mensagem[100];
	char mensagem_1[]= "Pai, qual é a verdadeira essência da sabedoria?";
	char mensagem_2[]= "Não façais nada violento, praticai somente aquilo que é justo e equilibrado.";
	char mensagem_3[]= "Mas até uma criança de três anos sabe disso!";
	char mensagem_4[]= "Sim, mas é uma coisa difícil de ser praticada até mesmo por um velho como eu...";

	// Cria o pipe
	pipe(fd);
	// Cria o processo
	pid = fork();
	// Codigo do pai
	if(pid != 0)
	{
		sleep(1);
///////////////////////////////////////////////////////////////////////////////
//////////			LEITURA DA PRIMEIRA MENSAGEM_1
///////////////////////////////////////////////////////////////////////////////
		printf("\nPai vai ler o pipe\n");
		if(read(fd[0], mensagem, 100) < 0) 
			printf("\nErro na leitura do pipe\n");
		else
			printf("\nPai leu: %s\n", mensagem);

		
///////////////////////////////////////////////////////////////////////////////
//////////			ESCRITA DA SEGUNDA MENSAGEM_2
///////////////////////////////////////////////////////////////////////////////
		printf("\nPai vai escrever no pipe\n");
		if (write(fd[1], mensagem_2, sizeof(mensagem_2)) < 0)
			printf("\nErro na escrita do pipe\n");
		printf("\nPai terminou de escrever no pipe\n");

		sleep(2);
///////////////////////////////////////////////////////////////////////////////
//////////			LEITURA DA  MENSAGEM_3
///////////////////////////////////////////////////////////////////////////////
		printf("\nPai vai ler o pipe\n");
		if(read(fd[0], mensagem, 100) < 0) 
			printf("\nErro na leitura do pipe\n");
		else
			printf("\nPai leu: %s\n", mensagem);
///////////////////////////////////////////////////////////////////////////////
//////////			ESCRITA DA MENSAGEM_4
///////////////////////////////////////////////////////////////////////////////
		printf("\nPai vai escrever no pipe\n");
		if (write(fd[1], mensagem_4, sizeof(mensagem_4)) < 0)
			printf("\nErro na escrita do pipe\n");
		printf("\nPai terminou de escrever no pipe\n");

		sleep(3);

	}
	// Codigo do filho
	else
	{
///////////////////////////////////////////////////////////////////////////////
//////////			ESCRITA DA PRIMEIRA MENSAGEM_1
///////////////////////////////////////////////////////////////////////////////

		printf("\nFilho vai escrever no pipe\n");
		if (write(fd[1], mensagem_1, sizeof(mensagem_1)) < 0)
			printf("\nErro na escrita do pipe\n");
		printf("\nFilho terminou de escrever no pipe\n");

		sleep(2);
///////////////////////////////////////////////////////////////////////////////
//////////			LEITURA DA SEGUNDA MENSAGEM_2
///////////////////////////////////////////////////////////////////////////////
		printf("\nFilho vai ler o pipe\n");
		if(read(fd[0], mensagem, 100) < 0) 
			printf("\nErro na leitura do pipe\n");
		else
			printf("\nFilho leu: %s\n", mensagem);

///////////////////////////////////////////////////////////////////////////////
//////////			ESCRITA DA TERCEIRA MENSAGEM_3
///////////////////////////////////////////////////////////////////////////////

		printf("\nFilho vai escrever no pipe\n");
		if (write(fd[1], mensagem_3, sizeof(mensagem_3)) < 0)
			printf("\nErro na escrita do pipe\n");
		printf("\nFilho terminou de escrever no pipe\n");

		sleep(2);
///////////////////////////////////////////////////////////////////////////////
//////////			LEITURA DA MENSAGEM_4
///////////////////////////////////////////////////////////////////////////////
		printf("\nFilho vai ler o pipe\n");
		if(read(fd[0], mensagem, 100) < 0) 
			printf("\nErro na leitura do pipe\n");
		else
			printf("\nFilho leu: %s\n", mensagem);

		sleep(3);
	}
	return 0;
}

```
```bash
marcosadriano@marcosadriano:~/Área de trabalho/Aula_07/Questão_02$ ./bib_arqs

Filho vai escrever no pipe

Filho terminou de escrever no pipe

Pai vai ler o pipe

Pai leu: Pai, qual é a verdadeira essência da sabedoria?

Pai vai escrever no pipe

Pai terminou de escrever no pipe

Filho vai ler o pipe

Filho leu: Não façais nada violento, praticai somente aquilo que é justo e equilibrado.

Filho vai escrever no pipe

Filho terminou de escrever no pipe

Pai vai ler o pipe

Pai leu: Mas até uma criança de três anos sabe disso!

Pai vai escrever no pipe

Pai terminou de escrever no pipe

Filho vai ler o pipe

Filho leu: Sim, mas é uma coisa difícil de ser praticada até mesmo por um velho como eu...
```

Neste exercício, quem recebe a mensagem via pipe é quem as escreve no terminal.


3. Crie um programa em C que cria dois processos-filhos e um pipe de comunicação. Utilize o pipe para executar a seguinte conversa entre processos:

```
FILHO1: Quando o vento passa, é a bandeira que se move.
FILHO2: Não, é o vento que se move.
PAI: Os dois se enganam. É a mente dos senhores que se move.
```
```C
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/signal.h>
#include <errno.h>


int main() {
	int pid;	// PIDs dos processos
	int fd[2];	// Descritores do pipe
	char mensagem[100];
	char mensagem_1[]= "FILHO1: Quando o vento passa, é a bandeira que se move.";
	char mensagem_2[]= "FILHO2: Não, é o vento que se move.";
	char mensagem_3[]= "PAI: Os dois se enganam. É a mente dos senhores que se move.";
	// Cria o pipe
	pipe(fd);
	// Cria o processo
	pid = fork();
	// Codigo do FILHO_1
	if(pid == 0)
	{
///////////////////////////////////////////////////////////////////////////////
//////////			ESCRITA FILHO_1 para FILHO 2
///////////////////////////////////////////////////////////////////////////////
		printf("\nFILHO 1 vai escrever no pipe\n");
		if (write(fd[1], mensagem_1, sizeof(mensagem_1)) < 0)
			printf("\nErro na escrita do pipe\n");
		printf("\nFILHO 1 terminou de escrever no pipe\n");
		sleep(2);
///////////////////////////////////////////////////////////////////////////////
//////////			ESCRITA FILHO_1 para pai
///////////////////////////////////////////////////////////////////////////////
		printf("\nFILHO 1 vai escrever no pipe\n");
		if (write(fd[1], mensagem_1, sizeof(mensagem_1)) < 0)
			printf("\nErro na escrita do pipe\n");
		printf("\nFILHO 1 terminou de escrever no pipe\n");
		sleep(3);
///////////////////////////////////////////////////////////////////////////////
//////////			LEITURA DA  MENSAGEM FILHO_2
///////////////////////////////////////////////////////////////////////////////
		printf("\nFILHO 1  vai ler o pipe\n");
		if(read(fd[0], mensagem, 100) < 0) 
			printf("\nErro na leitura do pipe\n");
		else
			printf("\nFILHO 1 leu: %s\n", mensagem);
		sleep(2);
///////////////////////////////////////////////////////////////////////////////
//////////			LEITURA DA  MENSAGEM PAI
///////////////////////////////////////////////////////////////////////////////
		printf("\nFILHO 1 vai ler o pipe\n");
		if(read(fd[0], mensagem, 100) < 0) 
			printf("\nErro na leitura do pipe\n");
		else
			printf("\nFILHO 1 leu: %s\n", mensagem);
	sleep(2);
	// Codigo do filho
	}
	else
	{
		pid = fork();
		// Codigo do FILHO 2
		if(pid == 0)
		{	
		sleep(1);
///////////////////////////////////////////////////////////////////////////////
//////////			LEITURA DA  MENSAGEM FILHO_1
///////////////////////////////////////////////////////////////////////////////
		printf("\nFILHO_2 vai ler o pipe\n");
		if(read(fd[0], mensagem, 100) < 0) 
			printf("\nErro na leitura do pipe\n");
		else
			printf("\nFILHO 2 leu: %s\n", mensagem);
		sleep(2);
//////////////////////////////////////////////////////////////////////////////
//////////			ESCRITA FILHO_2 PARA FILHO 1
///////////////////////////////////////////////////////////////////////////////
		printf("\nFILHO 2 vai escrever no pipe\n");
		if (write(fd[1], mensagem_2, sizeof(mensagem_2)) < 0)
			printf("\nErro na escrita do pipe\n");
		printf("\nFILHO 2 terminou de escrever no pipe\n");
		sleep(2);
//////////////////////////////////////////////////////////////////////////////
//////////			ESCRITA FILHO_2 para PAI
///////////////////////////////////////////////////////////////////////////////
		printf("\nFILHO 2 vai escrever no pipe\n");
		if (write(fd[1], mensagem_2, sizeof(mensagem_2)) < 0)
			printf("\nErro na escrita do pipe\n");
		printf("\nFILHO 2 terminou de escrever no pipe\n");
		sleep(4);
///////////////////////////////////////////////////////////////////////////////
//////////			LEITURA DA  MENSAGEM DO PAI
///////////////////////////////////////////////////////////////////////////////
		printf("\nFILHO_2 vai ler o pipe\n");
		if(read(fd[0], mensagem, 100) < 0) 
			printf("\nErro na leitura do pipe\n");
		else
			printf("\nFILHO 2 leu: %s\n", mensagem);
		sleep(2);
		}
///////////////////////////////////////////////////////////////////////////////
//////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//////////			CODIGO PAI
///////////////////////////////////////////////////////////////////////////////
		else
		{
		sleep(3);
///////////////////////////////////////////////////////////////////////////////
//////////			LEITURA DA  MENSAGEM FILHO_1
///////////////////////////////////////////////////////////////////////////////
		printf("\nPAI vai ler o pipe\n");
		if(read(fd[0], mensagem, 100) < 0) 
			printf("\nErro na leitura do pipe\n");
		else
			printf("\nPAI leu: %s\n", mensagem);

		sleep(3);
///////////////////////////////////////////////////////////////////////////////
//////////			LEITURA DA  MENSAGEM FILHO_2
///////////////////////////////////////////////////////////////////////////////
		printf("\nPAI  vai ler o pipe\n");
		if(read(fd[0], mensagem, 100) < 0) 
			printf("\nErro na leitura do pipe\n");
		else
			printf("\nPAI leu: %s\n", mensagem);
		}
///////////////////////////////////////////////////////////////////////////////
//////////			PAI ESCREVE para FILHO 1
///////////////////////////////////////////////////////////////////////////////

		printf("\nPAI vai escrever no pipe\n");
		if (write(fd[1], mensagem_3, sizeof(mensagem_3)) < 0)
			printf("\nErro na escrita do pipe\n");
		printf("\nPAI terminou de escrever no pipe\n");
	sleep(2);
///////////////////////////////////////////////////////////////////////////////
//////////			PAI ESCREVE para FILHO 2
//////////////////////////////////////////////////////////////////////////////
		printf("\nPAI vai escrever no pipe\n");
		if (write(fd[1], mensagem_3, sizeof(mensagem_3)) < 0)
			printf("\nErro na escrita do pipe\n");
		printf("\nPAI terminou de escrever no pipe\n");
	sleep(2);
	}
	return 0;
}
```
```bash
marcosadriano@marcosadriano:~/Área de trabalho/Aula_07/Questão_03$ ./bib_arqs

FILHO 1 vai escrever no pipe

FILHO 1 terminou de escrever no pipe

FILHO_2 vai ler o pipe

FILHO 2 leu: FILHO1: Quando o vento passa, é a bandeira que se move.

FILHO 1 vai escrever no pipe

FILHO 1 terminou de escrever no pipe

PAI vai ler o pipe

PAI leu: FILHO1: Quando o vento passa, é a bandeira que se move.

FILHO 2 vai escrever no pipe

FILHO 2 terminou de escrever no pipe

FILHO 1  vai ler o pipe

FILHO 1 leu: FILHO2: Não, é o vento que se move.

FILHO 2 vai escrever no pipe

FILHO 2 terminou de escrever no pipe

PAI  vai ler o pipe

PAI leu: FILHO2: Não, é o vento que se move.

PAI vai escrever no pipe

PAI terminou de escrever no pipe

FILHO 1 vai ler o pipe

FILHO 1 leu: PAI: Os dois se enganam. É a mente dos senhores que se move.

PAI vai escrever no pipe

PAI terminou de escrever no pipe

FILHO_2 vai ler o pipe

FILHO 2 leu: PAI: Os dois se enganam. É a mente dos senhores que se move.
```


Neste exercício, quem recebe a mensagem via pipe é quem as escreve no terminal.


4. Crie um programa em C que cria um processo-filho e um pipe de comunicação. O processo-filho deverá pedir o nome do usuário, envia-lo para o pai via pipe, e o pai deverá escrever o nome do usuário no terminal.
```C
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/signal.h>
#include <errno.h>

int main() {
	int pid, pid_pai;	// PIDs dos processos
	int fd[2];	// Descritores do pipe
	char nome_usuario[100];
	// Cria o pipe
	pipe(fd);
	// Cria o processo
	pid = fork();
	// Codigo do FILHO_1
	if(pid == 0)
	{
///////////////////////////////////////////////////////////////////////////////
//////////			PERGUNTAR O NOME
///////////////////////////////////////////////////////////////////////////////
		printf("\nDiga seu nome:\n");
		scanf("%s", nome_usuario);
		if (write(fd[1], nome_usuario, sizeof(nome_usuario)) < 0)
			printf("\nErro na escrita do pipe\n");
		sleep(2);
	// Codigo do filho
	}
	else
	{
		sleep(2);
///////////////////////////////////////////////////////////////////////////////
//////////			LEITURA DA  MENSAGEM FILHO_2
///////////////////////////////////////////////////////////////////////////////
//		signal(SIGUSR1,escrever_nome);
//		printf("\nENTREI AQUI %s\n");
		
		if(read(fd[0], nome_usuario, 100) < 0) 
			printf("\nErro na leitura do pipe\n");
		else
			printf("\nNome lido: %s\n", nome_usuario);
		sleep(2);
	}
	return 0;
}
```
```bash
marcosadriano@marcosadriano:~/Área de trabalho/Aula_07/Questão_04$ ./bib_arqs

Diga seu nome:
Marcos

Nome lido: Marcos

```


5. Utilize o sinal de alarme para chamar a cada segundo o comando `ps` ordenando todos os processos de acordo com o uso da CPU. Ou seja, seu código atualizará a lista de processos a cada segundo. Além disso, o código deverá tratar o sinal do CTRL-C, escrevendo "Processo terminado!" na tela antes de terminar a execução do processo.

```C
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>


void ctrlC_SIGINT()
{
	puts("Processo terminado");
	exit(0);
}

void ps()
{
	if (!fork())
		execlp("ps", "aux", "--sort=-pcpu", (char *)NULL);
	else
		alarm(1);
}

int main(void)
{
	signal(SIGINT, ctrlC_SIGINT);
	signal(SIGALRM, ps);
	alarm(1);
	while (1);
	return 0;
}
```
