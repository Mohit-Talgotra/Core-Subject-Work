#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_PRODS 50
#define MAX_RHS 20
#define LEN 200
#define NT_LEN 8

typedef struct
{
    char left[NT_LEN];
    char rhs[MAX_RHS][LEN];
    int rhsCount;
} Production;

Production prods[MAX_PRODS];
int prodCount = 0;

char input[200];
int ipos = 0;

void error()
{
    printf("Error at position %d\n", ipos + 1);
}

void match(char c)
{
    if (input[ipos] == c)
    {
        ipos++;
    }
    else
    {
        error();
    }
}

int parseProduction(char *rhs);

int findProdIndex(char *nt)
{
    for (int k = 0; k < prodCount; k++)
    {
        if (strcmp(prods[k].left, nt) == 0)
        {
            return k;
        }
    }
    return -1;
}

int parse(char *nt)
{
    int idx = findProdIndex(nt);
    if (idx == -1)
    {
        return 0;
    }
    for (int m = 0; m < prods[idx].rhsCount; m++)
    {
        int save = ipos;
        if (parseProduction(prods[idx].rhs[m]))
        {
            return 1;
        }
        ipos = save;
    }
    return 0;
}

int parseProduction(char *rhs)
{
    if (strlen(rhs) == 0)
    {
        return 1;
    }

    for (int j = 0; j < (int) strlen(rhs); j++)
    {
        char c = rhs[j];
        if (isupper(c))
        {
            char nt[NT_LEN] = "";
            nt[0] = c;
            nt[1] = '\0';
            if (j + 1 < (int) strlen(rhs) && rhs[j + 1] == '\'')
            {
                nt[1] = '\'';
                nt[2] = '\0';
                j++;
            }
            if (!parse(nt))
            {
                return 0;
            }
        }
        else if (c == 'i' && j + 1 < (int) strlen(rhs) && rhs[j + 1] == 'd')
        {
            if (input[ipos] == 'i' && input[ipos + 1] == 'd')
            {
                ipos += 2;
                j++;
            }
            else
            {
                return 0;
            }
        }
        else
        {
            if (input[ipos] == c)
            {
                ipos++;
            }
            else
            {
                return 0;
            }
        }
    }
    return 1;
}

void makeNewSymbol(char *dest, const char *base, int suffix)
{
    if (strlen(base) + 2 < NT_LEN)
    {
        strcpy(dest, base);
        strcat(dest, "'");
        if (suffix > 0)
        {
            int l = strlen(dest);
            dest[l] = '0' + (suffix % 10);
            dest[l + 1] = '\0';
        }
    }
    else
    {
        strncpy(dest, base, NT_LEN - 2);
        dest[NT_LEN - 2] = '\'';
        dest[NT_LEN - 1] = '\0';
    }
}

int symbolEqualsAt(const char *rhs, int pos, const char *sym)
{
    int sLen = strlen(sym);
    if (pos + sLen > (int) strlen(rhs))
    {
        return 0;
    }
    return strncmp(rhs + pos, sym, sLen) == 0;
}

// remove immediate left recursion for a single production pindex
// may append new productions to prods and update newCount (passed by pointer)
void removeLeftRecursionIndex(int pindex, int *newCount)
{
    Production *p = &prods[pindex];

    char alpha[MAX_RHS][LEN];
    char beta[MAX_RHS][LEN];
    int alphaCount = 0;
    int betaCount = 0;

    for (int j = 0; j < p->rhsCount; j++)
    {
        char *r = p->rhs[j];
        if (symbolEqualsAt(r, 0, p->left))
        {
            strcpy(alpha[alphaCount++], r + strlen(p->left));
        }
        else
        {
            strcpy(beta[betaCount++], r);
        }
    }

    if (alphaCount == 0)
    {
        return;
    }

    Production newP;
    strcpy(newP.left, p->left);
    newP.rhsCount = 0;

    Production newPprime;
    newPprime.rhsCount = 0;

    int suffix = 0;
    char primeName[NT_LEN];
    makeNewSymbol(primeName, p->left, suffix);
    while (findProdIndex(primeName) != -1)
    {
        suffix++;
        makeNewSymbol(primeName, p->left, suffix);
    }
    strcpy(newPprime.left, primeName);

    for (int b = 0; b < betaCount; b++)
    {
        char temp[LEN];
        strncpy(temp, beta[b], LEN - NT_LEN - 1);
        temp[LEN - NT_LEN - 1] = '\0';
        int l = strlen(temp);
        strncat(temp, newPprime.left, LEN - l - 1);
        strcpy(newP.rhs[newP.rhsCount++], temp);
    }

    for (int a = 0; a < alphaCount; a++)
    {
        char temp[LEN];
        strncpy(temp, alpha[a], LEN - NT_LEN - 1);
        temp[LEN - NT_LEN - 1] = '\0';
        int l = strlen(temp);
        strncat(temp, newPprime.left, LEN - l - 1);
        strcpy(newPprime.rhs[newPprime.rhsCount++], temp);
    }

    strcpy(newPprime.rhs[newPprime.rhsCount++], ""); // epsilon

    *p = newP;
    prods[*newCount] = newPprime;
    (*newCount)++;
}

int main()
{
    printf("Enter number of productions: ");
    int initialCount = 0;
    if (scanf("%d", &initialCount) != 1)
    {
        return 0;
    }

    printf("Enter productions (use | for multiple and id for identifiers):\n");
    for (int k = 0; k < initialCount; k++)
    {
        char line[LEN];
        scanf("%s", line);
        prods[k].rhsCount = 0;
        // left side may be of form E or E' but user gives uppercase single letter usually
        int pos = 0;
        // read left as contiguous up to '->'
        while (line[pos] != '-' && line[pos] != '\0')
        {
            pos++;
        }
        if (pos == 0 || line[pos] != '-')
        {
            return 0;
        }
        // copy left
        int l = pos;
        if (l >= NT_LEN)
        {
            l = NT_LEN - 1;
        }
        strncpy(prods[k].left, line, l);
        prods[k].left[l] = '\0';

        char *rhs = strtok(line + pos + 2, "|");
        while (rhs != NULL)
        {
            strcpy(prods[k].rhs[prods[k].rhsCount++], rhs);
            rhs = strtok(NULL, "|");
        }
    }
    prodCount = initialCount;

    int newCount = prodCount;
    for (int k = 0; k < prodCount; k++)
    {
        removeLeftRecursionIndex(k, &newCount);
    }
    prodCount = newCount;

    printf("\nGrammar after removing left recursion:\n");
    for (int k = 0; k < prodCount; k++)
    {
        printf("%s -> ", prods[k].left);
        for (int r = 0; r < prods[k].rhsCount; r++)
        {
            if (r > 0) printf(" | ");
            if (strlen(prods[k].rhs[r]) == 0)
            {
                printf("ε");
            }
            else
            {
                printf("%s", prods[k].rhs[r]);
            }
        }
        printf("\n");
    }

    printf("Enter input string: ");
    scanf("%s", input);
    ipos = 0;

    char start[NT_LEN];
    strcpy(start, prods[0].left);

    if (parse(start) && input[ipos] == '\0')
    {
        printf("Parsing successful\n");
    }
    else
    {
        printf("Parsing failed\n");
    }

    return 0;
}
