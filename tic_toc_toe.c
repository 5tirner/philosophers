#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>


int main()
{

    // game loop
    char *save = 0;
    int checker = 0;
    while (1)
    {
        int opponent_row;
        int opponent_col;
        scanf("%d%d", &opponent_row, &opponent_col);
        int valid_action_count;
        char lkhassm[5];
        lkhassm[0] = (opponent_row + 48);
        lkhassm[1] = ' ';
        lkhassm[2] = (opponent_col + 48);
        lkhassm[3] = '\n';
        lkhassm[4] = '\0';
        scanf("%d", &valid_action_count);
        char **str = (char **)malloc(sizeof(char *) * valid_action_count);
        int j = 0;
        for (int i = 0; i < valid_action_count; i++)
        {
            str[j] = malloc(5);
            int row;
            int col;
            scanf("%d%d", &row, &col);
            str[j][0] = row + 48;
            str[j][1] = ' ';
            str[j][2] = col + 48;
            str[j][3] = '\n';
            str[j][4] = '\0';
            j++;
        }
        str[j] = 0;
        int r = 0, i = 0;
        char *midlle= "1 1\n1 4\n1 7\n4 1\n4 4\n4 7\n7 1\n7 4\n7 7\n";
        char *corner= "0 0\n0 2\n0 3\n0 5\n0 6\n0 8\n2 0\n2 2\n2 3\n2 5\n2 6\n2 8\n3 0\n3 2\n3 3\n3 5\n3 6\n3 8\n5 0\n5 2\n5 3\n5 5\n5 6\n5 8\n6 0\n6 2\n6 3\n6 5\n6 6\n6 8\n8 0\n8 2\n8 3\n8 5\n8 6\n8 8\n";
        char *others= "0 1\n0 4\n0 7\n1 0\n1 2\n1 3\n1 5\n1 6\n1 8\n2 1\n2 4\n2 7\n3 1\n3 4\n3 7\n4 0\n4 2\n4 3\n4 5\n4 6\n4 8\n5 1\n5 4\n5 7\n6 1\n6 4\n6 7\n7 0\n7 2\n7 3\n7 5\n7 6\n7 8\n8 1\n8 4\n8 7\n";
        char *top   = "0 0\n0 1\n0 2\n0 3\n0 4\n0 5\n0 6\n0 7\n0 8\n";
        char *left  = "0 0\n1 0\n2 0\n3 0\n4 0\n5 0\n6 0\n7 0\n8 0\n";
        char *right = "0 8\n1 8\n2 8\n3 8\n4 8\n5 8\n6 8\n7 8\n9 8\n";
        char *last  = "8 0\n8 1\n8 2\n8 3\n8 4\n8 5\n8 6\n8 7\n8 8\n";
        while (str[i])
        {
            if (strstr(top, str[i]) || strstr(left, str[i]) || strstr(right, str[i]) || strstr(last, str[i]))
            {
                printf("%s", str[i]);
                r = 10;
                break;
            }
            i++;
        }
        if (r == 0)
        {
            i = 0;
            while (str[i])
            {
                if (strstr(midlle, str[i]))
                {
                    printf("%s", str[i]);
                    r = 100;
                }
                i++;
            }
        }
        if (r == 0)
        {
            while (str[i])
            {
                i = 0;
                if (strstr(corner, str[i]))
                {
                    printf("%s", str[i]);
                    r = 1000;
                }
                i++;
            }
        }
        if (r == 0)
        {
            while (str[i])
            {
                i = 0;
                if (strstr(others, str[i]))
                {
                    printf("%s", str[i]);
                    //r = 5000;
                    break;
                }
                i++;
            }
        }
        if (r == 0)
            printf("%s", str[0]);
    }
}