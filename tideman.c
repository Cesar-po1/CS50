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
bool check_cycle(int n, int m);

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
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (i < j)
            {
                preferences[ranks[i]][ranks[j]] ++;
            }
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    pair_count = 0;
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
            else if (preferences[i][j] < preferences[j][i])
            {
                pairs[pair_count].winner = j;
                pairs[pair_count].loser = i;
                pair_count++;
            }
            printf("pairs %d / %d \n",pairs[pair_count-1].winner,pairs[pair_count-1].loser );
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    pair temporary; // temporary
    for (int n = 0; n < pair_count * pair_count; n++) //repeat pair_count^2 times (because of the big O(worst case) in bubble sort)
    {
        for (int i =  0; i < pair_count; i++)
        {
            for (int j = i + 1; j < pair_count; j++) //bubble sort
            {
                if (preferences[pairs[i].winner][pairs[i].loser] <= preferences[pairs[j].winner][pairs[j].loser])
                //if the preferences of pair j is bigger than pair i, then save pair j as a temporary, copy pair i to j, and copy the temporary pair to i
                //this way i and j has now switched
                {
                    temporary.winner = pairs[j].winner;
                    temporary.loser = pairs[j].loser;
                    pairs[j].winner = pairs[i].winner;
                    pairs[j].loser = pairs[i].loser;
                    pairs[i].winner = temporary.winner;
                    pairs[i].loser = temporary.loser;
                }
            }
        }
    }
    //another check: 
    //for (int i = 0; i < pair_count; i++)
    //{
      //  printf("Pair_sort: Pair number %i is %s over %s with %i votes\n", i + 1, candidates[pairs[i].winner], candidates[pairs[i].loser], preferences[pairs[i].winner][pairs[i].loser]);
    //}
    // TODO
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
     // TODO
    for (int i = 0; i < pair_count; i++)
    {
        if (!check_cycle(pairs[i].winner, pairs[i].loser))
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
    }
    return;
}

// Print the winner of the election
void print_winner(void)
{
    // TODO
    for (int i = 0; i < candidate_count; i++)
    {
        bool source = true;

        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[j][i] == true)
            {
                source = false;
                break;
            }
        }

        if (source == true)
        {
            printf("%s\n", candidates[i]);
        }
    }

    return;
}

//checking for cycle
bool check_cycle(int n, int m)
{
    if (locked[m][n] == true)
    {
        return true;
    }

    for (int i = 0; i < candidate_count; i++)
    {
        if (locked[i][n] == true)
        {
            if (check_cycle(i, m))
            {
                return true;   
            }
            else 
            {
                return false;
            }
        }
    }
    return false;
}