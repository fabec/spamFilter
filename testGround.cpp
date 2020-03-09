#include <stdio.h>
#include <math.h>
#include <string.h>

int d[100][100];

int main()
{
    int i, j, m, n, temp, tracker;
    char s[] = "Sanfoundry";
    char t[] = "Education";
    m = strlen(s);
    n = strlen(t);

    for (i = 0; i <= m; i++)
        d[0][i] = i;

    for (j = 0; j <= n; j++)
        d[j][0] = j;

    for (j = 1; j <= m; j++)
    {
        for (i = 1; i <= n; i++)
        {
            if (s[i - 1] == t[j - 1])
            {
                tracker = 0;
            }
            else
            {
                tracker = 1;
            }
        }
    }

    printf("the Levinstein distance is %d\n", d[n][m]);

    return 0;
}