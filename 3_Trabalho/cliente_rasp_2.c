/*
    C ECHO client example using sockets
*/
#include<stdio.h> //printf
#include<string.h>    //strlen
#include<sys/socket.h>    //socket
#include<arpa/inet.h> //inet_addr
 
int main(int argc , char *argv[])
{
    int sock;
    struct sockaddr_in server;
    char message[1000] , server_reply[5000], *watchDog;
     
    //Create socket
    sock = socket(AF_INET , SOCK_STREAM , 0);
    if (sock == -1)
    {
        printf("Could not create socket");
    }
    puts("Socket created");
     
    server.sin_addr.s_addr = inet_addr("192.168.2.152");
    server.sin_family = AF_INET;
    server.sin_port = htons( 8888 );
 
    //Connect to remote server
    if (connect(sock , (struct sockaddr *)&server , sizeof(server)) < 0)
    {
        perror("connect failed. Error");
        return 1;
    }
     
    puts("Connected\n");
     
    //keep communicating with server
    while(1)
    {
        //printf("Enter message : ");
        //scanf("%s" , message);
        watchDog = "+sendMe\n"; 
        //Send some data
        if( send(sock , watchDog , strlen(watchDog) , 0) < 0)
        {
            puts("Send failed");
            return 1;
        }
		
    while(1)
	{
        //Receive a reply from the server
        if( recv(sock , server_reply , 5000 , 0) < 0)
        {
            puts("recv failed");
            break;
        }
		   
        //puts("Server reply :");
		//if(server_reply != NULL || server_reply != ' ')
        puts(server_reply);
			usleep(500000);
	}
    }
     
    close(sock);
    return 0;
}
