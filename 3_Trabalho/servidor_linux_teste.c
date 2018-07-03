/*
    C socket server example, handles multiple clients using threads
*/
 
#include<stdio.h>
#include<string.h>    //strlen
#include<stdlib.h>    //strlen
#include<sys/socket.h>
#include<arpa/inet.h> //inet_addr
#include<unistd.h>    //write
#include<pthread.h> //for threading , link with lpthread
#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <fcntl.h> 
#include <termios.h>
#include <string.h>
#include <sys/types.h>

 

//the thread function
void *connection_handler(void *);
void thread_leitura_arquivo();
void thread_atualizar_arquivo();
int chave = 30;
char placa[7] = "000000", cont_placa[2];
char mensagem[300], mensagem_lida[10000], temp_mensagem[500], mensagem_trans[10000];
  


////////////////////////////////////////////////////////////////////////////////////
//		MAIN
////////////////////////////////////////////////////////////////////////////////////

int main(int argc , char *argv[])
{
    int socket_desc , client_sock , c , *new_sock;
	pthread_t pesquisar_banco, atualizar_banco;

	pthread_create( &pesquisar_banco , NULL ,  &thread_leitura_arquivo , NULL);
	pthread_create( &atualizar_banco , NULL ,  &thread_atualizar_arquivo , NULL);

    struct sockaddr_in server , client;
	int read_size, count;
	char *ref_message, client_message;

    //Create socket
    socket_desc = socket(AF_INET , SOCK_STREAM , 0);
    if (socket_desc == -1)
    {
        printf("Could not create socket");
    }
    puts("Socket created");
     
    //Prepare the sockaddr_in structure
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons( 8888 );
     
    //Bind
    if( bind(socket_desc,(struct sockaddr *)&server , sizeof(server)) < 0)
    {
        //print the error message
        perror("bind failed. Error");
        return 1;
    }
    puts("bind done");
     
    //Listen
    listen(socket_desc , 3);
     
    //Accept and incoming connection
    puts("Waiting for incoming connections...");
    c = sizeof(struct sockaddr_in);
     
     
    //Accept and incoming connection
    puts("Waiting for incoming connections...");
    c = sizeof(struct sockaddr_in);
	
	//ATRIBUI UM ENDEREÇO AO NOVO SOCKET
	//int accept(int s, struct sockaddr *addr, socklen_t *addrlen);





    while( (client_sock = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c)) )
    {
        puts("Connection accepted");
         
        pthread_t sniffer_thread;
        new_sock = malloc(1);
        *new_sock = client_sock;
		






        if( pthread_create( &sniffer_thread , NULL ,  connection_handler , (void*) new_sock) < 0)
        {
            perror("could not create thread");
            return 1;
        }
         
		count++;
        //Now join the thread , so that we dont terminate before the thread
        //pthread_join( sniffer_thread , NULL);
        puts("Handler assigned");
    }
     
    if (client_sock < 0)
    {
        perror("accept failed");
        return 1;
    }

	pthread_join(pesquisar_banco,NULL);
	pthread_join(atualizar_banco,NULL);

     
    return 0;
}


