// https://cs50.harvard.edu/x/2021/psets/3/runoff/

#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max voters and candidates
#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

// preferences[i][j] is jth preference for voter i
int preferences[MAX_VOTERS][MAX_CANDIDATES];

// Candidates have name, vote count, eliminated status
typedef struct
{
    string name;
    int votes;
    bool eliminated;
}
candidate;

// Array of candidates
candidate candidates[MAX_CANDIDATES];

// Numbers of voters and candidates
int voter_count;
int candidate_count;

// Function prototypes
bool vote(int voter, int rank, string name);
void tabulate(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min);
void eliminate(int min);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: runoff [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX_CANDIDATES)
    {
        printf("Maximum number of candidates is %i\n", MAX_CANDIDATES);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
        candidates[i].eliminated = false;
    }

    voter_count = get_int("Number of voters: ");
    if (voter_count > MAX_VOTERS)
    {
        printf("Maximum number of voters is %i\n", MAX_VOTERS);
        return 3;
    }

    // Keep querying for votes
    for (int i = 0; i < voter_count; i++)
    {

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);
            vote(i, j, name);
            // Record vote, unless it's invalid
            if (!vote(i, j, name))
            {
                printf("Invalid vote.\n");
                return 4;
            }
        }

        printf("\n");
    }

    // Keep holding runoffs until winner exists
    while (true)
    {
        // Calculate votes given remaining candidates
        tabulate();

        // Check if election has been won
        bool won = print_winner();
        if (won)
        {
            break;
        }

        // Eliminate last-place candidates
        int min = find_min();
        bool tie = is_tie(min);

        // If tie, everyone wins
        if (tie)
        {
            for (int i = 0; i < candidate_count; i++)
            {
                if (!candidates[i].eliminated)
                {
                    printf("%s\n", candidates[i].name);
                }
            }
            break;
        }

        // Eliminate anyone with minimum number of votes
        eliminate(min);

        // Reset vote counts back to zero
        for (int i = 0; i < candidate_count; i++)
        {
            candidates[i].votes = 0;
        }
    }
    return 0;
}

// Record preference if vote is valid
bool vote(int voter, int rank, string name)
{
    // loops through all candidates
    for (int i = 0; i < candidate_count; i++)
    {
        // if name is found among the candidates
        if (strcmp(candidates[i].name, name) == 0)
        {
            /* an int with value "i" corresponding to the candidate is placed on the voters respective rank.
            note "i" corresponds to the candidate's place in the candidates array */
            preferences[voter][rank] = i;
            return true;
        }
    }
    // if name is not found, return false.
    return false;
}

// Tabulate votes for non-eliminated candidates
void tabulate(void)
{
    // loops through all voters
    for (int i = 0; i < voter_count; i++)
    {
        // loops through all voter preferences (here, the same number as candidates - according to the problem set)
        for (int j = 0; j < candidate_count; j++)
        {
            // if the candidate hasn't been eliminated yet
            if (!candidates[preferences[i][j]].eliminated)
            {
                // increment his vote tally by 1
                candidates[preferences[i][j]].votes++;
                // break of this for loop and go to the next voter
                break;
            }
        }
    }
    return;
}

// Print the winner of the election, if there is one
bool print_winner(void)
{
    // loops through all candidates
    for (int i = 0; i < candidate_count; i++)
    {
        // if a candidate has majority
        if (candidates[i].votes > (voter_count / 2))
        {
            // print out his name
            printf("%s\n", candidates[i].name);
            return true;
        }
    }
    return false;
}

// Return the minimum number of votes any remaining candidate has
int find_min(void)
{
    // we initialize min_vote with the maximum possible value
    int min_vote = voter_count;
    // we loop through the candidates
    for (int i = 0; i < candidate_count; i++)
    {
        // we skip those who have already been eliminated
        if (!candidates[i].eliminated)
        {
            // updates the minimum vote
            if (candidates[i].votes < min_vote)
            {
                min_vote = candidates[i].votes;
            }
        }
    }
    return min_vote;
}

// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{
    // loops through the candidates
    for (int i = 0; i < candidate_count; i++)
    {
        // if a candidate has a vote tally bigger than the one with the lowest tally, a tie is impossible.
        if (candidates[i].votes > min)
        {
            return false;
        }
    }
    // if no candidate has more votes than the minimum tally, and a winner is not declared yet, we have a tie.
    return true;
}

// Eliminate the candidate (or candidates) in last place
void eliminate(int min)
{
    // loops through the candidates
    for (int i = 0; i < candidate_count; i++)
    {
        // if the candidate has the lowest number of votes
        if (candidates[i].votes == min)
        {
            // the candidate is eliminated from this runoff
            candidates[i].eliminated = true;
        }
    }
    return;
}