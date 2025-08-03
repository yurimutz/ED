#include "arvore.h"
#include "aluno.h"

int main(){


    Aluno *Yuri = CriaAluno(1, "Yuri");
    Aluno *Davi = CriaAluno(2, "Davi");
    Aluno *Pedro = CriaAluno(3, "Pedro");
    Aluno *Carlos = CriaAluno(4, "Carlos");
    Aluno *Roberto = CriaAluno(5, "Roberto");
    Aluno *Jonas = CriaAluno(6, "Jonas");

    Arv* arvore = abb_criaVazia();

    //abb_insere (Arv* a, Aluno *v)
    arvore = abb_insere (arvore , Pedro);
    arvore = abb_insere (arvore , Davi);
    arvore = abb_insere (arvore , Yuri);
    arvore = abb_insere (arvore , Roberto);
    arvore = abb_insere (arvore , Carlos);
    arvore = abb_insere (arvore , Jonas);

    arv_imprime(arvore);

    /*so um filho*/
    // arvore = abb_retira (arvore, 2);
    // printf("\n");
    // arv_imprime(arvore);

    /*dois filhos*/
    // arvore = abb_retira (arvore, 5);
    // printf("\n");
    // arv_imprime(arvore);

    DestroiAluno(Yuri);
    DestroiAluno(Pedro);
    DestroiAluno(Carlos);
    DestroiAluno(Davi);
    DestroiAluno(Jonas);
    DestroiAluno(Roberto);

    abb_libera(arvore);

    return 0;

}