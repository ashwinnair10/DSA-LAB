#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
int n;
int minDistance(int dist[], bool sptSet[]){
    int min = INT_MAX, min_index;
    for (int v = 0; v < n; v++)
        if (sptSet[v] == false && dist[v] <= min)
            min = dist[v], min_index = v;
    return min_index;
}
void printSolution(int dist[]){
    for (int i = 0; i < n; i++)
        printf("%d ",dist[i]);
}
void dijkstra(int graph[n][n], int src){
    int dist[n];
    bool sptSet[n];
    for (int i = 0; i < n; i++)
        dist[i] = INT_MAX, sptSet[i] = false;
    dist[src] = 0;
    for (int count = 0; count < n - 1; count++){
        int u = minDistance(dist, sptSet);
        sptSet[u] = true;
        for (int v = 0; v < n; v++)
            if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX && dist[u] + graph[u][v] < dist[v])
                dist[v] = dist[u] + graph[u][v];
    }
    printSolution(dist);
}
int main(){
    scanf("%d", &n);
    int a[n][n], b[n][n], graph[n][n];
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            a[i][j] = -1, b[i][j] = -1, graph[i][j] = 0;
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            scanf("%d", &a[i][j]);
            if (getchar() == '\n')
                break;
        }
    }
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            scanf("%d", &b[i][j]);
            if (getchar() == '\n')
                break;
        }
    }
    for (int i = 0; i < n; i++)
        for (int j = 1; j < n; j++)
            if (a[i][j] != -1)
                graph[a[i][0] - 1][a[i][j] - 1] = b[i][j];
    int src;
    scanf("%d",&src);
    dijkstra(graph, src-1);
    return 0;
}
