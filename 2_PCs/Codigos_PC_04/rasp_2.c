//https://raspberrypi.stackexchange.com/questions/55850/rpi-bluetooth-headless-communication-with-android-phone-no-pairing
//
//https://stackoverflow.com/questions/26736762/linking-with-libbluetooth-so
//gcc simplescan.c -lbluetooth -o simplescan

//g++ -std=c++11 -pthread rfcomm-server.cpp -o rfcomm-server_teste -lbluetooth ` pkg-config --cflags --libs opencv`
//
////////////////////////////////////////////////////
#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/rfcomm.h>
#include "opencv2/opencv.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <thread>         // std::thread
#include <fcntl.h> 
#include <termios.h>
#include <string.h>
#include <sys/types.h>

using namespace std;
using namespace cv;

    struct sockaddr_rc loc_addr = { 0 }, rem_addr = { 0 };
    char buf[1024] = { 0 };
	char placa[7], placa_aux[7];
	char c, mensagem[500];
	char leitura_banco[500] = "Atual";
	char leitura[2];
	char nome_arquivo[30] = "Banco_placas/";
    int s, client, bytes_read;
	//ENDEREÇO DO DISPOSITIVO QUE IRA RECEBER DADOS
	char address[18] = "B8:27:EB:22:79:E7";

////////////////////////////////////////////////////////////////////
//			THREAD_READ 
//		ESSA THREAD É RESPONSAVEL PELO RECEBMENTO DE DADOS VIA BLUETOOTH
////////////////////////////////////////////////////////////////////////////	
void thread_read()
{	 	
    // read data from the client
	while(c != 27){
		bytes_read = read(client, buf, sizeof(char));
		printf("received [%s]\n", buf);		
////////////////////////////////////////////////////////
		if(buf[0] == '-')
		{
			puts("Recebe placa:");
//	AQUI FAZ-SE A LEITURA DO BUFFER DA COMUNICAÇÃO E ESCREVE EM UMA STRING
// 	ATENTA-SE QUE A PLACA TEM 7 CARACTERES
			for(int n = 0; n < 7; n++)
			{
				bytes_read = read(client, buf, sizeof(buf));
				placa[n] = buf[0];
				printf("received [%s]\n", buf);
				if( bytes_read < 0 ) {
					printf("received [%s]\n", buf);
					break;
				}
		
			}
				placa[7] = NULL;
				//MOSTRA QUAL FOI A PLACA LIDA
				printf("A placa é: %s \n", placa);
				
		}
		//A PLACA É COPIADA PARA UMA OUTRA VARIAVEL DE FORMA QUE POSSA FICAR 
		//VISIVEL A OUTRA THREADS E AS DEMAIS NÃO ENTREM EM CHOQUE COM ESSA
		stpcpy(placa_aux, placa);
	}	
}

/////////////////////////////////////////////////////////////////////
//			THREAD APRESENTAR BANCO DE DADOS
/////////////////////////////////////////////////////////////////////
void thread_banco_dados()
{
	//puts("Entrou");
	
	Mat source, scaleDown;
	char palavra_temp[25], temp[2];
		 
	
	 while(c != 27)
	 {
	scaleDown = imread("fundo.jpg");
	cv::resize(scaleDown, source, Size(), 2, 2, INTER_LINEAR );
	namedWindow("Original", WINDOW_AUTOSIZE); 
	putText(source,mensagem, Point(30,50), FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 255, 0), 1);
	imshow("Original", source);	
	c = (char)waitKey(25);
	}
			destroyAllWindows();
}
//////////////////////////////////////////////////////////////////////////////////
//		THREAD_LEITURA_ARQUIVO ABRE O ARQUIVO RESPONSAVEL POR GUARDAR
//		TODOS OS DADOS DOS VEICULOS, DESDE SUA REGULARIDADE ATENTA-SE
//		QUAIS VIRIAM A SER SUAS INFRAÇÕES
//////////////////////////////////////////////////////////////////////////////////
void thread_leitura_arquivo()
{
		int descritor, descritor2, m = 0, chave = 30, g = 0;
		char temp[2], temp_mensagem[500], placa_lida[7];
		//ABRE O AQUIVO QUE GUARDA OS DADOS
		descritor = open("banco_placas.txt", O_RDWR);
		puts("abriu");
		while(c != 27)
		{
			
				while(1)
				{
					//LÊ OS DADOS LINHA A LINHA
					read(descritor, temp_mensagem, sizeof(char));
					//printf("%d",descritor);
					//printf("%s", temp_mensagem);
					mensagem[m] = temp_mensagem[0];
					m++;
					mensagem[m] = '\0';
					if(temp_mensagem[0]=='\n') 
					{	
						break;
					}
					usleep(50);
				}
				
				//MARCADOR PARA FIM DE ARQUIVO
				//A FUNÇÃO LSEEK VOLTA O DESCRITOR
				//AO INICIO DO ARQUIVO
				if(mensagem[0] == '-')
					lseek(descritor, 0, SEEK_SET);
				
				//OUTRO MARCADOR QUE DEFINE AONDE
				//ESTA ESCRITO A PLACA
				if(mensagem[0] == '0')
				{
 				for(int z = 0; z < 7; z++)
				{
						chave = 0;
					//if(placa_lida[z] != placa_aux[z])
					if(mensagem[z+9] != placa_aux[z])
					{
						chave = 30;
						break;
					}
				}
				}
					
				if(chave == 0)
				{
					for(int r = 0; r < 28; r++)
					{	
						g = 0;
						while(1)
						{
							//printf("");
							read(descritor, temp_mensagem, sizeof(char));
							printf("%s", temp_mensagem);
							//printf("%s", temp_mensagem);
							mensagem[g] = temp_mensagem[0];
							g++;
							mensagem[g] = '\0';
							if(temp_mensagem[0]=='\n') break;
							//if(temp_mensagem[0]=='-') break;
							usleep(50);
						}
						//printf("%s", mensagem);
					}
					stpcpy(placa_aux, "0000000");
					chave = 30;
				}
				usleep(300);
				m = 0;
				
			}
		close(descritor);
} 

int main(int argc, char **argv)
{
    socklen_t opt = sizeof(rem_addr);

    // allocate socket
    s = socket(AF_BLUETOOTH, SOCK_STREAM, BTPROTO_RFCOMM);

    // bind socket to port 1 of the first available 
    // local bluetooth adapter
    loc_addr.rc_family = AF_BLUETOOTH;
	////////////////////////////////////////////////
    //loc_addr.rc_bdaddr = *BDADDR_ANY;
	str2ba( address, &loc_addr.rc_bdaddr);
	//////////////////////////////////////////////
    loc_addr.rc_channel = (uint8_t) 1;
    bind(s, (struct sockaddr *)&loc_addr, sizeof(loc_addr));

    // put socket into listening mode
    listen(s, 1);

    // accept one connection
    client = accept(s, (struct sockaddr *)&rem_addr, &opt);

    ba2str( &rem_addr.rc_bdaddr, buf );
    fprintf(stderr, "accepted connection from %s\n", buf);
    memset(buf, 0, sizeof(buf));

	thread first (thread_read);
	thread second (thread_banco_dados);
	thread third (thread_leitura_arquivo);
	
	first.join();                // pauses until first finishes 
	second.join();                // pauses until second finishes 
	third.join();                // pauses until second finishes 
	
    // close connection
    close(client);
    close(s);
    return 0;
}
