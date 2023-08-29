#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// Preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// Locked[i][j] means i is locked in over j
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
bool has_cycle(int loser, int winner);

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

    for (int row = 0; row < candidate_count; row++)
    {
        for (int col = 0; col < candidate_count; col++)
        {
            if (row == col)
            {
                preferences[ranks[row]][ranks[col]] = 0;
            }
            else if (row < col)
            {
                preferences[ranks[row]][ranks[col]]++;
            }
        }
    }

    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    /** 
     * Loop over the preferences array
     * Compare the pairs, like 0 and 1
     * If preferences[0][1] has a greater number than preferences[1][0]
     * Then declare the winner and loser of the comparison
     * Update the pairs array based on that
     * Update the pairs count to be the number of pairs candidates
     * 
    */


    pair_count = 0;

    for (int row = 0; row < candidate_count; row++)
    {
        //loop through
        for (int col = row + 1; col < candidate_count; col++)
        {
            if (row != col)
            {
                if (preferences[row][col] > preferences[col][row])
                {
                    pairs[pair_count].winner = row;
                    pairs[pair_count].loser = col;
                    pair_count++;
                }
                else if (preferences[row][col] < preferences[col][row])
                {
                    pairs[pair_count].winner = col;
                    pairs[pair_count].loser = row;
                    pair_count++;
                }
            }
        }
    }
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    /**
     * Loop through the pairs array
     * If the preference of a candidate is higher bubble sort the pairs array
     * Swap the pair to to the left
    */

    for (int i = 0; i < pair_count - 1; i++)
    {
        for (int j = 0; j < pair_count - i - 1; j++)
        {
            if (preferences[pairs[j].winner][pairs[j].loser] < preferences[pairs[j + 1].winner][pairs[j + 1].loser])
            {
                pair temp = pairs[j];
                pairs[j] = pairs[j + 1];
                pairs[j + 1] = temp;
            }
            else if (preferences[pairs[i].winner][pairs[i].loser] == preferences[pairs[i].loser][pairs[i].winner])
            {
                return;
            }
        }
    }
    return;
}

bool has_cycle(int loser, int winner)
{
    if (loser == winner)
    {
        return true;
    }

    for (int i = 0; i < candidate_count; i++)
    {
        if (locked[loser][i])
        {
            if (has_cycle(i, winner))
            {

                return true;
            }
        }
    }
    return false;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    /**
     * Loop through the locked array
     * Creating edges by decreasing of victory strengh
     * If the winner of the first pair is the same as the loser of
     * The last pair and they altenate between pairs,
     * It is a sign of a cycle and that last arrow should be skipped
    */

    for (int i = 0; i < pair_count; i++)
    {
        if (!has_cycle(pairs[i].loser, pairs[i].winner))
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
    }
    return;
}

// Print the winner of the election
void print_winner(void)
{
    for (int col = 0; col < candidate_count; col++)
    {
        int source_found = 0;
        for (int row = 0; row < candidate_count; row++)
        {
            if (locked[row][col] == false)
            {
                source_found++;
                if (source_found == candidate_count)
                {
                    printf("%s\n", candidates[col]);
                }
            }
        }
    }
    return;
}