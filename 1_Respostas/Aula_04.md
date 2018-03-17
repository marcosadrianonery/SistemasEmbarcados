Para todas as questões, utilize as funções da biblioteca `stdio.h` de leitura e de escrita em arquivo (`fopen()`, `fclose()`, `fwrite()`, `fread()`, dentre outras). Compile os códigos com o gcc e execute-os via terminal.

1. Crie um código em C para escrever "Ola mundo!" em um arquivo chamado 'ola_mundo.txt'.

```C
#include <stdio.h>
#include <stdlib.h> /* Para a função exit() */
int main(int argc, const char * argv[]) {

FILE *fp;
fp=fopen ("ola_mundo.txt","w");
char c[100] = "ola_mundo!"; 
fputs(c, fp);
return 0;
}
```

2. Crie um código em C que pergunta ao usuário seu nome e sua idade, e escreve este conteúdo em um arquivo com o seu nome e extensão '.txt'. Por exemplo, considerando que o código criado receb1eu o nome de 'ola_usuario_1':

```bash
$ ./ola_usuario_1
$ Digite o seu nome: Eu
$ Digite a sua idade: 301
$ cat Eu.txt
$ Nome: Eu
$ Idade: 30 anos
//SAIDA
drico@drico-VirtualBox:~/Área de Trabalho/Sistemas_Embarcados/Aula_04/02$ cat Nome.txt
Digite o seu nome: Marcos Adriano 
Digite a sua idade: 21 
```
```C
#include <stdio.h>
#include <stdlib.h>
#include "reciprocal.h"

int main(int argc, const char * argv[]) {
	char nome[100];
	int idade;
	FILE *pf;
	pf = fopen ("Nome.txt","w");
	printf("Digite o seu nome: ");
	gets(nome);
	printf("Digite a sua idade: ");
	scanf("%d", &idade);
	fprintf(pf, "Digite o seu nome: %s \n", nome);
	fprintf(pf, "Digite a sua idade: %d \n", idade);
	fclose(pf);
	return 0;
}
```
3. Crie um código em C que recebe o nome do usuário e e sua idade como argumentos de entrada (usando as variáveis `argc` e `*argv[]`), e escreve este conteúdo em um arquivo com o seu nome e extensão '.txt'. Por exemplo, considerando que o código criado recebeu o nome de 'ola_usuario_2':

```bash
$ ./ola_usuario_2 Eu 30
$ cat Eu.txt
$ Nome: Eu
$ Idade: 30 anos

drico@drico-VirtualBox:~/Área de Trabalho/Sistemas_Embarcados/Aula_04/03$ ./reciprocal Marcos 21

```

```C
#include <stdio.h>
#include <stdlib.h>
#include "reciprocal.h"

int main(int argc, const char * argv[]) {

	char nome[100];
	int idade;


	FILE *pf;
	pf = fopen ("Nome.txt","w");
	fprintf(pf, "Digite o seu nome: %s \n", argv[1]);
	fprintf(pf, "Digite a sua idade: %s \n", argv[2]);

	fclose(pf);
	return 0;
}
```

4. Crie uma função que retorna o tamanho de um arquivo, usando o seguinte protótipo: `int tam_arq_texto(char *nome_arquivo);` Salve esta função em um arquivo separado chamado 'bib_arqs.c'. Salve o protótipo em um arquivo chamado 'bib_arqs.h'. Compile 'bib_arqs.c' para gerar o objeto 'bib_arqs.o'.
```bash
//TEXTO_ARQUIVO
Marcos Adriano

//Terminal
drico@drico-VirtualBox:~/Área de Trabalho/Sistemas_Embarcados/Aula_04/03$ ./bib_arqs 
Tamanho: 14 
```
```C
//MAIN
#include <stdio.h>
#include <stdlib.h>
#include "bib_arqs.h"

int main(int argc, const char * argv[]) {

	int tamanho = -1;
	char nome_arquivo[] = "Nome.txt";
	tamanho = tam_arq_texto(nome_arquivo);	
	printf("Tamanho: %d \n", tamanho);
	return 0;
}

//bib_arqs.h
int tam_arq_texto(char *nome_arquivo);

//bib_arqs.c
#include <stdio.h>
#include <stdlib.h>

int tam_arq_texto(char *nome_arquivo)
{

	int tamanho = -1;
	char c;
	FILE *fp;
	fp = fopen (nome_arquivo,"r");
	while((c = getc(fp) ) != EOF) tamanho++;
	fclose(fp);
	return tamanho;
}

```

