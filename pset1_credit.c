#include <cs50.h>
#include <stdio.h>
#include <math.h>

int calculate_odd(long num, long card_digit_length);
int calculate_even(long num, long card_digit_length);
bool validity(int result_of_Luhn_algorithm);
void invalid(void);

int main(void)
{
    long card;
    long card_len;
    bool card_validity;
    int card_type;

    //prompt user input of card number
    do
    {
        card = get_long("NUMBER: ");
    }
    while(card < 0);

    //the check process for card length of 16
    if (card / pow(10,15) < 10 && card / pow(10,15) > 1)
    {
        card_len = pow(10,15);
        card_validity = validity(calculate_even(card, card_len) + calculate_odd(card, card_len));
        if(card_validity)
        {
            //to check for card type
            card_type = card / pow(10,14);

            if(card_type > 50 && card_type < 56)
            {
                printf("MASTERCARD\n");
            }
            else if(card_type > 39 && card_type < 50)
            {
                printf("VISA\n");
            }
        }
        else
        {
            invalid();
        }
    }
    //the check process for card length of 15
    else if (card / pow(10,14) < 10 && card / pow(10,14) > 1)
    {
        card_len = pow(10,14);
        card_validity = validity(calculate_even(card, card_len) + calculate_odd(card, card_len));
        if(card_validity)
        {
            //to check for card type
            card_type = card / pow(10,13);

            if(card_type == 34 || card_type == 37)
            {
                printf("AMERICAN EXPRESS\n");
            }
        }
        else
        {
            invalid();
        }
    }
    //the check process for card length of 13
    else if (card / pow(10,12) < 10 && card / pow(10,12) > 1)
    {
        card_len = pow(10,12);
        card_validity = validity(calculate_even(card, card_len) + calculate_odd(card, card_len));
        if(card_validity)
        {
            //to check for card type
            card_type = card / pow(10,12);

            if(card_type == 4)
            {
                printf("MASTERCARD\n");
            }
        }
        else
        {
            invalid();
        }
    }
    //to skip all other card that doesn't have 13, 15, or 16 digits
    else
    {
        invalid();
    }

}


//custom functions:
//Luhn's Algorithm 1/3: multiply every other digit by 2, starting with the number’s second-to-last digit, and then add those products’ digits together.
int calculate_even(long num, long card_digit_length)
{
    int y = 0;
    int z = 0;

    for (long i = 1; i <= card_digit_length; i*=100)
    {
        z = ((num % (100 * i)) / (10 * i)) * 2;

        if (z > 10)
        {
            int int_div = z / 10;
            int modulus = z % 10;
            z = int_div + modulus;
        }

        y += z;
    }
    return y;
}

//Luhn's Algorithm 2/3: add every other digit starting with the number’s last digit altogether.
int calculate_odd(long num, long card_digit_length)
{
    int y = 0;
    int z = 0;

    for (long i = 1; i <= card_digit_length; i*=100)
    {
        z = (num % (10 * i)) / (1 * i);
        y += z;
    }
    return y;
}

//Luhn's Algorithm 3/3: Check if the total’s last digit is 0 (or, put more formally, if the total modulo 10 is congruent to 0), the number is valid!
bool validity(int result_of_Luhn_algorithm)
{
    if(result_of_Luhn_algorithm % 10 == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

//print "invalid"
void invalid(void)
{
    printf("INVALID\n");
}