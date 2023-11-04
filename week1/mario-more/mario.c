#include <cs50.h>
#include <stdio.h>

int main(void)
{
    //set the height prompt
    int height;
    do
    {
        height = get_int("type the height: ");
    }
    while (height < 1 || height > 8);
    //for nested loop with i and j to define how to form the pyramid
    for (int i = 0; i < height ; i++)
    {
        for (int j = 0; j < height * 2 + 2 ; j++)
        {
            if (j < height - i - 1 || j == height || j == height + 1 || j > height + i + 2)
            {
                printf(" ");
            }
            else
            {
                printf("#");
            }
        }
        printf("\n");
    }
    //print everything

}