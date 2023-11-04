#include <cs50.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
bool only_digits(string text);
char rotate(char c, int n);
bool check;
int digit;
char encrypted;
int main(int argc, string argv[])
{
    // put the input of the key as a command line --- just 1 key as argv --
    if (argc == 2)
    {
        check = only_digits(argv[1]);
        if (check == false)
        {
            printf("Usage: ./caesar key\n");
            return 1;
        }
        else
        {
            digit = atoi(argv[1]); // from string to int for the key
            string plaintext = get_string("plaintext: "); // user input of plaintext
            printf("ciphertext: ");
            for (int i = 0; i < strlen(plaintext); i++) // user output of plaintext and ciphertext
            {
                encrypted = rotate(plaintext[i], digit);
                printf("%c", encrypted);
            }
            printf("\n");
            return 0;
        }
    }
    else
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    // make sure to define all the errors (more than 1 key, key different from digits)


}
bool only_digits(string text)
{
    int count = 0;
    for (int i = 0; i < strlen(text); i++)
    {
        if (text[i] >= 48 && text[i] <= 57)
        {
            count++;
        }
    }
    if (count == strlen(text))
    {
        return true;
    }
    else
    {
        return false;
    }
}

char rotate(char c, int n)
{
    char crypt;
    if (c >= 65 && c <= 90)
    {
        crypt = (((int) c - 65 + n) % 26 + 65);
    }
    else if (c >= 97 && c <= 122)
    {
        crypt = (((int) c - 97 + n) % 26 + 97);
    }
    else
    {
        crypt = c;
    }
    return crypt;
}