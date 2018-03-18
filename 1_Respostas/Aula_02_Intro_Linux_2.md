Para todas as questões, escreva os comandos correspondentes no terminal.

1. Escreva o texto "Ola mundo cruel!" em um arquivo denominado "Ola_mundo.txt". Apresente o conteúdo deste arquivo no terminal.
```bash
drico@drico-VirtualBox:~$ echo "Ola mundo cruel." > Ola_mundo.txt
drico@drico-VirtualBox:~$ cat  Ola_mundo.txt
Ola mundo cruel.
```
2. Apresente o nome de todos os arquivos e pastas na pasta 'root'.
```bash
$ ls /
```
3. Apresente o tipo de todos os arquivos e pastas na pasta 'root'.
```bash
$ ls -l /
```
4. Apresente somente as pastas dentro da pasta 'root'.
```bash
	$ cd /
	$ ls -d */
```
5. Descubra em que dia da semana caiu o seu aniversário nos últimos dez anos.
```bash
drico@drico-VirtualBox:~$ date -d "27 sep 2007"
Qui Set 27 00:00:00 BRT 2007
drico@drico-VirtualBox:~$ date -d "27 sep 2008"
Sáb Set 27 00:00:00 BRT 2008
drico@drico-VirtualBox:~$ date -d "27 sep 2009"
Dom Set 27 00:00:00 BRT 2009
drico@drico-VirtualBox:~$ date -d "27 sep 2010"
Seg Set 27 00:00:00 BRT 2010
drico@drico-VirtualBox:~$ date -d "27 sep 2011"
Ter Set 27 00:00:00 BRT 2011
drico@drico-VirtualBox:~$ date -d "27 sep 2012"
Qui Set 27 00:00:00 BRT 2012
drico@drico-VirtualBox:~$ date -d "27 sep 2013"
Sex Set 27 00:00:00 BRT 2013
drico@drico-VirtualBox:~$ date -d "27 sep 2014"
Sáb Set 27 00:00:00 BRT 2014
drico@drico-VirtualBox:~$ date -d "27 sep 2015"
Dom Set 27 00:00:00 BRT 2015
drico@drico-VirtualBox:~$ date -d "27 sep 2016"
Ter Set 27 00:00:00 BRT 2016
drico@drico-VirtualBox:~$ date -d "27 sep 2017"
Qua Set 27 00:00:00 BRT 2017
```
Para as questões a seguir, use a pasta no endereço https://github.com/DiogoCaetanoGarcia/Sistemas_Embarcados/raw/master/Questoes/02_Intro_Linux_arqs.zip

6. Liste somente os arquivos com extensão .txt.
```bash
drico@drico-VirtualBox:~/Área de Trabalho/Sistemas_Embarcados/Aula_02/02_Intro_L
inux_arqs/Arqs_aula_02$ ls *.txt
arquivo.txt   cal_1996.txt  cal_2003.txt  cal_2010.txt  cal_2017.txt
cal_1990.txt  cal_1997.txt  cal_2004.txt  cal_2011.txt  cal_2018.txt
cal_1991.txt  cal_1998.txt  cal_2005.txt  cal_2012.txt  cal_2019.txt
cal_1992.txt  cal_1999.txt  cal_2006.txt  cal_2013.txt  cal_2020.txt
cal_1993.txt  cal_2000.txt  cal_2007.txt  cal_2014.txt  cal.txt
cal_1994.txt  cal_2001.txt  cal_2008.txt  cal_2015.txt  cal_types.txt
cal_1995.txt  cal_2002.txt  cal_2009.txt  cal_2016.txt
```
7. Liste somente os arquivos com extensão .png.
```bash
drico@drico-VirtualBox:~/Área de Trabalho/Sistemas_Embarcados/Aula_02/02_Intro_L
inux_arqs/Arqs_aula_02$ ls *.png
BusinessTux.png               linux.png
linux1.png                    Tux-in-a-suit.png
linux2.png                    tux-linux-professional_0-100520358-orig.png
linux3.png                    TUX.png
linux_inside.png              xanderrun-tux-construction-8454.png
linux-penguin-icon-39742.png
```
8. Liste somente os arquivos com extensão .jpg.
```bash
drico@drico-VirtualBox:~/Área de Trabalho/Sistemas_Embarcados/Aula_02/02_Intro_L
inux_arqs/Arqs_aula_02$ ls *.jpg
d36f1a2be6a927ac3e2e1e4eacdedded.jpg  oRva1OGD.jpg
oRva1OGD_400x400.jpg                  zz39112bb5.jpg
```
9. Liste somente os arquivos com extensão .gif.
```bash
drico@drico-VirtualBox:~/Área de Trabalho/Sistemas_Embarcados/Aula_02/02_Intro_L
inux_arqs/Arqs_aula_02$ ls *.gif
1086970.gif
```
10. Liste somente os arquivos que contenham o nome 'cal'.
```bash
drico@drico-VirtualBox:~/Área de Trabalho/Sistemas_Embarcados/Aula_02/02_Intro_L
inux_arqs/Arqs_aula_02$ ls . | grep "cal"
cal_1990.txt
cal_1991.txt
cal_1992.txt
cal_1993.txt
cal_1994.txt
cal_1995.txt
cal_1996.txt
cal_1997.txt
cal_1998.txt
cal_1999.txt
cal_2000.txt
cal_2001.txt
cal_2002.txt
cal_2003.txt
cal_2004.txt
cal_2005.txt
cal_2006.txt
cal_2007.txt
cal_2008.txt
cal_2009.txt
cal_2010.txt
cal_2011.txt
cal_2012.txt
cal_2013.txt
cal_2014.txt
cal_2015.txt
cal_2016.txt
cal_2017.txt
cal_2018.txt
cal_2019.txt
cal_2020.txt
cal.txt
cal_types.txt
```
11. Liste somente os arquivos que contenham o nome 'tux'.
```bash
drico@drico-VirtualBox:~/Área de Trabalho/Sistemas_Embarcados/Aula_02/02_Intro_L
inux_arqs/Arqs_aula_02$ ls . | grep -i "tux"
BusinessTux.png
Tux-in-a-suit.png
tux-linux-professional_0-100520358-orig.png
TUX.png
xanderrun-tux-construction-8454.png
```
12. Liste somente os arquivos que comecem com o nome 'tux'.
```bash
drico@drico-VirtualBox:~/Área de Trabalho/Sistemas_Embarcados/Aula_02/02_Intro_L
inux_arqs/Arqs_aula_02$ ls . | grep -i "^tux"
Tux-in-a-suit.png
tux-linux-professional_0-100520358-orig.png
TUX.png
```
