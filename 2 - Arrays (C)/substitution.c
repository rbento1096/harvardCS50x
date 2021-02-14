//https://cs50.harvard.edu/x/2020/psets/2/substitution/

#include <stdio.h>
#include <cs50.h>


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

    int key_count = 0;
    // to simplify the reading, argv[1] is substituted by "key"
    string key = argv[1];
    string key_error = "Error: Please insert exactly 26 unique alphabetic characters\n";
    // for cycle counts the number of characters in key by incrementing key_count
    for (int i = 0; argv[1][i] != 0; i++)
    {
        key_count++;
        // returns an error if the key contains non alphabetic characters
        if (key[i] < 65 || (key[i] > 90 && key[i] < 97) || key[i] > 122)
        {
            printf("%s", key_error);
            return 1;
        }
        // checks if the current character is repeated in in the key.
        // j = i + 1. If it looped through the whole array it would find itself and key[i] would equal key[j]
        for (int j = i + 1; key[j] != 0; j++)
        {
            if (key[i] == key[j])
            {
                printf("%s", key_error);
                return 1;
            }
        }
    }
    // key must contain exaclty 26 characters
    if (key_count != 26)
    {
        printf("%s", key_error);
        return 1;
    }

    string plaintext = get_string("plaintext: ");
    for (int i = 0; plaintext[i] != 0; i++)
    {
        if (plaintext[i] >= 65 && plaintext[i] <= 90) // capitalized alphabet (A-Z) goes from positions 65 through to 90 in Unicode.
        {
            int pos = plaintext[i] - 65; // position relative to the first letter.
            // if the corresponding position in the key is also capitalized
            if (key[pos] >= 65 && key[pos] <= 90)
            {
                plaintext[i] = key[pos]; // case is preserved
            }
            else
            {
                plaintext[i] = key[pos] - (97 - 65); // if its lower-case we have to subtract the difference between upper and lower case
            }
        }
        else if (plaintext[i] >= 97 && plaintext[i] <= 122) // lower-case alphabet (a-z) goes from positions 97 through to 122 in Unicode.
        {
            int pos = plaintext[i] - 97;
            // if the corresponding position in the key is also lower-case
            if (key[pos] >= 97 && key[pos] <= 122)
            {
                plaintext[i] = key[pos]; // case is preserved
            }
            else
            {
                plaintext[i] = key[pos] + (97 - 65); // if its capital, we add the difference between upper and lower case.
            }
        }
    }
    printf("ciphertext: %s\n", plaintext);
}