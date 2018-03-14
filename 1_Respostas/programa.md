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
