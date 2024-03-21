#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_NODES 1000
int al[MAX_NODES][MAX_NODES],arr[MAX_NODES][MAX_NODES] ,l[MAX_NODES], visit[MAX_NODES], n, a, b;
int path[MAX_NODES], k = 0, cc = 0,cycle=0;
void dfs(int i){
    if(!visit[al[i][0]])
    cc++;
    visit[al[i][0]]=1;
    for(int j=1;j<n;j++){
        if(al[i][j]!=-1&&!visit[al[i][j]]){
            visit[al[i][j]]=1;
            dfs(j);
        }
    }
}
void adfs(int i) {
    path[k++] = al[i][0];
    visit[al[i][0]] = 1;
    for (int j = 1; j < n; j++) {
        if (al[i][j] != -1 && !visit[al[i][j]]) {
            if (al[i][j] == b) {
                path[k++] = al[i][j];
                
                for (int x = 0; x < k; x++) {
                    printf("%d ", path[x]);
                }
                printf("\n");
                
                
                k--;
            }
            visit[al[i][j]] = 1;
            adfs(al[i][j]);
            visit[al[i][j]] = 0;
        }
    }
    k--;
}
void initialize(){
    for(int i=0;i<1000;i++){
        path[i]=0;
        visit[i]=0;
    }
}
int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            al[i][j] = -1,arr[i][j]=0;
        l[i] = 0, visit[i] = 0, path[i] = -1;
    }
    for (int i = 0; i < n; i++) {
        scanf("%d", &a);
        al[i][l[i]++]=a;
        while (getchar() != '\n') {
            scanf("%d", &b);
            al[i][l[i]++]=b;
            arr[a][b]=1;
        }
    }
    int e=0;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++)
        {
            if(arr[i][j]==1){
                e++;
                arr[j][i]=0;
                arr[i][j]=0;
            }
        }
    }
    while(1){
        char ch[2];
        scanf("%s",ch);
        ch[1]='\0';
        if(strcmp(ch,"t")==0){
            cc=0;
            initialize();
            for(int i=0;i<n;i++)
            if(!visit[i])
            dfs(i);
            if(e==n-1&&cc==1)
            printf("1\n");
            else
            printf("-1\n");
        }
        if(strcmp(ch,"a")==0){
            for (int i = 0; i < n; i++)
            initialize();
            scanf("%d %d", &a, &b);
            adfs(a);
        }
        if(strcmp(ch,"x")==0)
        break;
    }
    return 0;
}