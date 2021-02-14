// https://cs50.harvard.edu/x/2021/labs/5/#:~:text=check50%20cs50/labs/2021/x/inheritance
// Simulate genetic inheritance of blood type

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Each person has two parents and two alleles
typedef struct person
{
    struct person *parents[2];
    char alleles[2];
}
person;

const int GENERATIONS = 3;
const int INDENT_LENGTH = 4;

person *create_family(int generations);
void print_family(person *p, int generation);
void free_family(person *p);
char random_allele();

int main(void)
{
    // Seed random number generator
    srand(time(0));

    // Create a new family with three generations
    person *p = create_family(GENERATIONS);

    // Print family tree of blood types
    print_family(p, 0);

    // Free memory
    free_family(p);
}

// Create a new individual with `generations`
person *create_family(int generations)
{
    // allocates memory for one person
    person *p = malloc(sizeof(person));
    // Generation with parent data
    if (generations > 1)
    {
        for (int i = 0; i < 2; i++)
        {
            // creates the parent's family through recursion
            p->parents[i] = create_family(generations - 1);
            // each allele is chosen at random from one of the parent's alleles
            p->alleles[i] = p->parents[i]->alleles[rand() % 2];
        }
    }

    // Generation without parent data
    else
    {
        for (int i = 0; i < 2; i++)
        {
            // the last member of the generation has no parent info
            p->parents[i] = NULL;
            // so their alleles are randomly generated
            p->alleles[i] = random_allele();
        }
    }

    // returns the created person
    if (p != NULL)
    {
        return p;
    }

    // else...
    return NULL;
}

// Free `p` and all ancestors of `p`.
void free_family(person *p)
{
    // base case
    if (p == NULL)
    {
        return;
    }

    // frees all the parents first recursively
    for (int i = 0; i < 2; i++)
    {
        free_family(p->parents[i]);
    }

    // frees the child recursively (parents are also children)
    free(p);
    return;
}

// Print each family member and their alleles.
void print_family(person *p, int generation)
{
    // Handle base case
    if (p == NULL)
    {
        return;
    }

    // Print indentation
    for (int i = 0; i < generation * INDENT_LENGTH; i++)
    {
        printf(" ");
    }

    // Print person
    printf("Generation %i, blood type %c%c\n", generation, p->alleles[0], p->alleles[1]);
    print_family(p->parents[0], generation + 1);
    print_family(p->parents[1], generation + 1);
}

// Randomly chooses a blood type allele.
char random_allele()
{
    int r = rand() % 3;
    if (r == 0)
    {
        return 'A';
    }
    else if (r == 1)
    {
        return 'B';
    }
    else
    {
        return 'O';
    }
}
