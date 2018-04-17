1. Especifique algumas portas importantes pré-definidas para o protocolo TCP/IP.

2. Com relação a endereços IP, responda:

(a) Qual é a diferença entre endereços IP externos e locais?
```bash
A diferença é exatamente essa: o primeiro é usado apenas na sua rede local, 
e é fornecido/controlado pelo seu roteador. Já o último é usado na internet,
e é controlado pelo Servidor.
```
(b) Como endereços IP externos são definidos? Quem os define?
```bash
Uma das funções do seu roteador é pegar os pacotes que vc envia pra internet,
e trocar o seu IP interno pelo externo, de forma que as máquinas da internet 
saibam fazer os pacotes de resposta voltarem pra você. Na volta, o roteador 
troca de volta o IP externo para o interno, pra que o pacote chegue até você.
Essa técnica é chamada NAT. 
```

(c) Como endereços IP locais são definidos? Quem os define?
```bash
Uma das funções do seu roteador é pegar os pacotes que vc envia pra internet,
e trocar o seu IP interno pelo externo, de forma que as máquinas da internet 
saibam fazer os pacotes de resposta voltarem pra você. Na volta, o roteador 
troca de volta o IP externo para o interno, pra que o pacote chegue até você.
Essa técnica é chamada NAT. 
```
(d) O que é o DNS? Para que ele serve?
```bash
O Sistema de Nomes de Domínio,mais conhecido pela nomenclatura em Inglês Domain
Name System (DNS), é um sistema hierárquico e distribuído de gerenciamento de 
nomes para computadores, serviços ou qualquer máquina conectada à Internet ou 
a uma rede privada. Faz a associação entre várias informações atribuídas a nomes
de domínios e cada entidade participante. Em sua utilização mais convencional,
associa nomes de domínios mais facilmente memorizáveis a endereços IP numéricos,
necessários à localização e identificação de serviços e dispositivos, processo 
esse denominado resolução de nome. Em virtude do banco de dados de DNS ser 
distribuído, seu tamanho é ilimitado e o desempenho não se degrada substancialmente
quando se adicionam mais servidores. Por padrão, o DNS usa o protocolo User Datagram
Protocol (UDP) na porta 53 para servir as solicitações e as requisições.
```

3. Com relação à pilha de protocolos TCP/IP, responda:

(a) O que são suas camadas? Para que servem?
```bash
A pilha TCP/IP é formada por quatro camadas. Este modelo apresenta uma solução prática
ao modelo OSI que nunca chegou a ser implementado. Servem para descrever e normatizar 
as conexões e comunicação na internet.
```
(b) Quais são as camadas existentes? Para que servem?
```bash
- As camadas que formam o TCP/IP são:
- Aplicação, funcionam os serviços que são diretamente fornecidos ao usuário da Internet.
Nesta camada funcionam protocolos como HTTP, DNS, DHCP, MSN Messenger e outros. É 
implementada simplesmente por software. Sua principal funcionalidade é padronizar a forma
com que os programas consigam conversar entre si, definindo regras que devem ser obedecidas
por todos os softwares que implementem tal serviço.
- A camada Transporte é responsável por criar uma comunicação fim-a-fim, ou seja, ela faz 
uma conexão virtual entre a origem e o destino. Os principais protocolos dessa camada são
o TCP (Transmission Control Protocol - Protocolo de Controle de Transmissão) e o UDP 
(User Datagram Protocol - protocolo de datagramas do usuário). 
- A camada de Redes está relacionada com o transporte dos pacotes da origem até o destino.
Quando se fala nisso, se fala em roteadores, que são os responsáveis por esse trabalho. Eles
não devem conhecer a localização de cada endereço na rede de ip em redes de comunicação curta.
Os protocolos tcp/ip dessa camada não podem garantir que pacotes possam ser roteados pela rede,
ou seja, protocolos que contenham endereçamento de origem e destino (IP, IPX/SPX, etc.) e 
protocolos que conheçam a rede e os respectivos endereços nela (RIP, OSPF, EIGRP, IS-IS, etc.),
além de utilizarem algoritmos de roteamento para determinar o caminho de menor custo. O principal
protocolo dessa camada é o IP (Internet Protocol). Nessa camada, os segmentos da camada superior
(transporte) são agrupados em datagramas.
- A camada de Enlace de dados é responsável por dar acesso ao meio físico de comunicação. Como é
uma camada bem próxima à transferência de bits, ela também fornece correção de erros, através da
Checagem Cíclica de Redunância (CRC - Cyclic Redundancy Checksum). Também é responsável por fazer
o controle do fluxo de bits, de forma que o receptor possa receber os dados a uma velocidade que 
possa processar. Essa camada trata as topologias de rede e engloba dispositivos como Switch, 
placas de rede, interfaces, etc. Os pacotes de dados, nessa camada, são denominados quadros. 
Exemplos de protocolos da camada de enlace são o Ethernet e o PPP, e é nessa camada onde são 
adicionados cabeçalhos e trailers MAC. Isso permite que seja feita a análise do MAC Address em
um dado aplicativo. Uma breve descrição a respeito do MAC Address é feita abaixo.
```
(c) Quais camadas são utilizadas pela biblioteca de sockets?
```bash
Os sockets estão entre a camada de transporte e a de aplicações. Estando nesse ponto de
intercessão, eles conseguem fazer uma interface entre a aplicação e rede de maneira bem
transparente. Assim, aplicações são implementadas através de uma comunicação lógica. 
Lógica no sentido de que para esses programas, eles estão se comunicando diretamente 
um com o outro, mas na prática, eles estão passando pela rede para trocar mensagens.
```
(d) As portas usadas por servidores na função bind() se referem a qual camada?
```bash
Camada de redes.
```

(e) Os endereços usados por clientes na função connect() se referem a qual camada?
```bash
Camada de redes.
```
4. Qual é a diferença entre os métodos `GET` e `POST` no protocolo HTTP?
```bash
Os principais métodos de comunicação HTTP são: GET e POST.
Visibilidade – A grande diferença entre os métodos GET e POST provavelmente é a visibilidade.
Uma requisição GET é enviada como string anexada a URL, enquanto que a requisição
POST é encapsulada junto ao corpo da requisição HTTP e não pode ser vista.

Tamanho – Como a requisição GET é feita via URL, obviamente há uma limitação no tamanho da mensagem enviada. A string não pode conter mais que 255 caracteres(embora exista diferenças entre navegadores, mas em geral o limite é 255). Já na requisição POST não há limitações de comprimento da mensagem, já que a mesma é enviada no corpo da requisição HTTP.

Performance – A requisição GET é relativamente mais rápida, já que ela é mais simples. Na requisição POST há uma perda de tempo no encapsulamento da mensagem.

Tipos – Já que GET é enviado via URL, então nós sabemos que ela só transporta textos. A requisição POST não tem restrições, pode transportar tanto texto, como dados binários.

Favoritos/Bookmarks – Por se tratar apenas de uma URL, a requisição GET pode ser armazenada em cache, ou em um sistema de bookmark(favoritos). A mesma coisa não é possível para requisições POST.

Método HTML Padrão – GET é o método HTML padrão. Para submeter um formulário HTML usando POST é preciso especificar no atributo “method” o valor “POST”.

Dados – As requisições GET são limitadas ao padrão ASCII, enquanto que requisições POST também podem usar o atributo “enctype” com o valor “multipart/form-data”, que faz uso do padrão UCS(Universal Multiple-Octet Coded Character Set).
```
