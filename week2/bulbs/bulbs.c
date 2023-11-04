#include <cs50.h>
#include <stdio.h>
#include <string.h>

const int BITS_IN_BYTE = 8;

void print_bulb(int bit);

int main(void)
{
    // TODO
    string text = get_string("Message: ");
    int n;
    int module;
    int bin_array[BITS_IN_BYTE];
    for (int i = 0; i < strlen(text); i++)
    {
        n = text[i];
        for (int j = BITS_IN_BYTE - 1; j >= 0; j--)
        {
            module = n % 2;
            n /= 2;
            if (module == 0)
            {
                bin_array[j] = 0;
            }
            else if (module == 1)
            {
                bin_array[j] = 1;
            }
        }
        for (int loop = 0; loop < BITS_IN_BYTE; loop++)
        {
            print_bulb(bin_array[loop]);
        }
        printf("\n");
    }
}

void print_bulb(int bit)
{
    if (bit == 0)
    {
        // Dark emoji
        printf("\U000026AB");
    }
    else if (bit == 1)
    {
        // Light emoji
        printf("\U0001F7E1");
    }
}