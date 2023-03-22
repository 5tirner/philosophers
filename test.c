#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>


int main()
{

    // game loop
	int	**board = (int **)malloc(sizeof(int *) * 9);
	int l = 0;
	while (l < 9)
	{
		int j = 0;
		board[l] = malloc(sizeof(int) * 9);
		while (j < 9)
		{
			board[l][j] = 8;
			j++;
		}
		l++;
	}
    while (1)
    {
        int vs1;
        int vs2;
        scanf("%d%d", &vs1, &vs2);
        int valid_action_count;
        scanf("%d", &valid_action_count);
        for (int i = 0; i < valid_action_count; i++)
        {
            int row;
            int col;
            scanf("%d%d", &row, &col);
        }
        int r = 0;
        board[vs1][vs2] = 0;
        int i = 0;
        while (i < 9)
        {
            int j = 0;
            while (j < 9)
            {
                if (board[i][j] == 8)
                {
                    board[i][j] = 1;
                    printf("%d %d\n", i, j);
                    r = 11;
                    break;
                }
                j++;
            }
            if (r == 11)
                break;
            i++;
        }
    }
}