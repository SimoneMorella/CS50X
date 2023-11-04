#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // create input between 1 and 8
    int n;
    do
    {
        n = get_int("Insert height: ");
    }
    while (n < 1 || n > 8);

    // create for nested loop for drawing the pyramid
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (j == n - 1 - i || j > n - 1 - i)
            {
                printf("#");
            }
            else
            {
                printf(" ");
            }
        }
        printf("\n");
    }

}