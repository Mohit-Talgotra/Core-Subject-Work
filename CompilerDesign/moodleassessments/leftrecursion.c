#include <stdio.h>
#include <string.h>

int main()
{
    char nonTerminal, newNonTerminal;
    char production[100], part[20][20];
    char alpha[20][20], beta[20][20];
    int i, j, k, n, len, aCount = 0, bCount = 0;

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

    for (i = 0; i < n; i++)
    {
        if (part[i][0] == nonTerminal)
        {
            for (j = 1; part[i][j] != '\0'; j++)
            {
                alpha[aCount][j - 1] = part[i][j];
            }
            alpha[aCount][j - 1] = '\0';
            aCount++;
        }
        else
        {
            strcpy(beta[bCount++], part[i]);
        }
    }

    newNonTerminal = nonTerminal + 1;

    printf("After removing left recursion:\n");

    printf("%c -> ", nonTerminal);
    for (i = 0; i < bCount; i++)
    {
        printf("%s%c", beta[i], newNonTerminal);
        if (i < bCount - 1)
        {
            printf(" | ");
        }
    }
    printf("\n");

    printf("%c -> ", newNonTerminal);
    for (i = 0; i < aCount; i++)
    {
        printf("%s%c", alpha[i], newNonTerminal);
        if (i < aCount - 1)
        {
            printf(" | ");
        }
    }
    printf(" | ε\n");
    return 0;
}