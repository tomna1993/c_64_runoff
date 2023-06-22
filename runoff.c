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

bool vote(int voter, int rank, char name[MAX_CHARS], char preference[MAX_VOTERS][MAX_CANDIDATES][MAX_CHARS], struct candidate candidates[MAX_CANDIDATES], int candidate_count);


int main(int argc, char *argv[])
{
    const int candidate_count = argc - 1;

    if (candidate_count < 1 || candidate_count > MAX_CANDIDATES)
    {
        printf ("Usage: ./runoff <candidate1> .. <candidate9>\n");
        return EXIT_FAILURE;
    }

    // Create a candidates struct to hold informations about the candidates 
    struct candidate candidates[candidate_count];


    // Save candidate names into structure
    for (int i = 0; i < candidate_count; i++)
    {
        strcpy(candidates[i].Name, argv[i + 1]);

        candidates[i].Votes = 0;
        candidates[i].Eliminated = false;
    }

    int number_of_voters;

    do
    {
        number_of_voters = get_int("Number of voters: ");
        
    } while (number_of_voters < 0 || number_of_voters > MAX_VOTERS);

    printf ("\n");
    
    const int voter_count = number_of_voters;

    // Create an array to hold the preferences of voters
    char preferences[voter_count][candidate_count][MAX_CHARS];

    // LOOP to ask for votes
    for (int voter = 0; voter < voter_count; voter++)
    {
        for (int rank = 0; rank < candidate_count; rank++)
        {
            bool valid_vote;

            do
            {
                char name[MAX_CHARS];
                
                strcpy(name, get_string("Rank %i: ", rank + 1));

                valid_vote = vote(voter, rank, name, preferences, candidates, candidate_count);

            } while (valid_vote == false);
        }

        printf ("\n");
    }

    // Total votes required to win the election
    int required_votes_to_win = (voter_count * 0.5) + 1;

    tabulate()

    return EXIT_SUCCESS;
}


bool vote(int voter, int rank, char name[MAX_CHARS], char preference[MAX_VOTERS][MAX_CANDIDATES][MAX_CHARS], struct candidate candidates[MAX_CANDIDATES], int candidate_count)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp (name, candidates[i].Name) == 0)
        {
            strcpy (preference[voter][rank], name);
    
            return true;
        }
    }

    return false;
}


int tabulate()
{
}

bool print_winner()
{
}


int find_min()
{
}


bool is_tie()
{
}


int eliminate()
{
}