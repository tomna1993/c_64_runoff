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
int tabulate(char preference[MAX_VOTERS][MAX_CANDIDATES][MAX_CHARS], int voter_count, struct candidate candidates[MAX_CANDIDATES], int candidate_count);
bool print_winner(struct candidate candidates[MAX_CANDIDATES], int candidate_count, int required_votes_to_win);
int find_min(struct candidate candidates[MAX_CANDIDATES], int candidate_count);
bool is_tie(struct candidate candidates[MAX_CANDIDATES], int candidate_count, int min_vote);
int eliminate(char preference[MAX_VOTERS][MAX_CANDIDATES][MAX_CHARS], struct candidate candidates[MAX_CANDIDATES], int candidate_count, int voter_count, int min_vote);

int main(int argc, char *argv[])
{
    const int candidate_count = argc - 1;

    if (candidate_count < 1 || candidate_count > MAX_CANDIDATES)
    {
        printf ("Usage: ./runoff <candidate1> .. <candidate9>\n");
        return EXIT_FAILURE;
    }

    // Create a candidates struct to hold informations about the candidates 
    struct candidate candidates[MAX_CANDIDATES];

    // Save candidate names into structure
    for (int cand = 0; cand < candidate_count; cand++)
    {
        strcpy(candidates[cand].Name, argv[cand + 1]);

        candidates[cand].Votes = 0;
        candidates[cand].Eliminated = false;
    }

    int number_of_voters;

    do
    {
        number_of_voters = get_int("Number of voters: ");
        
    } while (number_of_voters < 0 || number_of_voters > MAX_VOTERS);

    printf ("\n");
    
    const int voter_count = number_of_voters;

    // Create an array to hold the preferences of voters
    char preferences[MAX_VOTERS][MAX_CANDIDATES][MAX_CHARS];

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

    while(true)
    {
        tabulate(preferences, voter_count, candidates, candidate_count);

        bool found_winner = print_winner(candidates, candidate_count, required_votes_to_win);

        if (found_winner)
        {
            return EXIT_SUCCESS;
        }

        int min_vote = find_min(candidates, candidate_count);

        bool tie = is_tie(candidates, candidate_count, min_vote);

        if (tie)
        {
            for (int cand = 0; cand < candidate_count; cand++)
            {
                if (candidates[cand].Eliminated)
                {
                    continue;
                }

                printf ("%s\n", candidates[cand].Name);
            }

            return EXIT_SUCCESS;
        }

        eliminate(preferences, candidates, candidate_count, voter_count, min_vote);
    }

    return EXIT_FAILURE;
}


bool vote(int voter, int rank, char name[MAX_CHARS], char preference[MAX_VOTERS][MAX_CANDIDATES][MAX_CHARS], struct candidate candidates[MAX_CANDIDATES], int candidate_count)
{
    for (int cand = 0; cand < candidate_count; cand++)
    {
        if (strcmp (candidates[cand].Name, name) == 0)
        {
            strcpy (preference[voter][rank], name);
    
            return true;
        }
    }

    return false;
}

int tabulate(char preference[MAX_VOTERS][MAX_CANDIDATES][MAX_CHARS], int voter_count, struct candidate candidates[MAX_CANDIDATES], int candidate_count)
{
    // Clear votes
    for (int cand = 0; cand < candidate_count; cand++)
    {
        candidates[cand].Votes = 0;
    }

    for (int voter = 0; voter < voter_count; voter++)
    {
        bool vote_done = false;

        for (int rank = 0; rank < candidate_count; rank++)
        {
            for (int cand = 0; cand < candidate_count; cand++)
            {
                if (!candidates[cand].Eliminated && strcmp(preference[voter][rank], candidates[cand].Name) == 0)
                {
                    candidates[cand].Votes++;

                    vote_done = true;

                    break;
                }
            }

            // Go to the next voter if voting has been done for the actual voter
            if (vote_done)
            {
                break;
            }
        }
    }

    return EXIT_SUCCESS;
}

bool print_winner(struct candidate candidates[MAX_CANDIDATES], int candidate_count, int required_votes_to_win)
{
    for (int cand = 0; cand < candidate_count; cand++)
    {
        if (!candidates[cand].Eliminated && candidates[cand].Votes >= required_votes_to_win)
        {
            printf ("%s\n", candidates[cand].Name);
            return true;
        }
    }

    return false;
}

int find_min(struct candidate candidates[MAX_CANDIDATES], int candidate_count)
{
    int min_votes = 0;

    for (int cand = 0; cand < candidate_count; cand++)
    {
        if (candidates[cand].Eliminated)
        {
            continue;
        }

        min_votes = candidates[cand].Votes;
        break;
    }

    for (int cand = 0; cand < candidate_count; cand++)
    {
        if (candidates[cand].Eliminated)
        {
            continue;
        }

        if (candidates[cand].Votes < min_votes)
        {
            min_votes = candidates[cand].Votes;
        }
    }

    return min_votes;
}

bool is_tie(struct candidate candidates[MAX_CANDIDATES], int candidate_count, int min_vote)
{
    int count_candidates_with_min_vote = 0;

    int active_candidate_count = 0;

    for (int cand = 0; cand < candidate_count; cand++)
    {
        if (candidates[cand].Eliminated)
        {
            continue;
        }

        if (candidates[cand].Votes == min_vote)
        {
            count_candidates_with_min_vote++;
        }

        active_candidate_count++;
    }

    // DEBUG
    // printf ("Candidates with min votes: %i\n", count_candidates_with_min_vote);
    // printf ("Active candidates: %i\n", active_candidate_count);

    // All of the candidates have the same amount of votes 
    if (count_candidates_with_min_vote == active_candidate_count)
    {
        return true;   
    }

    return false;
}

int eliminate(char preference[MAX_VOTERS][MAX_CANDIDATES][MAX_CHARS], struct candidate candidates[MAX_CANDIDATES], int candidate_count, int voter_count, int min_vote)
{
    for (int cand = 0; cand < candidate_count; cand++)
    {
        if (candidates[cand].Eliminated)
        {
            continue;
        }

        if (candidates[cand].Votes == min_vote)
        {
            candidates[cand].Eliminated = true;

            // DEBUG
            // printf ("%s has been eliminated!\n", candidates[cand].Name);
        }
    }

    return EXIT_SUCCESS;
}
