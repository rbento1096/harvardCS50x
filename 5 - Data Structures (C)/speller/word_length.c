#include <stdio.h>
#include <string.h>

int main(void)
{
    char name[45];
    strcpy(name, "hello");

    int size = 0;
    int i = 0;

    while (name[i])
    {
        size++;
        i++;
    }

    int method2 = strlen(name);

    printf("this is the first character: %c\n", name[0]); // this outputs h for "hello" - WE WANT THIS
    printf("this is size output: %i\n", size); // this outputs 5 for "hello"
    printf("this is size output: %i\n", method2); // this outputs 5 for "hello" - WE WANT THIS ALSO
    printf("this is the name: %s\n", name); // this outputs hello for "hello"
    printf("this is the size: %lu\n", sizeof(name)/sizeof(char) - 1); // this outputs 44 for "hello"
}