#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INF 99999
#define MAX 20   // Maximum vertices

// -------------------- GLOBAL --------------------
int graph[MAX][MAX];
int V;  // number of vertices

// -------------------- (a) READ GRAPH IN SIF --------------------
/*
   SIF format example:
   A B 4
   A C 2
   B C 5
   B D 10
   C D 3
   END
   (means: A-B has weight 4, A-C has weight 2, etc.)
*/
int getIndex(char nodes[MAX][10], char *name, int *count) {
    for (int i = 0; i < *count; i++) {
        if (strcmp(nodes[i], name) == 0) return i;
    }
    strcpy(nodes[*count], name);
    (*count)++;
    return (*count) - 1;
}

void readSIF() {
    char u[10], v[10];
    int w;
    char nodes[MAX][10];
    int count = 0;

    printf("Enter edges in SIF format (u v w). Type END to stop:\n");

    for (int i = 0; i < MAX; i++)
        for (int j = 0; j < MAX; j++)
            graph[i][j] = (i == j) ? 0 : INF;

    while (1) {
        scanf("%s", u);
        if (strcmp(u, "END") == 0) break;
        scanf("%s %d", v, &w);

        int i = getIndex(nodes, u, &count);
        int j = getIndex(nodes, v, &count);
        graph[i][j] = w;  // directed graph
        graph[j][i] = w;  // make this undirected if needed
    }
    V = count;

    printf("\nGraph adjacency matrix:\n");
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            if (graph[i][j] == INF) printf("INF ");
            else printf("%3d ", graph[i][j]);
        }
        printf("\n");
    }
}

// -------------------- (b) DIJKSTRA --------------------
void dijkstra(int src) {
    int dist[MAX], visited[MAX];
    for (int i = 0; i < V; i++) {
        dist[i] = INF;
        visited[i] = 0;
    }
    dist[src] = 0;

    for (int count = 0; count < V - 1; count++) {
        int u = -1, min = INF;
        for (int i = 0; i < V; i++)
            if (!visited[i] && dist[i] < min) {
                min = dist[i];
                u = i;
            }

        visited[u] = 1;

        for (int v = 0; v < V; v++) {
            if (!visited[v] && graph[u][v] != INF &&
                dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
            }
        }
    }

    printf("\nDijkstra (source %d):\n", src);
    for (int i = 0; i < V; i++) {
        if (dist[i] == INF) printf("Node %d: INF\n", i);
        else printf("Node %d: %d\n", i, dist[i]);
    }
}

// -------------------- (c) FLOYD WARSHALL --------------------
void floydWarshall() {
    int dist[MAX][MAX];

    for (int i = 0; i < V; i++)
        for (int j = 0; j < V; j++)
            dist[i][j] = graph[i][j];

    for (int k = 0; k < V; k++)
        for (int i = 0; i < V; i++)
            for (int j = 0; j < V; j++)
                if (dist[i][k] + dist[k][j] < dist[i][j])
                    dist[i][j] = dist[i][k] + dist[k][j];

    printf("\nFloyd-Warshall All-Pairs Shortest Paths:\n");
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            if (dist[i][j] == INF) printf("INF ");
            else printf("%3d ", dist[i][j]);
        }
        printf("\n");
    }
}

// -------------------- MAIN --------------------
int main() {
    int choice, src;

    while (1) {
        printf("\n--- Graph Algorithms ---\n");
        printf("1. Read Graph (SIF)\n2. Dijkstra (Single Source)\n3. Floyd-Warshall (All Pairs)\n4. Exit\nChoice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                readSIF();
                break;
            case 2:
                printf("Enter source vertex index (0-%d): ", V-1);
                scanf("%d", &src);
                dijkstra(src);
                break;
            case 3:
                floydWarshall();
                break;
            case 4:
                exit(0);
            default:
                printf("Invalid choice!\n");
        }
    }
    return 0;
}