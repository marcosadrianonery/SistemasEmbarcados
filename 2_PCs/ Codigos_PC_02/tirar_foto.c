#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
int main(int argc, const char * argv[]) {
int n;
char entrada[40];
char string_foto[40];
		strcpy (entrada, argv[1]);
		strcat (entrada, " ");		
		strcat (entrada, argv[2]);
		//puts(entrada);
		system(entrada);
		//sleep(2);
		strcpy (string_foto, "gpicview");
		strcat (string_foto, " ");		
		strcat (string_foto, argv[2]);
		system(string_foto);	
}
