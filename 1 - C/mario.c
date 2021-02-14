#include <stdio.h>
#include <cs50.h>

// functions declared here:
void pyramid(int height);

int main(void)
{
    int height;
    do
    {
        height = get_int("Height? ");
    }
    // height must be between 1 and 8 as stipulated in the problem statement
    while ( height > 8 || height < 1);

    pyramid(height);
}

// functions built here:
void pyramid(int height)
{
    // go through each layer until the height is reached
    for (int i = 1; i <= height; i++)
    {
        // the first line will have height - i, with i starting at 1, white spaces
        for (int m = 0; m < height - i; m++)
        {
            printf(" ");
        }
        // the pyramid, built using "#", will have an increasing number of blocks until number of blocks = height
        for (int n = 0; n < i; n++)
        {
            printf("#");
        }
        // two white spaces separate each half of the pyramid
        printf("  ");
        
        for (int n = 0; n < i; n++)
        {
            printf("#");
        }
        printf("\n");
    }
}