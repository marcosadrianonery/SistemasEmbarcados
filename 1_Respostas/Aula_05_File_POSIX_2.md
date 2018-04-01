Para todas as questões, utilize as funções da norma POSIX (`open()`, `close()`, `write()`, `read()` e `lseek()`). Compile os códigos com o gcc e execute-os via terminal.

1. Crie um código em C para escrever "Ola mundo!" em um arquivo chamado 'ola_mundo.txt'.]
```C
#include <stdio.h>
#include <unistd.h> 
#include <fcntl.h> 
#include <termios.h>

int main(int argc, const char * argv[]) {

	char nome_arquivo[] = "Ola_mundo.txt", string_[] = "Ola mundo!" ;
	int descritor, n_bytes;
    
	descritor = open(nome_arquivo, O_WRONLY | O_CREAT);
	n_bytes = write(descritor,  string_, sizeof(string_) );		
	close(descritor);
	return 0;
}

```

2. Crie um código em C que pergunta ao usuário seu nome e sua idade, e escreve este conteúdo em um arquivo com o seu nome e extensão '.txt'. Por exemplo, considerando que o código criado recebeu o nome de 'ola_usuario_1':

```bash
$ ./ola_usuario_1
$ Digite o seu nome: Eu
$ Digite a sua idade: 30
$ cat Eu.txt
$ Nome: Eu
$ Idade: 30 anos
```
```C
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 
#include <fcntl.h> 
#include <termios.h>
#include <string.h>


int main(int argc, const char * argv[]) {

	char nome[20], escrever[100] = "Nome: ", idade[3];
	int descritor, n_bytes;
	printf("Nome: ");
	scanf("%s", nome);
	printf("Idade: ");
	scanf("%s", idade);
	strcat(escrever,nome);
	strcat(escrever,".\nIdade: ");
	strcat(escrever,idade);
	strcat(escrever," anos.");
	strcat(nome,".txt");
	descritor = open(nome, O_WRONLY | O_CREAT);
	n_bytes = write(descritor,  escrever, sizeof(escrever) );		
	close(descritor);
	return 0;
}
```

3. Crie um código em C que recebe o nome do usuário e e sua idade como argumentos de entrada (usando as variáveis `argc` e `*argv[]`), e escreve este conteúdo em um arquivo com o seu nome e extensão '.txt'. Por exemplo, considerando que o código criado recebeu o nome de 'ola_usuario_2':

```bash
$ ./ola_usuario_2 Eu 30
$ cat Eu.txt
$ Nome: Eu
$ Idade: 30 anos

root@marcosadriano:/home/marcosadriano/Área de trabalho/Questã./bib_arqs Marcos 21
root@marcosadriano:/home/marcosadriano/Área de trabalho/Questão_1/Questão_3# cat Marcos.txt
Nome: Marcos.
Idade: 21 anos.

```
```C
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 
#include <fcntl.h> 
#include <termios.h>
#include <string.h>


int main(int argc, const char * argv[]) {

	char nome[20], escrever[100] = "Nome: ";
	int descritor, n_bytes;
    strcpy(nome,argv[1]);
    strcat(escrever, nome);
    strcat(escrever,".\nIdade: ");
    strcat(escrever, argv[2]);
    strcat(escrever," anos.");
    strcat(nome,".txt");
	descritor = open(nome, O_WRONLY | O_CREAT);
	n_bytes = write(descritor,  escrever, sizeof(escrever) );		
	close(descritor);
	return 0;
}
```


4. Crie uma função que retorna o tamanho de um arquivo, usando o seguinte protótipo: `int tam_arq_texto(char *nome_arquivo);` Salve esta função em um arquivo separado chamado 'bib_arqs.c'. Salve o protótipo em um arquivo chamado 'bib_arqs.h'. Compile 'bib_arqs.c' para gerar o objeto 'bib_arqs.o'.
```bash
root@marcosadriano:/home/marcosadriano/Área de trabalho/Questão_1/Questão_4# cat arquivo.txt 
Marcos

root@marcosadriano:/home/marcosadriano/Área de trabalho/Questão_1/Questão_4# ./bib_arqs
6 
```

