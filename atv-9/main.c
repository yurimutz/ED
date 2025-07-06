#include "arvore.h"
#include <stdio.h>

int main(){

    Aluno *Yuri = CriaAluno(1, "Yuri");
    Aluno *Davi = CriaAluno(2, "Davi");
    Aluno *Pedro = CriaAluno(3, "Pedro");
    Aluno *Carlos = CriaAluno(4, "Carlos");
    Aluno *Roberto = CriaAluno(5, "Roberto");
    Aluno *Jonas = CriaAluno(6, "Jonas");

    //Arv* b = arv_criavazia();
    //Arv* c = arv_criavazia();
    Arv *f = arv_cria(Roberto, arv_criavazia(), arv_criavazia());
    Arv *e = arv_cria(Jonas, arv_criavazia(), arv_criavazia());
    Arv *d = arv_cria(Carlos, e, f);
    Arv* b = arv_cria(Davi, arv_criavazia(), arv_criavazia());
    Arv* c = arv_cria(Pedro, arv_criavazia(), d);
    Arv* a = arv_cria(Yuri, b, c);

    //faz impressao de uma arvore
    arv_imprime (a); //ok

    //encontra pai de uma arvore
    Arv *aux = arv_pai(a, 7); //ok

    if(!arv_vazia (aux)){

        imprime2(aux);

    }

    //printa numero de folhas de uma arvore
    printf("Numero de folhas %d\n", folhas(a)); //ok

    //printa num de ocorrencias de uma arvore
    printf("Ocorrencias do aluno %s: %d\n", retNome(Jonas), ocorrencias (a, 6)); //ok

    //printf a altura de uma arvore(numero de setas)
    printf("A altura da arvore e: %d\n", altura(a)); //ok

    DestroiAluno(Yuri);
    DestroiAluno(Pedro);
    DestroiAluno(Carlos);
    DestroiAluno(Davi);
    DestroiAluno(Jonas);
    DestroiAluno(Roberto);

    arv_libera(a);

    return 0;

}