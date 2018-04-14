1. Crie um programa em C que cria uma thread, e faça com que o programa principal envie os valores
1, 2, 3, 4, 5, 6, 7, 8, 9 e 10 para a thread, com intervalos de 1 segundo entre cada envio. 
Depois de o programa principal enviar o número 10, ele aguarda 1 segundo e termina a execução.
A thread escreve na tela cada valor recebido, e quando ela receber o valor 10, ela termina a execução.
```C
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

	int parametro[20];
    int i;

void *print_thread(void *parameters)
{
	int *p = (int *)parameters;

 	for(int n = 0; n < 10 ; n++)
 	{    
        printf("Estou na thread_1: %d\n", i);
		printf("Recebi %d\n", parametro[i - 1]);
		sleep(1);
    }
	return NULL;
}
 int main()
 {
 	
     pthread_t thread_1;

 	pthread_create(&thread_1,NULL, &print_thread, &thread_1);
    
 	for(i = 1; i < 11 ; i++)
 	{
        printf("Enviando %d\n", i);
 		parametro[i - 1] = i;
 		sleep(1);
 	}
 	
 	pthread_join(thread_1,NULL);
 	return 0;
}

``` 
```bash
root@marcosadriano:/home/marcosadriano/Área de trabalho/Aula_08/Questão_01# ./main.exe
Enviando 1
Estou na thread_1: 1
Recebi 1
Enviando 2
Estou na thread_1: 2
Recebi 2
Enviando 3
Estou na thread_1: 3
Recebi 3
Enviando 4
Estou na thread_1: 4
Recebi 4
Enviando 5
Estou na thread_1: 5
Recebi 5
Enviando 6
Estou na thread_1: 6
Recebi 6
Enviando 7
Estou na thread_1: 7
Recebi 7
Enviando 8
Estou na thread_1: 8
Recebi 8
Enviando 9
Estou na thread_1: 9
Recebi 9
Enviando 10
Estou na thread_1: 10
Recebi 10

```

2. Crie um programa em C que preenche o vetor `long int v[50000]` completamente com valores aleatórios 
(use a função `random()`), e que procura o valor máximo do vetor por dois métodos:

(a) Pela busca completa no vetor `v[]`;

```C
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>

	long int v[50000];
    int i;
    int parametro[30];
 int main()
 {
     int quantidade = 0, valor = 542734400;
     for(i = 0; i < 50000 ; i++)
 	{
        v[i] = random();
        
    }
       for(i = 0; i < 50000 ; i++)
 	{
        if(v[i] == valor)
        {    
            quantidade++;
        }
 	} 
    printf("Iguais: %d\n", quantidade); 	
 	return 0;
}
C

(b) Separando o vetor em 4 partes, e usando 4 threads para cada uma encontrar o máximo de cada parte. Ao final das threads, o programa principal compara o resultado das quatro threads para definir o máximo do vetor.

Ao final do programa principal, compare os resultados obtidos pelos dois métodos.

3. Repita o exercício anterior, mas calcule a média do vetor ao invés do valor máximo.

4. Repita o exercício anterior, mas calcule a variância do vetor ao invés da média.
