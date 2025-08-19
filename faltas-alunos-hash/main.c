#include "aluno.h"
#include "hash.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){

    int numAulas=0;
    char lixo;

    Hash *tab = hsh_cria();

    FILE *fp = fopen("entrada.txt", "r");

    fscanf(fp, "%c %d", &lixo, &numAulas);
    fscanf(fp, "%*c");

    while(!feof(fp)){

        Aluno*aluno = leAluno(fp);
        //imprimeAluno(aluno);

        hsh_insere(tab, aluno);

    }

    return 0;
 
}