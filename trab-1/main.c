// Feito dia 09/06/2025
// Yuri Tressmann Mutz
// Todos os direitos reservados

#include "leitor.h"
#include "livro.h"
#include "recomendacao.h"
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

                    Lista *listaAuxDesejados2 = retListaDesejados(leitorAux2);

                    Celula *retBusca2 = busca(listaAuxDesejados2, retIdLivroLista(livroAux2));

                    if(retBusca2 == NULL){

                        insereCelula(listaAuxDesejados2, livroAux2);

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

                Celula *leitorFazRec3 = busca(leitores, idLeitor3);
                    
                Celula *leitorDest3 = busca(leitores, idLeitorDest3);

                if(leitorFazRec3 == NULL){

                    fprintf(saida, "Erro: Leitor recomendador com ID %d não encontrado\n", idLeitor3);

                } else if(livroAux3 == NULL){
       
                    fprintf(saida, "Erro: Livro com ID %d não encontrado\n", idLivro);

                } else if(leitorDest3 == NULL){

                    fprintf(saida, "Erro: Leitor destinatário com ID %d não encontrado\n", idLeitorDest3);

                } else {

                    Lista *auxRec3 = retListaRecomendados(leitorDest3);

                    Lista *lidos3 = retListaLidos(leitorDest3);

                    Lista *desejados3 = retListaDesejados(leitorDest3);

                    Lista *recProd3 = retListaRecProd(leitorDest3); //novo

                    Celula *retBusca3 = busca(lidos3, retIdLivroLista(livroAux3));

                    Celula *retbusca33 = busca(desejados3, retIdLivroLista(livroAux3));

                    if(comparaIdsLista(leitorFazRec3, leitorDest3)){

                        fprintf(saida, "%s não pode recomendar livros para si mesmo\n", retLeitorNomeLista(leitorFazRec3));

                    } else if(retBusca3 != NULL){

                        fprintf(saida, "%s não precisa da recomendação de \"%s\" pois já leu este livro\n", retLeitorNomeLista(leitorDest3), retLivroTituloLista(livroAux3));

                    } else if(retbusca33 != NULL){

                        fprintf(saida, "%s já deseja ler \"%s\", recomendação desnecessária\n", retLeitorNomeLista(leitorDest3), retLivroTituloLista(livroAux3));

                    } else {

                        Rec *recAux = criaRec(retProdLista(livroAux3), retProdLista(leitorFazRec3)); //novo

                        insereLista(recProd3, recAux, 2); //novo

                        insereCelula(auxRec3, livroAux3);

                        fprintf(saida, "%s recomenda \"%s\" para %s\n", retLeitorNomeLista(leitorFazRec3), retLivroTituloLista(livroAux3), retLeitorNomeLista(leitorDest3));

                    }

                }

                break;

            case 4:
                    
                int idLivro4=0, idRecebeRec=0, idFazRec=0;

                fscanf(fp3, "%d;%d;%d\n", &idRecebeRec, &idLivro4, &idFazRec);
                    
                Celula *livroAux4 = busca(livros, idLivro4);

                Celula *leitorRecebe4 = busca(leitores, idRecebeRec);
                    
                Celula *leitorFazRec4 = busca(leitores, idFazRec);
                

                if(leitorRecebe4 == NULL){

                    fprintf(saida, "Erro: Leitor com ID %d não encontrado\n", idRecebeRec);
                
                } else if(leitorFazRec4 == NULL){

                    fprintf(saida, "Erro: Leitor recomendador com ID %d não encontrado\n", idFazRec);

                } else if(livroAux4 == NULL){

                    fprintf(saida, "%s não possui recomendação do livro ID %d feita por %s\n", retLeitorNomeLista(leitorRecebe4), idLivro4 ,retLeitorNomeLista(leitorFazRec4));

                } else {

                    Lista *auxRec4 = retListaRecomendados(leitorRecebe4);

                    Lista *recProd4 = retListaRecProd(leitorRecebe4); //novo

                    Lista *auxDesejados4 = retListaDesejados(leitorRecebe4);

                    if(existeRec(recProd4, idLivro4, idFazRec)){

                        Celula *ret4 = retiraLista(auxRec4, retLivroTituloLista(livroAux4));

                        Celula *ret4Teste = retiraLista(recProd4, retLivroTituloLista(livroAux4)); //novo

                        insereCelula(auxDesejados4, ret4);

                        free(ret4);

                        fprintf(saida, "%s aceita recomendação \"%s\" de %s\n", retLeitorNomeLista(leitorRecebe4), retLivroTituloLista(livroAux4), retLeitorNomeLista(leitorFazRec4));

                    } else {

                        fprintf(saida, "%s não possui recomendação do livro ID %d feita por %s\n", retLeitorNomeLista(leitorRecebe4), retIdLivroLista(livroAux4),retLeitorNomeLista(leitorFazRec4));

                    }

                }

                break;

            case 5:
                    
                int idLivro5=0, idRecebeRec2=0, idFazRec2=0;

                fscanf(fp3, "%d;%d;%d\n", &idRecebeRec2, &idLivro5, &idFazRec2);
        
                Celula *livroAux5 = busca(livros, idLivro5);

                Celula *leitorRecebe5 = busca(leitores, idRecebeRec2);
                    
                Celula *leitorFazRec5 = busca(leitores, idFazRec2);

                if(leitorRecebe5 == NULL){

                    fprintf(saida, "Erro: Leitor com ID %d não encontrado\n", idRecebeRec2);
                
                } else if(leitorFazRec5 == NULL){

                    fprintf(saida, "Erro: Leitor recomendador com ID %d não encontrado\n", idFazRec2);

                } else if(livroAux5 == NULL){
       
                    fprintf(saida, "%s não possui recomendação do livro ID %d feita por %s\n", retLeitorNomeLista(leitorRecebe5), idLivro5 ,retLeitorNomeLista(leitorFazRec5));

                } else if(leitorRecebe5 != NULL && livroAux5 != NULL && leitorFazRec5 != NULL){

                    Lista *auxRec5 = retListaRecomendados(leitorRecebe5);

                    Lista *recProd5 = retListaRecProd(leitorRecebe5); //novo

                    if(existeRec(recProd5, idLivro5, idFazRec2)){

                        Celula *livroRet = retiraLista(auxRec5, retLivroTituloLista(livroAux5));

                        Celula *livroRetTeste = retiraLista(recProd5, retLivroTituloLista(livroAux5));

                        free(livroRet);

                        fprintf(saida, "%s rejeita recomendação \"%s\" de %s\n", retLeitorNomeLista(leitorRecebe5), retLivroTituloLista(livroAux5), retLeitorNomeLista(leitorFazRec5));

                    } else {

                        fprintf(saida, "%s não possui recomendação do livro ID %d feita por %s\n", retLeitorNomeLista(leitorRecebe5), retIdLivroLista(livroAux5), retLeitorNomeLista(leitorFazRec5));

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
                    
                char vazio8[50];

                fscanf(fp3, "%[^\n]", vazio8);

                imprimeBookED(leitores, saida);

                break;
                
            default:

                char vazio[50];

                fscanf(fp3, "%[^\n]", vazio);

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