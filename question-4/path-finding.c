#include <stdio.h>
#include <limits.h>

#define V 6
char *cities[V] = {"Bumbogo", "Nayinzira", "Kanombe", "Mushimire", "Airport", "Kimironko"};
int graph[V][V] = {
    {0,10,30,0,0,0},
    {10,0,0,10,0,0},
    {30,0,0,0,5,0},
    {0,10,0,0,15,3},
    {0,0,5,15,0,4},
    {0,0,0,3,4,0}
};

int minDistance(int dist[], int visited[]) {
    int min = INT_MAX, min_index;
    for (int v = 0; v < V; v++)
        if (!visited[v] && dist[v] <= min) min = dist[v], min_index = v;
    return min_index;
}

void dijkstra(int src, int dest) {
    int dist[V], visited[V], prev[V];
    for (int i = 0; i < V; i++) dist[i] = INT_MAX, visited[i] = 0;
    dist[src] = 0;

    for (int count = 0; count < V-1; count++) {
        int u = minDistance(dist, visited);
        visited[u] = 1;
        for (int v = 0; v < V; v++)
            if (!visited[v] && graph[u][v] && dist[u] != INT_MAX && dist[u]+graph[u][v] < dist[v])
                dist[v] = dist[u] + graph[u][v], prev[v] = u;
    }

    printf("Shortest path time: %d\nPath: ", dist[dest]);
    int path[V], p = 0, c = dest;
    while (c != src) path[p++] = c, c = prev[c];
    path[p] = src;
    for (int i = p; i >= 0; i--) printf("%s ", cities[path[i]]);
}

int main() {
    dijkstra(0, 4); // Example: Bumbogo to Airport
    return 0;
}
