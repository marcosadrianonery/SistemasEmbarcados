
1. Crie um programa em C que preenche matrizes `long int A[60][60]` e `long int B[60][60]` completamente com valores aleatórios (use a função `random()`), e que calcula a soma das duas matrizes por dois métodos:

(a) De forma sequencial;

(b) De forma paralela.
```C
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

    long int A[60][60];
    long int B[60][60];
    long int soma_serie[60][60];
    long int soma_paralelo[60][60];
    
    int i;

//////////////////////////////////////////////////////////////////    
//                 THREADS_FUNCTIONS
//////////////////////////////////////////////////////////////////    
void *function_thread_1(void *parameters)
{
 	for(int n = 0; n < 20 ; n++)
 	{    
        for(int p = 0; p < 60 ; p++)
 	{
            soma_paralelo[n][p] = (A[n][p]) + (B[n][p]);
 	}
        
    }
	return NULL;
}
    
void *function_thread_2(void *parameters)
{

 	for(int m = 20; m < 40 ; m++)
 	{    
         	for(int q = 0; q < 60 ; q++)
 	{
            soma_paralelo[m][q] = (A[m][q]) + (B[m][q]);
 	}
        
    }
	return NULL;
}

void *function_thread_3(void *parameters)
{
 	for(int o = 40; o < 60 ; o++)
 	{    
         	for(int r = 0; r < 60 ; r++)
 	{
            soma_paralelo[o][r] = (A[o][r]) + (B[o][r]);
 	}
        
    }
	return NULL;
}

//////////////////////////////////////////////////////////////////
//                     IMPRIMIR_VALORES
//////////////////////////////////////////////////////////////////
    
void printf_matrix(long int matrix[][60])
{
    for(int m = 0; m < 60; m++)
    {
            for(int k = 0; k < 60; k++)
            {
                 printf("[%d][%d]: %ld  |",m+1,k+1,matrix[m][k]);
            }    
        printf("\n");
        printf("\n");
    }
    
}

//////////////////////////////////////////////////////////////////
//                     FUNCTION_COMPARAR
//////////////////////////////////////////////////////////////////
    
void comparar(long int matrix_serie[][60], long int matrix_paralela[][60])
{
    int diferente = 0;
    for(int m = 0; m < 60; m++)
    {
            for(int k = 0; k < 60; k++)
            {
                 if (matrix_serie[m][k] != matrix_paralela[m][k])
                 {
                     diferente = 1;
            printf("matrix_serie [%d][%d]: %ld", m, k, matrix_serie[m][k]);
            printf("matrix_paralela [%d][%d]: %ld", m,k,matrix_paralela[m][k]);
                 }
            }    
    }
    
    if(diferente == 1)
    {
        printf("As matrizes são diferentes.");
    } else
    {
        printf("As matrizes são iguais.");
    }
        
    
}



//////////////////////////////////////////////////////////////////
//                     MAIN
//////////////////////////////////////////////////////////////////


 int main()
 {
/////////////////////////////////////////////////////////////////////////////
//             SOMA SERIE
////////////////////////////////////////////////////////////////////////////    

 	for(i = 0; i < 60 ; i++)
 	{
         	for(int n = 0; n < 60 ; n++)
 	{     
            A[i][n] = rand() % 100;
            B[i][n] = rand() % 100;
            soma_serie[i][n] = (A[i][n]) + (B[i][n]);
 	}
    }

//     printf_matrix(soma_serie);

/////////////////////////////////////////////////////////////////////////////
//             SOMA PARALELA
////////////////////////////////////////////////////////////////////////////    
//     TRABALHAR COM TRES THREDS CADA UMA SOMA UMA PARTE DA matrix
////////////////////////////////////////////////////////////////////////////    
    
    
      pthread_t thread_1, thread_2, thread_3;
 
  	pthread_create(&thread_1,NULL, &function_thread_1, NULL);
  	pthread_create(&thread_2,NULL, &function_thread_2, NULL);
  	pthread_create(&thread_3,NULL, &function_thread_3, NULL);

    
  	pthread_join(thread_1,NULL);
    pthread_join(thread_2,NULL);
  	pthread_join(thread_3,NULL);

//     printf_matrix(soma_paralelo);

         comparar(soma_serie, soma_paralelo);
    
    
//         int diferente = 0;
//     for(int m = 0; m < 60; m++)
//     {
//             for(int k = 0; k < 60; k++)
//             {
//                  if (soma_serie[m][k] != soma_paralelo[m][k])
//                  {
//                      diferente = 1;
//             printf("matrix_serie [%d][%d]: %ld", m, k, soma_serie[m][k]);
//             printf("matrix_paralela [%d][%d]: %ld", m,k,soma_paralelo[m][k]);
//                  }
//             }    
//     }
//     
//     if(diferente == 1)
//     {
//         printf("As matrizes são diferentes.");
//     } else
//     {
//         printf("As matrizes são iguais.");
//     }
    
    return 0;    
}
```

