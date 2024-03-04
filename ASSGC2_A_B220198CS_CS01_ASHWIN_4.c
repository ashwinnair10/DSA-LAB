#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct node{
    int k;
    int c;
    struct node* l;
    struct node* r;
    struct node* p;
};
typedef struct node* node;
node create(int k){
    node temp=(node)malloc(sizeof(struct node));
    temp->k=k;
    temp->c=-1;
    temp->l=NULL,temp->r=NULL,temp->p=NULL;
    return temp;
}
int blackheight(node head){
    if(head==NULL)
    return 1;
    int lb=blackheight(head->l);
    int rb=blackheight(head->r);
    if(lb!=rb)
    return -1;
    if(head->c==0)
    lb++;
    return lb;
}
node buildtree(char* s){
    int i=0,top=-1;
    node stack[100];
    while(i<strlen(s)){
        if(s[i]=='('&&s[i+2]==')')
        stack[++top]=NULL;
        int num=0;
        if(s[i]>='0'&&s[i]<='9'){
            while(s[i]>='0'&&s[i]<='9'){
                num=num*10+(s[i]-'0');
                i++;
            }
            stack[++top]=create(num);
        }
        if(s[i]=='R')
        stack[top]->c=1;
        if(s[i]=='B')
        stack[top]->c=0;
        if(s[i]==')'&&s[i-2]==')'){
            node t1=stack[top--];
            node t2=stack[top--];
            stack[top]->l=t2;
            stack[top]->r=t1;
            if(t1!=NULL)
            t1->p=stack[top];
            if(t2!=NULL)
            t2->p=stack[top];
        }
        i++;
    }
    return stack[0];
}
int redparent(node head){
    if(head!=NULL){
        if(head->c==1){
            if(head->p->c==1)
            return 0;
        }
        redparent(head->l);
        redparent(head->r);
        return 1;
    }
}
int redblacktree(node head){
    if(redparent(head)==0||blackheight(head)==-1||head->c==1)
    return 0;
    return 1;
}
int main(){
    char s[1000];
    gets(s);
    node head=buildtree(s);
    printf("%d\n",redblacktree(head));
    return 0;
}