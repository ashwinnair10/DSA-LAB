#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
struct node{
    char name[100];
    char roll[100];
    int age;
    struct node* next;
};
char *strlwr(char *str){
  unsigned char *p=(unsigned char *)str;
  while(*p){
     *p=tolower((unsigned char)*p);
      p++;
  }
  return str;
}
typedef struct node* node;
node createnode(char name[],char roll[],int age){
    node temp=(node)malloc(sizeof(struct node));
    strcpy(temp->name,name);
    strcpy(temp->roll,roll);
    temp->age=age;
    temp->next=NULL;
    return temp;
}
int indexer(char name[],int age){
    int s=0;
    for(int i=0;i<strlen(name);i++)
    s+=name[i];
    return (s+age)%4;
}
void insert(node hash[],node person){
    int index=indexer(person->name,person->age);
    if(hash[index]==NULL){
        hash[index]=person;
        return;
    }
    else{
        node temp=hash[index];
        while(temp!=NULL&&temp->next!=NULL)
        temp=temp->next;
        temp->next=person;
        return;
    }
}
void printindex(node hash[],int c){
    int count=0;
    node temp=hash[c];
    while(temp!=NULL){
        count++;
        temp=temp->next;
    }
    printf("%d ",count);
    temp=hash[c];
    while(temp!=NULL){
        printf("%s ",temp->name);
        temp=temp->next;
    }
    printf("\n");
    return;
}
void printbranch(node hash[],int c,char branch[]){
    node temp=hash[c];
    int flag=0;
    while(temp!=NULL){
        char ch[3]={'\0'};
        ch[0]=temp->roll[strlen(temp->roll)-2];
        ch[1]=temp->roll[strlen(temp->roll)-1];
        ch[2]='\0';
        if(strcmp(strlwr(ch),strlwr(branch))==0){
            printf("%s ",temp->name);
            flag++;
        }
        temp=temp->next;
    }
    if(!flag)
    printf("-1");
    printf("\n");
    return;
}
int main(){
    int n,age;
    char name[100],roll[100];
    scanf("%d",&n);
    node hash[4]={NULL,NULL,NULL,NULL};
    for(int i=0;i<n;i++){
        scanf("%s %s %d",name,roll,&age);
        node person=createnode(name,roll,age);
        insert(hash,person);
    }
    while(1){
        char ch[2]={'\0'};
        scanf("%s",ch);
        if(strcmp(ch,"c")==0){
            int c;
            scanf("%d",&c);
            printindex(hash,c);
        }
        if(strcmp(ch,"0")==0||strcmp(ch,"1")==0||strcmp(ch,"2")==0||strcmp(ch,"3")==0){
            char branch[3]={'\0'};
            int i;
            scanf("%s",branch);
            branch[2]='\0';
            printbranch(hash,atoi(ch),branch);
        }
        if(strcmp(ch,"e")==0)
        break;
    }
    return 0;
}