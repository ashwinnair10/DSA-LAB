#include <stdio.h>
#include <string.h>
#include <limits.h>
struct node
{
    char name[1000];
    char at[6];
    int p;
};
typedef struct node node;
void maxheapify(node a[], int *heapsize, int i)
{
    int l = i;
    int lc = 2 * i + 1;
    int rc = 2 * i + 2;
    if (lc < *heapsize && (a[lc].p > a[l].p || (a[lc].p == a[l].p && strcmp(a[lc].at, a[l].at) < 0)))
        l = lc;
    if (rc < *heapsize && (a[rc].p > a[l].p || (a[rc].p == a[l].p && strcmp(a[rc].at, a[l].at) < 0)))
        l = rc;
    if (l != i)
    {
        node temp = a[i];
        a[i] = a[l];
        a[l] = temp;
        maxheapify(a, heapsize, l);
    }
}
void buildmaxheap(node a[], int *heapsize)
{
    for (int i = (*heapsize) / 2 - 1; i >= 0; i--)
        maxheapify(a, heapsize, i);
}
void admitPatient(node a[], int *heapsize, char name[], int p, char at[])
{
    (*heapsize)++;
    strcpy(a[*heapsize - 1].name, name);
    strcpy(a[*heapsize - 1].at, at);
    a[*heapsize - 1].p = p;
    buildmaxheap(a, heapsize);
}
void treatNextPatient(node a[], int *heapsize)
{
    if (*heapsize == 0)
    {
        printf("-1\n");
        return;
    }
    printf("%s %d %s\n", a[0].name, a[0].p, a[0].at);
    a[0] = a[*heapsize - 1];
    (*heapsize)--;
    buildmaxheap(a, heapsize);
}
void checkNextPatient(node a[], int *heapsize)
{
    if (*heapsize == 0)
    {
        printf("-1\n");
        return;
    }
    printf("%s %d %s\n", a[0].name, a[0].p, a[0].at);
}
void dischargePatient(node a[], int *heapsize, char name[], char at[])
{
    if (*heapsize == 0)
    {
        printf("-1\n");
        return;
    }
    for (int i = 0; i < *heapsize; i++)
    {
        if (strcmp(a[i].name, name) == 0 && strcmp(a[i].at, at) == 0)
        {
            for (int j = i + 1; j < *heapsize; j++)
                a[j - 1] = a[j];
            (*heapsize)--;
            buildmaxheap(a, heapsize);
            return;
        }
    }
    printf("-1\n");
    return;
}
void updateConditionSeverity(node a[], int *heapsize, char name[], char at[], int p)
{
    if (*heapsize == 0)
    {
        printf("-1\n");
        return;
    }
    for (int i = 0; i < *heapsize; i++)
    {
        if (strcmp(a[i].name, name) == 0 && strcmp(a[i].at, at) == 0)
        {
            a[i].p = p;
            buildmaxheap(a, heapsize);
            return;
        }
    }
    printf("-1\n");
    return;
}
void printAllPatients(node a[], int *heapsize)
{
    if (*heapsize == 0)
    {
        printf("-1\n");
        return;
    }
    for (int i = (*heapsize) - 1; i > 0; i--)
    {
        node temp = a[0];
        a[0] = a[i];
        a[i] = temp;
        maxheapify(a, &i, 0);
    }
    for (int i = *heapsize - 1; i > -1; i--)
        printf("%s %d %s\n", a[i].name, a[i].p, a[i].at);
    buildmaxheap(a, heapsize);
}
int main()
{
    char c[2] = {'\0'};
    node a[1000];
    int heapsize = 0;
    while (1)
    {
        scanf("%s", c);
        c[1] = '\0';
        if (strcmp(c, "a") == 0)
        {
            char name[1000] = {'\0'}, at[6] = {'\0'};
            scanf("%s %d %s", name, &a[heapsize].p, at);
            admitPatient(a, &heapsize, name, a[heapsize].p, at);
        }
        if (strcmp(c, "t") == 0)
        {
            treatNextPatient(a, &heapsize);
        }
        if (strcmp(c, "c") == 0)
        {
            checkNextPatient(a, &heapsize);
        }
        if (strcmp(c, "d") == 0)
        {
            char name[1000] = {'\0'}, at[6] = {'\0'};
            scanf("%s %s", name, at);
            dischargePatient(a, &heapsize, name, at);
        }
        if (strcmp(c, "u") == 0)
        {
            char name[1000] = {'\0'}, at[6] = {'\0'};
            int p;
            scanf("%s %s %d", name, at, &p);
            updateConditionSeverity(a, &heapsize, name, at, p);
        }
        if (strcmp(c, "p") == 0)
        {
            printAllPatients(a, &heapsize);
        }
        if (strcmp(c, "e") == 0)
        {
            break;
        }
    }
    return 0;
}