Ao final do programa principal, compare os resultados obtidos pelos dois métodos.

2. Repita o exercício anterior, mas calcule o produto matricial A*B.
```C
include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

    long int A[60][60], aux=0;
    long int B[60][60];
    long int produto_serie[60][60];
    long int produto_paralelo[60][60];
    
    int i, coluna;

//////////////////////////////////////////////////////////////////    
//                 THREADS_FUNCTIONS
//////////////////////////////////////////////////////////////////    
void *function_thread_1(void *parameters)
{
    for(int m = 0; m < 60; m++)
    {
 	for(int n = 0; n < 60 ; n++)
 	{    
        for(int p = 0; p < 60 ; p++)
 	{
            aux = aux + (A[n][p])*(B[p][n]);
            
 	}

        produto_paralelo[m][n] = aux;
        aux = 0;
        coluna++;
    }
    }
	return NULL;
}


//////////////////////////////////////////////////////////////////
//                     IMPRIMIR_VALORES
//////////////////////////////////////////////////////////////////
    
void printf_matrix(long int matrix[][60])
{
    for(int m = 0; m < 60; m++)
    {
            for(int k = 0; k < 60; k++)
            {
                 printf("[%d][%d]: %ld  |",m+1,k+1,matrix[m][k]);
            }    
        printf("\n");
        printf("\n");
    }
    
}

//////////////////////////////////////////////////////////////////
//                     FUNCTION_COMPARAR
//////////////////////////////////////////////////////////////////
    
void comparar(long int matrix_serie[][60], long int matrix_paralela[][60])
{
    int diferente = 0;
    for(int m = 0; m < 60; m++)
    {
            for(int k = 0; k < 60; k++)
            {
                 if (matrix_serie[m][k] != matrix_paralela[m][k])
                 {
                     diferente = 1;
            printf("matrix_serie [%d][%d]: %ld", m, k, matrix_serie[m][k]);
            printf("matrix_paralela [%d][%d]: %ld", m,k,matrix_paralela[m][k]);
                 }
            }    
    }
    
    if(diferente == 1)
    {
        printf("As matrizes são diferentes.");
    } else
    {
        printf("As matrizes são iguais.");
    }
        
    
}



//////////////////////////////////////////////////////////////////
//                     MAIN
//////////////////////////////////////////////////////////////////


 int main()
 {
/////////////////////////////////////////////////////////////////////////////
//             SOMA SERIE
////////////////////////////////////////////////////////////////////////////    

 	for(i = 0; i < 60 ; i++)
 	{
         	for(int n = 0; n < 60 ; n++)
 	{     
            A[i][n] = 1;//rand() % 100;
            B[i][n] = 2;//rand() % 100;
 	}
    }
    
    for(int m = 0; m < 60; m++)
    {
 	for(int n = 0; n < 60 ; n++)
 	{    
        for(int p = 0; p < 60 ; p++)
 	{
            aux = aux + (A[n][p])*(B[p][n]);
            
 	}

        produto_serie[m][n] = aux;
        aux = 0;
        coluna++;
    }
    }
    
    
    
//      printf_matrix(produto_serie);

/////////////////////////////////////////////////////////////////////////////
//             SOMA PARALELA
////////////////////////////////////////////////////////////////////////////    
//     TRABALHAR COM TRES THREDS CADA UMA SOMA UMA PARTE DA matrix
////////////////////////////////////////////////////////////////////////////    
    
    
      pthread_t thread_1;
 
  	pthread_create(&thread_1,NULL, &function_thread_1, NULL);
 
    
  	pthread_join(thread_1,NULL);
 

//     printf_matrix(produto_paralelo);

         comparar(produto_serie, produto_paralelo);
    
    return 0;

     
}
```


