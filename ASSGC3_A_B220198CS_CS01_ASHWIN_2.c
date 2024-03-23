#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_NODES 100

int adj[MAX_NODES][MAX_NODES];
int visited[MAX_NODES], in_stack[MAX_NODES], low[MAX_NODES];
int stack[MAX_NODES], scc[MAX_NODES];
int scc_count, stack_top;

void initialize() {
    for (int i = 0; i < MAX_NODES; ++i) {
        visited[i] = 0;
        in_stack[i] = 0;
        low[i] = -1;
        scc[i] = -1;
        for (int j = 0; j < MAX_NODES; ++j) {
            adj[i][j] = 0;
        }
    }
}

void addEdge(int u, int v) {
    adj[u - 1][v - 1] = 1;
}

void strongconnect(int v) {
    visited[v] = 1;
    low[v] = v;
    stack[++stack_top] = v;
    in_stack[v] = 1;

    for (int i = 0; i < MAX_NODES; ++i) {
        if (adj[v][i]) {
            if (!visited[i]) {
                strongconnect(i);
                low[v] = (low[v] < low[i]) ? low[v] : low[i];
            } else if (in_stack[i]) {
                low[v] = (low[v] < low[i]) ? low[v] : low[i];
            }
        }
    }

    if (low[v] == v) {
        int w;
        do {
            w = stack[stack_top--];
            in_stack[w] = 0;
            scc[w] = scc_count;
        } while (w != v);
        scc_count++;
    }
}
int isCyclicUtil(int v, int visited[], int recStack[]) {
    if (visited[v] == 0) {
        visited[v] = 1;
        recStack[v] = 1;

        for (int i = 0; i < MAX_NODES; i++) {
            if (adj[v][i]) {
                if (!visited[i] && isCyclicUtil(i, visited, recStack)) {
                    return 1;
                } else if (recStack[i]) {
                    return 1;
                }
            }
        }
    }
    recStack[v] = 0;
    return 0;
}

int checkCycle(int V) {
    int visited[MAX_NODES] = {0};
    int recStack[MAX_NODES] = {0};

    for (int i = 0; i < V; i++) {
        if (isCyclicUtil(i, visited, recStack)) {
            return 1;
        }
    }
    return 0;
}

void findSCC(int n) {
    for (int i = 0; i < n; ++i) {
        if (!visited[i]) {
            strongconnect(i);
        }
    }
}

int main() {
    initialize();
    int V;
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

    while (1) {
        char ch[2];
        scanf("%s", ch);
        ch[1] = '\0';
        if (strcmp(ch, "t") == 0) {
            if (checkCycle(V)) {
                printf("-1\n");
            } else {
                printf("1\n");
            }
        }
        if (strcmp(ch, "c") == 0) {
            findSCC(V);
            printf("%d\n", scc_count);
        }
        if (strcmp(ch, "x") == 0)
            break;
    }
    return 0;
}
