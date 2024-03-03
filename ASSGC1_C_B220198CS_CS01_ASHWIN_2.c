#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
struct node{
    int k;
    struct node* next;
    struct node* prev;
};
typedef struct node* node;
node createnode(int k){
    node temp=(node)malloc(sizeof(struct node));
    temp->k=k;
    temp->prev=NULL;
    temp->next=NULL;
    return temp;
}
void insert(node hash[],int n,int k){
    node temp=createnode(k);
    int index=k%n;
    if(hash[index]==NULL){
        hash[index]=temp;
    }
    else{
        if(k==hash[index]->k){
            printf("-1\n");
            return;
        }
        if(k<hash[index]->k){
            hash[index]->prev=temp;
            temp->next=hash[index];
            hash[index]=temp;
        }
        else{
            node t=hash[index],t1=hash[index];
            while(t!=NULL){
                if(k==t->k){
                    printf("-1\n");
                    return;
                }
                if(k<t->k){
                    t->prev->next=temp;
                    temp->prev=t->prev;
                    temp->next=t;
                    t->prev=temp;
                    return;
                }
                t1=t;
                t=t->next;
            }
            t1->next=temp;
            temp->prev=t1;
        }
    }
}
node search(node hash[],int n,int k,int c){
    int index=k%n;
    if(hash[index]==NULL){
        printf("-1\n");
        return NULL;
    }
    else{
        node temp=hash[index];
        int t=1;
        while(temp!=NULL){
            if(temp->k==k){
                if(c==0)
                printf("%d %d\n",index,t);
                return temp;
            }
            temp=temp->next;
            t++;
        }
        if(c==0)
        printf("-1\n");
        return NULL;
    }
}
void deletef(node hash[], int n, int k) {
    int index = k % n,pos = 1;
    node temp = hash[index];
    if (temp == NULL) {
        printf("-1\n");
        return;
    }
    if (temp->k == k) {
        printf("%d %d\n", index, pos);
        hash[index] = temp->next;
        if (hash[index] != NULL)
            hash[index]->prev = NULL;
        return;
    }
    while (temp != NULL && temp->k != k) {
        temp = temp->next;
        pos++;
    }
    if (temp == NULL) {
        printf("-1\n");
        return;
    }
    printf("%d %d\n", index, pos);
    temp->prev->next = temp->next;
    if (temp->next != NULL)
        temp->next->prev = temp->prev;
}
void update(node hash[],int n,int ok,int nk){
    if(search(hash,n,ok,1)==NULL||search(hash,n,nk,1)!=NULL){
        printf("-1\n");
        return;
    }
    else{
        deletef(hash,n,ok);
        insert(hash,n,nk);
    }
}
void print(node hash[],int n,int k){
    if(k>n||hash[k]==NULL){
        printf("-1\n");
        return;
    }
    node temp=hash[k];
    while(temp!=NULL){
        printf("%d ",temp->k);
        temp=temp->next;
    }
    printf("\n");
    return;
}
int main(){
    int n,k;
    scanf("%d",&n);
    node hash[n];
    for(int i=0;i<n;i++)
    hash[i]=NULL;
    while(1){
        char ch[2]={'\0'};
        scanf("%s",ch);
        if(strcmp(ch,"i")==0){
            scanf("%d",&k);
            insert(hash,n,k);
        }
        if(strcmp(ch,"s")==0){
            scanf("%d",&k);
            search(hash,n,k,0);
        }
        if(strcmp(ch,"d")==0){
            scanf("%d",&k);
            deletef(hash,n,k);
        }
        if(strcmp(ch,"u")==0){
            int l;
            scanf("%d %d",&k,&l);
            update(hash,n,k,l);
        }
        if(strcmp(ch,"p")==0){
            scanf("%d",&k);
            print(hash,n,k);
        }
        if(strcmp(ch,"e")==0)
            break;
    }
    return 0;
}