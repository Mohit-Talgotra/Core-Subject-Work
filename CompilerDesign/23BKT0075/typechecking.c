#include <stdio.h>
#include <ctype.h>

//23BKT0075 Mohit Talgotra

#define INT 1
#define FLOAT 2

int main()
{
    char expr[50], vars[50], ops[50];
    int type[128] = {0};
    int nVars = 0, nOps = 0;
    int choice, ok = 1, hasDiv = 0;
    printf("Enter expression: ");
    scanf("%49s", expr);
    if (!isalpha(expr[0]) || expr[1] != '=')
    {
        printf("Error: Invalid expression format.\n");
        return 1;
    }
    char resVar = expr[0];
    for (int i = 2; expr[i]; i++)
    {
        char c = expr[i];
        if (isalpha(c))
        {
            vars[nVars++] = c;
        }
        else if (c == '+' || c == '-' || c == '*' || c == '/')
        {
            ops[nOps++] = c;
        }
    }
    if (nVars < 2 || nOps != nVars - 1)
    {
        printf("Error: Invalid expression format.\n");
        return 1;
    }
    if (type[(int) resVar] == 0)
    {
        printf("Enter data type for %c (1=int, 2=float): ", resVar);
        scanf("%d", &choice);
        while (choice != INT && choice != FLOAT)
        {
            printf("Enter 1 or 2: ");
            scanf("%d", &choice);
        }
        type[(int) resVar] = choice;
    }
    for (int i = 0; i < nVars; i++)
    {
        char v = vars[i];
        if (type[(int) v] == 0)
        {
            printf("Enter data type for %c (1=int, 2=float): ", v);
            scanf("%d", &choice);
            while (choice != INT && choice != FLOAT)
            {
                printf("Enter 1 or 2: ");
                scanf("%d", &choice);
            }
            type[(int) v] = choice;
        }
    }
    for (int i = 0; i < nOps; i++)
    {
        if (ops[i] == '/')
        {
            hasDiv = 1;
            char left = vars[i], right = vars[i + 1];
            if (type[(int) left] != FLOAT || type[(int) right] != FLOAT)
            {
                printf("Error: operands of '/' must be float.\n");
                ok = 0;
            }
        }
    }
    int curr = type[(int) vars[0]];
    for (int i = 0; i < nOps; i++)
    {
        int next = type[(int) vars[i + 1]];
        if (ops[i] == '/' || curr == FLOAT || next == FLOAT)
        {
            curr = FLOAT;
        }
        else
        {
            curr = INT;
        }
    }
    if (curr != type[(int) resVar])
    {
        printf("Error: cannot store result in %c (type mismatch).\n", resVar);
        ok = 0;
    }
    printf("Expression %s -> data %scompatible\n", expr, ok ? "" : "not ");
    if (hasDiv)
    {
        printf("Expression with division\n");
    }
    return ok ? 0 : 1;
}