#include <limits.h>
#include<string.h>
#include <stdbool.h>
#include <stdio.h>
int n,sv,f;
int minKey(int key[], bool mstSet[])
{
    int min = INT_MAX, min_index;
    for (int v = 0; v < n; v++)
        if (mstSet[v] == false && key[v] < min)
            min = key[v], min_index = v;
    return min_index;
}
void countMST(int parent[], int graph[n][n],int c)
{
    for (int i = 0; i < n; i++){
        if(parent[i]!=-1)
        c=c+ graph[i][parent[i]];
    }
    printf("%d\n", c);
}
void primMST(int graph[n][n],int c)
{
    int parent[n];
    int key[n];
    bool mstSet[n];
    for (int i = 0; i < n; i++)
        key[i] = INT_MAX, mstSet[i] = false,parent[i]=-1;
    key[sv] = 0;
    parent[sv] = -1;
    for (int count = 0; count < n; count++)
    {
        int u = minKey(key, mstSet);
        int v, a = INT_MAX, b = INT_MAX;
        mstSet[u] = true;
        for (v = 0; v < n; v++)
        {
            if (graph[u][v] && mstSet[v] == false && graph[u][v] < key[v])
                parent[v] = u, key[v] = graph[u][v];
        }
        if (parent[u] != -1&&!f)
            printf("%d %d ", parent[u], u);
    }
    if(f)
    countMST(parent, graph,c);
}
int main()
{
    scanf("%d", &n);
    int graph[n][n];
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &graph[i][j]);
    while(1){
        char ch[5];
        scanf("%s",ch);
        if(ch[0]=='t'){
            f=1,sv=0;
            primMST(graph,0);
        }
        if(ch[0]=='s')
        {
            int num=0,i=2;
            while(ch[i]!=')'){
                num=(num*10)+(ch[i]-48);
                i++;
            }
            sv=num,f=0;
            primMST(graph,0);
            printf("\n");
        }
        if(ch[0]=='x')
        break;
    }
    return 0;
}
