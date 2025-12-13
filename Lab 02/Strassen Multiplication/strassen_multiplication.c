#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Allocate n x n matrix, initialized with 0
int** makeMatrix(int n) {
    int** mat = (int**)malloc(n * sizeof(int*));
    if (mat == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    for (int i = 0; i < n; i++) {
        mat[i] = (int*)calloc(n, sizeof(int));
        if (mat[i] == NULL) {
            printf("Memory allocation failed!\n");
            // Free previously allocated memory
            for (int j = 0; j < i; j++) {
                free(mat[j]);
            }
            free(mat);
            exit(1);
        }
    }
    return mat;
}

// Free matrix
void freeMatrix(int** mat, int n) {
    for (int i = 0; i < n; i++) free(mat[i]);
    free(mat);
}

// Add two matrices
void addMatrix(int** A, int** B, int** C, int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C[i][j] = A[i][j] + B[i][j];
}

// Subtract two matrices
void subMatrix(int** A, int** B, int** C, int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C[i][j] = A[i][j] - B[i][j];
}

// Strassen recursive multiplication
void strassen(int** A, int** B, int** C, int n) {
    if (n == 1) { // base case
        C[0][0] = A[0][0] * B[0][0];
        return;
    }

    int k = n / 2;

    // allocate submatrices
    int** A11 = makeMatrix(k); int** A12 = makeMatrix(k);
    int** A21 = makeMatrix(k); int** A22 = makeMatrix(k);
    int** B11 = makeMatrix(k); int** B12 = makeMatrix(k);
    int** B21 = makeMatrix(k); int** B22 = makeMatrix(k);

    // divide matrices into 4 parts
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < k; j++) {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + k];
            A21[i][j] = A[i + k][j];
            A22[i][j] = A[i + k][j + k];

            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + k];
            B21[i][j] = B[i + k][j];
            B22[i][j] = B[i + k][j + k];
        }
    }

    // temporary matrices
    int** M1 = makeMatrix(k); int** M2 = makeMatrix(k);
    int** M3 = makeMatrix(k); int** M4 = makeMatrix(k);
    int** M5 = makeMatrix(k); int** M6 = makeMatrix(k);
    int** M7 = makeMatrix(k);

    int** T1 = makeMatrix(k); int** T2 = makeMatrix(k);

    // M1 = (A11 + A22)(B11 + B22)
    addMatrix(A11, A22, T1, k);
    addMatrix(B11, B22, T2, k);
    strassen(T1, T2, M1, k);

    // M2 = (A21 + A22)B11
    addMatrix(A21, A22, T1, k);
    strassen(T1, B11, M2, k);

    // M3 = A11(B12 - B22)
    subMatrix(B12, B22, T2, k);
    strassen(A11, T2, M3, k);

    // M4 = A22(B21 - B11)
    subMatrix(B21, B11, T2, k);
    strassen(A22, T2, M4, k);

    // M5 = (A11 + A12)B22
    addMatrix(A11, A12, T1, k);
    strassen(T1, B22, M5, k);

    // M6 = (A21 - A11)(B11 + B12)
    subMatrix(A21, A11, T1, k);
    addMatrix(B11, B12, T2, k);
    strassen(T1, T2, M6, k);

    // M7 = (A12 - A22)(B21 + B22)
    subMatrix(A12, A22, T1, k);
    addMatrix(B21, B22, T2, k);
    strassen(T1, T2, M7, k);

    // C11 = M1 + M4 - M5 + M7
    int** C11 = makeMatrix(k); int** C12 = makeMatrix(k);
    int** C21 = makeMatrix(k); int** C22 = makeMatrix(k);

    addMatrix(M1, M4, T1, k);
    subMatrix(T1, M5, T2, k);
    addMatrix(T2, M7, C11, k);

    // C12 = M3 + M5
    addMatrix(M3, M5, C12, k);

    // C21 = M2 + M4
    addMatrix(M2, M4, C21, k);

    // C22 = M1 - M2 + M3 + M6
    subMatrix(M1, M2, T1, k);
    addMatrix(T1, M3, T2, k);
    addMatrix(T2, M6, C22, k);

    // combine into result matrix C
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < k; j++) {
            C[i][j] = C11[i][j];
            C[i][j + k] = C12[i][j];
            C[i + k][j] = C21[i][j];
            C[i + k][j + k] = C22[i][j];
        }
    }

    // free all temporary matrices
    freeMatrix(A11, k); freeMatrix(A12, k);
    freeMatrix(A21, k); freeMatrix(A22, k);
    freeMatrix(B11, k); freeMatrix(B12, k);
    freeMatrix(B21, k); freeMatrix(B22, k);
    freeMatrix(M1, k); freeMatrix(M2, k); freeMatrix(M3, k);
    freeMatrix(M4, k); freeMatrix(M5, k); freeMatrix(M6, k); freeMatrix(M7, k);
    freeMatrix(C11, k); freeMatrix(C12, k); freeMatrix(C21, k); freeMatrix(C22, k);
    freeMatrix(T1, k); freeMatrix(T2, k);
}

