

    Quais são as vantagens e desvantagens em utilizar:

(a) fork?

    A execução de tarefas é feita de forma individual e exclusiva

    Cada filho tem seu espaço dememória protegido

    Os filhos criados rodam como processos específicos

    A comunicação é feita por pipes, sinais, etc

(b) threads?

    Uma só aplicação pode rodar várias threads

    Todas as threads compartilham o mesmo espaço de memória

    A comunicação é mais simples por usar memória compartilhada

    Risco de corrupção de dados

    Quantas threads serão criadas após as linhas de código a seguir? Quantas coexistirão? Por quê?

(a)
```C
void* funcao_thread_1(void *arg);
void* funcao_thread_2(void *arg);

int main (int argc, char** argv)
{
	pthread_t t1, t2;	//CRIADOS 2 DESCRITORES
	pthread_create(&t1, NULL, funcao_thread_1, NULL); //CRIADO THREAD
	pthread_create(&t2, NULL, funcao_thread_2, NULL); //CRIADO THREAD
	pthread_join(t1, NULL); //THREAD ESPERA FIM DE FUNÇÃO APONTADA POR DESCRITOR t1
	pthread_join(t2, NULL); //THREAD ESPERA FIM DE FUNÇÃO APONTADA POR DESCRITOR t2
	return 0;
}
```
Serão criadas 2 Threads e coexistirão 2;

(b)
```C
void* funcao_thread_1(void *arg);
void* funcao_thread_2(void *arg);

int main (int argc, char** argv)
{
	pthread_t t1, t2;	//CRIADOS 2 DESCRITORES
	pthread_create(&t1, NULL, funcao_thread_1, NULL);	/CRIADO THREAD COM DESCRITOR t1
	pthread_join(t1, NULL);		//THREAD ESPERA FIM DE FUNÇÃO APONTADA POR DESCRITOR t1
	
	//THREAD t1 FOI ENCERRADA;
	
	pthread_create(&t2, NULL, funcao_thread_2, NULL);	/CRIADO THREAD COM DESCRITOR t2
	pthread_join(t2, NULL);	//THREAD ESPERA FIM DE FUNÇÃO APONTADA POR DESCRITOR t2
	return 0;
}
```
Serão criadas 2 Threads e coexistirão 1 a cada vez, a segunda só é criada com o fim da pŕimeira;

    Apresente as características e utilidades das seguintes funções:

#include <pthread.h>

   int pthread_cancel(pthread_t thread);

   Compile and link with -pthread.

The pthread_cancel() function sends a cancellation request to the thread
thread. Whether and when the target thread reacts to the cancellation request
depends on two attributes that are under the control of that thread: its 
cancelability state and type.

(a) pthread_setcancelstate()

A thread's cancelability state, determined by pthread_setcancel‐state,  
can be enabled (the default for new threads) or disabled. If a thread
has disabled cancellation, then a cancellation request remains queued
until the thread enables cancellation. If a thread has enabled 
cancellation, then its cancelability type determines when 
cancellation occurs.

 PTHREAD_CANCEL_ENABLE
              The thread is cancelable.  This is the default cancelability
              state in all new threads, including the initial thread.  The
              thread's cancelability type determines when a cancelable
              thread will respond to a cancellation request.

       PTHREAD_CANCEL_DISABLE
              The thread is not cancelable.  If a cancellation request is
              received, it is blocked until cancelability is enabled.

(b) pthread_setcanceltype()

A thread's cancellation type, determined by pthread_setcanceltype(3), may be either asynchronous or deferred (the default for new threads). Asynchronous cancelability means that the thread can be canceled at any time (usually immediately, but the system does not guarantee this). Deferred cancelability means that cancellation will be delayed until the thread next calls a function that is a cancellation point. A list of functions that are or may be cancellation points is provided in pthreads(7).

(DICA: elas são relacionadas à função pthread_cancel().)
