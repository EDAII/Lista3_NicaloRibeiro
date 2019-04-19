#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define GNUPLOT "gnuplot -persist"

#define linhasArquivo 5562

//Quick Sort normal e com Bucket sort -- cod_ts, cod_ibge , populacao, região, estado
//Heap sort normal e com bucket sort --  ||         ||       ||          ||     ||
//Gerar grafico de tempos com gnu plot
void quickSort(int inicio, int fim, int tipo);
void heapSort(int tamanho, int tipo);
void quickSortOptions();
void heapSortOptions();
void verificaEcopia();
void gravaTempos();
void gnuPlot();
void mostrarRegOrdenado();
void gravarArquivoOrdenado();
void menu();

typedef struct registrosCidades
{
    int cod_tse, cod_ibge, populacao;
    char uf[3],localidade[30],regiao[15],microregiao[40];
    
}Cidades;

Cidades *dadosCidades = NULL;
Cidades *dadosCidadesOrdenados = NULL;

double *resultadoQuickSort = NULL, *resultadoHeapSort = NULL;
int qtdQuickSort = 0,qtdHeapSort = 0;

int main(){
    dadosCidades = malloc(sizeof(Cidades) * linhasArquivo);
    resultadoQuickSort = (double *)malloc(qtdQuickSort * sizeof(double));
    resultadoHeapSort = (double *)malloc(qtdHeapSort * sizeof(double));

    FILE *arq;
    arq = fopen("cadastrocm.txt", "r");
    if(arq == NULL){
        printf("Falha na abertura do aquivo.\n");
        exit(1);
    }else{
        printf("Arquivo Aberto.\n");
    }

    for(int c = 0; c<linhasArquivo && !feof(arq); c++){
        fscanf(arq,"\n%d,%d,%[^,],%[^,],%[^,],%[^,],%d",&dadosCidades[c].cod_tse,&dadosCidades[c].cod_ibge,
        dadosCidades[c].uf,dadosCidades[c].localidade,dadosCidades[c].regiao,dadosCidades[c].microregiao,
        &dadosCidades[c].populacao);   
    }

    menu();

    gravaTempos();
    gnuPlot();
    fclose(arq);
    free(dadosCidades);
    free(dadosCidadesOrdenados);
    free(resultadoHeapSort);
    free(resultadoQuickSort);

    return 0;

}

void menu(){
    int opcao;

    do{
        printf("\n|\t\tMENU\n");
        printf("|\t\t----\n");
        printf("|Escolha uma das opcões :\n");
        printf("|1-Realizar QICK SORT.\n");
        printf("|2-Realizar HEAP SORT.\n");
        printf("|3-Visualizar dados ordenados.\n");
        printf("|4-Gravar arquivo com os dados ordenados.\n"); 
        printf("|0-Sair\n");
        scanf("%d", &opcao);

        switch (opcao){
            case 1:
            system("clear");
            quickSortOptions();          
            break;
        
            case 2:
            system("clear");
            heapSortOptions();
            break;

            case 3:
            system("clear");
            mostrarRegOrdenado();
            break;

            case 4:
            gravarArquivoOrdenado();
            break;

            case 0:
            return;
            break;

            default:
            printf("Digite uma opção válida.\n");
            
        }

    }while(opcao != 0);
    
    return;
}