5. Crie uma função que lê o conteúdo de um arquivo-texto e o guarda em uma string, usando o seguinte protótipo: `void le_arq_texto(char *nome_arquivo, char *conteudo);` Repare que o conteúdo do arquivo é armazenado no vetor `conteudo[]`. Ou seja, ele é passado por referência. Salve esta função no mesmo arquivo da questão 4, chamado 'bib_arqs.c'. Salve o protótipo no arquivo 'bib_arqs.h'. Compile 'bib_arqs.c' novamente para gerar o objeto 'bib_arqs.o'.
```bash
//TEXTO_ARQUIVO
Marcos Adriano

//Terminal
drico@drico-VirtualBox:~/Área de Trabalho/Sistemas_Embarcados/Aula_04/05$ ./bib_arqs 
Conteudo: Marcos Adriano
```
```C
//MAIN
#include <stdio.h>
#include <stdlib.h>
#include "bib_arqs.h"

int main(int argc, const char * argv[]) {

	char nome_arquivo[] = "Nome.txt", conteudo[100];
	le_arq_texto(nome_arquivo, conteudo);
	tam_arq_texto(nome_arquivo);	
	printf("Conteudo: %s \n", conteudo);
	return 0;
}

//bib_arqs.h
int tam_arq_texto(char *nome_arquivo);
void le_arq_texto(char *nome_arquivo, char *conteudo);

//bib_arqs.c
#include "bib_arqs.h"
#include <stdio.h>
#include <stdlib.h>

int tam_arq_texto(char *nome_arquivo)
{

	int tamanho = -1;
	char c;
	FILE *fp;
	fp = fopen (nome_arquivo,"r");
	while((c = getc(fp) ) != EOF) tamanho++;
	fclose(fp);
	return tamanho;
}

void le_arq_texto(char *nome_arquivo, char *conteudo)
{
	int tamanho = 0;
	char c;
	FILE *fp;
	fp = fopen (nome_arquivo,"r");
	while((c = getc(fp) ) != EOF){
	conteudo[tamanho] = c;	
	tamanho++;
		
	}	
	fclose(fp);
}

```


6. Crie um código em C que copia a funcionalidade básica do comando `cat`: escrever o conteúdo de um arquivo-texto no terminal. Reaproveite as funções já criadas nas questões anteriores. Por exemplo, considerando que o código criado recebeu o nome de 'cat_falsificado':

```bash
$ echo Ola mundo cruel! Ola universo ingrato! > ola.txt
$ ./cat_falsificado ola.txt
$ Ola mundo cruel! Ola universo ingrato!

A QUESTÃO 5 FAZ EXATAMENTE ISSO.

//MAIN_COPIADA
#include <stdio.h>
#include <stdlib.h>
#include "bib_arqs.h"

int main(int argc, const char * argv[]) {

	char nome_arquivo[] = "Nome.txt", conteudo[100];
	le_arq_texto(nome_arquivo, conteudo);
	tam_arq_texto(nome_arquivo);	
	printf("Conteudo: %s \n", conteudo);
	return 0;
}

```


7. Crie um código em C que conta a ocorrência de uma palavra-chave em um arquivo-texto, e escreve o resultado no terminal. Reaproveite as funções já criadas nas questões anteriores. Por exemplo, considerando que o código criado recebeu o nome de 'busca_e_conta':

```bash
$ echo Ola mundo cruel! Ola universo ingrato! > ola.txt
$ ./busca_e_conta Ola ola.txt
$ 'Ola' ocorre 2 vezes no arquivo 'ola.txt'.
```
