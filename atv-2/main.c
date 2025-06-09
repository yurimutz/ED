#include "super.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void menu(){

    printf("-------------------------------\n");
    printf("1-Cadastra filial\n");
    printf("2-Adiciona um item a uma filial\n");
    printf("3-Infos atuais do supermercado\n");
    printf("4-Sair\n");
    printf("-------------------------------\n");

}

int main(){

    int flag=0;
    Super *s = criaSuper();

    while(flag != 1){

        menu();

        int mode=0;
        scanf("%d", &mode);
        scanf("%*c");

        switch (mode)
        {
        case 1:
            addFilial(s);
            break;

        case 2:
            char nome[50];
            printf("Digite o nome da filial que recebera o item:\n");
            scanf(" %[^\n]", nome);
            scanf("%*c");

            addItemNaFilial(s, nome);
            break;

        case 3:
            printaSuper(s);
            break;

        case 4:
            liberaSuper(s);
            flag=1;
            break;
        
        default:
            printf("Digite uma operacao valida!\n");
            break;
        }

    }

    return 0;

}