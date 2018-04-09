1. Quantos pipes serão criados após as linhas de código a seguir? Por quê?

(a)
```C
int pid;
int fd[2];
pipe(fd);
pid = fork();
```
```bash
Apenas 1 pipe com uma posição para leitura e outra para escrita.
Sendo que a criação do mesmo ocorreu antes do fork e tanto o Pai
quanto o Filho compartinham.
```

(b)
```C
int pid;
int fd[2];
pid = fork();
pipe(fd);

```bash
Tem-se 2 pipes sendo que cada um com uma posição para leitura e outra para escrita.
Sendo que a criação do mesmo ocorreu depois do fork e tanto o Pai
quanto o Filho criaram seu pipe em seu proprio processo, e um não enxerga o do outro.
``````


2. Apresente mais cinco sinais importantes do ambiente Unix, além do `SIGSEGV`, `SIGUSR1`, `SIGUSR2`,
`SIGALRM` e `SIGINT`. Quais são suas características e utilidades?
```bash
• SIGKILL (9) Destruição: “arma absoluta” para matar os 
processos. Não pode ser ignorada, tampouco interceptada
existe ainda o SIGTERM para uma morte mais “suave” para 
processos .
• SIGBUS(10) Emitido em caso de erro sobre o barramento. 
• SIGSEGV (11) Emitido em caso de violação da segmentação: 
tentativa de acesso a um dado fora do domínio de 
endereçamento do processo.
• SIGSYS( 12) Argumento incorreto de uma chamada de 
sistema. 
• SIGPIPE (13) Escrita sobre um pipe não aberto em leitura.
```

3. Considere o código a seguir:

```C
#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void tratamento_alarme(int sig)
{
	system("date");
	alarm(1);
}

int main()
{
	signal(SIGALRM, tratamento_alarme);
	alarm(1);
	printf("Aperte CTRL+C para acabar:\n");
	while(1);
	return 0;
}
```

Sabendo que a função `alarm()` tem como entrada a quantidade de segundos para terminar a contagem, 
quão precisos são os alarmes criados neste código? De onde vem a imprecisão? Este é um método 
confiável para desenvolver aplicações em tempo real?
```bash
A precisão da contagem não dá para saber com exatidão, pois o processador roda diversos processos
ao mesmo tempo e isto vai depender do tanto de tarefas que este estiver executando, quantos cores,
qual a velocidade de processamento, etc. Mas em um teste em sala foi possivél concluir que no
dispositivo testado a precisão é da ordem de algumas dezenas de milissegundos. A imprecisão é 
variável e não tem como torna este método confiável para aplicações em tempo real.```
