#include <cs50.h>
#include <stdio.h>

int checksum(long credit_n);
int counter(long credit_n);
int value_1_digit(long credit_n);
int value_2_digit(long credit_n);
int main(void)
{
    // prompt for input
    long credit_n = get_long("Insert Credit Card Number: ");

    // checksum
    int checksum_result = 0;
    checksum_result = checksum(credit_n);
    // count digits
    int dig_counter = counter(credit_n);
    // first digit value
    int digit_one = value_1_digit(credit_n);
    // second digit value
    int digit_two = value_2_digit(credit_n);
    // main check execution
    if (checksum_result == 1 && dig_counter == 15 && (digit_two == 4 || digit_two == 7) && digit_one == 3)
    {
        printf("AMEX\n");
    }
    else if (checksum_result == 1 && \
             (digit_two == 1 || digit_two == 2 || digit_two == 3 || digit_two == 4 || digit_two == 5) \
             && digit_one == 5)
    {
        printf("MASTERCARD\n");
    }
    else if (checksum_result == 1 && (dig_counter == 16 || dig_counter == 13) && digit_one == 4)
    {
        printf("VISA\n");
    }
    else
    {
        printf("INVALID\n");
    }
}


// define checksum function
int checksum(long credit_n)
{
    int digits;
    int alt_digits;
    int dig_times_two;
    int uni_dig;
    int dec_dig;
    int digits_sum = 0;
    while (credit_n != 0)
    {
        alt_digits = credit_n % 10;
        credit_n /= 10;
        digits = credit_n % 10;
        credit_n /= 10;
        dig_times_two = digits * 2;
        if (dig_times_two > 9)
        {
            uni_dig = dig_times_two % 10;
            dig_times_two /= 10;
            dec_dig = dig_times_two % 10;
            dig_times_two = uni_dig + dec_dig;
        }
        digits_sum += dig_times_two + alt_digits;
    }
    if (digits_sum % 10 == 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
// count digits
int counter(long credit_n)
{
    int counter = 0;
    while (credit_n != 0)
    {
        credit_n /= 10;
        counter ++;
    }
    return counter;
}
// find second digit value
int value_2_digit(long credit_n)
{
    int dig_value;
    int max_counter = counter(credit_n);
    int counter = 0;
    while (credit_n != 0)
    {
        credit_n /= 10;
        counter++;
        if (counter == max_counter - 2)
        {
            dig_value = credit_n % 10;
        }
    }
    return dig_value;
}
// Find first digit value
int value_1_digit(long credit_n)
{
    int dig_value;
    int max_counter = counter(credit_n);
    int counter = 0;
    while (credit_n != 0)
    {
        credit_n /= 10;
        counter++;
        if (counter == max_counter - 1)
        {
            dig_value = credit_n % 10;
        }
    }
    return dig_value;
}