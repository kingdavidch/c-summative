#include <stdio.h>
#include <stdlib.h>

#define MAX_NODES 10

// Function to initialize adjacency matrix
void initializeMatrix(int matrix[MAX_NODES][MAX_NODES], int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            matrix[i][j] = 0;
        }
    }
}

// Function to add an edge to the graph
void addEdge(int matrix[MAX_NODES][MAX_NODES], int u, int v) {
    matrix[u][v] = 1;
    matrix[v][u] = 1;
}

// Function to find direct contacts
void findDirectContacts(int matrix[MAX_NODES][MAX_NODES], int size, int node) {
    printf("Direct contacts of node %d: ", node);
    for (int i = 0; i < size; i++) {
        if (matrix[node][i] == 1) {
            printf("%d ", i);
        }
    }
    printf("\n");
}

int main() {
    int matrix[MAX_NODES][MAX_NODES];
    initializeMatrix(matrix, MAX_NODES);

    // Add edges based on the problem statement
    addEdge(matrix, 0, 1); // 0781 calls 0782
    addEdge(matrix, 0, 2); // 0781 calls 0783
    addEdge(matrix, 1, 3); // 0782 calls 0784
    addEdge(matrix, 2, 4); // 0783 calls 0785
    addEdge(matrix, 3, 4); // 0784 calls 0785
    addEdge(matrix, 3, 5); // 0784 calls 0786
    addEdge(matrix, 4, 6); // 0785 calls 0787
    addEdge(matrix, 5, 7); // 0786 calls 0788

    int node;
    printf("Enter a node to find direct contacts: ");
    scanf("%d", &node);

    findDirectContacts(matrix, MAX_NODES, node);

    return 0;
}
