#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
typedef struct node* node;
int a[100],t;
void initialize(){
    t=-1;
    for(int j=0;j<100;j++)
    a[j]=-1;
}
struct node
{
    int k;
    node left;
    node right;
    node parent;
};
node create(int k){
    node temp=(node)malloc(sizeof(struct node));
    temp->k=k;
    temp->left=NULL;
    temp->right=NULL;
    temp->parent=NULL;
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
            if(temp1!=NULL)
            temp1->parent=stack[top];
            if(temp2!=NULL)
            temp2->parent=stack[top];
        }
    }
    stack[0]->left=stack[1];
    stack[0]->right=stack[2];
    if(stack[1]!=NULL)
    stack[1]->parent=stack[0];
    if(stack[2]!=NULL)
    stack[2]->parent=stack[0];
    return stack[0];
}
void inorder(node head){
    if(head!=NULL){
        inorder(head->left);
        a[++t]=head->k;
        inorder(head->right);
    }
}
node search(node head,int k){
    if(head==NULL||head->k==k)
    return head;
    else if(k<head->k)
    search(head->left,k);
    else
    search(head->right,k);
}
void ancestor(node head,int k){
    node temp=search(head,k);
    while(temp!=NULL){
        printf("%d ",temp->k);
        temp=temp->parent;
    }
}
int main()
{
    initialize();
    char arr[1000]={'\0'};
    scanf("%s", arr);
    node root = buildtree(arr,(int)strlen(arr));
    char ch[2] = {'\0'};
    while (1)
    {
        scanf("%s", ch);
        ch[1] = '\0';
        if (strcmp(ch, "p") == 0){
            inorder(root);
            int k1,k2,l,r;
            scanf("%d %d",&k1,&k2);
            for(int i=0;i<100;i++){
                if(a[i]==k1){
                    l=i;
                    break;
                }
            }
            for(int i=0;i<100;i++){
                if(a[i]==k2){
                    r=i;
                    break;
                }
            }
            for(int i=l;i<=r;i++){
                printf("%d ",a[i]);
            }
            printf("\n");
        }
        if (strcmp(ch, "a") == 0){
            int k;
            scanf("%d",&k);
            ancestor(root,k);
            printf("\n");
        }
        if (strcmp(ch, "e") == 0)
            break;
    }
    return 0;
}