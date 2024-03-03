#include<stdio.h>
#include<stdlib.h>
#include<string.h>
//black=0,red=1
typedef struct node* node;
struct node{
    int k;
    int c;
    node l;
    node r;
    node p;
};
node head=NULL;
node createnode(int k){
    node temp=(node)malloc(sizeof(struct node));
    temp->k=k;
    temp->c=1;
    temp->p=NULL;
    temp->l=NULL;
    temp->r=NULL;
    return temp;
}
void leftrotate(node temp){
    node right = temp->r;
    temp->r = right->l;
    if (temp->r)
        temp->r->p = temp;
    right->p = temp->p;
    if (!temp->p)
        head = right;
    else if (temp == temp->p->l)
        temp->p->l = right;
    else
        temp->p->r = right;
    right->l = temp;
    temp->p = right;
}
void rightrotate(node temp){
    node left = temp->l;
    temp->l = left->r;
    if (temp->l)
        temp->l->p = temp;
    left->p = temp->p;
    if (!temp->p)
        head = left;
    else if (temp == temp->p->l)
        temp->p->l = left;
    else
        temp->p->r = left;
    left->r = temp;
    temp->p = left;
}
node insert(node head,node temp){
    if(head==NULL){
        return temp;
    }
    else{
        if(temp->k<head->k){
            head->l=insert(head->l,temp);
            head->l->p=head;
        }
        if(temp->k>head->k){
            head->r=insert(head->r,temp);
            head->r->p=head;
        }
        return head;
    }
}
void fixup(node head,node temp){
    node parent = NULL;
    node grandparent = NULL;
    while((temp!=head)&&(temp->c!=0)&&(temp->p->c==1)) {
        parent = temp->p;
        grandparent = temp->p->p;
        if(parent==grandparent->l) {
            node uncle = grandparent->r;
            if (uncle != NULL && uncle->c == 1) 
            {
                grandparent->c = 1;
                parent->c = 0;
                uncle->c = 0;
                temp = grandparent;
            }
            else {
                if (temp == parent->r) {
                    leftrotate(parent);
                    temp = parent;
                    parent = temp->p;
                }
                rightrotate(grandparent);
                int t = parent->c;
                parent->c = grandparent->c;
                grandparent->c = t;
                temp = parent;
            }
        }
        else {
            node uncle = grandparent->l;
            if ((uncle != NULL) && (uncle->c == 1)) 
            {
                grandparent->c = 1;
                parent->c = 0;
                uncle->c = 0;
                temp = grandparent;
            }
            else {
                if (temp == parent->l) {
                    rightrotate(parent);
                    temp = parent;
                    parent = temp->p;
                }
                leftrotate(grandparent);
                int t = parent->c;
                parent->c = grandparent->c;
                grandparent->c = t;
                temp = parent;
            }
        }
    }
}
void preorder(node head){
    if(head==NULL)
    printf("()");
    if(head!=NULL){
        printf("(");
        if(head->c==0)
        printf("%dB",head->k);
        else printf("%dR",head->k);
        preorder(head->l);
        preorder(head->r);
        printf(")");
    }
}
int main(){
    while(1){
        int i;
        scanf("%d",&i);
        if(getchar()=='e')
        break;
        node t;
        t=createnode(i);
        head=insert(head,t);
        fixup(head,t);
        head->c=0;
        preorder(head);
        printf("\n");
    }
    return 0;
}