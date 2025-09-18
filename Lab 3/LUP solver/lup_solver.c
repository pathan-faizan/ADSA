#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define EPSILON 1e-10

// Function declarations
double** makeMatrix(int n);
void freeMatrix(double **matrix, int n);
void printMatrix(double **matrix, int n, const char* name);
int isValidLowerTriangular(double **L, int n);
int isValidUpperTriangular(double **U, int n);
void swapRows(double **P, int r1, int r2, int n);
void applyPermutation(double **P, double *b, double *Pb, int n);
void forwardSolve(double **L, double *b, double *y, int n);
void backwardSolve(double **U, double *y, double *x, int n);

// Matrix allocation
double** makeMatrix(int n) {
    double **matrix = (double**)malloc(n * sizeof(double*));
    for(int i = 0; i < n; i++) {
        matrix[i] = (double*)calloc(n, sizeof(double));
    }
    return matrix;
}

// Matrix deallocation
void freeMatrix(double **matrix, int n) {
    for(int i = 0; i < n; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

// Print matrix with name
void printMatrix(double **matrix, int n, const char* name) {
    printf("\n%s:\n", name);
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            printf("%8.4lf ", matrix[i][j]);
        }
        printf("\n");
    }
}

// Validate lower triangular matrix
int isValidLowerTriangular(double **L, int n) {
    for(int i = 0; i < n; i++) {
        for(int j = i + 1; j < n; j++) {
            if(fabs(L[i][j]) > EPSILON) {
                return 0;
            }
        }
        if(fabs(L[i][i]) < EPSILON) {
            return 0;
        }
    }
    return 1;
}

// Validate upper triangular matrix
int isValidUpperTriangular(double **U, int n) {
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < i; j++) {
            if(fabs(U[i][j]) > EPSILON) {
                return 0;
            }
        }
        if(fabs(U[i][i]) < EPSILON) {
            return 0;
        }
    }
    return 1;
}

// Swap rows in permutation matrix
void swapRows(double **P, int r1, int r2, int n) {
    for(int j = 0; j < n; j++) {
        double temp = P[r1][j];
        P[r1][j] = P[r2][j];
        P[r2][j] = temp;
    }
}

// Apply permutation to vector
void applyPermutation(double **P, double *b, double *Pb, int n) {
    for(int i = 0; i < n; i++) {
        Pb[i] = 0;
        for(int j = 0; j < n; j++) {
            Pb[i] += P[i][j] * b[j];
        }
    }
}

// Forward substitution
void forwardSolve(double **L, double *b, double *y, int n) {
    for(int i = 0; i < n; i++) {
        y[i] = b[i];
        for(int j = 0; j < i; j++) {
            y[i] -= L[i][j] * y[j];
        }
        y[i] /= L[i][i];
    }
}

// Backward substitution
void backwardSolve(double **U, double *y, double *x, int n) {
    for(int i = n-1; i >= 0; i--) {
        x[i] = y[i];
        for(int j = i+1; j < n; j++) {
            x[i] -= U[i][j] * x[j];
        }
        x[i] /= U[i][i];
    }
}

int main() {
    int n;
    printf("Enter size of system n: ");
    scanf("%d", &n);

    if (n <= 0) {
        printf("Error: Matrix size must be positive\n");
        return 1;
    }

    double **L = makeMatrix(n);
    double **U = makeMatrix(n);
    double **P = makeMatrix(n);
    double *b = (double*)malloc(n * sizeof(double));
    double *Pb = (double*)malloc(n * sizeof(double));
    double *y = (double*)malloc(n * sizeof(double));
    double *x = (double*)malloc(n * sizeof(double));

    printf("\nEnter lower triangular matrix L (%d x %d) row by row:\n", n, n);
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            scanf("%lf", &L[i][j]);
        }
    }

    if (!isValidLowerTriangular(L, n)) {
        printf("Invalid lower triangular matrix L\n");
        freeMatrix(L, n); freeMatrix(U, n); freeMatrix(P, n);
        free(b); free(Pb); free(y); free(x);
        return 1;
    }

    printf("\nEnter upper triangular matrix U (%d x %d) row by row:\n", n, n);
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            scanf("%lf", &U[i][j]);
        }
    }

    if (!isValidUpperTriangular(U, n)) {
        printf("Invalid upper triangular matrix U\n");
        freeMatrix(L, n); freeMatrix(U, n); freeMatrix(P, n);
        free(b); free(Pb); free(y); free(x);
        return 1;
    }

    // Initialize P as identity
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            P[i][j] = (i == j) ? 1.0 : 0.0;
        }
    }

    printf("\nDo you want to enter row permutations? (1 for yes, 0 for no): ");
    int want_perm;
    scanf("%d", &want_perm);
    
        if(want_perm) {
        printf("How many row swaps? ");
        int num_swaps;
        scanf("%d", &num_swaps);
        
        for(int i = 0; i < num_swaps; i++) {
            int r1, r2;
            printf("Enter rows to swap (0 to %d): ", n-1);
            scanf("%d %d", &r1, &r2);
            if(r1 >= 0 && r1 < n && r2 >= 0 && r2 < n) {
                swapRows(P, r1, r2, n); 
                printf("Swapped rows %d and %d\n", r1, r2);
                printMatrix(P, n, "Current P matrix");
            } else {
                printf("Invalid row numbers! Try again.\n");
                i--;
            }
        }
    }

    printf("\nEnter RHS vector b (%d elements):\n", n);
    for(int i = 0; i < n; i++) {
        scanf("%lf", &b[i]);
    }

    applyPermutation(P, b, Pb, n);
    forwardSolve(L, Pb, y, n);
    backwardSolve(U, y, x, n);

    printMatrix(L, n, "Matrix L");
    printMatrix(U, n, "Matrix U");
    printMatrix(P, n, "Final Permutation Matrix P");

    printf("\nOriginal vector b:\n");
    for(int i = 0; i < n; i++) printf("%8.4lf ", b[i]);
    
    printf("\n\nPermuted vector Pb:\n");
    for(int i = 0; i < n; i++) printf("%8.4lf ", Pb[i]);
    
    printf("\n\nVector y from Ly = Pb:\n");
    for(int i = 0; i < n; i++) printf("%8.4lf ", y[i]);
    
    printf("\n\nSolution vector x from Ux = y:\n");
    for(int i = 0; i < n; i++) printf("%8.4lf ", x[i]);
    printf("\n");

    freeMatrix(L, n);
    freeMatrix(U, n);
    freeMatrix(P, n);
    free(b); free(Pb); free(y); free(x);

    return 0;
}