```C
//MAIN
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 
#include <fcntl.h> 
#include <termios.h>
#include <string.h>
#include "bib_arqs.h"

int main(int argc, const char * argv[]) {
    char nome[] = "arquivo.txt";
    int tamanho;
    tamanho = tam_arq_texto(nome);    
    printf("%d \n", tamanho);
	return 0;
}

//bib_arqs.h
int tam_arq_texto(char *nome_arquivo);

//bib_arqs.c
#include "bib_arqs.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 
#include <fcntl.h> 
#include <termios.h>
#include <string.h>


int tam_arq_texto(char *nome_arquivo)
{
	int tamanho = -1, descritor, n_byte;
	char c;
	descritor = open (nome_arquivo, O_RDWR | O_CREAT);
    
    if (descritor == -1) {
		return -1;
		close(descritor);
	}
    tamanho = lseek(descritor, 0, SEEK_END);
	close(descritor);
	return (tamanho - 1);
}





```


5. Crie uma função que lê o conteúdo de um arquivo-texto e o guarda em uma string, usando o seguinte protótipo: `void le_arq_texto(char *nome_arquivo, char *conteúdo);` Repare que o conteúdo do arquivo é armazenado no vetor `conteudo[]`. Ou seja, ele é passado por referência. Salve esta função no mesmo arquivo da questão 4, chamado 'bib_arqs.c'. Salve o protótipo no arquivo 'bib_arqs.h'. Compile 'bib_arqs.c' novamente para gerar o objeto 'bib_arqs.o'.
```bash
root@marcosadriano:/home/marcosadriano/Área de trabalho/Questão_1/Questão_5# ./bib_arqs
Marcos adriano 
root@marcosadriano:/home/marcosadriano/Área de trabalho/Questão_1/Questão_5# cat arquivo.txt 
Marcos adriano
```
```C
//MAIN
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 
#include <fcntl.h> 
#include <termios.h>
#include <string.h>
#include "bib_arqs.h"

int main(int argc, const char * argv[]) {
    char nome[] = "arquivo.txt", conteudo[100];
    int tamanho;
    tamanho = tam_arq_texto(nome);    
    le_arq_texto(nome, conteudo);
    printf("%s \n", conteudo);
	return 0;
}

//bib_arqs.c
#include "bib_arqs.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 
#include <fcntl.h> 
#include <termios.h>
#include <string.h>


int tam_arq_texto(char *nome_arquivo)
{
	int tamanho = -1, descritor, n_byte;
	char c;
	descritor = open (nome_arquivo, O_RDWR | O_CREAT);
    
    if (descritor < 0)
   {
      perror (nome_arquivo);
      return -1;
   }
    tamanho = lseek(descritor, 0, SEEK_END);
	close(descritor);
	return (tamanho - 1);
}

void le_arq_texto(char *nome_arquivo, char *conteudo)
{
    
	int tamanho = 0, n_byte, descritor;
	char c;
    
	tamanho = tam_arq_texto(nome_arquivo);
    
    descritor = open (nome_arquivo, O_RDWR | O_CREAT);
     
        if (descritor < 0){
            
            perror (nome_arquivo);
            return;
        }
    
       /* deve-se passar sempre o endereço de memória da variável que vai receber os bytes lidos */
   n_byte = read (descritor, conteudo, tamanho*sizeof(char));
 
   if (n_byte < 0)
   {
      perror (nome_arquivo);
      return;
   }
	close(descritor);
}

//bib_arqs.h
int tam_arq_texto(char *nome_arquivo);
void le_arq_texto(char *nome_arquivo, char *conteudo);
```

6. Crie um código em C que copia a funcionalidade básica do comando `cat`: escrever o conteúdo de um arquivo-texto no terminal. Reaproveite as funções já criadas nas questões anteriores. Por exemplo, considerando que o código criado recebeu o nome de 'cat_falsificado':

