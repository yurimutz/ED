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

        Aluno*aluno = leAluno2(fp);

        hsh_insere(tab, aluno);

    }

    fclose(fp);

    for(int i=1; i <= numAulas; i++){

        char dir[50];
        char ent[50] = "entrada";
        char txt[50] = ".txt";
        sprintf(dir, "%s%d%s", ent, i, txt);

        FILE *fp2 = fopen(dir, "r");

        while(!feof(fp2)){

            Aluno*aluno = leAluno(fp2);

            hsh_insere(tab, aluno);

        }
        
        fclose(fp2);

    }

    Aluno **vet = criarVetordenado(tab);

    int tam = retN(tab);

    imprimeVet(vet, tam);

    liberaHash(tab);

    liberaVet(vet, tam);

    return 0;
 
}