void quickSort(int inicio, int fim, int tipo){
    
    int i, j, meio;
    Cidades aux;
    Cidades pivo;
   
    i = inicio;
    j = fim;
   
    meio = ((i + j) / 2);
    pivo = dadosCidadesOrdenados[meio];    

    if(tipo == 1){
        
        do{
            while (dadosCidadesOrdenados[i].cod_tse < pivo.cod_tse){
                i++;
            }
            while (dadosCidadesOrdenados[j].cod_tse > pivo.cod_tse){
                j--;
            } 
      
            if(i <= j){
                aux = dadosCidadesOrdenados[i];
                dadosCidadesOrdenados[i] = dadosCidadesOrdenados[j];
                dadosCidadesOrdenados[j] = aux;
                i++;
                j--;
            }
        }while(j >= i);
   }

    else if(tipo == 2){
        do{
            while (dadosCidadesOrdenados[i].cod_ibge < pivo.cod_ibge){
                i++;
            }
            while (dadosCidadesOrdenados[j].cod_ibge > pivo.cod_ibge){
                j--;
            }
      
            if(i <= j){
                aux = dadosCidadesOrdenados[i];
                dadosCidadesOrdenados[i] = dadosCidadesOrdenados[j];
                dadosCidadesOrdenados[j] = aux;
                i++;
                j--;
            }
        }while(j >= i);
   }

   else if(tipo == 3){
       do{
            while (dadosCidadesOrdenados[i].populacao < pivo.populacao){
                i++;
            }
            while (dadosCidadesOrdenados[j].populacao > pivo.populacao){
                j--;
            }
      
            if(i <= j){
                aux = dadosCidadesOrdenados[i];
                dadosCidadesOrdenados[i] = dadosCidadesOrdenados[j];
                dadosCidadesOrdenados[j] = aux;
                i++;
                j--;
            }
        }while(j >= i);
   }

    if(inicio < j){
        quickSort(inicio, j, tipo);
    }
    if(i < fim){
        quickSort(i, fim, tipo);   
    }
}

void quickSortOptions(){
    verificaEcopia();
    clock_t time;
    double tempoQuicksort;
    int tipo;
      

    qtdQuickSort++;
    resultadoQuickSort = (double*)realloc(resultadoQuickSort, qtdQuickSort * sizeof(double));

    printf("Digite o parametro da ordenação (QUICK SORT): \n");
    printf("1- Código TSE\n");
    printf("2- Código IBGE\n");
    printf("3- Por POPULAÇÃO\n");
    scanf("%d", &tipo);  
    time = clock();
    quickSort(0,linhasArquivo - 1,tipo);
    time = clock() - time;
    tempoQuicksort = ((double)time)/CLOCKS_PER_SEC;
    printf("Ordenação efetuada\n");

    resultadoQuickSort[qtdQuickSort - 1] = tempoQuicksort;
    return;
}

void heapSort(int tamanho, int tipo){

    verificaEcopia();

    int i = tamanho / 2, pai, filho;
    Cidades aux;
    while(1) {
        if (i > 0) {
            i--;
            aux = dadosCidadesOrdenados[i];
        }else{
            tamanho--;
            if (tamanho == 0) return;
            aux = dadosCidadesOrdenados[tamanho];
            dadosCidadesOrdenados[tamanho] = dadosCidadesOrdenados[0];
        }
        pai = i;
        filho = i * 2 + 1;
        if(tipo == 1){
        while (filho < tamanho) {
            if ((filho + 1 < tamanho)  &&  (dadosCidadesOrdenados[filho + 1].cod_tse > dadosCidadesOrdenados[filho].cod_tse)){
                filho++;
            }
            if (dadosCidadesOrdenados[filho].cod_tse > aux.cod_tse) {
                dadosCidadesOrdenados[pai] = dadosCidadesOrdenados[filho];
                pai = filho;
                filho = pai * 2 + 1;
            }else{
                break;
            }
        }
        }
        if(tipo == 2){
             while (filho < tamanho) {
            if ((filho + 1 < tamanho)  &&  (dadosCidadesOrdenados[filho + 1].cod_ibge > dadosCidadesOrdenados[filho].cod_ibge)){
                filho++;
            }
            if (dadosCidadesOrdenados[filho].cod_ibge > aux.cod_ibge) {
                dadosCidadesOrdenados[pai] = dadosCidadesOrdenados[filho];
                pai = filho;
                filho = pai * 2 + 1;
            }else{
                break;
            }
        }

        }

        if(tipo == 3){
             while (filho < tamanho) {
            if ((filho + 1 < tamanho)  &&  (dadosCidadesOrdenados[filho + 1].populacao > dadosCidadesOrdenados[filho].populacao)){
                filho++;
            }
            if (dadosCidadesOrdenados[filho].populacao > aux.populacao) {
                dadosCidadesOrdenados[pai] = dadosCidadesOrdenados[filho];
                pai = filho;
                filho = pai * 2 + 1;
            }else{
                break;
            }
        }

        }
        dadosCidadesOrdenados[pai] = aux;
    }
    return;
}