//////////////////////////////////////////////////////////////////////////////////
//		THREAD_LEITURA_ARQUIVO ABRE O ARQUIVO RESPONSAVEL POR GUARDAR
//		TODOS OS DADOS DOS VEICULOS, DESDE SUA REGULARIDADE ATENTA-SE
//		QUAIS VIRIAM A SER SUAS INFRAÇÕES
//////////////////////////////////////////////////////////////////////////////////
void thread_leitura_arquivo()
{
		int descritor, descritor2, m = 0, g = 0;
		char temp[2], placa_lida[7];
		//ABRE O AQUIVO QUE GUARDA OS DADOS

				descritor = open("banco_placas.txt", O_RDWR);
				puts("abriu");

		while(1)
		{


				while(1)
				{
					//LÊ OS DADOS LINHA A LINHA
					read(descritor, temp_mensagem, sizeof(char));
					//printf("%d",descritor);
					//printf("%s", temp_mensagem);
					mensagem_lida[m] = temp_mensagem[0];
					m++;
					mensagem_lida[m] = '\0';
					if(temp_mensagem[0]=='\n') 
					{	
						break;
					}
					usleep(50);
				}
				
				//MARCADOR PARA FIM DE ARQUIVO
				//A FUNÇÃO LSEEK VOLTA O DESCRITOR
				//AO INICIO DO ARQUIVO

				if(mensagem_lida[0] == '-')
				{
					close(descritor);
					usleep(500);
					descritor = open("banco_placas.txt", O_RDWR);
					lseek(descritor, 0, SEEK_SET);
				}
				
				//OUTRO MARCADOR QUE DEFINE AONDE
				//ESTA ESCRITO A PLACA
				if(mensagem_lida[0] == '0')
				{
 				for(int z = 0; z < 7; z++)
				{
						chave = 0;
					//if(placa_lida[z] != placa_aux[z])
					if(mensagem_lida[z+9] != placa[z])
					{

						chave = 30;
						break;
					}
				}
				}
					
				if(chave == 0)
				{
					g = 0;
					for(int r = 0; r < 28; r++)
					{	
						
						while(1)
						{
							//printf("");
							read(descritor, temp_mensagem, sizeof(char));
							printf("%s", temp_mensagem);
							//printf("%s", temp_mensagem);
							mensagem_trans[g] = temp_mensagem[0];
							cont_placa[0] = temp_mensagem[0];
							g++;
							//mensagem_lida[g] = '\0';
							if(temp_mensagem[0]=='\n') break;
							//if(temp_mensagem[0]=='-') break;
							usleep(50);
						}
						//printf("%s", mensagem_lida);
					}
					stpcpy(placa, "0000000");
					chave = 30;
				}
				usleep(300);
				m = 0;
				
			}
				close(descritor);
} 



void thread_atualizar_arquivo()
{
	
     while(1){
      system("./atualizacaoserver.sh"); /*se o usuário tiver digitado 1 o sistema irá reiniciar*/
      sleep(20); //atualizar a cada 5 segundos
	}

}



/////////////////////////////////////////////////////////////////////////////////////////////Q
 
/*
 * This will handle connection for each client
 * */
void *connection_handler(void *socket_desc)
{
    //Get the socket descriptor
    int sock = *(int*)socket_desc;
    int read_size;
    char *message, *message_enviar, mensagem_socket;
     
    //Send some messages to the client
    message = "Bem vindo!\n";
    write(sock , message , strlen(message));
     
    //message = "Now type something and i shall repeat what you type \n";
    //write(sock , message , strlen(message));
     
    //Receive a message from client
    while( (read_size = recv(sock , mensagem , 2000 , 0)) > 0 )
    {
		puts(mensagem);
        //Send the message back to client
        write(sock , mensagem , strlen(mensagem));
	
	if(mensagem[0] == '-')
	{
		for(int n = 0; n < 7; n++)
		{
			placa[n] = mensagem[n + 1];
						//puts(placa);
						//puts(mensagem);
		}
		
   		message = "Recebi a placa.\n";
		write(sock , message , strlen(message));	
	
	} 
	if(mensagem[0] == '+')
	{
		while(1)
		{
			if(chave !=  0)
			{
				write(sock, mensagem_trans, strlen(mensagem_trans));
				usleep(5000000);
			}
	   		//message_enviar = "Enviando dados da placa.\n";
			//write(sock , message_enviar , strlen(message_enviar));	
			
		}
	
	} 


	//else{
		//message = "Reescreva a mensagem.\n";
		//write(sock , message , strlen(message));	
		//}

    }


     
    if(read_size == 0)
    {
        puts("Client disconnected");
        fflush(stdout);
    }
    else if(read_size == -1)
    {
        perror("recv failed");
    }
         
    //Free the socket pointer
    free(socket_desc);
     
    return 0;
}
