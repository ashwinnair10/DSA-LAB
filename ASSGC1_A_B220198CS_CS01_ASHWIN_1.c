#include <stdio.h>
#include <string.h>
int isoperator(char a)
{
    return (a == '(' || a == ')' || a == '*' || a == '/' || a == '+' || a == '-' || a == '%') ? 1 : 0;
}
int check(char *s, int n)
{
    for (int i = n; i > 0; i--)
    {
        if (s[i] == '(' && s[i - 1] == ')')
            return 1;
    }
    return 0;
}
int test(char *s, int n)
{
    int top = -1;
    char stack[1000] = {'\0'};
    for (int i = 0; i < n; i++)
    {
        int t = -1;
        char st[1000] = {'\0'};
        if (isoperator(s[i]))
        {
            stack[++top] = s[i];
            if (stack[top] == ')')
            {
                t = -1;
                while (stack[top] != '(')
                {
                    st[++t] = stack[top];
                    stack[top] = '\0';
                    top--;
                }
                st[++t] = stack[top];
                stack[top] = '\0';
                top--;
                if (check(st, t) == 1)
                    return 1;
            }
        }
    }
    return 0;
}
int main()
{
    char s[1000] = {'\0'};
    int n;
    scanf("%d", &n);
    scanf("%s", s);
    printf("%d\n", test(s, n));
    return 1;
}