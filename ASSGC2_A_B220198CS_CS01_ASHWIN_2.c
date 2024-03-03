#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int c=0;
struct ll{
    int k;
    int v;
    struct ll* next;
};
typedef struct ll* ll;
ll root=NULL;
ll create(int k,int v){
    ll temp=(ll)malloc(sizeof(struct ll));
    temp->k=k;
    temp->v=v;
    temp->next=NULL;
    return temp;
}
ll in(ll head,int k,int v){
    ll temp=create(k,v);
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
    int value;
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
node createnode(int k,int value){
    node temp=(node)malloc(sizeof(struct node));
    temp->k=k;
    temp->value=value;
    temp->left=NULL;
    temp->right=NULL;
    return temp;
}
node leftrotate(node head){
    node t=head->right;
    node l=t->left;
    t->left=head;
    head->right=l;
    return t;
}
node rightrotate(node head){
    node t=head->left;
    node l=t->right;
    t->right=head;
    head->left=l;
    return t;
}
node insert(node head,int k,int value){
    node temp=createnode(k,value);
    if(head==NULL)
    return temp;
    else if(head->k>k)
    head->left=insert(head->left,k,value);
    else if(head->k<k)
    head->right=insert(head->right,k,value);
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
        return head;
    }
    else if(k<head->k){
        return search(head->left,k);
    }
    else{
        return search(head->right,k);
    }
    return NULL;
}
void inorder(node head,int c){
    if(head!=NULL){
        inorder(head->left,c);
        if(c==1)
        printf("%d ",head->k);
        root=in(root,head->k,head->value);
        inorder(head->right,c);
    }
}
void lower(node head,int k){
    node temp=search(head,k);
    if(temp!=NULL){
        printf("%d %d\n",temp->k,temp->value);
        return;
    }
    else{
         inorder(head,0);
        ll t=root;
        node l;
        while(t!=NULL){
            if(t->k>=k){
                printf("%d %d\n",t->k,t->v);
                return;
            }
            t=t->next;
        }
    }
    printf("-1\n");
    return;
}
int main(){
    node head=NULL;
    while(1){
        char ch[2]={'\0','\0'};
        scanf("%s",ch);
        ch[1]='\0';
        if(strcmp(ch,"i")==0){
            int k,v;
            scanf("%d %d",&k,&v);
            node t=search(head,k);
            if(t==NULL){
                head=insert(head,k,v);
                c++;
            }
            else t->value=v;
        }
        else if(strcmp(ch,"f")==0){
            int k;
            scanf("%d",&k);
            if(search(head,k)==NULL)
            printf("-1\n");
            else
            printf("%d %d\n",search(head,k)->k,search(head,k)->value);
        }
        else if(strcmp(ch,"l")==0){
            int k;
            root=NULL;
            scanf("%d",&k);
            lower(head,k);
        }
        else if(strcmp(ch,"p")==0){
            if(head!=NULL)
            inorder(head,1);
            else
            printf("-1");
            printf("\n");
        }
        else if(strcmp(ch,"s")==0){
            if(c!=0)
            printf("%d\n",c);
            else
            printf("-1\n");
        }
        else if(strcmp(ch,"e")==0){
            if(head==NULL)
            printf("1\n");
            else printf("0\n");
        }
        else if(strcmp(ch,"t")==0)
        break;
    }
    return 0;
}