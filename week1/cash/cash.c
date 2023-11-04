#include <cs50.h>
#include <stdio.h>

int get_cents(void);
int calculate_quarters(int cents);
int calculate_dimes(int cents);
int calculate_nickels(int cents);
int calculate_pennies(int cents);

int main(void)
{
    // Ask how many cents the customer is owed
    int cents = get_cents();

    // Calculate the number of quarters to give the customer
    int quarters = calculate_quarters(cents);
    cents = cents - quarters * 25;

    // Calculate the number of dimes to give the customer
    int dimes = calculate_dimes(cents);
    cents = cents - dimes * 10;

    // Calculate the number of nickels to give the customer
    int nickels = calculate_nickels(cents);
    cents = cents - nickels * 5;

    // Calculate the number of pennies to give the customer
    int pennies = calculate_pennies(cents);
    cents = cents - pennies * 1;

    // Sum coins
    int coins = quarters + dimes + nickels + pennies;

    // Print total number of coins to give the customer
    printf("value of coin is %i\n", coins);
}

int get_cents(void)
{
    // TODO
    int cents;
    do
    {
        cents = get_int("Insert cents: ");
    }
    while (cents < 0);
    return cents;
}

int calculate_quarters(int cents)
{
    // TODO
    int quarters = 0;
    for (int i = 1; i < cents + 1; i++)
    {
        if (cents > 25 * i - 1 && cents < 25 * i + 25)
        {

            quarters = i;
        }



    }
    return quarters;
}

int calculate_dimes(int cents)
{
    // TODO
    int dimes = 0;
    for (int i = 1; i < cents + 1; i++)
    {
        if (cents > 10 * i - 1 && cents < 10 * i + 10)
        {
            dimes = i;
        }
    }
    return dimes;
}

int calculate_nickels(int cents)
{
    // TODO
    int nickels = 0;
    for (int i = 1; i < cents + 1; i++)
    {
        if (cents > 5 * i - 1 && cents < 5 * i + 5)
        {
            nickels = i;
        }
    }
    return nickels;
}

int calculate_pennies(int cents)
{
    // TODO
    int pennies = 0;
    for (int i = 0; i < cents + 1; i++)
    {
        if ((cents > 10 * i && cents < 10 * i + 5) || (cents > 10 * i + 5 && cents < 10 * i + 10))
        {
            if (cents % 10 == 1 || cents % 10 == 6)
            {
                pennies = 1;
            }
            if (cents % 10 == 2 || cents % 10 == 7)
            {
                pennies = 2;
            }
            if (cents % 10 == 3 || cents % 10 == 8)
            {
                pennies = 3;
            }
            if (cents % 10 == 4 || cents % 10 == 9)
            {
                pennies = 4;
            }
        }

    }
    return pennies;
}
