#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<limits.h>
#include<ctype.h>
#include<math.h>
int isprime(int a){
    double sqroot=sqrt(a); 
    for(int i=2;i<=sqroot;i++) 
    if(a%i==0)
    return 0; 
    return 1;
}
void linear(int a[],int n){
    int collision=0,opc=0,count=0;
    int op[n];
    int *hash=malloc(n*sizeof(int));
    if(hash==NULL)
    exit(1);
    for(int i=0;i<n;i++)
    hash[i]=-1;
    for(int i=0;i<n;i++){
        if(a[i]==INT_MIN)
        continue;
        count++;
        int index=a[i]%n;
        if(hash[index]==a[i])
        continue;
        if(hash[index]==-1){
            hash[index]=a[i];
            op[opc++]=index;
        }
        else{
            for(int j=(index+1)%n;j!=index;j=(j+1)%n){
                collision++;
                if(hash[j]==-1||hash[index]==a[i]){
                    hash[j]=a[i];
                    op[opc++]=j;
                    break;
                }
            }
        }
    }
    for(int i=0;i<count;i++){
        printf("%d ",op[i]);
    }
    printf("\n%d\n",collision);
}
void quadratic(int a[],int n){
    int collision=0,opc=0,count=0;
    int op[n];
    int *hash=malloc(n*sizeof(int));
    if(hash==NULL)
    exit(1);
    for(int i=0;i<n;i++)
    hash[i]=-1;
    for(int i=0;i<n;i++){
        if(a[i]==INT_MIN)
        continue;
        count++;
        int index=a[i]%n;
        if(hash[index]==a[i])
        continue;
        if(hash[index]==-1){
            hash[index]=a[i];
            op[opc++]=index;
        }
        else{
            int k=1;
            for(int j=(index+(k*k))%n;j!=index;j=(index+(k*k))%n){
                collision++;
                if(hash[j]==-1||hash[index]==a[i]){
                    hash[j]=a[i];
                    op[opc++]=j;
                    break;
                }
                k++;
            }
        }
    }
    for(int i=0;i<count;i++){
        printf("%d ",op[i]);
    }
    printf("\n%d\n",collision);
}
void dprobe(int a[],int n){
    int collision=0,opc=0,count=0,r;
    for(int i=n-1;i>1;i--){
        if(isprime(i)){
            r=i;
            break;
        }
    }
    int op[n];
    int *hash=malloc(n*sizeof(int));
    if(hash==NULL)
    exit(1);
    for(int i=0;i<n;i++)
    hash[i]=-1;
    for(int i=0;i<n;i++){
        if(a[i]==INT_MIN)
        continue;
        count++;
        int index=a[i]%n;
        if(hash[index]==a[i])
        continue;
        if(hash[index]==-1){
            hash[index]=a[i];
            op[opc++]=index;
        }
        else{
            int j=1;
            while(1){
                collision++;
                int test=(index+j*(r-(a[i]%r)))%n;
                if(hash[test]==-1||hash[index]==a[i]){
                    hash[test]=a[i];
                    op[opc++]=test;
                    break;
                }
                j++;
            }
        }
    }
    for(int i=0;i<count;i++){
        printf("%d ",op[i]);
    }
    printf("\n%d\n",collision);
}
int main(){
    int n;
    scanf("%d",&n);
    int arr[n];
    for(int i=0;i<n;i++)
    arr[i]=INT_MIN;
    for(int i=0;i<n;i++){
        scanf("%d",&arr[i]);
        if(getchar()=='\n')
        break;
    }
    linear(arr,n);
    quadratic(arr,n);
    dprobe(arr,n);
    return 0;
}
