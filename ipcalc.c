#include "lib/functions.h"      //todas as funcoes estao implementadas aqui

int main(int argc, char *argv[]){

	if(argc <= 1 || argc > 4){
		printf("Exemplo de uso: ipcalc 172.16.0.0/24 -s 50\n");
		return -1;
	}

	ip = argv[1];               //guardando o ip em uma variavel global dentro da functions.h

	allocateMemory();           //alocando toda a memoria necessaria

	if(ipIsValid()){            //verificando se o IP eh valido. Se for, todas as operacoes serao feitas e o resultado imprimido
		print();                //imprimindo o resultado
	}

    deallocate();     //desalocando toda a memoria usada

	return 0;
}
