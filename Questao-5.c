//Atividade - Programação

//Questão 05:

#include <stdio.h>
#include <stdlib.h> 
#include <string.h> 

// Estrutura para representar um nó na lista de adjacência
typedef struct Node {
    int data;
    struct Node* next;
} Node;

// Função para adicionar uma aresta à lista de adjacência
void addEdge(Node* adj[], int u, int v) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = v;
    newNode->next = adj[u];
    adj[u] = newNode;
}

// Função DFS para percorrer a árvore e contar pares similares
void dfs(int u, int k, Node* adj[], int parent[], int* count) {
    // Para cada nó, verifique todos os seus ancestrais
    int current = u;
    // Percorre para cima enquanto houver um pai e não for o nó raiz
    while (parent[current] != 0) {
        int ancestor = parent[current];
        if (abs(ancestor - u) <= k) {
            (*count)++;
        }
        current = ancestor;
    }

    // Chame DFS para cada filho
    Node* temp = adj[u];
    while (temp != NULL) {
        dfs(temp->data, k, adj, parent, count);
        temp = temp->next;
    }
}

int similarPair(int n, int k, int edges[][2], int m) {
    // Lista de adjacência para representar a árvore
    Node* adj[n + 1];
    for (int i = 0; i <= n; i++) {
        adj[i] = NULL;
    }

    // Array para armazenar o pai de cada nó (usado para encontrar ancestrais)
    // parent[i] armazena o pai do nó i. parent[raiz] será 0.
    int parent[n + 1];
    memset(parent, 0, sizeof(parent)); // Inicializa todos os pais como 0

    // Constrói a lista de adjacência e o array de pais
    for (int i = 0; i < m; i++) {
        int u = edges[i][0];
        int v = edges[i][1];
        addEdge(adj, u, v);
        parent[v] = u; // Define u como pai de v
    }

    int count = 0;
    // Encontre a raiz da árvore (o nó que não é filho de ninguém)
    int root = -1;
    for (int i = 1; i <= n; i++) {
        if (parent[i] == 0) {
            root = i;
            break;
        }
    }

    // Inicia a DFS a partir da raiz
    dfs(root, k, adj, parent, &count);

    // Libera a memória alocada para a lista de adjacência
    for (int i = 0; i <= n; i++) {
        Node* current = adj[i];
        while (current != NULL) {
            Node* next = current->next;
            free(current);
            current = next;
        }
    }

    return count;
}

// runTest sem os ícones
void runTest(int n, int k, int edges[][2], int m, int testNum) {
    printf("Teste %d\n", testNum);
    printf("n = %d, k = %d\nedges = ", n, k);
    for (int i = 0; i < m; i++) {
        printf("(%d,%d) ", edges[i][0], edges[i][1]);
    }
    printf("\nResultado: %d\n\n", similarPair(n, k, edges, m));
}

int main() {
    int test1[][2] = {{3, 2}, {3, 1}, {1, 4}, {1, 5}};
    int test2[][2] = {{1, 2}, {1, 3}, {2, 4}, {3, 5}, {3, 6}};
    int test3[][2] = {{1, 2}, {2, 3}, {3, 4}};
    int test4[][2] = {{1, 2}, {1, 3}, {2, 4}, {2, 5}, {3, 6}, {6, 7}};
    int test5[][2] = {{1, 2}, {2, 3}};

    runTest(5, 2, test1, 4, 1);
    runTest(6, 3, test2, 5, 2);
    runTest(4, 1, test3, 3, 3);
    runTest(7, 4, test4, 6, 4);
    runTest(3, 0, test5, 2, 5);

    return 0;
}
