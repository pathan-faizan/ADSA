#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Function to create a new matrix
double** newMatrix(int n) {
    double** matrix = (double**)malloc(n * sizeof(double*));
    for(int i = 0; i < n; i++) {
        matrix[i] = (double*)calloc(n, sizeof(double));
    }
    return matrix;
}

// Function to free matrix memory
void freeMatrix(double** matrix, int n) {
    for(int i = 0; i < n; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

// Function to swap rows in a matrix
void swapRows(double** matrix, int i, int j, int n) {
    for(int k = 0; k < n; k++) {
        double temp = matrix[i][k];
        matrix[i][k] = matrix[j][k];
        matrix[j][k] = temp;
    }
}

// Function to display matrix
void show(double** matrix, int n, const char* name) {
    printf("\n%s:\n", name);
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            printf("%8.4f ", matrix[i][j]);
        }
        printf("\n");
    }
}

// Initialize permutation array
void initPermutation(int *P, int n) {
    for(int i = 0; i < n; i++) {
        P[i] = i;
    }
}

// Swap elements in permutation array
void swapPermutation(int *P, int i, int j) {
    int temp = P[i];
    P[i] = P[j];
    P[j] = temp;
}

// Show permutation matrix
void showPermutation(int *P, int n) {
    printf("\nPermutation array P:\n");
    for(int i = 0; i < n; i++) {
        printf("%d ", P[i]);
    }
    printf("\n");
}

// Function to multiply matrices
double** multiplyMatrices(double **A, double **B, int n) {
    double **result = newMatrix(n);
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            result[i][j] = 0;
            for(int k = 0; k < n; k++) {
                result[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    return result;
}

// Function to create permutation matrix from P array
double** createPermutationMatrix(int *P, int n) {
    double **pMatrix = newMatrix(n);
    for(int i = 0; i < n; i++) {
        pMatrix[P[i]][i] = 1.0;
    }
    return pMatrix;
}

// LUP decomposition
int lupDecompose(double **A, double **L, double **U, int *P, int n) {
    // Initialize P
    initPermutation(P, n);
    
    // Initialize L to zero
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            L[i][j] = 0.0;
        }
    }
    
    // Copy A to U as initial step
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            U[i][j] = A[i][j];

    for(int i = 0; i < n; i++) {
        // Find pivot
        double pivot_value = 0.0;
        int pivot_row = i;
        
        for(int j = i; j < n; j++) {
            if(fabs(U[j][i]) > pivot_value) {
                pivot_value = fabs(U[j][i]);
                pivot_row = j;
            }
        }

        // Check for singularity
        if(pivot_value < 1e-10) {
            return 0;  // Matrix is singular
        }

        // Swap rows if necessary
        if(pivot_row != i) {
            swapRows(U, i, pivot_row, n);
            if(i > 0) {
                swapRows(L, i, pivot_row, i);
            }
            swapPermutation(P, i, pivot_row);
        }

        // Compute L and U entries
        L[i][i] = 1.0;
        for(int j = i + 1; j < n; j++) {
            L[j][i] = U[j][i] / U[i][i];
            for(int k = i; k < n; k++) {
                U[j][k] -= L[j][i] * U[i][k];
            }
        }
    }
    return 1;
}

int main() {
    int n;
    printf("Enter size of matrix: ");
    scanf("%d", &n);

    double **A = newMatrix(n);
    double **L = newMatrix(n);
    double **U = newMatrix(n);
    int *P = (int *)malloc(n * sizeof(int));

    printf("Enter matrix A (%dx%d):\n", n, n);
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            scanf("%lf", &A[i][j]);

    if(!lupDecompose(A, L, U, P, n)) {
        printf("Matrix is singular. Cannot perform LUP decomposition.\n");
    } else {
        show(A, n, "Original Matrix A");
        show(L, n, "Lower Triangular Matrix L");
        show(U, n, "Upper Triangular Matrix U");
        showPermutation(P, n);
        
        // Verify: PA = LU
        printf("\nVerification: PA = LU\n");
        double **P_matrix = createPermutationMatrix(P, n);
        double **PA = multiplyMatrices(P_matrix, A, n);
        double **LU = multiplyMatrices(L, U, n);

        show(PA, n, "PA Matrix");
        show(LU, n, "LU Matrix");

        // Check if PA = LU
        int isCorrect = 1;
        for(int i = 0; i < n && isCorrect; i++) {
            for(int j = 0; j < n && isCorrect; j++) {
                if(fabs(PA[i][j] - LU[i][j]) > 1e-10) {
                    isCorrect = 0;
                }
            }
        }
        printf("\nVerification %s\n", isCorrect ? "PASSED" : "FAILED");

        // Free verification matrices
        freeMatrix(P_matrix, n);
        freeMatrix(PA, n);
        freeMatrix(LU, n);
    }

    // Free memory
    freeMatrix(A, n);
    freeMatrix(L, n);
    freeMatrix(U, n);
    free(P);

    return 0;
}