3. Repita o exercício anterior, mas calcule o produto da matriz `long int A[60][60]` por um escalar `long int x`.
```C
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

    long int A[60][60], aux=0;
    long int escalar = 3;
    long int produto_serie[60][60];
    long int produto_paralelo[60][60];
    
    int i, coluna;

//////////////////////////////////////////////////////////////////    
//                 THREADS_FUNCTIONS
//////////////////////////////////////////////////////////////////    
void *function_thread_1(void *parameters)
{
    for(int m = 0; m < 60; m++)
    {
 	for(int n = 0; n < 60 ; n++)
 	{    
        produto_paralelo[m][n] = (A[m][n])*(escalar);
            
 	}        
    }
	return NULL;
}


//////////////////////////////////////////////////////////////////
//                     IMPRIMIR_VALORES
//////////////////////////////////////////////////////////////////
    
void printf_matrix(long int matrix[][60])
{
    for(int m = 0; m < 60; m++)
    {
            for(int k = 0; k < 60; k++)
            {
                 printf("[%d][%d]: %ld  |",m+1,k+1,matrix[m][k]);
            }    
        printf("\n");
        printf("\n");
    }
    
}

//////////////////////////////////////////////////////////////////
//                     FUNCTION_COMPARAR
//////////////////////////////////////////////////////////////////
    
void comparar(long int matrix_serie[][60], long int matrix_paralela[][60])
{
    int diferente = 0;
    for(int m = 0; m < 60; m++)
    {
            for(int k = 0; k < 60; k++)
            {
                 if (matrix_serie[m][k] != matrix_paralela[m][k])
                 {
                     diferente = 1;
            printf("matrix_serie [%d][%d]: %ld", m, k, matrix_serie[m][k]);
            printf("matrix_paralela [%d][%d]: %ld", m,k,matrix_paralela[m][k]);
                 }
            }    
    }
    
    if(diferente == 1)
    {
        printf("As matrizes são diferentes.");
    } else
    {
        printf("As matrizes são iguais.");
    }
        
    
}



//////////////////////////////////////////////////////////////////
//                     MAIN
//////////////////////////////////////////////////////////////////


 int main()
 {
/////////////////////////////////////////////////////////////////////////////
//             SOMA SERIE
////////////////////////////////////////////////////////////////////////////    

 	for(i = 0; i < 60 ; i++)
 	{
         	for(int n = 0; n < 60 ; n++)
 	{     
            A[i][n] = rand() % 100;
 	}
    }
    
    for(int m = 0; m < 60; m++)
    {
 	for(int n = 0; n < 60 ; n++)
 	{    
        produto_serie[m][n] = (A[m][n])*(escalar);
            
 	}        
    }
    
     printf_matrix(produto_serie);

/////////////////////////////////////////////////////////////////////////////
//             SOMA PARALELA
////////////////////////////////////////////////////////////////////////////    
//     TRABALHAR COM TRES THREDS CADA UMA SOMA UMA PARTE DA matrix
////////////////////////////////////////////////////////////////////////////    
    
    
      pthread_t thread_1;
 
  	pthread_create(&thread_1,NULL, &function_thread_1, NULL);
 
    
  	pthread_join(thread_1,NULL);
 

//     printf_matrix(produto_paralelo);

         comparar(produto_serie, produto_paralelo);
    
    return 0;

     
}
```
