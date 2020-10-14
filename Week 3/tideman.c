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
void lock_pairs(void);
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
    for (int i = 0; i < voter_count; i++)//for each voter
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)//rank each candidate
        {
            string name = get_string("Rank %i: ", j + 1);

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
    // TODO
    for (int i = 0; i < candidate_count; i++)//iterate over candidates
    {
        if (strcmp(name, candidates[i]) == 0)//if name input matches
        {
            ranks[rank] = i;//add candidate value to ranking array
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // TODO
    for (int i = 0; i < candidate_count; i++)//iterates over candidates
    {
        for (int j = i + 1; j < candidate_count; j++)//iterates over every candidate ranked after the candidate in i
        {
            preferences[ranks[i]][ranks[j]]++;//+1 candidate who is preferenced
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // TODO
    for (int i = 0; i < candidate_count; i++)//iterate over candidates
    {
        for (int j = i + 1; j < candidate_count; j++)//iterate over candidates pairs available with candidate above
        {
            if (preferences[i][j] > preferences[j][i])//check who is preferred and update winner
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;//update pair count in pair array
            }

            else if (preferences[i][j] < preferences[j][i])
            {
                pairs[pair_count].winner = j;
                pairs[pair_count].loser = i;
                pair_count++;
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // TODO
    int highScore = 0;//initialise highest margin of victory
    pair tempHighPair;//temp variable for swapping
    for (int i = 0; i < pair_count; i++)//record first part of array to compare against
    {
        for (int x = 0; x < pair_count; x++)//compare rest of array
        {
            int victoryStrength = pairs[x].winner - pairs[x].loser;//check strength of victory
            if (victoryStrength > highScore)//swap in decreasing order
            {
                tempHighPair = pairs[x];
                pairs[x] = pairs[i];
                pairs[i] = tempHighPair;
            }
        }
    }
    return;
}

int originalPair = 0;

//custom recursion
bool checkPath(int i)
{
    for (int j = 0; j < pair_count; j++)//iterate over pairs
    {
        if (locked[pairs[i].loser][pairs[j].loser] == true)//iterate over next node to find if there are any pathings
        {
            if (pairs[originalPair].winner == pairs[j].loser)//if pathing found from next node to original pair mark false
            {
                return false;
            }

            return checkPath(j);//else if path found, start search from the node to explorer paths
        }
    }

    if (originalPair > 0)//if it got to the top check after rchecks above if top points to original pair check started from
    {
        if (locked[pairs[originalPair].loser][pairs[i].winner] == true)
        {
            return false;//mark true if no pathing to original pair found
        }
    }

    return true;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // TODO
    for (int i = 0; i < pair_count; i++)//iterate over each sorted pair of i
    {
        originalPair  = i;
        locked[pairs[i].winner][pairs[i].loser] = checkPath(i);
    }

    return;
}

// Print the winner of the election
void print_winner(void)
{
    // TODO
    for (int i = 0; i < pair_count; i++)//iterate over loser of pairs
    {
        int trigger = 0;//to initialise detection
        for (int x = 0; x < pair_count; x++)//iterate over winners of pairs
        {
            if (locked[x][i] == true)//if reverse iteration finds arrow pointing
            {
                x = pair_count;//exit loop and do not trigger win print
                trigger++;
            }
        }

        if (trigger == 0)//if no arrow found from trigger print winner
        {
            printf("%s\n", candidates[i]);
            i = pair_count;//exit loop once candidate printed
        }
    }

    return;
}