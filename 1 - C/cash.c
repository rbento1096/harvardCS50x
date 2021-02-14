// https://cs50.harvard.edu/x/2020/psets/1/cash/#:~:text=other

#include <stdio.h>
#include <cs50.h>
#include <math.h>

// main

int main(void)
{
    // get change from user
    float change;

    do
    {
        change = get_float("Change owed: ");
    }
    while (change < 0);

    // convert to int to avoid floating point errors
    int cents;
    cents = round(change * 100);

    // set a counter for the coins and give a value to each coin in cents
    int coin_nr = 0;
    int quarter = 25;
    int dime = 10;
    int nickel = 5;
    int penny = 1;

    // starting with the biggest coin, subtract its value from the change until it equals 0, while incrementing the coin numbers
    while (cents >= quarter)
    {
        cents -= quarter;
        coin_nr++;
    };
    while (cents >= dime)
    {
        cents -= dime;
        coin_nr++;
    };
    while (cents >= nickel)
    {
        cents -= nickel;
        coin_nr++;
    };
    while (cents > 0)
    {
        cents -= penny;
        coin_nr++;
    };

    // print the number of coins
    printf("%i\n", coin_nr);
}