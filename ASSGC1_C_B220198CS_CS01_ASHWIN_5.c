#include<stdio.h>
int check(int a[]){
    int c=0;
    for(int i=0;i<1000;i++){
        if(a[i]!=0)
        c++;
    }
    return c;
}
int main(){
    int n,k;
    scanf("%d %d",&n,&k);
    int a[n];
    for(int i=0;i<n;i++){
        scanf("%d",&a[i]);
    }
    int hash[1000];
    for(int i=0;i<1000;i++){
        hash[i]=0;
    }
    for(int i=0;i<k;i++){
        hash[a[i]]++;
    }
    for(int i=1;i<n-k+1;i++){
        printf("%d ",check(hash));
        hash[a[i-1]]--;
        hash[a[i+k-1]]++;
    }
    printf("%d",check(hash));
    return 0;
}