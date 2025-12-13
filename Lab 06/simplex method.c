#include <stdio.h>

#define MAX 10  // Maximum number of variables or constraints

// Function to perform Simplex Algorithm
void simplex(int m, int n, float a[MAX][MAX], float b[MAX], float c[MAX]) {
    float ratio[MAX], z[MAX], x[MAX];
    int i, j, pivot_col, pivot_row;
    float pivot, temp, max;

    // Initialize basic variables to 0
    for (i = 0; i < n; i++)
        x[i] = 0;

    while (1) {
        // Step 1: Calculate Zj - Cj
        for (j = 0; j < n; j++) {
            z[j] = 0;
            for (i = 0; i < m; i++)
                z[j] += a[i][j] * x[i];
            z[j] -= c[j];
        }

        // Step 2: Find most negative Zj - Cj
        max = 0;
        pivot_col = -1;
        for (j = 0; j < n; j++) {
            if (z[j] < max) {
                max = z[j];
                pivot_col = j;
            }
        }

        // If all Zj - Cj ≥ 0, optimal solution reached
        if (pivot_col == -1)
            break;

        // Step 3: Compute ratios to find pivot row
        for (i = 0; i < m; i++) {
            if (a[i][pivot_col] > 0)
                ratio[i] = b[i] / a[i][pivot_col];
            else
                ratio[i] = 9999;  // Large number for invalid ratios
        }

        // Find smallest ratio
        pivot_row = 0;
        for (i = 1; i < m; i++)
            if (ratio[i] < ratio[pivot_row])
                pivot_row = i;

        // Step 4: Pivot operation
        pivot = a[pivot_row][pivot_col];
        for (j = 0; j < n; j++)
            a[pivot_row][j] /= pivot;
        b[pivot_row] /= pivot;

        for (i = 0; i < m; i++) {
            if (i != pivot_row) {
                temp = a[i][pivot_col];
                for (j = 0; j < n; j++)
                    a[i][j] -= temp * a[pivot_row][j];
                b[i] -= temp * b[pivot_row];
            }
        }
    }

    // Step 5: Display the result
    printf("\nOptimal solution:\n");
    for (i = 0; i < m; i++)
        printf("x%d = %.2f\n", i + 1, b[i]);
}

int main() {
    int m, n, i, j;
    float a[MAX][MAX], b[MAX], c[MAX];

    printf("Enter number of constraints: ");
    scanf("%d", &m);
    printf("Enter number of variables: ");
    scanf("%d", &n);

    printf("Enter the coefficients of constraints (A matrix):\n");
    for (i = 0; i < m; i++)
        for (j = 0; j < n; j++)
            scanf("%f", &a[i][j]);

    printf("Enter the RHS values (b array):\n");
    for (i = 0; i < m; i++)
        scanf("%f", &b[i]);

    printf("Enter the objective function coefficients (c array):\n");
    for (j = 0; j < n; j++)
        scanf("%f", &c[j]);

    simplex(m, n, a, b, c);
    return 0;
}
