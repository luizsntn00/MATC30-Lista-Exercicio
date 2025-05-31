//Atividade - programação 


//Questão 01:

#include <stdio.h>
#include <stdlib.h>

#define MAXN 20
#define MAXM 20

typedef struct {
    int x, y;
} Tunnel;

char maze[MAXN][MAXM];
Tunnel tunnels[MAXN * MAXM][2];
int tunnel_map[MAXN][MAXM];
int n, m, k;
int start_x, start_y;

void loadMaze() {
    scanf("%d %d %d", &n, &m, &k);

    for (int i = 0; i < n; i++) {
        scanf("%s", maze[i]);
        for (int j = 0; j < m; j++) {
            tunnel_map[i][j] = -1;
            if (maze[i][j] == 'A') {
                start_x = i;
                start_y = j;
            }
        }
    }

    for (int i = 0; i < k; i++) {
        int x1, y1, x2, y2;
        scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
        tunnels[i][0] = (Tunnel){x1, y1};
        tunnels[i][1] = (Tunnel){x2, y2};
        tunnel_map[x1][y1] = i;
        tunnel_map[x2][y2] = i;
    }
}

Tunnel getTunnelExit(int x, int y) {
    int tunnel_id = tunnel_map[x][y];
    if (tunnel_id == -1) return (Tunnel){x, y};

    if (tunnels[tunnel_id][0].x == x && tunnels[tunnel_id][0].y == y)
        return tunnels[tunnel_id][1];
    return tunnels[tunnel_id][0];
}

double dfs(int x, int y, int visitados[MAXN][MAXM]) {
    if (visitados[x][y]) return 0.0;
    visitados[x][y] = 1;

    char celula = maze[x][y];
    if (celula == '*') return 0.0;
    if (celula == '%') return 1.0;

    if (tunnel_map[x][y] != -1) {
        Tunnel exit_tunnel = getTunnelExit(x, y);
        x = exit_tunnel.x;
        y = exit_tunnel.y;
    }

    int moves[4][2] = {{0, 1}, {1, 0}, {-1, 0}, {0, -1}};
    int possibilidades = 0;
    double prob = 0.0;

    for (int i = 0; i < 4; i++) {
        int nx = x + moves[i][0], ny = y + moves[i][1];
        if (nx >= 0 && nx < n && ny >= 0 && ny < m && maze[nx][ny] != '#') {
            possibilidades++;
            int novo_visitados[MAXN][MAXM];
            for (int j = 0; j < n; j++)
                for (int k = 0; k < m; k++)
                    novo_visitados[j][k] = visitados[j][k];

            prob += dfs(nx, ny, novo_visitados);
        }
    }

    if (possibilidades == 0) return 0.0;
    return prob / possibilidades;
}

int main() {
    loadMaze();

    int visitados[MAXN][MAXM] = {0};
    double probabilidade = dfs(start_x, start_y, visitados);

    printf("%.6lf\n", probabilidade);
    return 0;
}
