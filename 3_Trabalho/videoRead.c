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
#include<string.h>    //strlen
#include<sys/socket.h>    //socket
#include<arpa/inet.h> //inet_addr
#include <ctype.h>



using namespace std;
using namespace cv;
		char verificador[7][11];
		char c = 0;
		Mat frame1, frame2, frame3;
		char conteudo[100];
		char conteudo_temp_banco[500];
		char nome_arquivo[30] = "Banco_placas/";
		char conteudo_temp[100];
		char placa[7];
		char placa_teste[7];
		char aux_placa[7];
		char leitura_banco[500] = "Atual";
		char placa_temp[3][7];
		char confia[7];
		char leitura[2];


/////////////////////////////////////////////////////////////////////
//			THREAD ALPR
/////////////////////////////////////////////////////////////////////
void thread_alpr()
{
//*************************************************************
// 		ESSE PASSO FAZ UMA CHAMADA NO SISTEMA PARA USAR O ALPR
//		A VARIAVEL c SERÁ ATUALIZADA GLOBALMENTE POR MEIO DE UMA
//		FUNÇÃO DO OPEN CV "waitKey(25)", PRESENTE NA THREAD CAMERA
//*************************************************************
	 while(c != 27){	 
			system("alpr -c eu imagemLida.jpg");
		
  }
}

/////////////////////////////////////////////////////////////////////
//			THREAD CAMERA
/////////////////////////////////////////////////////////////////////
void thread_camera()
{
//*************************************************************
// 		ABRE A CAMERA OU UMA FOTO, '0' DEFINE COMO A CAMERA CONECTADA A RASP
//		FUNÇÃO DA BIBLIOTECA OPEN CV
//		"cap" É O DESTINO
//*************************************************************
	  VideoCapture cap(0); 
 
  if(!cap.isOpened()){
    cout << "Error opening video stream or file" << endl;
  }
//*************************************************************
//		A VARIAVEL c SERÁ ATUALIZADA GLOBALMENTE POR MEIO DE UMA
//		FUNÇÃO DO OPEN CV "waitKey(25)", PRESENTE NA THREAD CAMERA
//*************************************************************  
  
	 while(c != 27){
//*************************************************************
// 		É ALOCADO EM frame1 e frame2 SÃO VARIAVEIS DO TIPO MAT
// 		DA BIBLIOTECA OPEN CV
//*************************************************************
		cap >> frame1;
		cap >> frame2;
//*************************************************************
// 		CASO AS VARIAVEIS ESTEJAM VAZIAS QUEBRA-SE O LOOP
//*************************************************************		
		if (frame1.empty())
		  break;
		if (frame2.empty())
		  break;	  
//*************************************************************
//		FUNÇÃO DO OPENCV QUE PERMITE APRESENTAR NA IMAGEM OS DADOS
//		TUDO FEITO NA IMAGEM DE frame1
//*************************************************************		
		putText(frame1, conteudo, Point(30,50), FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 255,2), 1);
		putText(frame1, verificador[0], Point(30,100), FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 255, 0), 1);
		putText(frame1, verificador[1], Point(30,125), FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 255, 0), 1);
		putText(frame1, verificador[2], Point(30,150), FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 255, 0), 1);
		putText(frame1, verificador[3], Point(30,175), FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 255, 0), 1);
		putText(frame1, verificador[4], Point(30,200), FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 255, 0), 1);
		putText(frame1, verificador[5], Point(30,225), FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 255, 0), 1);
		putText(frame1, verificador[6], Point(30,250), FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 255, 0), 1);
		putText(frame1,"Confianca amostra:" , Point(40,280), FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 255, 0), 1);
		putText(frame1, confia, Point(400,280), FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 255, 0), 1);
		putText(frame1,"Maior correspondencia entre:" , Point(40,320), FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 255, 0), 1);
		putText(frame1,"20 medidas:" , Point(40,350), FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 255, 0), 1);
		putText(frame1, aux_placa, Point(240,350), FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 255, 0), 1);
		putText(frame1, "A placa e:", Point(40,430), FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 255, 0), 2);
		putText(frame1, placa, Point(240,430), FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 255, 0), 2);
		
