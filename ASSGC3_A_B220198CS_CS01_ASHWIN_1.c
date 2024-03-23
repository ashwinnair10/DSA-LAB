#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int n,t=0,b=0,p=-1,cc=0,art[1000],visit[100],a[100][100],al[100][100],l[100],disc[100],low[100];
struct node{
    int k;
    struct node* l;
    struct node* r;
};
typedef struct node* node;
node create(int k){
    node t=(node)malloc(sizeof(struct node));
    t->k=k;
    t->l=NULL;
    t->r=NULL;
    return t;
}
node head=NULL;
node insert(node head,int k){
    node t=create(k);
    if(head==NULL)
    return t;
    else if(head->k>t->k)
    head->l=insert(head->l,k);
    else
    head->r=insert(head->r,k);
    return head;
}
void inorder(node head){
    if(head!=NULL){
        inorder(head->l);
        if(head->k)
        printf("%d ",head->k);
        inorder(head->r);
    }
}
void dfs(int i,int* c){
    if(!visit[al[i][0]-1])
    cc++,(*c)++;
    visit[al[i][0]-1]=1;
    for(int j=0;j<n;j++){
        if(al[i][j]!=-1&&!visit[al[i][j]-1]){
            visit[al[i][j]-1]++;
            (*c)++;
            dfs(al[i][j]-1,c);
        }
    }
}
void bridges(int u,int p){
    visit[u]=1;
    disc[u]=low[u]=++t;
    for(int i=0;i<n;i++){
        if(a[u][i]){
            if(i==p)
            continue;
            if(visit[i]){
                low[u]=low[u]>disc[i]?disc[i]:low[u];
            }
            else{
                bridges(i,u);
                low[u]=low[u]>low[i]?low[i]:low[u];
                if(low[i]>disc[u])
                b++;
            }
        }
    }
}
int ap=0;
void adfs(int u, int p){
    disc[u]=low[u]=++t;
    visit[u]=1;
    int child=0;
    for(int j=0;j<n;j++){
        if(al[u][j]!=-1){
            int v=al[u][j]-1;
            if(disc[v]==-1) {
                child++;
                adfs(v,u);
                low[u]=low[u]<low[v]?low[u]:low[v];
                if (low[v] >= disc[u]&&p!=-1)
                art[u]=1;
            }
            else if(v!=p)
            low[u]=low[u]<disc[v]?low[u]:disc[v];
        }
    }
    if(p==-1&&child>1)
    art[u]=1;
}
void articulation(){
    for(int i=0;i<n;i++){
        disc[i]=-1,low[i]=-1,art[i]=0;
    }
    for(int i=0;i<n;i++){
        if(disc[i]==-1){
            adfs(i,-1);
        }
    }
    int ap=0;
    for(int i=0;i<n;i++){
        if(art[i])
        ap++;
    }
    if(!ap)
    ap=-1;
    printf("%d",ap);
}
int main(){
    int c=0,x,y;
    scanf("%d",&n);
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++)
        a[i][j]=0,al[i][j]=-1;
        visit[i]=0,l[i]=0,disc[i]=0,low[i]=0;
    }
    for(int k=0;k<n;k++){
        scanf("%d",&x);
        al[x-1][l[x-1]++]=x;
        while(getchar()!='\n'){
            scanf("%d",&y);
            a[x-1][y-1]=1;
            al[x-1][l[x-1]++]=y;
        }
    }
    for(int i=0;i<n;i++){
        c=0;
        if(!visit[al[i][0]-1]){
            dfs(i,&c);
        }
        head=insert(head,c);
    }
    while(1){
        char ch[2];
        scanf("%s",ch);
        ch[1]='\0';
        if(strcmp(ch,"n")==0){
            printf("%d\n",cc);
        }
        if(strcmp(ch,"s")==0){
            inorder(head);
            printf("\n");
        }
        if(strcmp(ch,"b")==0){
            for(int i=0;i<n;i++)
            visit[i]=0;
            for(int i=0;i<n;i++)
            if(!visit[i])
            bridges(i,-1);
            if(!b)
            b=-1;
            printf("%d\n",b);
        }
        if(strcmp(ch,"a")==0){
            for(int i=0;i<n;i++)
            visit[i]=0;
            t=0;
            articulation();
            printf("\n");
        }
        if(strcmp(ch,"t")==0)
        break;
    }
    return 0;
}