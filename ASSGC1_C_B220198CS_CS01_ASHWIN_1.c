#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int search(int hash[],int n,int k){
    if(n==0)
    return 0;
    if(hash[k%n]==k){
        hash[k % n]=-1;
        return 1;
    }
    for(int i=((k%n)+1)%n;i!=k%n;i=(i+1)%n)
        if(hash[i]==k){
            hash[i]=-1;
            return 1;
        }
    return 0;
}
int *hashmap(int a[],int n){
    int *hash=malloc(n*sizeof(int));
    if(hash==NULL)
    exit(1);
    for(int i=0;i<n;i++)
    hash[i]=-1;
    for(int i=0;i<n;i++){
        int index=a[i]%n;
        if(hash[index]==a[i])
        continue;
        if(hash[index]==-1)
        hash[index]=a[i];
        else{
            for(int j=(index+1)%n;j!=index;j=(j+1)%n)
                if(hash[j]==-1||hash[index]==a[i]){
                    hash[j]=a[i];
                    break;
                }
        }
    }
    return hash;
}
void unionab(int a[],int b[],int m,int n){
    if(m==0&&n==0){
        printf("-1\n");
        return;
    }
   int *hasha=hashmap(a,m),*ah=hashmap(a,m),*hashb=hashmap(b,n),*bh=hashmap(b,n);
    for(int i=0;i<m;i++)
    if(search(hasha,m,a[i]))
    printf("%d ",a[i]);
    for(int i=0;i<n;i++)
    if(search(hashb,n,b[i]))
    if(!search(ah,m,b[i]))
    printf("%d ",b[i]);
    printf("\n");
    free(hasha),free(ah),free(hashb),free(bh);
}
void intersectab(int a[],int b[],int m,int n){
    if(m==0||n==0){
        printf("-1\n");
        return;
    }
    int *hasha=hashmap(a,m),*ah=hashmap(a,m),*hashb=hashmap(b,n),*bh=hashmap(b,n);
    for(int i=0;i<m;i++)
    if(search(hasha,m,a[i]))
    if(search(bh,n,a[i]))
    printf("%d ",a[i]);
    printf("\n");
    free(hasha),free(ah),free(hashb),free(bh);
}
void setdiffab(int a[],int b[],int m,int n){
    if(m==0&&n==0){
        printf("-1\n");
        return;
    }
    int *hasha=hashmap(a,m),*ah=hashmap(a,m),*hashb=hashmap(b,n),*bh=hashmap(b,n);
    int flag=0;
    for(int i=0;i<m;i++)
    if(search(hasha,m,a[i]))
    if(!search(hashb,n,a[i])){
        printf("%d ",a[i]);
        flag++;
    }
    if(!flag)
    printf("-1");
    printf("\n");
    free(hasha),free(ah),free(hashb),free(bh);
}
int main(){
    int m,n;
    scanf("%d %d",&m,&n);
    int a[m],b[n];
    for(int i=0;i<m;i++)
    scanf("%d",&a[i]);
    for(int i=0;i<n;i++)
    scanf("%d",&b[i]);
    char ch[2]={'\0'},ip1[2],ip2[2];
    while(1){
        scanf("%s",ch);
        ch[1]='\0';
        if(strcmp(ch,"u")==0){
            scanf("%s %s",ip1,ip2);
            ip1[1]='\0',ip2[1]='\0';
            if(strcmp(ip1,"A")==0&&strcmp(ip2,"B")==0)
            unionab(a,b,m,n);
            if(strcmp(ip1,"B")==0&&strcmp(ip2,"A")==0)
            unionab(b,a,n,m);
        }
        if(strcmp(ch,"i")==0){
            scanf("%s %s",ip1,ip2);
            ip1[1]='\0',ip2[1]='\0';
            if(strcmp(ip1, "A") == 0 && strcmp(ip2, "B") == 0)
            intersectab(a,b,m,n);
            if(strcmp(ip1, "B") == 0 && strcmp(ip2, "A") == 0)
            intersectab(b,a,n,m);
        }
        if (strcmp(ch,"s")==0){
            scanf("%s %s",ip1,ip2);
            ip1[1]='\0',ip2[1]='\0';
            if(strcmp(ip1,"A")==0&&strcmp(ip2,"B")==0)
            setdiffab(a,b,m,n);
            if(strcmp(ip1,"B")==0&&strcmp(ip2,"A")==0)
            setdiffab(b,a,n,m);
        }
        if(strcmp(ch,"e")==0)
        break;
    }
    return 0;
}