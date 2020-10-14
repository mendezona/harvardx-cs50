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
    for (int i = 0; i < candidate_count; i++)//iterate over candidates
    {
        if (strcmp(name, candidates[i].name) == 0)//if given name found amongst candidate names
        {
            preferences[voter][rank] = i;//record preference of candidate for voter in preferences array
            return true;
        }
    }

    return false;
}

// Tabulate votes for non-eliminated candidates
void tabulate(void)
{
    // TODO
    for (int i = 0; i < voter_count; i++)//iterates over voters
    {
        for (int a = 0; a < candidate_count; a++)//iterates over candidates
        {
            if (candidates[preferences[i][a]].eliminated == false)//checks if candidate that voter picked is eliminated
            {
                candidates[(preferences[i][a])].votes ++;//adds vote if not eliminated
                a = candidate_count;//ends loop when vote is cast
            }
        }
    }
    return;
}

// Print the winner of the election, if there is one
bool print_winner(void)
{
    // TODO
    for (int i = 0; i < candidate_count; i++)//iterate over candidates
    {
        if (candidates[i].votes > (voter_count / 2)) //check if their vote total is a majority
        {
            printf("%s\n", candidates[i].name);//print name if majority
            return true;
        }
    }

    return false;
}

// Return the minimum number of votes any remaining candidate has
int find_min(void)
{
    // TODO
    int lowScore = voter_count;//initialise lowscore to highest score possible
    for (int i = 0; i < candidate_count; i++)//iterate over candidates
    {
        if (candidates[i].eliminated == false)//check candidate is not eliminated
        {
            if (candidates[i].votes < lowScore)//if candidate vote total is lower than previous low, set as low score
            {
                lowScore = candidates[i].votes;
            }
        }
    }
    return lowScore;
}

// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{
    // TODO
    int candidatesAvailable = 0;
    int tieVote = 0;
    for (int i = 0; i < candidate_count; i++)//iterate over candidates
    {
        if (candidates[i].eliminated == false)//if candidate not eliminated
        {
            if (candidates[i].votes == min)
            {
                tieVote++;//record number of candidates with minimum vote
            }
            candidatesAvailable++;//record number of available candidates
        }
    }

    if (candidatesAvailable == tieVote)//return true if tie
    {
        return true;
    }

    else
    {
        return false;
    }
}

// Eliminate the candidate (or candidates) in last place
void eliminate(int min)
{
    // TODO
    for (int i = 0; i < candidate_count; i++)//iterate over candidates
    {
        if (candidates[i].votes == min)//if candidate has lowest number of votes, eliminate from race
        {
            candidates[i].eliminated = true;
        }
    }
    return;
}
