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
     int valor_max = 0, valor = 542734400;
     for(i = 0; i < 50000 ; i++)
 	{
        v[i] = random();
    }
       for(i = 0; i < 50000 ; i++)
 	{
        if(v[i] > valor_max)
        {
            valor_max = v[i];
            
        }
 	}  
     
    printf("Valor valor_max: %d\n", valor_max); 	

 	return 0;
}
```
```bash
root@marcosadriano:/home/marcosadriano/Área de trabalho/Aula_08/Questão_02_a# ./main.exe
Valor valor_max: 2147469841
```

(b) Separando o vetor em 4 partes, e usando 4 threads para cada uma encontrar o máximo de cada parte.
Ao final das threads, o programa principal compara o resultado das quatro threads para definir o 
máximo do vetor.
```C
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>

	long int v[50000];
    int i;
    int  valor_max = 0, valor = 542734400;
    

void *print_thread_1(void *parameters)
{

    for(i = 0; i < 12500 ; i++)
 	{
        if(v[i] > valor_max)
        {
            valor_max = v[i];
        }
 	}  
}

void *print_thread_2(void *parameters)
{
    for(int n = 12500; n < 25000 ; n++)
 	{
        if(v[n] > valor_max)
        {
            valor_max = v[n];
        }
 	}  
}

void *print_thread_3(void *parameters)
{
    for(int m = 25000; m < 37500 ; m++)
 	{
        if(v[m] > valor_max)
        {
             valor_max = v[m];      
        }
 	}  
     
}

void *print_thread_4(void *parameters)
{
    for(int k = 37500; k < 50000 ; k++)
 	{
        if(v[k] > valor_max)
        {
             valor_max = v[k];
        }
 	}  
     
}

 int main()
 {
 	
    pthread_t thread_1, thread_2, thread_3, thread_4;
    
     for(i = 0; i < 50000 ; i++)
 	{
        v[i] = random();
        
    }
     
    pthread_create(&thread_1,NULL, &print_thread_1, &thread_1);
 	pthread_create(&thread_2,NULL, &print_thread_2, &thread_2);
 	pthread_create(&thread_3,NULL, &print_thread_3, &thread_3);
 	pthread_create(&thread_4,NULL, &print_thread_4, &thread_4);

    pthread_join(thread_1,NULL);
    pthread_join(thread_2,NULL);
    pthread_join(thread_3,NULL);
    pthread_join(thread_4,NULL);
     	 	
    printf("Valor max: %d\n",  valor_max); 	    
    
    return 0;
}


```
```bash
root@marcosadriano:/home/marcosadriano/Área de trabalho/Aula_08/Questão_02_b# gcc main.c -lpthread -o main.exe
root@marcosadriano:/home/marcosadriano/Área de trabalho/Aula_08/Questão_02_b# ./main.exe
Iguais: 2147469841

```


Ao final do programa principal, compare os resultados obtidos pelos dois métodos.

3. Repita o exercício anterior, mas calcule a média do vetor ao invés do valor máximo.
```C
#include <string.h>

	long int v[50000], soma;
    int i;
    int parametro[30];

 int main()
 {

     for(i = 0; i < 50000 ; i++)
 	{
        v[i] = random();
        
    }
     
       for(i = 0; i < 50000 ; i++)
 	{
            soma = v[i] + soma;
            
    }

    printf("Soma: %ld\n", soma); 	
    printf("Valor media: %ld\n", soma/50000); 	

 	return 0;
}


```
```bash
root@marcosadriano:/home/marcosadriano/Área de trabalho/Aula_08/Questão_03_A# gcc main.c -lpthread -o main.exe
root@marcosadriano:/home/marcosadriano/Área de trabalho/Aula_08/Questão_03_A# ./main.exe
Soma: 53515543507997
Valor media: 1070310870

```
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
			PARTE B
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

```C
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>

	long int v[50000];
    int i;
    long int  soma, soma_1, soma_2, soma_3;
    

void *print_thread_1(void *parameters)
{

    for(i = 0; i < 12500 ; i++)
 	{
            soma = soma + v[i];
 	}  
}

void *print_thread_2(void *parameters)
{
    for(int n = 12500; n < 25000 ; n++)
 	{           
        soma_1 = soma_1 + v[n];
 	}  
}

void *print_thread_3(void *parameters)
{
    for(int m = 25000; m < 37500 ; m++)
 	{
        soma_2 = soma_2 + v[m];
 	}  
     
}

void *print_thread_4(void *parameters)
{
    for(int k = 37500; k < 50000 ; k++)
 	{
        soma_3 = soma_3 + v[k];
 	} 
     
}

 int main()
 {
 	
    pthread_t thread_1, thread_2, thread_3, thread_4;
    
     for(i = 0; i < 50000 ; i++)
 	{
        v[i] = random();
        
    }
     
    pthread_create(&thread_1,NULL, &print_thread_1, &thread_1);
 	pthread_create(&thread_2,NULL, &print_thread_2, &thread_2);
 	pthread_create(&thread_3,NULL, &print_thread_3, &thread_3);
 	pthread_create(&thread_4,NULL, &print_thread_4, &thread_4);

    pthread_join(thread_1,NULL);
    pthread_join(thread_2,NULL);
    pthread_join(thread_3,NULL);
    pthread_join(thread_4,NULL);

    soma = soma + soma_1 + soma_2 + soma_3;
    
    printf("Soma: %ld\n",  soma); 	    
    printf("Media: %ld\n",  soma/50000); 	    
    
    return 0;
}

```

```bash
root@marcosadriano:/home/marcosadriano/Área de trabalho/Aula_08/Questão_03_b# gcc main.c -lpthread -o main.exe
root@marcosadriano:/home/marcosadriano/Área de trabalho/Aula_08/Questão_03_b# ./main.exe
Soma: 53515543507997
Media: 1070310870
```

4. Repita o exercício anterior, mas calcule a variância do vetor ao invés da média.
