#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_NODES 100

int adj[MAX_NODES][MAX_NODES];
int visited[MAX_NODES], flag = 0, count = 0;

void initialize() {
    for (int i = 0; i < MAX_NODES; ++i) {
        visited[i] = 0;
        for (int j = 0; j < MAX_NODES; ++j) {
            adj[i][j] = 0;
        }
    }
}

void addEdge(int u, int v) {
    adj[u][v] = 1;
}

void BFS(int v, int n) {
    int queue[MAX_NODES];
    int front = 0, rear = 0;
    queue[rear++] = v;
    visited[v] = 1;

    while (front < rear) {
        int current = queue[front++];
        for (int i = 1; i <= n; ++i) {
            if (adj[current][i] && !visited[i]) {
                queue[rear++] = i;
                visited[i] = 1;
            } else if (adj[current][i] && visited[i] && i != v) {
                flag = 1;
            }
        }
    }
}

int isPath(int src, int des, int n) {
    for (int i = 0; i < MAX_NODES; ++i) {
        visited[i] = 0;
    }
    BFS(src, n);
    return visited[des];
}

int checkCycle(int V) {
    int deg[MAX_NODES] = {0};
    int queue[MAX_NODES];
    int front = 0, rear = 0;
    int counter = 0;

    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            if (adj[j][i]) {
                deg[i]++;
            }
        }
    }

    for (int i = 0; i < V; i++) {
        if (deg[i] == 0) {
            queue[rear++] = i;
        }
    }

    while (front < rear) {
        int u = queue[front++];
        counter++;
        for (int v = 0; v < V; v++) {
            if (adj[u][v]) {
                deg[v]--;
                if (deg[v] == 0) {
                    queue[rear++] = v;
                }
            }
        }
    }

    return counter != V;
}

void findSCC(int n, int edges[][2]) {
    int is_scc[MAX_NODES] = {0};
    for (int i = 1; i <= n; ++i) {
        if (!is_scc[i]) {
            int scc[MAX_NODES], scc_count = 0;
            scc[scc_count++] = i;

            for (int j = i + 1; j <= n; ++j) {
                if (!is_scc[j] && isPath(i, j, n) && isPath(j, i, n)) {
                    is_scc[j] = 1;
                    scc[scc_count++] = j;
                }
            }
            count++;
        }
    }
}

int main() {
    initialize();
    int V = 6;
    scanf("%d", &V);
    int edges[1000][2];
    for (int i = 0; i < 1000; i++)
        edges[i][0] = -1, edges[i][1] = -1;
    int k = 0;
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            int a;
            scanf("%d", &a);
            if (a) {
                edges[k][0] = i + 1;
                edges[k][1] = j + 1;
                addEdge(edges[k][0], edges[k][1]);
                k++;
            }
        }
    }
    if (checkCycle(V)) {
        printf("-1\n");
    } else {
        printf("1\n");
    }
    findSCC(V, edges);
    printf("Count : %d\n", count);

    return 0;
}
