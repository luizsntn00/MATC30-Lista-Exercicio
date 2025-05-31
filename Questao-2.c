//Atividade - programação 

//Questão 2:

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h> 

// G12xB3xR*C3

// Função que calcula o número total de deslocamentos (shifts)
// necessários para ordenar um vetor usando Insertion Sort.
// Toda e qualquer variável do código deve começar com gcbr.
long long gcbrInsertionSort(int gcbr_arr_count, int* gcbr_arr) {
    long long gcbr_total_shifts = 0; // Variável para armazenar o total de deslocamentos

    // Loop principal do Insertion Sort, começando do segundo elemento (índice 1)
    // pois o primeiro elemento (índice 0) é considerado já "ordenado" em relação a si mesmo.
    for (int gcbr_i = 1; gcbr_i < gcbr_arr_count; gcbr_i++) {
        int gcbr_key = gcbr_arr[gcbr_i]; // Elemento a ser inserido na sub-array ordenada
        int gcbr_j = gcbr_i - 1;         // Índice do último elemento da sub-array ordenada

        // Move os elementos de gcbr_arr[0...gcbr_i-1], que são maiores que gcbr_key,
        // uma posição para a direita de sua posição atual.
        while (gcbr_j >= 0 && gcbr_arr[gcbr_j] > gcbr_key) {
            gcbr_arr[gcbr_j + 1] = gcbr_arr[gcbr_j]; // Desloca o elemento para a direita
            gcbr_total_shifts++;                     // Incrementa o contador de deslocamentos
            gcbr_j--;                                // Move para o próximo elemento à esquerda
        }
        // gcbr_key é inserido na sua posição correta na sub-array ordenada
        gcbr_arr[gcbr_j + 1] = gcbr_key;
    }

    return gcbr_total_shifts;
}

// Funções auxiliares (starter code, renomeadas para seguir a convenção)
void gcbrGenerateRandomArray(int* gcbr_arr, int gcbr_size, int gcbr_min, int gcbr_max) {
    for (int gcbr_i = 0; gcbr_i < gcbr_size; gcbr_i++) {
        gcbr_arr[gcbr_i] = gcbr_min + rand() % (gcbr_max - gcbr_min + 1);
    }
}

void gcbrPrintArray(int* gcbr_arr, int gcbr_size) {
    printf("Array de entrada: [");
    for (int gcbr_i = 0; gcbr_i < gcbr_size; gcbr_i++) {
        printf("%d", gcbr_arr[gcbr_i]);
        if (gcbr_i < gcbr_size - 1) printf(", ");
    }
    printf("]\n");
}

int main() {
    // Inicializa a semente do gerador de números aleatórios
    srand(time(NULL)); 

    int gcbr_t; // Número de casos de teste
    scanf("%d", &gcbr_t);

    // Loop para cada caso de teste
    while (gcbr_t--) {
        int gcbr_n; // Tamanho do vetor
        scanf("%d", &gcbr_n);

        // Aloca dinamicamente o vetor para o caso de teste atual
        // Isso é importante para lidar com n variáveis, até 100000
        int* gcbr_arr = (int*) malloc(gcbr_n * sizeof(int));
        if (gcbr_arr == NULL) {
            fprintf(stderr, "Erro de alocacao de memoria!\n");
            return 1; // Retorna com erro
        }

        // Lê os elementos do vetor
        for (int gcbr_i = 0; gcbr_i < gcbr_n; gcbr_i++) {
            scanf("%d", &gcbr_arr[gcbr_i]);
        }

        // Chama a função de ordenação e conta os deslocamentos
        long long gcbr_result = gcbrInsertionSort(gcbr_n, gcbr_arr);
        
        // Imprime o resultado para o caso de teste atual
        printf("%lld\n", gcbr_result);

        // Libera a memória alocada para o vetor
        free(gcbr_arr);
    }

    return 0;
}