//*************************************************************
// 		imshow APRESENTA A IMAGEM NA TELA OU DISPLAY, TAMBÉM DO OPEN CV
//*************************************************************
		imshow( "Frame", frame1 );
		c =(char)waitKey(25);
  }
		cap.release();
		destroyAllWindows();
}

/////////////////////////////////////////////////////////////////////
//			THREAD GRAVAR
/////////////////////////////////////////////////////////////////////
void thread_grava()
{
	 while(c != 27){
		usleep(100000);	
//*************************************************************
// 		É NECESSARIO SALVAR A IMAGEM PARA QUE O ALPR REALIZE A LEITURA
//		A IMAGEM É SOBRESCRITA SOBRE SUA ANTERIOR
//		A IMAGEM SALVA É  QUE GUARDOU-SE ANTERIORMENTE EM frame2
//		ASSIM NÃO HÁ CONFLITO COM O QUE É REALIZADO SOBRE A frame1
//		imwrite É UMA FUNÇÃO DA OPEN CV
//*************************************************************		
		imwrite("imagemLida.jpg", frame2);
  }
}
/////////////////////////////////////////////////////////////////////
//			THREAD LER
/////////////////////////////////////////////////////////////////////
void thread_ler_dados()
{
	verificador[0][10] = '\0';
	int descritor, n_byte, aux = 0;
	char nome_arquivo[] = "dado.txt";
//*************************************************************
// 		A IMAGEM É SALVA NO ARQUIVO "data,txt" E É REALIZADO SUA LEITURA
//*************************************************************	
	descritor = open (nome_arquivo, O_RDWR | O_CREAT);
	
	 while(c != 27){
 		//usleep(10000); 

//*************************************************************
// 		CASO DESCRITOR MENOR QUE 0, ESPERA UM TEMPO E TENTA-SE
//		NOVAMENTE ABRIR O ARQUIVO
//*************************************************************		
        if (descritor < 0){
				usleep(200000); 
        }	
	 	char temp[2]; 
		int conta = 0, aux;
		
		while(1)
		{
//*************************************************************
// 		LEITURA DO ARQUIVO
//*************************************************************		
			n_byte = read(descritor, temp, sizeof(char));
		
				if (descritor < 0){
					usleep(20000);
					n_byte = read(descritor, temp, sizeof(char));
				}	
//*************************************************************
//		LÊ-SE APENAS UMA LINHA
//*************************************************************		
				if(temp[0]=='\n') break;
			
//*************************************************************
 //		O CONTEUDO É SALVO NA VARIAVEL conteudo _temp
 //		A VARIAVEL conta APRESENTA O TAMANHO DA LINHA LIDA
//*************************************************************		
			conteudo_temp[conta] = temp[0];
			conta++;
		}

//*************************************************************
//		É ACRESCIDO O CARACTER PARA INDICAR O FIM DA STRING E ELA É
//		COPIADA PARA A VARIAVEL conteudo
//*************************************************************				
		conteudo_temp[conta+1] = '\0';
		strcpy(conteudo, conteudo_temp);
//*************************************************************
//		IMPRIME NA TELA AS LEITURAS INDEPENDENTEMENTE DA CONFIANÇA
//		DA AMOSTRA APENAS PARA VISUALIZAÇÃO
//*************************************************************			
  		if(conteudo[4] == '-')
		{
			verificador[0][aux] = conteudo[6];
			verificador[1][aux] = conteudo[7];
			verificador[2][aux] = conteudo[8];
			verificador[3][aux] = conteudo[9];
			verificador[4][aux] = conteudo[10];
			verificador[5][aux] = conteudo[11];
			verificador[6][aux] = conteudo[12];			
			aux ++;			
		}

		if(aux == 10){
			aux = 0;
		} 
//*************************************************************
//		TEMPO PARA A PROXIMA LEITURA
//*************************************************************		
		usleep(100000);
	}	
} 
/////////////////////////////////////////////////////////////////////
//			THREAD_DEFINIR PLACA
/////////////////////////////////////////////////////////////////////
void thread_placa()
{
  float confianca, confianca_atual = 0;
  int aux = 0;
  
 	while(c != 27)
	{
//************************************************************************
//			EXEMPLO_DE_LEITURA
//************************************************************************
/* plate0: 10 results
    - 5F084	 confidence: 84.9662
    - 5FE084	 confidence: 82.231
    - 5FQ84	 confidence: 81.9552
    - 5F5084	 confidence: 81.2061
    - 5FEQ84	 confidence: 79.22
    - I5F084	 confidence: 78.9241
    - D5F084	 confidence: 78.5321
    - 5FO84	 confidence: 78.4593
    - 5F5Q84	 confidence: 78.1951
    - 5FD84	 confidence: 78.1254
 */
 
 
 
//************************************************************************
//				NESSA ETAPA SÓ SERÃO ADMITIDOS LEITURAS QUE DEVEM SER CONSIDERADAS
//************************************************************************
	if(conteudo[4] == '-' )
	{

		for(int n = 26; n < 33; n++)
		{
			confia[n - 26] = conteudo[n];
		}
		confianca = atof(confia);
		

//************************************************************************
//		CADA LEITURA TEM UM NIVEL DE CONFIANÇA DEFINIDO PELO PROPRIO ALPR
//		AQUI É SELECIONADO OS MAIORES NIVEIS DE CONFIANÇA
// 		EX:     - 5FD84	 confidence: 78.1254
// 		O NIVEL DE CONFIANÇA É RESETADO PARA 85 
//		A CADA 20 AMOSTRAS COMO SERÁ VISTO ABAIXO
//************************************************************************
		if(confianca > confianca_atual)
		{
			confianca_atual = confianca;
			if (conteudo[12] != '	')
			{				
			aux_placa[0] = conteudo[6];
			aux_placa[1] = conteudo[7];
			aux_placa[2] = conteudo[8];
			aux_placa[3] = conteudo[9];
			aux_placa[4] = conteudo[10];
			aux_placa[5] = conteudo[11];
			aux_placa[6] = conteudo[12];			
			}
			
//************************************************************************
//				OS PRIMEIROS TRES DIGITOS DA PLACA SÃO LETRAS
//				TENDO CIENCIA DISSO QUALQUER ERRO DE LEITURA 
//				NO SENTIDO DE CONFUSÃO É CORRIGIDO NESSE PASSO
//************************************************************************
				for(int n = 0; n < 3; n++)
				{
					if(conteudo[n + 6] == '5')
					{
						aux_placa[n] = 'S';
					}								
					if(conteudo[n + 6] == '0')
					{
						aux_placa[n] = 'Q';
					}	
					if(conteudo[n + 6] == '1')
					{
						aux_placa[n] = 'I';
					}
					if(conteudo[n + 6] == '8')
					{
						aux_placa[n] = 'B';
					}					
				}

//************************************************************************
//				OS UTIMOS QUATRO DIGITOS DA PLACA SÃO NUMEROS
//				TENDO CIENCIA DISSO QUALQUER ERRO DE LEITURA 
//				NO SENTIDO DE CONFUSÃO É CORRIGIDO NESSE PASSO
//************************************************************************

				for(int n = 3; n < 7; n++)
				{
					if(conteudo[n + 6] == 'Q')
					{
						aux_placa[n] = '0';
					}	
					if(conteudo[n + 6] == 'I')
					{
						aux_placa[n] = '1';
					}		
					if(conteudo[n + 6] == 'S')
					{
						aux_placa[n] = '5';
					}		
					if(conteudo[n + 6] == 'D')
					{
						aux_placa[n] = '0';
					}
					if(conteudo[n + 6] == 'B')
					{
						aux_placa[n] = '8';
					}				
			}			

	
		}

//************************************************************************
//		A CADA 20, 40, 60 LEITURAS É SE GUARDADO A LEITURA NA VARIAVEL
//		PLACA_TEMP E QUANDO FEITA A LEITURA DESSAS TRES MAIS CONFIAVEIS AMOSTRAS
//		DENTRO DO GRUPO DE 20 É TESTADO QUAL DAS AMOSTRAS SE REPETEM
//************************************************************************
		aux++;
		
		if(aux == 10)
		{
			confianca_atual = 80.0;
			placa_temp[0][0] = aux_placa[0];
			placa_temp[0][1] = aux_placa[1];
			placa_temp[0][2] = aux_placa[2];
			placa_temp[0][3] = aux_placa[3];
			placa_temp[0][4] = aux_placa[4];
			placa_temp[0][5] = aux_placa[5];
			placa_temp[0][6] = aux_placa[6];
			
		}
		if(aux == 20)
		{
			confianca_atual = 80.0;
			placa_temp[1][0] = aux_placa[0];
			placa_temp[1][1] = aux_placa[1];
			placa_temp[1][2] = aux_placa[2];
			placa_temp[1][3] = aux_placa[3];
			placa_temp[1][4] = aux_placa[4];
			placa_temp[1][5] = aux_placa[5];
			placa_temp[1][6] = aux_placa[6];			
		}
		if(aux == 30)
		{
			aux = 0;
			confianca_atual = 80.0;
			placa_temp[2][0] = aux_placa[0];
			placa_temp[2][1] = aux_placa[1];
			placa_temp[2][2] = aux_placa[2];
			placa_temp[2][3] = aux_placa[3];
			placa_temp[2][4] = aux_placa[4];
			placa_temp[2][5] = aux_placa[5];
			placa_temp[2][6] = aux_placa[6];			
		}		

//*******************************************************
//		AQUI TESTA-SE QUAIS AMOSTRAS SE REPETEM
//**********************************************************		
		for(int n = 0; n < 7; n++)
		{
			if(placa_temp[0][n] == placa_temp[1][n])
			{	
				placa[n] = placa_temp[0][n];
			}					
			
			if(placa_temp[0][n] == placa_temp[2][n])
			{	
				placa[n] = placa_temp[0][n];
			}					
			
			if(placa_temp[1][n] == placa_temp[2][n])
			{	
				placa[n] = placa_temp[1][n];
			}		
		}
		
		
			stpcpy(placa_teste, placa);
		
	}
		usleep(100000);
	}
}



