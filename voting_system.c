#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CANDIDATES 10
#define MAX_VOTERS 100

typedef struct {
    char name[50];
    int votes;
} Candidate;

typedef struct {
    char name[50];
    char address[100];
    int id;
    int voted;
} Voter;

void displayMenu();
void addCandidates(Candidate candidates[], int *numCandidates);
void addVoter(Voter voters[], int *numVoters);
void castVote(Candidate candidates[], int numCandidates, Voter voters[], int numVoters);
void displayWinner(Candidate candidates[], int numCandidates);

int main() {
    Candidate candidates[MAX_CANDIDATES];
    Voter voters[MAX_VOTERS];
    int numCandidates = 0;
    int numVoters = 0;
    int choice;

    do {
        displayMenu();
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                addCandidates(candidates, &numCandidates);
                break;
            case 2:
                addVoter(voters, &numVoters);
                break;
            case 3:
                castVote(candidates, numCandidates, voters, numVoters);
                break;
            case 4:
                displayWinner(candidates, numCandidates);
                break;
            case 5:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 5);

    return 0;
}

void displayMenu() {
    printf("\n===== Voting System Menu =====\n");
    printf("1. Add candidates\n");
    printf("2. Add voter\n");
    printf("3. Cast vote\n");
    printf("4. Display winner\n");
    printf("5. Exit\n");
}

void addCandidates(Candidate candidates[], int *numCandidates) {
    if (*numCandidates >= MAX_CANDIDATES) {
        printf("Maximum number of candidates reached.\n");
        return;
    }

    printf("Enter candidate name: ");
    scanf("%s", candidates[*numCandidates].name);
    candidates[*numCandidates].votes = 0;

    (*numCandidates)++;
}

void addVoter(Voter voters[], int *numVoters) {
    if (*numVoters >= MAX_VOTERS) {
        printf("Maximum number of voters reached.\n");
        return;
    }

    printf("Enter voter name: ");
    scanf("%s", voters[*numVoters].name);
    printf("Enter voter address: ");
    scanf("%s", voters[*numVoters].address);
    printf("Enter voter ID: ");
    scanf("%d", &voters[*numVoters].id);
    voters[*numVoters].voted = 0;

    (*numVoters)++;
}

void castVote(Candidate candidates[], int numCandidates, Voter voters[], int numVoters) {
    char voterName[50];
    int i, choice;

    printf("Enter your name: ");
    scanf("%s", voterName);

    for (i = 0; i < numVoters; i++) {
        if (strcmp(voterName, voters[i].name) == 0 && voters[i].voted == 0) {
            printf("Candidates:\n");
            for (int j = 0; j < numCandidates; j++) {
                printf("%d. %s\n", j + 1, candidates[j].name);
            }
            printf("%d. NOTA\n", numCandidates + 1);
            printf("Enter your choice: ");
            scanf("%d", &choice);

            if (choice >= 1 && choice <= numCandidates + 1) {
                if (choice <= numCandidates) {
                    candidates[choice - 1].votes++;
                }
                printf("Vote casted successfully!\n");
                voters[i].voted = 1;
                return;
            } else {
                printf("Invalid choice. Please try again.\n");
                return;
            }
        }
    }

    printf("You have already voted or your name is not in the list.\n");
}

void displayWinner(Candidate candidates[], int numCandidates) {
    int maxVotes = 0;
    printf("Candidates with maximum votes:\n");

    for (int i = 0; i < numCandidates; i++) {
        if (candidates[i].votes > maxVotes) {
            maxVotes = candidates[i].votes;
        }
    }

    if (maxVotes == 0) {
        printf("No votes casted yet.\n");
    } else {
        printf("Winner(s):\n");
        for (int i = 0; i < numCandidates; i++) {
            if (candidates[i].votes == maxVotes) {
                printf("%s\n", candidates[i].name);
            }
        }
    }
}
