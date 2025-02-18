#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct SongNode {
    char name[100];
    struct SongNode* next;
    struct SongNode* prev;
} SongNode;

// Function to create a new song node
SongNode* createSongNode(const char* name) {
    SongNode* newNode = (SongNode*)malloc(sizeof(SongNode));
    strcpy(newNode->name, name);
    newNode->next = NULL;
    newNode->prev = NULL;
    return newNode;
}

// Function to add a song to the doubly linked list
void addSong(SongNode** head, const char* name) {
    SongNode* newNode = createSongNode(name);
    if (*head == NULL) {
        *head = newNode;
        return;
    }
    SongNode* temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
    newNode->prev = temp;
}

// Function to navigate the playlist
void navigatePlaylist(SongNode** current) {
    char command;
    while (1) {
        if (*current == NULL) {
            printf("No songs available.\n");
            return;
        }
        printf("Now playing: %s\n", (*current)->name);
        printf("Enter 'n' for next, 'p' for previous, or 'q' to quit: ");
        scanf(" %c", &command);

        if (command == 'n') {
            if ((*current)->next != NULL) {
                *current = (*current)->next;
            } else {
                printf("End of playlist reached.\n");
            }
        } else if (command == 'p') {
            if ((*current)->prev != NULL) {
                *current = (*current)->prev;
            } else {
                printf("Start of playlist reached.\n");
            }
        } else if (command == 'q') {
            break;
        } else {
            printf("Invalid command. Try again.\n");
        }
    }
}

int main() {
    SongNode* head = NULL;
    SongNode* current = NULL;

    // Add songs to the playlist
    addSong(&head, "Song1");
    addSong(&head, "Song2");
    addSong(&head, "Song3");

    current = head;

    // Navigate the playlist
    navigatePlaylist(&current);

    // Free memory
    while (head != NULL) {
        SongNode* temp = head;
        head = head->next;
        free(temp);
    }

    return 0;
}
