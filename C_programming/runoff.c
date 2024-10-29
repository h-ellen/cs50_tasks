#include "cs50.h"
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

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
} candidate;

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
    // TODO
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i].name) == 0)
        {
            preferences[voter][rank] = i;
            return (true);
        }
    }
    return false;
}

// Tabulate votes for non-eliminated candidates
void tabulate(void)
{
    // for loop to loop through all voters
    for (int i = 0; i < voter_count; i++)
    {
        /* for loop to loop through all candidate preferences 
         * for that voter
         */
        for (int j = 0; j < candidate_count; j++)
        {
            // if checks whether that candidate's jth preference
            // has been eliminated or not
            if (!(candidates[preferences[i][j]].eliminated))
            {
                candidates[preferences[i][j]].votes += 1;
                break;
            }
        }
    }
    return;
}

// Print the winner of the election, if there is one
bool print_winner(void)
{
    // check what percent of votes each candidate has
    for (int i = 0; i < candidate_count; i++)
    {
        float percent_vote = (candidates[i].votes / (float)voter_count) * 100;
        // if percent more than 50 then print their name
        if (round(percent_vote) > 50)
        {
            printf("%s\n", candidates[i].name);
            return (true);
        }
    }
    return false;
}

// Return the minimum number of votes any remaining candidate has
int find_min(void)
{
    int min = voter_count;
    // loop through all candidates
    for (int i = 0; i < candidate_count; i++)
    {
        // check if eliminated
        if(!(candidates[i].eliminated))
        {
            // check if number of votes < min
            if (candidates[i].votes < min)
            {
                // change value of min to number of votes
                min = candidates[i].votes;
            }
        }
    }
    return (min);
}

// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{
    // loop through all candidates
    for (int i = 0; i < candidate_count; i++)
    {
        // consider only candidates that are not eliminated
        if (!(candidates[i].eliminated))
        {
            if (candidates[i].votes != min)
            {
                return(false);
            }
        }
    }
    return (true);
}

// Eliminate the candidate (or candidates) in last place
void eliminate(int min)
{
    // loop through all candidates
    for (int i = 0; i < candidate_count; i++)
    {
        // eliminate candidate with minumun votes
        if (candidates[i].votes == min)
        {
            candidates[i].eliminated = true;
        }
    }
    return;
}