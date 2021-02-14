// https://cs50.harvard.edu/x/2020/psets/2/caesar

#include <stdio.h>
#include <cs50.h>
#include <math.h>
#include <stdlib.h>

int main(int argc, string argv[])
{

    // Checks for the number of arguments. Only one can be passed.
    int arg_count = 0;
    for (int i = 0; i < argc; i++)
    {
        arg_count++;
    }
    if (arg_count != 2)
    {
        if (arg_count == 1)
        {
            printf("Error: Please, provide a command line argument.\n");
        }
        else
        {
            printf("Error: Please, provide only one command line argument!\n");
        }
        return 1;
    }

    // checks if all characters in the input are decimal characters. Note the arguments are strings, not ints.
    // we don't convert the key to an int yet, so the Unicode values from 0 to 9 aren't accidentaly validated.
    for (int i = 0; argv[1][i] != 0; i++)
    {
        if (argv[1][i] < 48 || argv[1][i] > 57)
        {
            printf("Usage: ./caesar key\n");
            return 1;
        }
    }
    // convert the key to a numerical value.
    int key = atoi(argv[1]);

    string plaintext = get_string("plaintext: ");
    for (int i = 0; plaintext[i] != 0; i++)
    {
        if (plaintext[i] >= 65 && plaintext[i] <= 90) // capitalized alphabet (A-Z) goes from positions 65 through to 90 in Unicode.
        {
            int pos = plaintext[i] - 65; // position relative to the first letter.
            // adding the difference in position, with the key while dividing by 26, returns the number of changed positions
            int change = (pos + key) % 26;
            plaintext[i] = 65 + change; // prints the ciphercharacter
        }
        else if (plaintext[i] >= 97 && plaintext[i] <= 122) // lower-case alphabet (a-z) goes from positions 97 through to 122 in Unicode.
        {
            int pos = plaintext[i] - 97;
            int change = (pos + key) % 26;
            plaintext[i] = 97 + change;
        }
    }
    printf("ciphertext: %s\n", plaintext);
}