/////////////////////////////////////////////////////////////////////
//			THREAD APRESENTAR BANCO DE DADOS
/////////////////////////////////////////////////////////////////////
/* void thread_banco_dados()
{

	Mat source, scaleDown;
	char palavra_temp[25], temp[2];
		 
	
	 while(c != 27){

	//stpcpy(nome_arquivo, "Banco_placas/");
	stpcpy(palavra_temp, placa);
    strcat(palavra_temp,".txt");
    strcpy(nome_arquivo,palavra_temp);

	scaleDown = imread("fundo.jpg",1);
	cv::resize(scaleDown, source, Size(), 2, 2, INTER_LINEAR );

	namedWindow("Original", WINDOW_AUTOSIZE); 
		
		putText(source,nome_arquivo, Point(30,50), FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 255, 0), 1);
		putText(source,	leitura_banco, Point(30,100), FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 255, 0), 1);
		putText(source,	leitura, Point(30,150), FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 255, 0), 1);
		//putText(source,conteudo_temp_banco, Point(20,100), FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 255, 0), 1);
		
		
		imshow("Original", source);	
		
	usleep(800000);
	}
	
}
 */

 



/////////////////////////////////////////////////////////////////////
//			THREAD LER BANCO DE DADOS
/////////////////////////////////////////////////////////////////////
void thread_ler_banco_dados()
{
	int fp;
	int conta;
   
	while(1){
	conta = 0;
	fp = open (nome_arquivo, O_RDWR | O_CREAT, S_IRWXU);
	if(fp==-1)
	{
		//printf ("Erro na abertura do arquivo.\n");
		//exit (1);
	}
	usleep(1000000);
	do{
		read(fp, leitura, sizeof(char));
		if(leitura != NULL)
		{
		leitura_banco[conta] = leitura[0];
		conta++;
		}
	} while(leitura[0] != EOF || leitura[0] != NULL);

	close(fp);
	
	}	
}

 
/////////////////////////////////////////////////////////////////////
//			THREAD 	CLIENTE
/////////////////////////////////////////////////////////////////////
int thread_cliente()
{
    int sock;
    struct sockaddr_in server;
    char message[1000] , envia[8], server_reply[2000], codigo[2] = {'-'};
     
    //Create socket
    sock = socket(AF_INET , SOCK_STREAM , 0);
    if (sock == -1)
    {
        printf("Could not create socket");
    }
    puts("Socket created");
     
    server.sin_addr.s_addr = inet_addr("172.29.28.15");
    server.sin_family = AF_INET;
    server.sin_port = htons( 8888 );
 
    //Connect to remote server
    if (connect(sock , (struct sockaddr *)&server , sizeof(server)) < 0)
    {
        perror("connect failed. Error");
    }
     
    puts("Connected\n");
     
    //keep communicating with server
    while(1)
    {
        //printf("Enter message : ");
        //scanf("%s" , message);
         
		 
        //Send some data
		//send(sock , codigo , sizeof(char), 0);
		
		//stpcpy(envia, '-');
		
		
		
		
 		envia[0] = '-';
		envia[1] = toupper(placa[0]);
		envia[2] = toupper(placa[1]);
		envia[3] = toupper(placa[2]);
		envia[4] = placa[3];
		envia[5] = placa[4];
		envia[6] = placa[5];
		envia[7] = placa[6]; 

/* 		envia[0] = '-';
		envia[1] = 'n';
		envia[2] = 'n';
		envia[3] = 'n';
		envia[4] = '3';
		envia[5] = '8';
		envia[6] = '0';
		envia[7] = '1';	 */	
		//strcat(envia, placa);
		
        if( send(sock , envia , strlen(envia) , 0) < 0)
        {
            puts("Send failed");
            return 1;
        }
		
		sleep(2);
         
        //Receive a reply from the server
        if( recv(sock , server_reply , 2000 , 0) < 0)
        {
            //puts("recv failed");
            break;
        }
         
        //puts("Server reply :");
        //puts(server_reply);
    }
     
    close(sock);	
} 
 

////////////////////////////////////////////////////////////////////////////
//			MAIN - FUNÇÃO PRINCIPAL
/////////////////////////////////////////////////////////////////////////

int main(){
//*************************************************************
// 		CRIAÇÃO DAS THREDS
//*************************************************************
	thread first (thread_camera);
	thread second (thread_grava);
	thread third (thread_alpr);
	thread four (thread_ler_dados);
	thread five (thread_placa);
	thread six (thread_cliente);
	
	//thread six (thread_banco_dados);
	//thread seven (thread_ler_banco_dados);
	
//*************************************************************
// 		ESPERAR PELO FIM DAS THREDS
//*************************************************************
	first.join();                // pauses until first finishes 
	second.join();                // pauses until second finishes 
	third.join();                // pauses until second finishes 
	four.join();                // pauses until second finishes 
	five.join();                // pauses until second finishes 
	six.join();                // pauses until second finishes 
	//seven.join();                // pauses until second finishes 
	return 0;
}
