// https://cs50.harvard.edu/x/2020/psets/1/credit/#:~:text=Luhn’s%20Algorithm

#include <stdio.h>
#include <cs50.h>
#include <math.h>

// declare functions here:


// main function

int main(void)
{
    // request card number - long because the number of digits may be too many to store in an integer
    long card_number;
    // the unaltered card number
    long ori_nr;
    // this will store the value of the card's first digit
    int first_digit;
    // this will store the value of the card's second digit
    int second_digit;
    // this will count the number of digits in the card
    int nr_card_digits = 0;
    // this will count each iteration through the card number. It starts as 1 to represent the first digit
    int cycle_count = 1;
    // odd digits will be stored here
    int odd_digits = 0;
    // even digits will be stored here (used only for debugging)
    int even_digits = 0;
    // the sum of each digit of the odd's product by 2 will be stored here
    int product_digits = 0;
    // the name of the company - our desired output
    string company_name = "";

    // prompt the user for a credit card number
    card_number = get_long("Type the credit card number: ");
    // save the original card number, as the previous variable will be changed
    ori_nr = card_number;

    // we will gradually remove a digit from the card number until it equals 0
    while (card_number > 0)
    {
        // this will destinguish between even and odd digits
        if (cycle_count % 2 == 0)
        {
            // used only in debugging
            even_digits += card_number % 10;
            // in the product variable, we want the sum of the digits of the even number's product by 2.
            // If the product >= 10 it will have two digits. This step separates them.
            if ((card_number % 10) * 2 >= 10)
            {
                // we'll divide the number by ten and have a float.
                // this step adds the decimal digit to the product_digits variable
                product_digits += ((card_number % 10) * 2) % 10;
                // this step adds the integer digit to the product_digits variable
                product_digits += round(((card_number % 10) * 2) / 10);
            }
            else
            {
                // if the product of the digit by 2 is smaller than 10 (i.e. only has one digit), we can just add it
                product_digits += (card_number % 10) * 2;
            }
            // removes the last digit of the card number
            card_number /= 10;
            // updates the cycle count - to distinguish odd and even digits
            cycle_count++;
            // updates the number of total digits in the card
            nr_card_digits++;
        }
        else
        {
            // works the same way as the with the even digits, but merely adds the numbers
            odd_digits += (card_number % 10);
            card_number /= 10;
            cycle_count++;
            nr_card_digits++;
        }
    };

    // we add the odd digits with the digits of the product of the eve digits by 2
    int sum = odd_digits + product_digits;
    // if the last digit is different from 0, then, through Luhn's Algorithm, it is an invalid credit card
    if (sum % 10 != 0)
    {
        company_name = "INVALID";
        printf("%s\n", company_name);
    }
    else
    {
        // to get the first two digits we can divide the card number by a base 10 to the power of the number of digits - 2
        long dividend = pow(10, nr_card_digits - 2);
        // rounding the previous float will give us an integer containing the first two numbers
        int last_digits = round(ori_nr / dividend);
        // similarly to the code on lines 52 and 54 we separate the integer value from the floating value
        first_digit = round(last_digits / 10);
        second_digit = last_digits % 10;
        // if Luhn's algorithm validates the card next step is to compare with the numbers from the given companies
        if (first_digit == 3 && (second_digit == 4 || second_digit == 7) && nr_card_digits == 15)
        {
            // if the card stars with 34 or 37 and the number of digits is equal to 15, the card is from American Express
            company_name = "AMEX";
        }
        else if (first_digit == 4 && (nr_card_digits == 13 || nr_card_digits == 16))
        {
            // VISA cards start with a 4 and have 13 or 16 digits. Any variation is an invalid card number
            company_name = "VISA";
        }
        else if (first_digit == 5 && (second_digit > 0 && second_digit < 6) && nr_card_digits == 16)
        {
            // MASTERCARD has 16-digit cards starting at 51, 52, 53, 54 or 55
            company_name = "MASTERCARD";
        }
        else
        {
            company_name = "INVALID";
        }
        // the final company name is returned
        printf("%s\n", company_name);
    }
}