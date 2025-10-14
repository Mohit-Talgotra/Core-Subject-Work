#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX 50

char productions[20][MAX];
int n;

void add(char *arr, char c)
{
    for (int i = 0; i < strlen(arr); i++)
    {
        if (arr[i] == c)
        {
            return;
        }
    }
    int l = strlen(arr);
    arr[l] = c;
    arr[l + 1] = '\0';
}

void findFirst(char *res, char c)
{
    if (!isupper(c))
    {
        add(res, c);
        return;
    }
    for (int i = 0; i < n; i++)
    {
        if (productions[i][0] == c)
        {
            if (productions[i][3] == '#')
            {
                add(res, '#');
            }
            else
            {
                for (int j = 3; j < strlen(productions[i]); j++)
                {
                    char sym = productions[i][j];
                    char temp[MAX] = "";
                    findFirst(temp, sym);
                    int hasEps = 0;
                    for (int k = 0; k < strlen(temp); k++)
                    {
                        if (temp[k] == '#')
                        {
                            hasEps = 1;
                        }
                        else
                        {
                            add(res, temp[k]);
                        }
                    }
                    if (!hasEps)
                    {
                        break;
                    }
                    if (hasEps && j == strlen(productions[i]) - 1)
                    {
                        add(res, '#');
                    }
                }
            }
        }
    }
}

void findFollow(char *res, char c)
{
    if (c == productions[0][0])
    {
        add(res, '$');
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = 3; j < strlen(productions[i]); j++)
        {
            if (productions[i][j] == c)
            {
                if (j + 1 < strlen(productions[i]))
                {
                    char temp[MAX] = "";
                    findFirst(temp, productions[i][j + 1]);
                    int hasEps = 0;
                    for (int k = 0; k < strlen(temp); k++)
                    {
                        if (temp[k] == '#')
                        {
                            hasEps = 1;
                        }
                        else
                        {
                            add(res, temp[k]);
                        }
                    }
                    if (hasEps)
                    {
                        char temp2[MAX] = "";
                        findFollow(temp2, productions[i][0]);
                        for (int k = 0; k < strlen(temp2); k++)
                        {
                            add(res, temp2[k]);
                        }
                    }
                }
                else
                {
                    if (productions[i][0] != c)
                    {
                        char temp[MAX] = "";
                        findFollow(temp, productions[i][0]);
                        for (int k = 0; k < strlen(temp); k++)
                        {
                            add(res, temp[k]);
                        }
                    }
                }
            }
        }
    }
}

void printSet(char *label, char nt, char *set)
{
    printf("%s(%c) = { ", label, nt);
    for (int i = 0; i < strlen(set); i++)
    {
        printf("%c", set[i]);
        if (i != strlen(set) - 1)
        {
            printf(", ");
        }
    }
    printf(" }\n");
}

int main()
{
    printf("Enter number of productions: ");
    scanf("%d", &n);
    printf("Enter productions (use | for multiple and # for epsilon):\n");
    char input[MAX];
    int count = 0;
    for (int i = 0; i < n; i++)
    {
        scanf("%s", input);
        char left = input[0];
        char *rhs = strtok(input + 3, "|");
        while (rhs != NULL)
        {
            productions[count][0] = left;
            productions[count][1] = '-';
            productions[count][2] = '>';
            strcpy(productions[count] + 3, rhs);
            count++;
            rhs = strtok(NULL, "|");
        }
    }
    n = count;

    char done[20] = "";
    printf("\nFIRST sets:\n");
    for (int i = 0; i < n; i++)
    {
        char nt = productions[i][0];
        if (strchr(done, nt) == NULL)
        {
            char temp[MAX] = "";
            findFirst(temp, nt);
            printSet("FIRST", nt, temp);
            add(done, nt);
        }
    }

    strcpy(done, "");
    printf("\nFOLLOW sets:\n");
    for (int i = 0; i < n; i++)
    {
        char nt = productions[i][0];
        if (strchr(done, nt) == NULL)
        {
            char temp[MAX] = "";
            findFollow(temp, nt);
            printSet("FOLLOW", nt, temp);
            add(done, nt);
        }
    }
    return 0;
}