// Helper to compute next power of 2
int nextPowerOfTwo(int n) {
    int p = 1;
    while (p < n) p <<= 1;
    return p;
}

// ...existing code until main()...

int main() {
    int r1, c1, r2, c2;
    char newline;
    
    // Input validation for first matrix
    printf("Enter size of first matrix (rows cols): ");
    if(scanf("%d %d%c", &r1, &c1, &newline) != 3 || newline != '\n' || r1 <= 0 || c1 <= 0) {
        printf("Invalid input! Please enter only two positive integers.\n");
        return 0;
    }

    // Input validation for second matrix
    printf("Enter size of second matrix (rows cols): ");
    if(scanf("%d %d%c", &r2, &c2, &newline) != 3 || newline != '\n' || r2 <= 0 || c2 <= 0) {
        printf("Invalid input! Please enter only two positive integers.\n");
        return 0;
    }

    // Check if multiplication is possible
    if (c1 != r2) {
        printf("Matrix multiplication not possible!\n");
        return 0;
    }

    // Find the maximum dimension and get next power of 2
    int n = nextPowerOfTwo(fmax(fmax(r1, c1), fmax(r2, c2)));

    // Allocate matrices with padding
    int** A = makeMatrix(n);
    int** B = makeMatrix(n);
    int** C = makeMatrix(n);

    // Input for first matrix with validation
    printf("\nEnter first matrix (%dx%d):\n", r1, c1);
    for (int i = 0; i < r1; i++) {
        for (int j = 0; j < c1; j++) {
            if (scanf("%d", &A[i][j]) != 1) {
                printf("Invalid input! Please enter integers only.\n");
                freeMatrix(A, n);
                freeMatrix(B, n);
                freeMatrix(C, n);
                return 0;
            }
        }
    }
    while(getchar() != '\n'); // Clear input buffer

    // Input for second matrix with validation
    printf("\nEnter second matrix (%dx%d):\n", r2, c2);
    for (int i = 0; i < r2; i++) {
        for (int j = 0; j < c2; j++) {
            if (scanf("%d", &B[i][j]) != 1) {
                printf("Invalid input! Please enter integers only.\n");
                freeMatrix(A, n);
                freeMatrix(B, n);
                freeMatrix(C, n);
                return 0;
            }
        }
    }
    while(getchar() != '\n'); // Clear input buffer

    // Display input matrices
    printf("\nFirst Matrix (%dx%d):\n", r1, c1);
    for (int i = 0; i < r1; i++) {
        for (int j = 0; j < c1; j++)
            printf("%d ", A[i][j]);
        printf("\n");
    }

    printf("\nSecond Matrix (%dx%d):\n", r2, c2);
    for (int i = 0; i < r2; i++) {
        for (int j = 0; j < c2; j++)
            printf("%d ", B[i][j]);
        printf("\n");
    }

    // If matrices were padded, inform user
    if (n > r1 || n > c1 || n > r2 || n > c2) {
        printf("\nNote: Matrices will be padded to %dx%d for Strassen multiplication\n", n, n);
    }

    // Perform multiplication
    strassen(A, B, C, n);

    // Display only the relevant part of result
    printf("\nResultant Matrix (%dx%d):\n", r1, c2);
    for (int i = 0; i < r1; i++) {
        for (int j = 0; j < c2; j++)
            printf("%d ", C[i][j]);
        printf("\n");
    }

    // Free memory
    freeMatrix(A, n);
    freeMatrix(B, n);
    freeMatrix(C, n);

    return 0;
}