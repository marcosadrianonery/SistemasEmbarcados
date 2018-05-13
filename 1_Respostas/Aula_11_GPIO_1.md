1. Apresente 5 sistemas operacionais suportados pelo Raspberry Pi, e algumas de suas características.  
* Raspbian: sistema operacional (SO) oficial, baseado no Debian GNU/Linux.  
Possibilita o uso de grande parte dos pacotes disponíveis nos repositórios do  
Debian e possui software especializado para as placas Raspberry.
* Ubuntu MATE: derivação oficial do Ubuntu que usa o abiente de área de  
trabalho MATE.
* Snappy Ubuntu Core: versão mínima do Ubuntu voltada para dispositivos IoT.  
Precisa de credenciais Ubuntu SSO.
* Windows 10 IoT Core: sucessor do Windows CE.
* OSMC: sistema de código livre e aberto especializado em reproduzir mídia.  
Baseado no Debian GNu/Linux e no Kodi Media Center.

2. Apresente as formas de instalação de sistemas operacionais para o Raspberry Pi.  
Instalação apartir de uma midia de instalação, no caso por via de um SD card aonde o mesmo fica instalado
tambem pode ser por meio do porprio instalador.

3. Apresente 3 formas de desenvolvimento de software para o Raspberry Pi.  
Compilação cruzada no computador anfitrião (_host_) e enviar executáveis pela
conexão SSH, compilação direta no Raspberry por meio de conexão pelo SSH e
compilação cruzada e colocar executáveis diretamente no sistema de arquivos.

4. Apresente 3 formas de acesso remoto ao Raspberry Pi.  
SSH via rede, VNC, terminal UART (porta serial).

5. Apresente as formas possíveis de compilação de código em C para o Raspberry Pi.  
Compilação na propria Raspberry usando o GCC.
Compilação em um computador com outra arquitetura através de uma _toolchain_ que permita
compilação cruzada.

6. Apresente as formas possíveis de compilação de código em Python para o Raspberry Pi.  
Por meio do interpretador especifico.
