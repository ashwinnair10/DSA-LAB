#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
int arr[100][100],t[100],s=0;
void initialize(){
    for(int i=0;i<100;i++){
        t[i]=-1;
        for(int j=0;j<100;j++)
        arr[i][j]=INT_MIN;
    }
}
typedef struct node* node;
int max(int a,int b){
    return (a>b)?a:b;
}
struct node
{
    int k;
    node left;
    node right;
};
node create(int k){
    node temp=(node)malloc(sizeof(struct node));
    temp->k=k;
    temp->left=NULL;
    temp->right=NULL;
    return temp;
}
node buildtree(int in[],int pre[],int l,int r,int* h){
    if(l>r)
    return NULL;
    else{
        int current=pre[(*h)++],pivot,i;
        node currentroot=create(current);
        for(i=l;i<=r;i++)
        if(current==in[i])
        pivot=i;
        currentroot->left=buildtree(in,pre,l,pivot-1,h);
        currentroot->right=buildtree(in,pre,pivot+1,r,h);
        return currentroot;
    }
}
int height(node head){
    if(head==NULL)
    return 0;
    else{
        int lh=height(head->left);
        int rh=height(head->right);
        return max(lh,rh)+1;
    }
}
void sum(node head,int l,int level){
    if(head!=NULL){
        if(l==1){
            arr[level][++t[level]]=head->k;
            if(head->left!=NULL&&head->left->left==NULL&&head->left->right==NULL)
            s+=head->left->k;
        }
        else if(l>1){
            sum(head->left,l-1,level);
            sum(head->right,l-1,level);
        }
    }
    else return;
}
void traverse(node head,int l,int level,int e){
    if(head!=NULL){
        if(l==1){
            printf("%d ",head->k);
            arr[level][++t[level]]=head->k;

        }
        else if(l>1&&e==1){
            traverse(head->left,l-1,level,e);
            traverse(head->right,l-1,level,e);
        }
        else if(l>1&&e==0){
            traverse(head->right,l-1,level,e);
            traverse(head->left,l-1,level,e);
        }
    }
    else return;
}
void zigzag(node head){
    for(int i=1;i<=height(head);i++)
    traverse(head,i,i,i%2);
}
void findsum(node head){
    for(int i=1;i<=height(head);i++)
    sum(head,i,i);
}

void postorder(node root){
    if(root!=NULL){
        postorder(root->left);
        postorder(root->right);
        printf("%d ",root->k);
    }
}
void levelmax(){
    for(int i=0;i<100;i++){
        int max=arr[i][0];
        for(int j=1;j<100;j++){
            if(arr[i][j]>max)
            max=arr[i][j];
        }
        if(max!=INT_MIN)
        printf("%d ",max);
    }
}
int diameter(node head){
    if(head==NULL)
    return 0;
    else{
        int ld=diameter(head->left);
        int rd=diameter(head->right);
        return max(max(ld,rd),height(head->left)+height(head->right)+1);
    }
}
int main()
{
    int n, i, rootindex;
    scanf("%d", &n);
    int pre[n], in[n];
    for (i = 0; i < n; i++)
        scanf("%d", &in[i]);
    for (i = 0; i < n; i++)
        scanf("%d", &pre[i]);
    int h=0;
    node root = buildtree(in,pre,0,n-1,&h);
    char ch[2] = {'\0'};
    initialize();
    while (1)
    {
        scanf("%s", ch);
        ch[1] = '\0';
        if (strcmp(ch, "p") == 0)
        {
            postorder(root);
            printf("\n");
        }
        if (strcmp(ch, "z") == 0)
        {
            zigzag(root);
            printf("\n");
        }
        if (strcmp(ch, "m") == 0){
            levelmax();
            printf("\n");
        }
        if (strcmp(ch, "d") == 0)
            printf("%d\n",diameter(root));
        if (strcmp(ch, "s") == 0){
            findsum(root);
            printf("%d\n",s);
        }
        if (strcmp(ch, "e") == 0)
            break;
    }
    return 0;
}