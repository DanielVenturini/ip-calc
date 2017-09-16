#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define TRUE 1
#define FALSE 0

unsigned char *octeto1;             //cada octeto do ip sera guardado em uma variavel diferente
unsigned char *octeto2;
unsigned char *octeto3;
unsigned char *octeto4;

unsigned char *netmask1;            //cada octeto da mascara sera guardada em uma variavel diferente
unsigned char *netmask2;
unsigned char *netmask3;
unsigned char *netmask4;

char *ip;                           //variavel aonde se encontra guardado o IP

char *cidr;                         //variavel aonde se encontra guardado o valor do CIDR

char ultimaPos = 0;                 //necessario para saber qual a posicao do proximo octeto do IP

void deallocate(){                  //funcao para desalocar a memoria

    free(octeto1);
    free(octeto2);
    free(octeto3);
    free(octeto4);

    free(netmask1);
    free(netmask2);
    free(netmask3);
    free(netmask4);

    free(cidr);
}

void allocateMemory(){              //funcao para alocar a memoria

	octeto1 = (char*)(malloc(sizeof(char)));
	octeto2 = (char*)(malloc(sizeof(char)));
	octeto3 = (char*)(malloc(sizeof(char)));
	octeto4 = (char*)(malloc(sizeof(char)));

	*octeto1 = 0;
	*octeto2 = 0;
	*octeto3 = 0;
	*octeto4 = 0;

    netmask1 = (char*) malloc(sizeof(char));
    netmask2 = (char*) malloc(sizeof(char));
    netmask3 = (char*) malloc(sizeof(char));
    netmask4 = (char*) malloc(sizeof(char));

    *netmask1 = 0;
    *netmask2 = 0;
    *netmask3 = 0;
    *netmask4 = 0;

    cidr = (char*)malloc(sizeof(char));

    *cidr = 0;
}

void print(){                       //funcao que imprime o resultado

    unsigned char notmask1 = ~*netmask1;    //pegando a negacao da mascara, necessaria para descobrir o ultimo enderedo da rede
    unsigned char notmask2 = ~*netmask2;    //ultimo endereco: IP or (not MASCARA)
    unsigned char notmask3 = ~*netmask3;
    unsigned char notmask4 = ~*netmask4;

    long int hosts = pow(2, 32-*cidr);      //numero maximo de hosts: 2 elevado a 32-CIDR

    printf("Address: %d.%d.%d.%d\n", *octeto1, *octeto2, *octeto3, *octeto4);
    printf("Netmask: %d.%d.%d.%d\n", *netmask1, *netmask2, *netmask3, *netmask4);
    printf("Wildcard: %d.%d.%d.%d\n", 255-*netmask1, 255-*netmask2, 255-*netmask3, 255-*netmask4);
    printf("=>\n");
    printf("HostMin: %d.%d.%d.%d\n", *octeto1&*netmask1, *octeto2&*netmask2, *octeto3&*netmask3, (*octeto4&*netmask4)+1);
    printf("HostMax: %d.%d.%d.%d\n", *octeto1|notmask1, *octeto2|notmask2, *octeto3|notmask3, (*octeto4|notmask4)-1);
    printf("Broadcast: %d.%d.%d.%d\n", *octeto1|notmask1, *octeto2|notmask2, *octeto3|notmask3, *octeto4|notmask4);
    printf("Hosts/Net: %ld\n", hosts-2);

}

int isValid(char *octeto){

	char i, mult, j = 0;
	char oc[3] = {'0','0','0'};

	for(i = ultimaPos, mult = 1; i < ultimaPos+3 ; i ++, mult *= 10){   //o for vai ate 3 porque o octeto tem no maximo tres digitos
		if(ip[i] == '.' && i < ultimaPos+1){    //se a dada posicao for um . e o i for menor do que 1
			return FALSE;                       //quer dizer que o IP esta faltando um octeto ou
		}                                       //tem um . a mais: 12.12..32 ou 12..13.65.43

		if(ip[i] == '.'){   //se for um ponto entao chegou ao fim do octeto
            break;
        }

		if(ip[i] == '/' && i > 6){  //se a dada posicao for uma / entao quer dizer que acabou o IP
            *octeto = (int) atoi(oc);//mas tem que verificar se o i eh maior do que 6, pois se nao, esta faltando um octeto.
            ultimaPos = i+1;        //pois o menor ip, em numero de digitos, seria por exemplo: 4.2.5.1/12.
			return TRUE;
		}

        oc[0] = oc[1];      //o valor do octeto esta sendo guardado no vetor oc, pois pegamos uma posicao por vez, e para usar
        oc[1] = oc[2];      //o atoi tem que ser um vetor. Entao desloca para frente tudo o que ja tem para poder inserir mais um
                            //digito do octeto.
		oc[2] = ip[i];      //adicionando o digito do octeto.
	}

	if(ip[i] != '.' && ip[i] != '/'){   //se o octeto tiver um digito no lugar do ., por exemplo: 12.12.3232.32, entao aqui
		return FALSE;                   //eh verificado isso
	}

    if((*octeto = (int) atoi(oc)) > 255){   //se o valor do octeto for maior do que 255, entao retorna falso
        return FALSE;
    }

	ultimaPos = i+1;        //atualiza a ultimaPos com i+1, pois o i esta "apontando" para o ponto. Entao fazendo
                            //i+1 faz com que o ultimaPos esteja com a posicao do comeco do proximo octeto
	return TRUE;
}

