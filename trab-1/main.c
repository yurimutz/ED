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

    contador=0;

    while(!feof(fp3)){

        if(contador == 0){

            char aux[50];
            fscanf(fp2, "%[^\n]", aux);
            fscanf(fp2, "%[\n]", aux);

            contador++;

        } else {

            int mode=0;
            fscanf(fp3, "%d;", &mode);

            switch (mode){

                case 1:

                    int idLivro=0, idLeitor=0, lixo=0;

                    fscanf(fp3, "%d;%d;%d\n", &idLeitor, &idLivro, &lixo);
                    printf("%d %d %d \n", idLeitor, idLivro, lixo);
                    
                    Celula *livroAux = busca(livros, idLivro);

                    Celula *leitorAux = busca(leitores, idLeitor);

                    Lista *aux = retListaLidos(leitorAux);

                    insereCelula(aux, livroAux);

                    imprimeLista(aux);

                    break;
                
                case 2:
                    
                    break;

                case 3:
                    
                    break;

                case 4:
                    
                    break;

                case 5:
                    
                    break;

                case 6:
                    
                    break;

                case 7:
                    
                    break;

                case 8:
                    
                    break;
                
                default:
                    break;

            }

        }

    }

    fclose(fp3);

    return 0;

}