```bash
$ echo Ola mundo cruel! Ola universo ingrato! > ola.txt
$ ./cat_falsificado ola.txt
$ Ola mundo cruel! Ola universo ingrato!

root@marcosadriano:/home/marcosadriano/Área de trabalho/Questão_1/Questão_6# ./bib_arqs marcos.txt
Marcos Adriano 
```
```C
//MAIN
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 
#include <fcntl.h> 
#include <termios.h>
#include <string.h>
#include "bib_arqs.h"

int main(int argc, const char * argv[]) {
    char nome[] = "arquivo.txt", conteudo[100];
    strcpy(nome,argv[1]);
    int tamanho;
    tamanho = tam_arq_texto(nome);    
    le_arq_texto(nome, conteudo);
    printf("%s \n", conteudo);
	return 0;
}

//bib_arqs.c
#include "bib_arqs.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 
#include <fcntl.h> 
#include <termios.h>
#include <string.h>


int tam_arq_texto(char *nome_arquivo)
{
	int tamanho = -1, descritor, n_byte;
	char c;
	descritor = open (nome_arquivo, O_RDWR | O_CREAT);
    
    if (descritor < 0)
   {
      perror (nome_arquivo);
      return -1;
   }
    tamanho = lseek(descritor, 0, SEEK_END);
	close(descritor);
	return (tamanho - 1);
}

void le_arq_texto(char *nome_arquivo, char *conteudo)
{
    
	int tamanho = 0, n_byte, descritor;
	char c;
    
	tamanho = tam_arq_texto(nome_arquivo);
    
    descritor = open (nome_arquivo, O_RDWR | O_CREAT);
     
        if (descritor < 0){
            
            perror (nome_arquivo);
            return;
        }
    
       /* deve-se passar sempre o endereço de memória da variável que vai receber os bytes lidos */
   n_byte = read (descritor, conteudo, tamanho*sizeof(char));
 
   if (n_byte < 0)
   {
      perror (nome_arquivo);
      return;
   }
	close(descritor);
}

//bib_arqs.h
int tam_arq_texto(char *nome_arquivo);
void le_arq_texto(char *nome_arquivo, char *conteudo);
```


7. Crie um código em C que conta a ocorrência de uma palavra-chave em um arquivo-texto, e escreve o resultado no terminal. Reaproveite as funções já criadas nas questões anteriores. Por exemplo, considerando que o código criado recebeu o nome de 'busca_e_conta':

```bash
$ echo Ola mundo cruel! Ola universo ingrato! > ola.txt
$ ./busca_e_conta Ola ola.txt
$ 'Ola' ocorre 2 vezes no arquivo 'ola.txt'.

root@marcosadriano:/home/marcosadriano/Área de trabalho/Questão_1/Questão_7# echo Ola mundo cruel! Ola universo ingrato! > ola.txt
root@marcosadriano:/home/marcosadriano/Área de trabalho/Questão_1/Questão_7# ./bib_arqs Ola ola.txt 
Iguais: 2 

```

```C
//MAIN
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 
#include <fcntl.h> 
#include <termios.h>
#include <string.h>
#include "bib_arqs.h"

int main(int argc, const char * argv[]) {
    char nome[20], conteudo[500], palavra_chave[20];
    strcpy(nome,argv[2]);
    strcpy(palavra_chave,argv[1]);
    int tamanho_texto, tamanho_palavra, n, i, igual = 0, diferente = 0;;
    
    tamanho_texto = tam_arq_texto(nome); 
    le_arq_texto(nome, conteudo);
    tamanho_palavra = strlen(palavra_chave);
    
    for(n = 0; n <= tamanho_texto; n++)
    {       
            if((conteudo[n] == ' ') || (conteudo[n] == 'EOF') || (n == tamanho_texto) || (conteudo[n] == '.') || (conteudo[n] == ','))
            {
                for(i = 0; i < tamanho_palavra; i++)
                {
                    if(conteudo[n - tamanho_palavra + i] != palavra_chave[i])
                    {
                        diferente = 1;
                        break;
                    }
                }
                if (diferente != 1 )
                {
                    igual++;
                }   
            }        
            diferente = 0;
    }       
    printf("Iguais: %d \n", igual);
    return 0;
}

//bib_arqs.c
#include "bib_arqs.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 
#include <fcntl.h> 
#include <termios.h>
#include <string.h>


int tam_arq_texto(char *nome_arquivo)
{
	int tamanho = -1, descritor, n_byte;
	char c;
	descritor = open (nome_arquivo, O_RDWR | O_CREAT);
    
    if (descritor < 0)
   {
      perror (nome_arquivo);
      return -1;
   }
    tamanho = lseek(descritor, 0, SEEK_END);
	close(descritor);
	return (tamanho - 1);
}

void le_arq_texto(char *nome_arquivo, char *conteudo)
{
    
	int tamanho = 0, n_byte, descritor;
	char c;
    
	tamanho = tam_arq_texto(nome_arquivo);
    
    descritor = open (nome_arquivo, O_RDWR | O_CREAT);
     
        if (descritor < 0){
            
            perror (nome_arquivo);
            return;
        }
    
       /* deve-se passar sempre o endereço de memória da variável que vai receber os bytes lidos */
   n_byte = read (descritor, conteudo, tamanho*sizeof(char));
 
   if (n_byte < 0)
   {
      perror (nome_arquivo);
      return;
   }
	close(descritor);
}

//bib_arqs.h
int tam_arq_texto(char *nome_arquivo);
void le_arq_texto(char *nome_arquivo, char *conteudo);
```