int address(){                  //funcao que verifica se o IP e valido octeto por octeto

	if(!isValid(octeto1)){
		return FALSE;
	}

	if(!isValid(octeto2)){
		return FALSE;
	}

	if(!isValid(octeto3)){
		return FALSE;
	}

	if(!isValid(octeto4)){
		return FALSE;
	}

	return TRUE;
}

int netmaskCIDR(){
    char oc[2] = {'0','0'};     //somente aqui o CIDR eh descoberto de acordo com o resto do ip passado no parametro
    oc[0] = ip[ultimaPos];
    oc[1] = ip[ultimaPos+1];
    int cc = atoi(oc);
    *cidr = cc;
    return cc;
}

int netmask(int cc){                  //funcao que descobre o valor da mascara de acordo com o CIDR

    if(cc == -1){                       //se cc for passado como -1, entao nao foi descoberto o valor do CIDR
        cc = netmaskCIDR();             //se nao for -1, entao eh porque o novo valor do CIDR esta em cc.
        if(cc > 32 || cc < 0){                //se o CIDR for maior que 32 entao nao eh valido
            return FALSE;
        }
    }

    int elevado = 7;            //para calcular algum octeto da mascara, começa elevando dois a 7

    if(*cidr > 8){
        *netmask1 = 255;
    } else {
        *netmask1 = 0;
        while(cc > 0){
            *netmask1 += (pow(2, elevado--));
            cc -= 1;
        }
    }

    if(*cidr > 16){
        *netmask2 = 255;
    } else {
        *netmask2 = 0;
        while(cc > 8){
            *netmask2 += (pow(2.0, elevado--));
            cc -= 1;
        }
    }

    if(*cidr > 24){
        *netmask3 = 255;
    } else {
        *netmask3 = 0;
        while(cc > 16){
            *netmask3 += (pow(2.0, elevado--));
            cc -= 1;
        }
    }

    while(cc > 24){
            *netmask4 += (pow(2.0, elevado--));
            cc -= 1;
        }

    return TRUE;
}

int ipIsValid(){                    //funcao que verifica se o IP e a mascara sao validas

    if(!address()){
        printf("Illegal value for ADDRESS (%s).\n", ip);
        return FALSE;
    }

    if(!netmask(-1)){
        printf("Illegal value for NETMASK (%d).\n", *cidr);
        return FALSE;
    }

    return TRUE;
}

void printSubRede(){                       //funcao que imprime o resultado

    unsigned char notmask1 = ~*netmask1;    //pegando a negacao da mascara, necessaria para descobrir o ultimo enderedo da rede
    unsigned char notmask2 = ~*netmask2;    //ultimo endereco: IP or (not MASCARA)
    unsigned char notmask3 = ~*netmask3;
    unsigned char notmask4 = ~*netmask4;

    long int hosts = pow(2, 32-*cidr);      //numero maximo de hosts: 2 elevado a 32-CIDR

    printf("Netmask: %d.%d.%d.%d\n", *netmask1, *netmask2, *netmask3, *netmask4);
    printf("HostMin: %d.%d.%d.%d\n", *octeto1&*netmask1, *octeto2&*netmask2, *octeto3&*netmask3, (*octeto4&*netmask4)+1);
    printf("HostMax: %d.%d.%d.%d\n", *octeto1|notmask1, *octeto2|notmask2, *octeto3|notmask3, *octeto4|notmask4-1);
    printf("Broadcast: %d.%d.%d.%d\n", *octeto1|notmask1, *octeto2|notmask2, *octeto3|notmask3, *octeto4|notmask4);
    printf("Hosts/Net: %ld\n", hosts-2);

}

void sub_rede(int size){

    size += 2;                          //se queremos 'size' ips, entao nao consideramos o ip de origem nem o de broadcast
                                        //entao somamos 2 para garantir que, tirando esses dois ips, teremos a quantidade certa

    printf("\n1. Requested size: %d.\n", size-2);

    int i;
    for(i = 0; pow(2, i) < size; i ++); //descobre a quantidade minima para a quantidade de IP desejada.

    *cidr = 32-i;                       //atualiza o cidr para a nova quantidade
    netmask(*cidr);                     //recalcula a mascara

    printSubRede();                     //somente printar o resultado
}
