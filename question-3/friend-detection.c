#include <stdio.h>
#include <string.h>

#define MAX_NODES 8
char *numbers[MAX_NODES] = {"0781", "0782", "0783", "0784", "0785", "0786", "0787", "0788"};
int matrix[MAX_NODES][MAX_NODES] = {0};

int getIndex(char *num) {
    for (int i = 0; i < MAX_NODES; i++)
        if (strcmp(numbers[i], num) == 0) return i;
    return -1;
}

void addEdge(char *a, char *b) {
    int i = getIndex(a), j = getIndex(b);
    matrix[i][j] = matrix[j][i] = 1;
}

void printContacts(char *num) {
    int idx = getIndex(num);
    if (idx == -1) { printf("Invalid number\n"); return; }
    printf("Direct contacts: ");
    for (int i = 0; i < MAX_NODES; i++)
        if (matrix[idx][i]) printf("%s ", numbers[i]);
    printf("\n");
}

void printMatrix() {
    printf("\nAdjacency Matrix:\n");
    for (int i = 0; i < MAX_NODES; i++) {
        for (int j = 0; j < MAX_NODES; j++)
            printf("%d ", matrix[i][j]);
        printf("\n");
    }
}

int main() {
    // Define edges as per the problem
    addEdge("0781", "0782"); addEdge("0781", "0783");
    addEdge("0782", "0784"); addEdge("0783", "0785");
    addEdge("0784", "0785"); addEdge("0784", "0786");
    addEdge("0785", "0787"); addEdge("0786", "0788");

    char input[5];
    printf("Enter a phone number: ");
    scanf("%s", input);
    printContacts(input);
    printMatrix();
    return 0;
}
