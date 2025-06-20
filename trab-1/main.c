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
    FILE *saida = fopen("saida.txt", "w");

    char aux[50];
    fscanf(fp3, "%[^\n]", aux);
    fscanf(fp3, "%[\n]", aux);
    
    int flag=0;

    while(!feof(fp3)){
  
        if(flag != 0){

            break;

        }

        int mode=0;
        fscanf(fp3, "%d;", &mode);

        switch (mode){

            case 1:

                int idLivro=0, idLeitor=0, lixo=0;

                fscanf(fp3, "%d;%d;%d\n", &idLeitor, &idLivro, &lixo);
                    
                Celula *livroAux = busca(livros, idLivro);

                Celula *leitorAux = busca(leitores, idLeitor);

                if(leitorAux == NULL){

                    fprintf(saida, "Erro: Leitor com ID %d não encontrado\n", idLeitor);

                } else if(livroAux == NULL){
       
                    fprintf(saida, "Erro: Livro com ID %d não encontrado\n", idLivro);                   

                } else {

                    Lista *aux = retListaLidos(leitorAux);

                    Celula *retBusca = busca(aux, retIdLivroLista(livroAux));

                    if(retBusca == NULL){

                        insereCelula(aux, livroAux);

                        fprintf(saida, "%s leu \"%s\"\n", retLeitorNomeLista(leitorAux), retLivroTituloLista(livroAux));

                    } else {

                        fprintf(saida, "%s já leu \"%s\"\n", retLeitorNomeLista(leitorAux), retLivroTituloLista(livroAux));

                    }

                }
            
                    break;
                
            case 2:

                int idLivro2=0, idLeitor2=0, lixo2=0;

                fscanf(fp3, "%d;%d;%d\n", &idLeitor2, &idLivro2, &lixo2);
                    
                Celula *livroAux2 = busca(livros, idLivro2);

                Celula *leitorAux2 = busca(leitores, idLeitor2);

                if(leitorAux2 == NULL){

                    fprintf(saida, "Erro: Leitor com ID %d não encontrado\n", idLeitor2);

                } else if(livroAux2 == NULL){
       
                    fprintf(saida, "Erro: Livro com ID %d não encontrado\n", idLivro2);


                } else {

                    Lista *aux2 = retListaDesejados(leitorAux2);

                    Celula *retBusca2 = busca(aux2, retIdLivroLista(livroAux2));

                    if(retBusca2 == NULL){

                        insereCelula(aux2, livroAux2);

                        fprintf(saida, "%s deseja ler \"%s\"\n", retLeitorNomeLista(leitorAux2), retLivroTituloLista(livroAux2));

                    } else {

                        fprintf(saida, "%s já deseja ler \"%s\"\n", retLeitorNomeLista(leitorAux2), retLivroTituloLista(livroAux2));

                    }

                }

                break;

            case 3:
                    
                int idLivro3=0, idLeitor3=0, idLeitorDest3=0;

                fscanf(fp3, "%d;%d;%d\n", &idLeitor3, &idLivro3, &idLeitorDest3);
                    
                Celula *livroAux3 = busca(livros, idLivro3);

                Celula *leitorAux3 = busca(leitores, idLeitor3);
                    
                Celula *leitorDest3 = busca(leitores, idLeitorDest3);

                if(leitorAux3 == NULL){

                    fprintf(saida, "Erro: Leitor recomendador com ID %d não encontrado\n", idLeitor3);

                } else if(livroAux3 == NULL){
       
                    fprintf(saida, "Erro: Livro com ID %d não encontrado\n", idLivro);

                } else if(leitorDest3 == NULL){

                    fprintf(saida, "Erro: Leitor destinatário com ID %d não encontrado\n", idLeitorDest3);

                } else {

                    Lista *aux3 = retListaRecomendados(leitorDest3);

                    Lista *lidos3 = retListaLidos(leitorDest3);

                    Lista *desejados3 = retListaDesejados(leitorDest3);

                    Celula *retBusca3 = busca(lidos3, retIdLivroLista(livroAux3));

                    Celula *retbusca33 = busca(desejados3, retIdLivroLista(livroAux3));

                    if(comparaIdsLista(leitorAux3, leitorDest3)){

                        fprintf(saida, "%s não pode recomendar livros para si mesmo\n", retLeitorNomeLista(leitorAux3));

                    } else if(retBusca3 != NULL){

                        fprintf(saida, "%s não precisa da recomendação de \"%s\" pois já leu este livro\n", retLeitorNomeLista(leitorDest3), retLivroTituloLista(livroAux3));

                    } else if(retbusca33 != NULL){

                        fprintf(saida, "%s já deseja ler \"%s\", recomendação desnecessária\n", retLeitorNomeLista(leitorDest3), retLivroTituloLista(livroAux3));

                    } else {

                        insereCelula(aux3, livroAux3);

                        fprintf(saida, "%s recomenda \"%s\" para %s\n", retLeitorNomeLista(leitorAux3), retLivroTituloLista(livroAux3), retLeitorNomeLista(leitorDest3));

                    }

                }

                break;

            case 4:
                    
                int idLivro4=0, idRecebeRec=0, idFazRec=0;

                fscanf(fp3, "%d;%d;%d\n", &idRecebeRec, &idLivro4, &idFazRec);
                    
                Celula *livroAux4 = busca(livros, idLivro4);

                Celula *leitorRecebe = busca(leitores, idRecebeRec);
                    
                Celula *leitorFazRec = busca(leitores, idFazRec);

                if(leitorRecebe == NULL){

                    fprintf(saida, "Erro: Leitor com ID %d não encontrado\n", idRecebeRec);
                
                } else if(leitorFazRec == NULL){

                    fprintf(saida, "Erro: Leitor recomendador com ID %d não encontrado\n", idFazRec);

                } else if(livroAux4 == NULL){
       
                    fprintf(saida, "%s não possui recomendação do livro ID %d feita por %s\n", retLeitorNomeLista(leitorRecebe), idLivro4 ,retLeitorNomeLista(leitorFazRec));

                } else {

                    Lista *auxRec = retListaRecomendados(leitorRecebe);

                    Lista *auxDesejados = retListaDesejados(leitorRecebe);

                    Celula *buscaRet4 = busca(auxRec, retIdLivroLista(livroAux4));

                    if(buscaRet4 != NULL){

                        Celula *temp = retiraLista(auxRec, retLivroTituloLista(livroAux4));

                        insereCelula(auxDesejados, temp);

                        free(temp);

                        fprintf(saida, "%s aceita recomendação \"%s\" de %s\n", retLeitorNomeLista(leitorRecebe), retLivroTituloLista(livroAux4), retLeitorNomeLista(leitorFazRec));

                    } else {

                        fprintf(saida, "%s não possui recomendação do livro ID %d feita por %s\n", retLeitorNomeLista(leitorRecebe), retIdLivroLista(livroAux4),retLeitorNomeLista(leitorFazRec));

                    }

                }

                break;

            case 5:
                    
                int idLivro5=0, idRecebeRec2=0, idFazRec2=0;

                fscanf(fp3, "%d;%d;%d\n", &idRecebeRec2, &idLivro5, &idFazRec2);
        
                Celula *livroAux5 = busca(livros, idLivro5);

                Celula *leitorRecebe2 = busca(leitores, idRecebeRec2);
                    
                Celula *leitorFazRec2 = busca(leitores, idFazRec2);

                if(leitorRecebe2 == NULL){

                    fprintf(saida, "Erro: Leitor com ID %d não encontrado\n", idRecebeRec2);
                
                } else if(leitorFazRec2 == NULL){

                    fprintf(saida, "Erro: Leitor recomendador com ID %d não encontrado\n", idFazRec2);

                } else if(livroAux5 == NULL){
       
                    fprintf(saida, "%s não possui recomendação do livro ID %d feita por %s\n", retLeitorNomeLista(leitorRecebe2), idLivro5 ,retLeitorNomeLista(leitorFazRec2));

                } else if(leitorRecebe2 != NULL && livroAux5 != NULL && leitorFazRec2 != NULL){

                    Lista *auxRec = retListaRecomendados(leitorRecebe2);

                    Celula *buscaRet5 = busca(auxRec, retIdLivroLista(livroAux5));

                    if(buscaRet5 != NULL){

                        Celula *livroRet = retiraLista(auxRec, retLivroTituloLista(livroAux5));

                        free(livroRet);

                        fprintf(saida, "%s rejeita recomendação \"%s\" de %s\n", retLeitorNomeLista(leitorRecebe2), retLivroTituloLista(livroAux5), retLeitorNomeLista(leitorFazRec2));

                    } else {

                        fprintf(saida, "%s não possui recomendação do livro ID %d feita por %s\n", retLeitorNomeLista(leitorRecebe2), retIdLivroLista(livroAux5), retLeitorNomeLista(leitorFazRec2));

                    }

                }

                break;

            case 6:
                    
                int nada2=0, idLeitorLivroComum1=0, idLeitorLivroComum2=0;

                fscanf(fp3, "%d;%d;%d\n", &idLeitorLivroComum1, &nada2, &idLeitorLivroComum2);
            
                Celula *leitorLivroComum1 = busca(leitores, idLeitorLivroComum1);
                    
                Celula *leitorLivroComum2 = busca(leitores, idLeitorLivroComum2);

                if(leitorLivroComum1 == NULL){

                    fprintf(saida, "Erro: Leitor com ID %d não encontrado\n", idLeitorLivroComum1);

                } else if(leitorLivroComum2 == NULL){

                    fprintf(saida, "Erro: Leitor com ID %d não encontrado\n", idLeitorLivroComum2);
        
                } else {

                    verificaLivrosEmComum(leitorLivroComum1, leitorLivroComum2, saida);

                }

                break;

            case 7:
                    
                int nada=0, idAfinidade1=0, idAfinidade2=0;

                fscanf(fp3, "%d;%d;%d\n", &idAfinidade1, &nada, &idAfinidade2);

                Celula *leitorAfinidade1 = busca(leitores, idAfinidade1);
                    
                Celula *leitorAfinidade2 = busca(leitores, idAfinidade2);

                if(leitorAfinidade1 == NULL){

                    fprintf(saida, "Erro: Leitor com ID %d não encontrado\n", idAfinidade1);

                } else if(leitorAfinidade2 == NULL){

                    fprintf(saida, "Erro: Leitor com ID %d não encontrado\n", idAfinidade2);

                } else {

                    verificaAfinidadeLista(leitorAfinidade1, leitorAfinidade2, saida);

                }

            break;

            case 8:
                    
                imprimeBookED(leitores, saida);
                flag++;

                break;
                
            default:

                char vazio[50];

                fscanf(fp3, "%s", vazio);

                fprintf(saida, "Erro: Comando %d não reconhecido\n", mode);  

                break;

        }

    }

    fclose(fp3);
    fclose(saida);

    liberaLista(leitores);
    liberaLista(livros);

    return 0;

}