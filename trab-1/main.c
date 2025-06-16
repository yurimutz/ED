// Feito dia 09/06/2025
// Yuri Tressmann Mutz
// Todos os direitos reservados

#include "leitor.h"
#include "livro.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){

    Lista *leitores = criaLista();
    Lista* livros = criaLista();

    FILE *fp = fopen("leitores.txt", "r");

    int contador=0;

    while(!feof(fp)){

        if(contador == 0){

            char aux[50];
            fscanf(fp, "%[^\n]", aux);
            fscanf(fp, "%[\n]", aux);

            contador++;

        } else {

            Leitor *l = leLeitor(fp);

            //gambiarra
            if(retId(l)>=1 && retId(l)<=30){

                insereLista(leitores, l, LEITOR);

            } else {

                liberaLeitor(l);

            }

        }

    }

    fclose(fp);

    adicionaAfinidades(leitores);

    FILE *fp2 = fopen("livros.txt", "r");

    contador=0;

    while(!feof(fp2)){

        if(contador == 0){

            char aux[50];
            fscanf(fp2, "%[^\n]", aux);
            fscanf(fp2, "%[\n]", aux);

            contador++;

        } else {

            Livro *l = leLivro(fp2);

            insereLista(livros, l, LIVRO);    

        }

    }

    fclose(fp2);

    FILE *fp3 = fopen("comandos.txt", "r");

    char aux[50];
    fscanf(fp3, "%[^\n]", aux);
    fscanf(fp3, "%[\n]", aux);

    while(!feof(fp3)){
  
        int mode=0;
        fscanf(fp3, "%d;", &mode);

        switch (mode){

            case 1:

                int idLivro=0, idLeitor=0, lixo=0;

                fscanf(fp3, "%d;%d;%d\n", &idLeitor, &idLivro, &lixo);
                //printf("%d %d %d \n", idLeitor, idLivro, lixo);
                    
                Celula *livroAux = busca(livros, idLivro);

                Celula *leitorAux = busca(leitores, idLeitor);

                if(leitorAux != NULL && livroAux != NULL){

                    Lista *aux = retListaLidos(leitorAux);

                    insereCelula(aux, livroAux);

                    printf("%s leu \"%s\"\n", retLeitorNomeLista(leitorAux), retLivroTituloLista(livroAux));

                    }
            
                    break;
                
            case 2:

                int idLivro2=0, idLeitor2=0, lixo2=0;

                fscanf(fp3, "%d;%d;%d\n", &idLeitor2, &idLivro2, &lixo2);
                //printf("%d %d %d \n", idLeitor2, idLivro2, lixo2);
                    
                Celula *livroAux2 = busca(livros, idLivro2);

                Celula *leitorAux2 = busca(leitores, idLeitor2);

                if(leitorAux2 != NULL && livroAux2 != NULL){

                    Lista *aux2 = retListaDesejados(leitorAux2);

                    insereCelula(aux2, livroAux2);

                    printf("%s deseja ler \"%s\"\n", retLeitorNomeLista(leitorAux2), retLivroTituloLista(livroAux2));

                }

                break;

            case 3:
                    
                int idLivro3=0, idLeitor3=0, idLeitorDest3=0;

                fscanf(fp3, "%d;%d;%d\n", &idLeitor3, &idLivro3, &idLeitorDest3);
                //printf("%d %d %d \n", idLeitor3, idLivro3, idLeitorDest3);
                    
                Celula *livroAux3 = busca(livros, idLivro3);

                Celula *leitorAux3 = busca(leitores, idLeitor3);
                    
                Celula *leitorDest3 = busca(leitores, idLeitorDest3);

                if(leitorAux3 != NULL && livroAux3 != NULL && leitorDest3 != NULL){

                    Lista *aux3 = retListaRecomendados(leitorDest3);

                    insereCelula(aux3, livroAux3);

                    printf("%s recomenda \"%s\" para %s\n", retLeitorNomeLista(leitorAux3), retLivroTituloLista(livroAux3), retLeitorNomeLista(leitorDest3));

                }

                break;

            case 4:
                    
                int idLivro4=0, idRecebeRec=0, idFazRec=0;

                fscanf(fp3, "%d;%d;%d\n", &idRecebeRec, &idLivro4, &idFazRec);
                //printf("%d %d %d \n", idRecebeRec, idLivro4, idFazRec);
                    
                Celula *livroAux4 = busca(livros, idLivro4);

                Celula *leitorRecebe = busca(leitores, idRecebeRec);
                    
                Celula *leitorFazRec = busca(leitores, idFazRec);

                if(leitorRecebe != NULL && livroAux4 != NULL && leitorFazRec != NULL){

                    Lista *auxRec = retListaRecomendados(leitorRecebe);

                    Lista *auxDesejados = retListaDesejados(leitorRecebe);

                    Celula *temp = retiraLista(auxRec, retLivroTituloLista(livroAux4));

                    insereCelula(auxDesejados, temp);

                    free(temp);

                    printf("%s aceita recomendação \"%s\" de %s\n", retLeitorNomeLista(leitorRecebe), retLivroTituloLista(livroAux4), retLeitorNomeLista(leitorFazRec));

                }

                break;

            case 5:
                    
                int idLivro5=0, idRecebeRec2=0, idFazRec2=0;

                fscanf(fp3, "%d;%d;%d\n", &idRecebeRec2, &idLivro5, &idFazRec2);
                //printf("%d %d %d \n", idRecebeRec2, idLivro5, idFazRec2);
                    
                Celula *livroAux5 = busca(livros, idLivro5);

                Celula *leitorRecebe2 = busca(leitores, idRecebeRec2);
                    
                Celula *leitorFazRec2 = busca(leitores, idFazRec2);

                if(leitorRecebe2 != NULL && livroAux5 != NULL && leitorFazRec2 != NULL){

                    Lista *auxRec = retListaRecomendados(leitorRecebe2);

                    Celula *livroRet = retiraLista(auxRec, retLivroTituloLista(livroAux5));

                    free(livroRet);

                    printf("%s rejeita recomendação \"%s\" de %s\n", retLeitorNomeLista(leitorRecebe2), retLivroTituloLista(livroAux5), retLeitorNomeLista(leitorFazRec2));

                }

                break;

            case 6:
                    
                int nada2=0, idLeitorLivroComum1=0, idLeitorLivroComum2=0;

                fscanf(fp3, "%d;%d;%d\n", &idLeitorLivroComum1, &nada2, &idLeitorLivroComum2);
                //printf("%d %d %d \n", idLeitorLivroComum1, nada, idLeitorLivroComum2);
                    
                Celula *leitorLivroComum1 = busca(leitores, idLeitorLivroComum1);
                    
                Celula *leitorLivroComum2 = busca(leitores, idLeitorLivroComum2);

                if(leitorLivroComum1 != NULL && leitorLivroComum2 != NULL){

                    verificaLivrosEmComum(leitorLivroComum1, leitorLivroComum2);

                }

                break;

            case 7:
                    
                int nada=0, idAfinidade1=0, idAfinidade2=0;

                fscanf(fp3, "%d;%d;%d\n", &idAfinidade1, &nada, &idAfinidade2);
                //printf("%d %d %d \n", idLeitorLivroComum1, nada, idLeitorLivroComum2);

                Celula *leitorAfinidade1 = busca(leitores, idAfinidade1);
                    
                Celula *leitorAfinidade2 = busca(leitores, idAfinidade2);

                if(leitorAfinidade1 != NULL && leitorAfinidade2 != NULL){

                    verificaAfinidadeLista(leitorAfinidade1, leitorAfinidade2);

                }

            break;

            case 8:
                    
                imprimeBookED(leitores);

                break;
                
            default:

                break;

        }

    }

    fclose(fp3);

    liberaLista(leitores);
    liberaLista(livros);

    return 0;

}