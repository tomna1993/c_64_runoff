#include <cs50.h>
#include <stdio.h>
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
    struct candidate candidates[MAX_CANDIDATES];
    
    
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