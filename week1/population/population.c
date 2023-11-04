#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // TODO: Prompt for start size
    int s_size;
    do
    {
        s_size = get_int("starting size: ");
    }
    while (s_size < 9);

    // TODO: Prompt for end size
    int e_size;
    do
    {
        e_size = get_int("ending size: ");
    }
    while (e_size < s_size);

    // TODO: Calculate number of years until we reach threshold
    int n = 0;
    while (s_size < e_size)
    {
        s_size += s_size / 3 - s_size / 4;
        n++;

    }

    // TODO: Print number of years
    printf("Years: %i\n", n);
}
