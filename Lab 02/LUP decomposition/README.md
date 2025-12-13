# LUP Decomposition in C

## 📌 Problem Statement
LUP Decomposition breaks down a matrix A into three matrices: L (lower triangular), U (upper triangular), and P (permutation) such that PA = LU. This decomposition is useful for solving linear equations and finding matrix inverses.

---

## ⚙️ Algorithm Explanation

1. **Initialization**
   - Create matrices L, U and permutation array P
   - Copy matrix A to U
   - Initialize L as zero matrix with diagonal elements as 1
   - Initialize P as [0,1,2,...,n-1]

2. **Pivot Selection**
   - For each column i
   - Find the largest absolute value in column i (pivot)
   - Swap current row with pivot row if necessary
   - Update P array to track row swaps

3. **Matrix Decomposition**
   - Compute L and U entries:
   - L[j][i] = U[j][i] / U[i][i]
   - U[j][k] -= L[j][i] * U[i][k]
   - Ensure L has unit diagonal elements

4. **Verification**
   - Verify PA = LU by matrix multiplication
   - Convert P array to permutation matrix
   - Compare PA and LU matrices

---

## ⏱️ Time Complexity
- **Overall Complexity:** `O(n³)`
- **Space Complexity:** `O(n²)`

---

## ⚙️ How to Run

### **Compile from Source**
```bash
git clone https://github.com/pathan-faizan/ADSA.git
cd "Lab 3/LUP decomposition"

# Compile
gcc lup_decomposition.c -o lup_decomposition -lm

# Run
./lup_decomposition
```

### Input Example
```bash
Enter size of matrix: 3
Enter matrix A (3x3):
2 -1 0
-1 2 -1
0 -1 2
```

### Output Example
```bash
Original Matrix A:
2.0000 -1.0000  0.0000
-1.0000  2.0000 -1.0000
0.0000 -1.0000  2.0000

Lower Triangular Matrix L:
1.0000  0.0000  0.0000
-0.5000  1.0000  0.0000
0.0000 -0.6667  1.0000

Upper Triangular Matrix U:
2.0000 -1.0000  0.0000
0.0000  1.5000 -1.0000
0.0000  0.0000  1.3333

Permutation array P:
0 1 2

Verification PASSED
```

---

## 🔍 Key Functions

1. **Matrix Operations**
   - `newMatrix()`: Allocates memory for a new matrix
   - `freeMatrix()`: Frees allocated matrix memory
   - `swapRows()`: Swaps rows in a matrix
   - `multiplyMatrices()`: Multiplies two matrices

2. **Permutation Handling**
   - `initPermutation()`: Initializes permutation array
   - `swapPermutation()`: Swaps elements in permutation array
   - `createPermutationMatrix()`: Converts P array to matrix

3. **Display Functions**
   - `show()`: Displays a matrix
   - `showPermutation()`: Displays permutation array

### Note
- Matrix must be non-singular for successful decomposition
- Numerical stability is ensured through partial pivoting
- Program includes verification of PA = LU