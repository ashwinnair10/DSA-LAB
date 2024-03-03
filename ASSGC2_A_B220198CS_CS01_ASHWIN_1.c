#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int lr=0,rr=0;
struct ll{
    int k;
    struct ll* next;
};
typedef struct ll* ll;
ll root=NULL;
ll create(int k){
    ll temp=(ll)malloc(sizeof(struct ll));
    temp->k=k;
    temp->next=NULL;
    return temp;
}
ll in(ll head,int k){
    ll temp=create(k);
    ll t=head;
    if(t==NULL)
    return temp;
    while(t->next!=NULL)
    t=t->next;
    t->next=temp;
    return head;
}
struct node{
    int k;
    struct node* left;
    struct node* right;
};
typedef struct node* node;
int max(int a,int b){
    return a>b?a:b;
}
int height(node head){
    if(head==NULL)
    return 0;
    return max(height(head->left),height(head->right))+1;
}
node createnode(int k){
    node temp=(node)malloc(sizeof(struct node));
    temp->k=k;
    temp->left=NULL;
    temp->right=NULL;
    return temp;
}
node leftrotate(node head){
    node t=head->right;
    node l=t->left;
    t->left=head;
    head->right=l;
    lr++;
    return t;
}
node rightrotate(node head){
    node t=head->left;
    node l=t->right;
    t->right=head;
    head->left=l;
    rr++;
    return t;
}
node insert(node head,int k){
    node temp=createnode(k);
    if(head==NULL)
    return temp;
    else if(head->k>k)
    head->left=insert(head->left,k);
    else if(head->k<k)
    head->right=insert(head->right,k);
    else return head;
     int bal=height(head->left)-height(head->right);
     if(bal>1&&temp->k<head->left->k){
         return rightrotate(head);
     }
     if(bal>1&&temp->k>head->left->k){
         head->left=leftrotate(head->left);
         return rightrotate(head);
     }
     if(bal<-1&&temp->k>head->right->k){
         return leftrotate(head);
     }
     if(bal<-1&&temp->k<head->right->k){
         head->right=rightrotate(head->right);
         return leftrotate(head);
     }
    return head;
}
node search(node head,int k){
    if(head==NULL)
    return NULL;
    if(head->k==k){
        root=in(root,k);
        return head;
    }
    else if(k<head->k){
        root=in(root,head->k);
        return search(head->left,k);
    }
    else{
        root=in(root,head->k);
        return search(head->right,k);
    }
    return NULL;
}
void preorder(node head){
    if(head!=NULL){
        printf("%d ",head->k);
        preorder(head->left);
        preorder(head->right);
    }
}
int main(){
    node head=NULL;
    while(1){
        char ch[2]={'\0','\0'};
        scanf("%s",ch);
        ch[1]='\0';
        if(strcmp(ch,"i")==0){
            int k;
            scanf("%d",&k);
            head=insert(head,k);
        }
        else if(strcmp(ch,"x")==0){
            int k;
            scanf("%d",&k);
            if(search(head,k)==NULL)
            printf("-1\n");
            else{
                while(root!=NULL){
                    printf("%d ",root->k);
                    root=root->next;
                }
                root=NULL;
                printf("\n");
            }
        }
        else if(strcmp(ch,"p")==0){
            preorder(head);
            printf("\n");
        }
        else if(strcmp(ch,"s")==0){
            printf("%d %d\n",lr,rr);
        }
        else if(strcmp(ch,"e")==0)
        break;
    }
    return 0;
}