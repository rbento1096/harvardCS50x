// https://cs50.harvard.edu/x/2020/psets/2/readability

#include <stdio.h>
#include <cs50.h>
#include <math.h>

// functions
float cnt_letters(string str);
float cnt_words(string str);
float cnt_sent(string str);

int main(void)
{
    string text = get_string("Text: ");

    // all variables are stored as floats to prevent truncating when multiplying and dividing.
    float letters = cnt_letters(text);
    float words = cnt_words(text);
    float sentences = cnt_sent(text);
    // L, S and index values very likely will always have a decimal component.
    float L = 100 / words * letters;
    float S = 100 / words * sentences;
    float index = round(0.0588 * L - 0.296 * S - 15.8);

    // The output, as sepecified in the problem set.
    if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    else if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade %i\n", (int)index);
    }
}

float cnt_letters(string str)
{
    float count = 0;
    for (int i = 0; str[i] != 0; i++)
    {
        if (str[i] >= 65 && str[i] <= 90) // capitalized alphabet (A-Z) goes from positions 65 through to 90 in Unicode.
        {
            count++;
        }
        else if (str[i] >= 97 && str [i] <= 122) // lower-case alphabet (a-z) goes from positions 97 through to 122 in Unicode.
        {
            count++;
        }
    }
    return count;
}

float cnt_words(string str)
{
    // Every two words will be separated by a single space. After a sentence a space precedes the word. So nr words = nr spaces + 1
    float count = 1;

    for (int i = 0; str[i] != 0; i++)
    {
        if (str[i] == 32) // 32 is the unicode value for a blank space
        {
            count++;
        }
    }

    return count;
}

float cnt_sent(string str)
{
    float count = 0;

    for (int i = 0; str[i] != 0; i++)
    {
        // In this exercise, a sentence is defined as a sequence ending in "?", "!" or ".". "Mr. Potter." will be counted as 2 sentences, by request.
        if (str[i] == 63 || str[i] == 46 || str[i] == 33) // 63 = ?; 46 = !; 33 = .
        {
            count++;
        }
    }

    return count;
}