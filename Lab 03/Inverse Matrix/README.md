# 🔁 Matrix Inversion Using Gauss–Jordan Elimination (C Program)

This program computes the **inverse of an n × n matrix** using the **Gauss–Jordan elimination** method.  
It augments the input matrix with the identity matrix and performs row operations until the input becomes the identity, producing the inverse.

---

## 📌 Features
- Supports matrices up to **10 × 10**
- Performs:
  - Pivot selection
  - Row swapping if needed
  - Pivot normalization
  - Row elimination (above & below pivot)
- Detects **singular matrices**
- Outputs the final **inverse matrix**

---

## 🧠 How Gauss–Jordan Works

Given matrix **A**, augment it with identity **I**:
```
[A | I]
```

Apply row operations to transform it into:
```
[I | A⁻¹]
```

Steps used in the program:
1. **Find pivot**; if zero, swap rows.
2. **Normalize pivot row** (pivot → 1).
3. Eliminate pivot column in all other rows.
4. Continue until whole matrix is reduced.

If a pivot cannot be found → matrix is **singular** → no inverse.

---

## 🚀 Build & Run

### Compile
```bash
gcc gauss_jordan_inverse.c -o gauss_jordan_inverse
```

### Run
```bash
./gauss_jordan_inverse
```

---

## 📊 Example Input & Output
```
Enter size of square matrix (n x n): 3
Enter elements of matrix:
1 2 3
0 1 4
5 6 0

Inverse Matrix:
   -24.000     18.000      5.000
    20.000    -15.000     -4.000
    -5.000      4.000      1.000
```

---

## 🧠 Insight
Gauss–Jordan elimination is a fundamental numerical method used to:
- Compute matrix inverse  
- Solve linear systems  
- Perform rank analysis  

This implementation shows the full row-reduction process clearly and efficiently.

