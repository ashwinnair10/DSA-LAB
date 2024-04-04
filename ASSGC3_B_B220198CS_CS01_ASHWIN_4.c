#include <stdio.h>
#define INF 99999
int n;
void printSolution(int dist[][n]);
void floydWarshall(int dist[][n])
{
	int i, j, k;
	for (k = 0; k < n; k++) {
		for (i = 0; i < n; i++) {
			for (j = 0; j < n; j++) {
				if (dist[i][k] + dist[k][j] < dist[i][j])
					dist[i][j] = dist[i][k] + dist[k][j];
			}
		}
	}
	printSolution(dist);
}
void printSolution(int dist[][n])
{
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (dist[i][j] != INF)
				printf("%d ", dist[i][j]);
		}
		printf("\n");
	}
}
int main()
{
    scanf("%d",&n);
    int graph[n][n];
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            scanf("%d",&graph[i][j]);
            if(graph[i][j]==-1)
            graph[i][j]=INF;
        }
    }
	floydWarshall(graph);
	return 0;
}
