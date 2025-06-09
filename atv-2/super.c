#include "super.h"
#include "filial.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct Super{

    char *nome;
    Filial **fi;
    int qtdAtual;
    int qtdMax;

};

Super *criaSuper(){

    Super *s = malloc(sizeof(Super));
    s->fi = malloc(10 * sizeof(Filial*));
    s->qtdAtual = 0;
    s->qtdMax = 10;

    s->nome = malloc(50 * sizeof(char));
    printf("Digite o nome do supermercado:\n");
    scanf(" %[^\n]", s->nome);
    scanf("%*c");

    return s;

}

void liberaSuper(Super *s){

    for(int i=0; i<s->qtdAtual; i++){

        liberaFilial(s->fi[i]);

    }
    free(s->fi);
    free(s->nome);
    free(s);

}

void addFilial(Super *s){

    Filial *f = leFilial();
    
    if(s->qtdAtual == s->qtdMax){

        s->qtdMax = 2 * s->qtdMax;
        s->fi = realloc(s->fi, s->qtdMax * sizeof(Filial*));

    }

    s->fi[s->qtdAtual] = f;
    s->qtdAtual++;

}

void addItemNaFilial(Super *s, char *nome){

    for(int i=0; i<s->qtdAtual; i++){   
        if(strcmp(retornaNomeFilial(s->fi[i]), nome) == 0){    
            addEstoqueDaFilial(s->fi[i]);
        }
    }

}

float valorEstoqueSuper(Super *s){

    float valor=0;
    for(int i=0; i<s->qtdAtual; i++){
        valor += valorEstoqueFilial(s->fi[i]);
    }

    return valor;

}

void printaSuper(Super *s){

    printf("Nome: %s, Estoque Total: %0.2f\n", s->nome, valorEstoqueSuper(s));
    for(int i=0; i<s->qtdAtual; i++){   
        printaFilial(s->fi[i]);
    }

}
