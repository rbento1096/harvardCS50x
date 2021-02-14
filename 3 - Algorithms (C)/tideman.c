//https://cs50.harvard.edu/x/2021/psets/3/tideman/

#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
int margin(pair);
void lock_pairs(void);
bool is_cycle(int, int);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);
            vote(j, name, ranks);
            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }
        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    // check if the voted candidate exists
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(candidates[i], name) == 0)
        {
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // loops through the voters ranked preferences...
    for (int i = 0; i < candidate_count; i++)
    {
        // ... and loops through all the candidates below the current preference (i)
        for (int j = i + 1; j < candidate_count; j++)
        {
            // increments by 1 to indicate i beats j
            preferences[ranks[i]][ranks[j]]++;
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // loops through the whole i x j matrix
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            // if i beating j is more favored than the opposite (excludes ties)
            if (preferences[i][j] > preferences[j][i])
            {
                // i is the winner in this pair
                pairs[pair_count].winner = i; // pair count is initialized at 0, the first position in the array.
                // j is the loser
                pairs[pair_count].loser = j;
                // pair count is incremented by 1 allowing a new value to be added to the pairs array.
                pair_count++;
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    for (int i = 0; i < pair_count; i++)
    {
        // the index initializes at i
        int index = i;
        // checks all pairs after i to check if i is in position
        for (int j = i + 1; j < pair_count; j++)
        {
            // if any pair, has bigger win margin between them, than the current pair
            if (margin(pairs[j]) > margin(pairs[i]))
            {
                // update the index to the one corresponding to the highest value
                index = j;
            }
        }
        // creates a temporary value to store the i pair
        pair temp = pairs[i];
        // switches the i pair with the pair with the highest margin
        pairs[i] = pairs[index];
        // places the i pair in the position of the just sorted pair
        pairs[index] = temp;
    }
    return;
}

// Calculate victory margin between a winner-loser pair

int margin(pair pair)
{
    // the margin of victory is the difference between the votes in i over j and the votes in j over i.
    int diff = preferences[pair.winner][pair.loser] - preferences[pair.loser][pair.winner];
    return diff;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    for (int i = 0; i < pair_count; i++)
    {
        // if locking this pair DOES NOT result in a cycle
        if (!is_cycle(pairs[i].winner, pairs[i].loser))
        {
            // lock them, creating an edge
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
    }
    return;
}

// Check if a cycle is formed
bool is_cycle(int winner, int loser)
{
    // base case. check if the current winner beats the proposed loser.
    if (locked[winner][loser] == true)
    {
        // a cycle is formed
        return true;
    }
    // loops through all candidates
    for (int i = 0; i < candidate_count; i++)
    {
        // if any candidate beats the proposed winner
        if (locked[i][winner] == true)
        {
            // if i beats the winner and is the proposed loser, a cycle is created.
            if (i == loser)
            {
                return true;
            }
            // else check if the proposed loser has already been beaten by the candidate which beat the proposed winner
            return is_cycle(i, loser);
        }
    }
    // if none of the conditions return true, no cycle is formed.
    return false;
}

// Print the winner of the election
void print_winner(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            // the winner (or winners) can't be locked.
            if (locked[j][i] == true)
            {
                break;
            }
        }
        // prints all candidates that haven't lost againt anyone.
        printf("%s\n", candidates[i]);
    }
    return;
}
