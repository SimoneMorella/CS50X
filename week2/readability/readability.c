#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
int count_letters(string text);
int count_words(string text);
int count_sentences(string text);

int main(void)
{
    string text = get_string("Text: ");
    printf("%s\n", text);
    int letters = count_letters(text);
    int words = count_words(text);
    int sentences = count_sentences(text);
    float L = (float) letters / (float) words * 100.0;
    float S = (float) sentences / (float) words * 100.0;
    int index = round(0.0588 * L - 0.296 * S - 15.8);
    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", index);
    }
}

int count_letters(string text)
{
    int countL = 0;
    for (int i = 0; i < strlen(text); i++)
    {
        if ((text[i] >= 'a' && text[i] <= 'z') || (text[i] >= 'A' && text[i] <= 'Z'))
        {
            countL++;
        }
    }
    return countL;
}

int count_words(string text)
{
    int countW = 1;
    for (int i = 0; i < strlen(text); i++)
    {
        if (text[i] == ' ' && (text[i + 1] >= 33 && text[i + 1] <= 126))
            // trial with int for including also symbols, idk if it is worth it.
        {
            countW++;
        }
    }
    return countW;
}

int count_sentences(string text)
{
    int countS = 0;
    for (int i = 0; i < strlen(text); i++)
    {
        if ((text[i] == '.' || text[i] == '!' || text[i] == '?')\
            && ((text[i - 1] >= 'a' && text[i - 1] <= 'z') || (text[i - 1] >= 'A' && text[i - 1] <= 'Z')))
        {
            countS++;
        }
    }
    return countS;
}