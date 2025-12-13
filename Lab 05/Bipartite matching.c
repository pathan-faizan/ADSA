#include <stdio.h>
#include <stdbool.h>

#define MAX 10

int n, m;                     // n = left vertices, m = right vertices
int graph[MAX][MAX];          // adjacency matrix
int matchR[MAX];              // which left node each right node is matched to
bool visited[MAX];

// Try to find a match for left node u
bool findMatch(int u) {
    for (int v = 0; v < m; v++) {
        // if there is an edge and right vertex v is not visited
        if (graph[u][v] && !visited[v]) {
            visited[v] = true;

            // if right vertex v is free OR
            // previously matched left vertex for v can be rematched
            if (matchR[v] == -1 || findMatch(matchR[v])) {
                matchR[v] = u;    // assign v to u
                return true;
            }
        }
    }
    return false;
}

int main() {
    printf("Enter number of left vertices: ");
    scanf("%d", &n);
    printf("Enter number of right vertices: ");
    scanf("%d", &m);

    printf("Enter adjacency matrix (%d x %d):\n", n, m);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            scanf("%d", &graph[i][j]);

    // initialize all right vertices as unmatched
    for (int i = 0; i < m; i++)
        matchR[i] = -1;

    int result = 0;  // count of matches

    // try to find match for every left vertex
    for (int u = 0; u < n; u++) {
        for (int i = 0; i < m; i++)
            visited[i] = false;

        if (findMatch(u))
            result++;
    }

    printf("\nMaximum matching = %d\n", result);
    printf("Matched pairs (Left -> Right):\n");
    for (int v = 0; v < m; v++) {
        if (matchR[v] != -1)
            printf("%d -> %d\n", matchR[v], v);
    }

    return 0;
}