void heapSortOptions(){
    
    clock_t time;
    double tempoHeapsort;
    int tipo;

    qtdHeapSort++;
    resultadoHeapSort = (double*)realloc(resultadoHeapSort, qtdHeapSort * sizeof(double));

    printf("Digite o parametro da ordenação (HEAP SORT): \n");
    printf("1- Código TSE\n");
    printf("2- Código IBGE\n");
    printf("3- Por POPULAÇÃO\n");
    scanf("%d", &tipo);  
    time = clock();
    heapSort(linhasArquivo,tipo);
    time = clock() - time;
    tempoHeapsort = ((double)time)/CLOCKS_PER_SEC;
    printf("Ordenação efetuada\n");

    resultadoHeapSort[qtdHeapSort - 1] = tempoHeapsort;

    return;

}

void verificaEcopia(){
    if(dadosCidadesOrdenados == NULL){
        dadosCidadesOrdenados = malloc(sizeof(Cidades) * linhasArquivo);
    }else if(dadosCidadesOrdenados != NULL){
        free(dadosCidadesOrdenados);
        dadosCidadesOrdenados = malloc(sizeof(Cidades) * linhasArquivo);
    }

    for(int i = 0; i < linhasArquivo; i++){
        dadosCidadesOrdenados[i] = dadosCidades[i];
    }
    return;
}

void gravaTempos(){

    if(qtdQuickSort != 0){
        FILE *arqT;
   
        arqT = fopen("tempoQuick.txt", "w");
        fprintf ( arqT,"# x \t f(x) \n" );

        for(int i = 0; i < qtdQuickSort; i++){
            fprintf(arqT, "%.7f \t %d \n",resultadoQuickSort[i],i);
    
        }
        fclose(arqT);
    }
    if(qtdHeapSort != 0){
        FILE *arqH;

        arqH = fopen("tempoHeap.txt", "w");
        fprintf ( arqH,"# x \t f(x) \n" );
        for(int i = 0; i < qtdHeapSort; i++){
            fprintf(arqH, "%.7f \t %d \n",resultadoHeapSort[i],i);
        }
        fclose(arqH);
    }
}

void gnuPlot(){

    FILE *gp;
    gp = popen(GNUPLOT, "w");
    if (gp == NULL) {
        printf("Erro ao abrir pipe para o GNU plot.\n"
            "Instale com 'sudo apt-get install gnuplot'\n");
        exit(0);
    }
    fprintf(gp, "plot 'tempoQuick.txt'\n");
    fprintf(gp, "rep 'tempoHeap.txt'\n");
    fclose(gp);

}
void mostrarRegOrdenado(){

    int voltar = 1;
    do{
        system("clear");

        if(dadosCidadesOrdenados == NULL){
            printf("Nenhuma ordenação foi feita ainda.\n\n");
            return;
        }

        for(int i = 0; i < linhasArquivo; i++){
            printf("%d,%d,%s,%s,%s,%s,%d\n",dadosCidadesOrdenados[i].cod_tse, dadosCidadesOrdenados[i].cod_ibge,
             dadosCidadesOrdenados[i].uf,dadosCidadesOrdenados[i].localidade,dadosCidadesOrdenados[i].regiao,
             dadosCidadesOrdenados[i].microregiao,dadosCidadesOrdenados[i].populacao);
        }

        printf("Digite <0> para voltar ao MENU\n");
        scanf("%d", &voltar);
    }while(voltar);

    system("clear");
    return;

}

void gravarArquivoOrdenado(){
    if(dadosCidadesOrdenados == NULL){
        printf("Os registros ainda nao foram ordenados.\n");
        return;
    }
    FILE *arqOrd;
    arqOrd = fopen("cadastrocmOrdenado.txt","w");
    if (arqOrd == NULL){
        printf("Erro na abertura do arquivo.\n");
        exit(1);
    }
    for(int i = 0; i < linhasArquivo; i++){
        fprintf(arqOrd,"%d,%d,%s,%s,%s,%s,%d\n",dadosCidadesOrdenados[i].cod_tse, dadosCidadesOrdenados[i].cod_ibge,
             dadosCidadesOrdenados[i].uf,dadosCidadesOrdenados[i].localidade,dadosCidadesOrdenados[i].regiao,
             dadosCidadesOrdenados[i].microregiao,dadosCidadesOrdenados[i].populacao);
        

    }
    printf("Gravação Concluída.\n");
    fclose(arqOrd);
    return;
}
