#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CHARS 20

#define MAX_CANDIDATES 9
#define MAX_VOTERS 9

struct candidate
{
    char    Name[MAX_CHARS];
    int     Votes;
    bool    Eliminated;
};


bool vote(int voter, int rankm, char name[MAX_CHARS]);

int main(int argc, char *argv[])
{
    const int candidate_count = argc - 1;

    if (candidate_count < 1 || candidate_count > MAX_CANDIDATES)
    {
        printf ("Usage: ./runoff <candidate1> .. <candidate9>\n");
        return EXIT_FAILURE;
    }

    struct candidate candidates[MAX_CANDIDATES];

    // Save candidate names into structure
    for (int i = 0; i < candidate_count; i++)
    {
        strcpy(candidates[i].Name, argv[i + 1]);

        candidates[i].Votes = 0;
        candidates[i].Eliminated = false;
    }

    for (int i = 0; i < candidate_count; i++)
    {
        printf ("%s\n", candidates[i].Name);
    }
    
}

bool vote(int voter, int rankm, char name[MAX_CHARS])
{
    return false;
}

int tabulate()
{
    return 0;
}

int print_winner()
{
    return 0;
}

int find_min()
{
    int min;
    return min;
}

bool is_tie(int min)
{
    return false;
}

int eliminate(int min)
{
    return 0;
}