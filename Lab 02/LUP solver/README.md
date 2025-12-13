# LUP Matrix Solver in C

## 📌 Problem Statement
Solve a system of linear equations `Ax = b` using LUP decomposition where A = PLU:
- L is a lower triangular matrix
- U is an upper triangular matrix 
- P is a permutation matrix

---

## ⚙️ Algorithm Explanation

1. **Matrix Input & Initialization**
   - Get system size n
   - Input L (lower triangular)
   - Input U (upper triangular)
   - Initialize P as identity matrix
   - Input vector b

2. **Matrix Validation**
   ```c
   // Lower triangular check
   if L[i][j] ≈ 0 for i < j
   if L[i][i] ≠ 0 for all i

   // Upper triangular check  
   if U[i][j] ≈ 0 for i > j
   if U[i][i] ≠ 0 for all i
   ```

3. **Solution Steps**
   ```
   1. Apply permutation: Pb = P × b
   2. Forward substitution: Ly = Pb
   3. Backward substitution: Ux = y
   ```

---

## ⏱️ Complexity Analysis
- **Space Complexity:** `O(n²)` for matrices + `O(n)` for vectors
- **Time Complexity:** `O(n²)` for triangular solves

---

## ⚙️ How to Run

### **Compilation**
```bash
gcc lup_solver.c -o lup_solver -lm
```

### **Execution**
```bash
./lup_solver
```

### **Input Format**
```
Enter size of system n: 2

Enter lower triangular matrix L (2x2):
1 0
2 1

Enter upper triangular matrix U (2x2):
1 2
0 1

Do you want to enter row permutations? (1 for yes, 0 for no): 1
Enter rows to swap (0 to 1): 0 1

Enter RHS vector b (2 elements):
1
2
```

### **Output Format**
```
Matrix L:
1.0000  0.0000
2.0000  1.0000

Matrix U:
1.0000  2.0000
0.0000  1.0000

Final Permutation Matrix P:
0.0000  1.0000
1.0000  0.0000

Solution vector x:
[x₁ x₂]
```

---

## 🔍 Key Features

1. **Matrix Validation**
   - Validates triangular structure
   - Checks for zero diagonal elements
   - Verifies matrix dimensions

2. **Permutation Handling**
   - Interactive row swapping
   - Displays intermediate states
   - Validates swap indices

3. **Error Handling**
   - Memory allocation checks
   - Input validation
   - Matrix structure verification

---

## 📝 Notes & Limitations
- Matrices must be properly triangular
- Non-zero diagonal elements required
- System size must be positive integer
- Row indices for permutations must be valid (0 to n-1)
- Uses double precision floating-point arithmetic

---

## 💡 Example Use Case
```
Ax = b where A = PLU

Given:
L = [1 0; 2 1]
U = [1 2; 0 1]
P = [0 1; 1 0]
b = [1; 2]

Solve:
1. Pb = [2; 1]
2. Ly = Pb → y = [2; -3]
3. Ux = y → x = [1; -1]
```