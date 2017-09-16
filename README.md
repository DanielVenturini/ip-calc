========================================
|        Redes de Computadores 2        |
========================================

implementacao de uma calculadora de IP, que dado um IP, descobre:
  endereço de rede;
  mascara de rede;
  complemento da mascara;
  primeiro endereço da rede;
  ultimo endereço da rede;
  endereço de broadcast; e
  numero maximo de hosts.

Implementado totalmente em C usando o Code::Blocks, foi criado uma biblioteca em lib/functions.h para armazenar as funções. Praticamente todas as variaveis sao do tipo char, pois como algumas operacoes sao binarias, fica mais facil de realizar. Tambem porque os octetos do IP e da mascara são todos de 8 bits cada e variaveis do tipo char tem 8 bits, assim deixando o programa mais logico e com mais economia de memória do computador.

Para calcular quantidade de subrede, usa-se o parametro -s 'quantidade', por exemplo: ./ipcalc 192.168.3.3/25 -s 1023. Então é imprimido todas as informações referentes a quantidade e os ips para tal.

compile:

    gcc ipcalc.c -o ipcalc -lm

run:

    ./ipcalc 192.168.3.3/25
