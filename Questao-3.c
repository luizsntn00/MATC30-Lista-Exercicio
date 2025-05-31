//Atividade programação

//Questão 03:

#include <stdio.h>
#include <stdlib.h> 
#include <time.h>   
#include <string.h> 
#include <math.h>   

// G12xB3xR*C3

// Função principal que calcula o número de notificações
int activityNotifications(int* expenditure, int n, int d) {
    int notifications = 0;
    
    // Array de frequências para contar os gastos (0 a 200)
    int counts[201] = {0}; 

    // Preenche a janela inicial com os 'd' primeiros gastos
    for (int i = 0; i < d; i++) {
        counts[expenditure[i]]++;
    }

    // Itera a partir do dia 'd' até o último dia (n-1)
    for (int i = d; i < n; i++) {
        double median;
        int sum_so_far = 0;
        int median1_val = -1; // Para o primeiro valor da mediana (ou único para d ímpar)
        int median2_val = -1; // Para o segundo valor da mediana (apenas para d par)

        // Se d é ímpar, target_pos1 é o único índice mediano.
        // Se d é par, target_pos1 é o primeiro índice central, target_pos2 é o segundo.
        int target_pos1 = (d % 2 == 1) ? (d / 2) : (d / 2 - 1); 
        int target_pos2 = d / 2; 
        
        // Loop para encontrar os valores da mediana no array de frequências
        for (int val = 0; val <= 200; val++) {
            sum_so_far += counts[val];

            if (d % 2 == 1) { // Caso d ímpar: um único valor mediano
                if (sum_so_far > target_pos1) { 
                    median = (double)val;
                    break; // Mediana encontrada, pode sair do loop
                }
            } else { // Caso d par: dois valores medianos
                if (median1_val == -1 && sum_so_far > target_pos1) {
                    median1_val = val;
                }
                if (sum_so_far > target_pos2) {
                    median2_val = val;
                    // Ambos os valores medianos encontrados, calcula a média e sai
                    median = (double)(median1_val + median2_val) / 2.0;
                    break; 
                }
            }
        }
        
        // Verifica a condição de notificação
        if (expenditure[i] >= 2.0 * median) {
            notifications++;
        }

        // Decrementa a contagem do gasto mais antigo
        counts[expenditure[i - d]]--; 
        // Incrementa a contagem do gasto mais recente 
        counts[expenditure[i]]++;     
    }

    return notifications;
}

// Função principal para leitura de entrada e impressão da saída
int main() {
    // Declara variáveis para n e d
    int n, d;

    // Lê n e d do console
    scanf("%d %d", &n, &d);

    // Aloca dinamicamente o array de gastos
    int* gastos = (int*) malloc(n * sizeof(int));
    if (gastos == NULL) {
        // Em caso de falha na alocação de memória, imprime um erro e sai
        fprintf(stderr, "Erro de alocacao de memoria!\n");
        return 1; 
    }

    // Lê os n gastos diários para o array
    for (int i = 0; i < n; i++) {
        scanf("%d", &gastos[i]);
    }
    
    // Chama a função para calcular o número de notificações
    int resultado = activityNotifications(gastos, n, d);
    
    // Imprime apenas o resultado final
    printf("%d\n", resultado);

    // Libera a memória alocada dinamicamente
    free(gastos);

    return 0;
}
