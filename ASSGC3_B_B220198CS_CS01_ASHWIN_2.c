#include <stdio.h> 
#include <stdlib.h> 
int comparator(const void* p1, const void* p2) 
{ 
	const int(*x)[3] = p1; 
	const int(*y)[3] = p2; 
	return (*x)[2] - (*y)[2]; 
} 
void makeSet(int parent[], int rank[], int n) 
{ 
	for (int i = 0; i < n; i++) { 
		parent[i] = i; 
		rank[i] = 0; 
	} 
} 
int findParent(int parent[], int component) 
{ 
	if (parent[component] == component) 
		return component; 
	return parent[component] 
		= findParent(parent, parent[component]); 
} 
void unionSet(int u, int v, int parent[], int rank[], int n) 
{ 
	u = findParent(parent, u); 
	v = findParent(parent, v); 
	if (rank[u] < rank[v]) { 
		parent[u] = v; 
	} 
	else if (rank[u] > rank[v]) { 
		parent[v] = u; 
	} 
	else { 
		parent[v] = u; 
		rank[u]++; 
	} 
} 
void kruskalAlgo(int n, int edge[n][3]) 
{ 
	qsort(edge, n, sizeof(edge[0]), comparator); 
	int parent[n]; 
	int rank[n]; 
	makeSet(parent, rank, n); 
	int minCost = 0;  
	for (int i = 0; i < n; i++) { 
		int v1 = findParent(parent, edge[i][0]); 
		int v2 = findParent(parent, edge[i][1]); 
		int wt = edge[i][2]; 
		if (v1 != v2) { 
			unionSet(v1, v2, parent, rank, n); 
			minCost += wt; 
		} 
	} 
	printf("%d\n", minCost); 
} 
int main() 
{ 
    int n;
    scanf("%d",&n);
    int a[n][n],b[n][n];
    for(int i=0;i<n;i++)
    for(int j=0;j<n;j++)
    a[i][j]=-1,b[i][j]=-1;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            scanf("%d",&a[i][j]);
            if(getchar()=='\n')
            break;
        }
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            scanf("%d",&b[i][j]);
            if(getchar()=='\n')
            break;
        }
    }
    int edge[n*n][3];
    int k=0;
    for(int i=0;i<n;i++){
        for(int j=1;j<n;j++){
            if(a[i][j]!=-1){
                edge[k][0]=a[i][0],edge[k][1]=a[i][j],edge[k][2]=b[i][j];
                k++;
            }
        }
    }
	kruskalAlgo(k, edge); 
	return 0; 
}
