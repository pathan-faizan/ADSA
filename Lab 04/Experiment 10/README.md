# ⚡ Strassen’s Matrix Multiplication (Recursive Implementation in C)

This program implements **Strassen’s Algorithm**, an optimized method for matrix multiplication that reduces the number of multiplications from 8 to **7**, improving efficiency over the standard divide-and-conquer approach.

It accepts two **n × n matrices** where **n must be a power of 2** (e.g., 2, 4, 8).

---

## 📌 Features
- Recursive **Strassen algorithm**
- Supports matrices up to **10 × 10**
- Performs matrix:
  - Addition  
  - Subtraction  
- Divides matrices into four submatrices
- Computes 7 Strassen products:  
  `M1` to `M7`
- Combines submatrices back into the final result
- Clean formatted matrix print function

---

## 🧠 How Strassen Algorithm Works

For matrices A and B:

A is divided as:  
```
A11 A12
A21 A22
```

B is divided as:  
```
B11 B12
B21 B22
```

Compute 7 products:
```
M1 = (A11 + A22)(B11 + B22)
M2 = (A21 + A22)B11
M3 = A11(B12 − B22)
M4 = A22(B21 − B11)
M5 = (A11 + A12)B22
M6 = (A21 − A11)(B11 + B12)
M7 = (A12 − A22)(B21 + B22)
```

Then compute the final quadrants:
```
C11 = M1 + M4 − M5 + M7
C12 = M3 + M5
C21 = M2 + M4
C22 = M1 − M2 + M3 + M6
```

---

## 🚀 Build & Run

### Compile
```bash
gcc strassen.c -o strassen
```

### Run
```bash
./strassen
```

---

## 📊 Example Session
```
Enter the size of the square matrices (power of 2, e.g., 2, 4, 8): 2
Enter elements of Matrix A:
1 2
3 4
Enter elements of Matrix B:
5 6
7 8

Resultant Matrix after Strassen Multiplication:
  19   22
  43   50
```

---

## ✔ Requirements
- Matrix dimension **must be a power of 2**
- Use padding (adding zeros) for other sizes (not implemented here)

---

## 🧠 Insight
Strassen reduces complexity:
- Standard multiplication: **O(n³)**
- Strassen: **O(n^2.81)**

This program demonstrates a classic divide-and-conquer optimization used in advanced numerical algorithms.

