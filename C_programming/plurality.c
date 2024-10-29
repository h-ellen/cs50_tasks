#include "cs50.h"
#include <stdio.h>
#include <string.h>
#include <math.h>

// Max number of candidates
#define MAX 9

//Candidates have name and vote count
typedef struct
{
    string name;
    int votes;
} candidate;

// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Function prototypes
bool vote(string name);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: ./plurality [candidate ...]\n");
        return (1);
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return (2);
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count = get_int("Number of voters: ");

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");

        // Check for invalid vote
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }

    // Display winner of election
    print_winner();
}

// Update vote totals given a new vote
bool vote(string name)
{
    // Check through all candidates for name matching vote.
    for (int i = 0; i < candidate_count; i++)
    {
        // If a match is found increase vote count by one and return true
        if (strcmp(name, candidates[i].name) == 0)
        {
            candidates[i].votes += 1;
            return (true);
        }
    }
    // else return false
    return (false);
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    // initialise max_votes to 0
    int max_votes = candidates[0].votes;

    /**
     *check through all votes one by one whether they are greater than
     * the value of the candidate's votes
     * if so, replace max_votes with that value of candidate votes
     */
    for (int i = 0; i < candidate_count; i++)
    {
        if (max_votes < candidates[i].votes)
        {
            max_votes = candidates[i].votes;
        }
    }

    /**
     * now compare and print out name(s) of candidate(s) with that vote
     * count
     */
    for (int i = 0; i < candidate_count; i++)
    {
        if(max_votes == candidates[i].votes)
        {
            printf("%s\n", candidates[i].name);
        }
    }
    return;
}