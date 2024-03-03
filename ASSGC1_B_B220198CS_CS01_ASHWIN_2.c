#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
typedef struct node* node;
int max(int a,int b){
    return (a>b)?a:b;
}
int a[100][100],t[100],r;
int b[100][100],p[100],s=0;
void initialize(){
    r=0;
    for(int i=0;i<100;i++){
        t[i]=-1;
        for(int j=0;j<100;j++)
        a[i][j]=-1;
    }
    for(int i=0;i<100;i++){
        p[i]=-1;
        for(int j=0;j<100;j++)
        b[i][j]=INT_MIN;
    }
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
node buildtree(char arr[],int n){
    node stack[1000];
    int top=-1,i;
    for(i=0;i<n;i++)
    if(arr[i]=='(')
    break;
    char te[i+1];
    for(int k=0;k<i;k++)
    {
        te[k]=arr[0+k];
    }
    stack[++top]=create(atoi(te));
    for(i=0;i<n;i++){
        if(arr[i]=='('&&arr[i+1]>='0'&&arr[i+1]<='9'){
            int j=0;
            while(arr[i+j+1]!='('&&arr[i+j]!=')'){
                j++;
            }
            char num[j+1];
            for(int k=0;k<j;k++)
            {
                num[k]=arr[i+1+k];
                num[j]='\0';
            }
            node temp=create(atoi(num));
            stack[++top]=temp;
        }
        if(arr[i]=='('&&arr[i+1]==')')
        stack[++top]=NULL;
        if(arr[i]==')'&&arr[i-1]==')'){
            node temp1=stack[top--];
            node temp2=stack[top--];
            stack[top]->right=temp1;
            stack[top]->left=temp2;
        }
    }
    stack[0]->left=stack[1];
    stack[0]->right=stack[2];
    return stack[0];
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
void traverse(node head,int level,int l){
    if(head!=NULL){
        if(l==1){
            printf("%d ",head->k);
             b[level-1][++p[level-1]]=head->k;
        }
        else if(l>1){
            traverse(head->left,level,l-1);
            traverse(head->right,level,l-1);
        }
    }
    else return;
}
void levelorder(node head){
    for(int i=1;i<=height(head);i++)
    traverse(head,i,i);
}
void inorder(node head){
    if(head!=NULL){
        inorder(head->left);
        a[r][++(t[r])]=head->k;
        inorder(head->right);
    }
}
int check(int a[],int n){
    for(int i=0;i<n-1;i++){
        if(a[i]>=a[i+1])
        return 0;
    }
    return 1;
}
int sum(int a[],int n){
    int s=0;
    for(int i=0;i<n;i++)
    s+=a[i];
    return s;
}
void searchbst(node head){
    if(head!=NULL){
        inorder(head);
        r++;
        searchbst(head->left);
        searchbst(head->right);
    }
}
int maxsumbst(){
    int maxsum=0,i,j;
    for(i=0;i<100;i++){
        for(j=0;j<100;j++){
            if(a[i][j]==-1)
            break;
        }
        if(check(a[i],j)){
            maxsum=max(maxsum,sum(a[i],j));
        }
    }
    return maxsum;
}
void rightview(node head){
    int i,j;
    for(i=0;i<100;i++){
        for(j=0;j<100;j++){
            if(b[i][j]==INT_MIN)
            break;
        }
        if(b[i][j-1]!=INT_MIN)
        printf("%d ",b[i][j-1]);
    }
}
int main()
{
    char arr[1000]={'\0'};
    scanf("%s", arr);
    node root = buildtree(arr,(int)strlen(arr));
    char ch[2] = {'\0'};
    initialize();
    while (1)
    {
        scanf("%s", ch);
        ch[1] = '\0';
        if (strcmp(ch, "l") == 0)
        {
            levelorder(root);
            printf("\n");
        }
        if (strcmp(ch, "m") == 0){
            searchbst(root);
            printf("%d\n",maxsumbst());
        }
        if (strcmp(ch, "r") == 0){
            rightview(root);
            printf("\n");
        }
        if (strcmp(ch, "e") == 0)
            break;
    }
    return 0;
}