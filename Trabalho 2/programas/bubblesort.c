#include <stdio.h>
#include <stdlib.h>

#define MAX 2
#define TRUE 1
#define FALSE 0 

void swap(int *n1, int *n2){
   int troca = *n1;
	 *n1 = *n2;
	 *n2 = troca;
}


int main() {

    int trocas = 0;
    int comparacoes = 0;
    int pos_troca = 0;
    int troca = TRUE;
    int qtd_elementos = MAX-1;

    int array[MAX]; 

    for (int i = 0; i < MAX; i++){
        array[i] = rand() % 100;
    }

    while(troca){
        troca = FALSE;
        for(int i=0; i<qtd_elementos;i++){ 
            comparacoes = comparacoes + 1;
            if( array[i] > array[i+1]){
                swap(&array[i], &array[i+1]);
                troca = TRUE;
                pos_troca = i;
                trocas = trocas + 1;
            }
        }
        qtd_elementos = pos_troca;                
    }

    for (int i = 0; i < MAX; i++){
        printf("%i;\n",array[i]);
    }

}