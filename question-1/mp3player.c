#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include <termios.h>

// Song node structure
typedef struct SongNode {
    char title[256];
    struct SongNode *prev;
    struct SongNode *next;
} SongNode;

// Global pointers for current song and list head
SongNode *current = NULL;
SongNode *head = NULL;

// Non-blocking input setup
struct termios orig_termios;

void disableInputBuffering() {
    tcgetattr(STDIN_FILENO, &orig_termios);
    struct termios new_termios = orig_termios;
    new_termios.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &new_termios);
}

void restoreInputBuffering() {
    tcsetattr(STDIN_FILENO, TCSANOW, &orig_termios);
}

// Load songs from directory
void loadSongs(const char *dirPath) {
    DIR *dir = opendir(dirPath);
    if (!dir) {
        printf("Error: Could not open directory '%s'. Ensure it exists.\n", dirPath);
        return;
    }

    struct dirent *entry;
    SongNode *prev = NULL;

    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_type == DT_REG) { // Regular file
            SongNode *newNode = (SongNode *)malloc(sizeof(SongNode));
            if (!newNode) {
                printf("Memory allocation failed.\n");
                closedir(dir);
                return;
            }

            strcpy(newNode->title, entry->d_name);
            newNode->prev = prev;
            newNode->next = NULL;

            if (head == NULL) {
                head = newNode;
            } else {
                prev->next = newNode;
                newNode->prev = prev;
            }
            prev = newNode;
        }
    }
    closedir(dir);
}

// Simulate play/pause/stop (audio library integration recommended)
void playSong() {
    if (current)
        printf("Playing: %s\n", current->title);
}

void pauseSong() { printf("Paused\n"); }
void stopSong() { printf("Stopped\n"); }

// Free memory allocated for the linked list
void cleanup() {
    SongNode *temp = head;
    while (temp) {
        SongNode *next = temp->next;
        free(temp);
        temp = next;
    }
}

int main() {
    loadSongs("./songs"); // Load from directory

    // Check if songs were loaded
    if (head == NULL) {
        printf("No songs found in the directory.\n");
        return 1;
    }

    current = head;
    disableInputBuffering();

    char cmd;
    while (1) {
        printf("\nCommand [n: next, p: previous, s: stop, q: quit]: ");
        cmd = getchar();
        getchar(); // To consume newline character

        switch (cmd) {
            case 'n':
                if (current->next) {
                    current = current->next;
                    playSong();
                } else {
                    printf("End of playlist.\n");
                }
                break;
            case 'p':
                if (current->prev) {
                    current = current->prev;
                    playSong();
                } else {
                    printf("Start of playlist.\n");
                }
                break;
            case 's':
                stopSong();
                break;
            case 'q':
                restoreInputBuffering();
                cleanup();
                printf("Exiting...\n");
                return 0;
            default:
                printf("Invalid command. Use 'n' for next, 'p' for previous, 's' for stop, 'q' for quit.\n");
        }
    }
}
