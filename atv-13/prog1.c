#include "abbgen.h"
#include "aluno.h"

int main(){

    Arv *arvore = abb_criaVazia();

    FILE *fp = fopen("entrada.txt", "r");

    while(!feof(fp)){

        Aluno *aluno = LeAluno(fp);

        arvore = abb_insere (arvore, aluno, comparaMat);

    }
    
    fclose(fp);

    FILE *saida = fopen("saida.txt", "w");

    abb_imprime (arvore, imprimeAluno, saida);

    fclose(saida);

    abb_libera (arvore, DestroiAluno);

    return 0;

}
