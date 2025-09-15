#include <stdio.h>
#include <string.h>

int main()
{
    char nonTerminal, newNonTerminal;
    char production[100], part[20][20];
    char prefix[50];
    int i, j, k, n, len, index, minLen;

    printf("Enter the non-terminal: ");
    scanf(" %c", &nonTerminal);

    printf("Enter the production (format: %c=... using | for OR): ", nonTerminal);
    scanf("%s", production);

    len = strlen(production);

    n = 0;
    k = 0;
    for (i = 2; i <= len; i++)
    {
        if (production[i] == '|' || production[i] == '\0')
        {
            part[n][k] = '\0';
            n++;
            k = 0;
        }
        else
        {
            part[n][k++] = production[i];
        }
    }

    strcpy(prefix, part[0]);
    minLen = strlen(prefix);

    for (i = 1; i < n; i++)
    {
        j = 0;
        while (j < strlen(part[i]) && j < strlen(prefix) && part[i][j] == prefix[j])
        {
            j++;
        }
        prefix[j] = '\0';
        if (strlen(prefix) < minLen)
        {
            minLen = strlen(prefix);
        }
    }

    if (strlen(prefix) == 0)
    {
        printf("No Left Factoring needed:\n");
        printf("%c -> ", nonTerminal);
        for (i = 0; i < n; i++)
        {
            printf("%s", part[i]);
            if (i < n - 1)
            {
                printf(" | ");
            }
        }
        printf("\n");
    }
    else
    {
        newNonTerminal = nonTerminal + 1;
        printf("After Left Factoring:\n");
        printf("%c -> %s%c\n", nonTerminal, prefix, newNonTerminal);

        printf("%c -> ", newNonTerminal);
        for (i = 0; i < n; i++)
        {
            index = strlen(prefix);
            if (part[i][index] == '\0')
            {
                printf("ε");
            }
            else
            {
                printf("%s", part[i] + index);
            }
            if (i < n - 1)
            {
                printf(" | ");
            }
        }
        printf("\n");
    }

    return 0;
}