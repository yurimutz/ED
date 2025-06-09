#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"

void printMenu(){

    printf("Escolha a operacao:\n");
    printf("1 - Adiciona produto\n");
    printf("2 - Retira produto\n");
    printf("3 - imprime lista\n");
    printf("4 - Sair\n");

}

int main(){

    Lista *l = criaLista();

    int flag = 0;

    while(flag != 1){

        printMenu();

        int mode;
        scanf("%d", &mode);
        scanf("%*c");

        switch(mode){

            case 1:

                Produto *p = leProduto();

                insereLista(l, p);

                break;

            case 2:

                int codigoAux=0;

                printf("Digite o codigo do produto a ser retirado:\n");
                scanf("%d", &codigoAux);
                scanf("%*c");

                retiraLista(l, codigoAux);

                break;

            case 3:

                imprimeLista(l);

                break;

            case 4:

                liberaLista(l); 
                flag = 1;

                break;

        }

    }

    return 0;

}