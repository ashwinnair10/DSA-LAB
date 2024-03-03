#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct node
{
    int k;
    struct node *next;
};
struct tnode
{
    int k;
    struct tnode *left;
    struct tnode *right;
};
typedef struct tnode *tnode;
typedef struct node *node;
tnode createtnode(int k)
{
    tnode temp = (struct tnode *)malloc(sizeof(struct tnode));
    temp->k = k;
    temp->left = NULL;
    temp->right = NULL;
    return temp;
}
tnode inserttree(tnode head, int k)
{
    tnode t = createtnode(k);
    tnode temp = head;
    if (head == NULL)
        return t;
    while (temp != NULL)
    {
        if (k >= temp->k)
        {
            if (temp->right == NULL)
            {
                temp->right = t;
                return head;
            }
            else
                temp = temp->right;
        }
        else
        {
            if (temp->left == NULL)
            {
                temp->left = t;
                return head;
            }
            else
                temp = temp->left;
        }
    }
    return head;
}
tnode search(tnode head, int k)
{
    if (head == NULL || head->k == k)
        return head;
    else if (head->k > k)
        return search(head->left, k);
    else
        return search(head->right, k);
}
node createnode(int k)
{
    node temp = (struct node *)malloc(sizeof(struct node));
    temp->k = k;
    temp->next = NULL;
    return temp;
}
node insert(node head, int k)
{
    node t = createnode(k);
    node temp = head;
    if (temp == NULL)
        return t;
    while (temp->next != NULL)
        temp = temp->next;
    temp->next = t;
    return head;
}
node delete(node head, int i)
{
    if(head==NULL){
        printf("-1\n");
        return head;
    }
    if (i == 1)
    {
        head = head->next;
        return head;
    }
    else
    {
        int j = 1;
        node temp = head;
        while (temp->next != NULL && j != i - 1)
        {
            temp = temp->next;
            j++;
        }
        if (temp->next != NULL)
        {
            printf("%d\n", temp->next->k);
            temp->next = temp->next->next;
        }
        else
            printf("-1\n");
        return head;
    }
}
void print(node head)
{
    node temp = head;
    if (head == NULL)
    {
        printf("-1\n");
        return;
    }
    while (temp != NULL)
    {
        printf("%d ", temp->k);
        temp = temp->next;
    }
    printf("\n");
    return;
}
node dup(node head)
{
    tnode t = NULL;
    if (head == NULL)
    {
        printf("-1\n");
        return head;
    }
    node temp = head;
    node result = NULL;
    while (temp != NULL)
    {
        if (search(t, temp->k) == NULL)
        {
            t = inserttree(t, temp->k);
            result = insert(result, temp->k);
        }
        temp = temp->next;
    }
    print(result);
    return result;
}
node reverse(node head)
{
    node prev = NULL;
    node current = head;
    node next = NULL;
    while (current != NULL)
    {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    return prev;
}
void palindrome(node head)
{
    if (head == NULL)
    {
        printf("-1\n");
        return;
    }
    node t = NULL, temp = head;
    while (temp != NULL)
    {
        t = insert(t, temp->k);
        temp = temp->next;
    }
    node rev = reverse(t);
    temp = head;
    while (rev != NULL && temp != NULL)
    {
        if (rev->k != temp->k)
        {
            printf("N\n");
            return;
        }
        rev = rev->next;
        temp = temp->next;
    }
    printf("Y\n");
    return;
}
int main()
{
    node head = NULL;
    char a[2];
    while (1)
    {
        scanf("%s", a);
        a[1] = '\0';
        if (strcmp(a, "a") == 0)
        {
            int k;
            scanf("%d", &k);
            head = insert(head, k);
        }
        if (strcmp(a, "r") == 0)
        {
            int i;
            scanf("%d", &i);
            head = delete (head, i);
        }
        if (strcmp(a, "d") == 0)
            head = dup(head);
        if (strcmp(a, "p") == 0)
            palindrome(head);
        if (strcmp(a, "s") == 0)
            print(head);
        if (strcmp(a, "e") == 0)
            break;
    }
    return 1;
}