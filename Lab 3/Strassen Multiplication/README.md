# Strassen Matrix Multiplication in C

## 📌 Problem Statement
Strassen's algorithm is a **divide-and-conquer algorithm** for matrix multiplication that reduces the number of recursive multiplications from 8 to 7, improving the theoretical complexity from O(n³) to O(n^2.807).

---

## ⚙️ Algorithm Explanation

1. **Matrix Division**
   - Divide input matrices A and B into four sub-matrices of equal size
   - Pad matrices with zeros if dimensions aren't powers of 2

2. **Strassen's Seven Multiplications**
   - M1 = (A11 + A22)(B11 + B22)
   - M2 = (A21 + A22)B11
   - M3 = A11(B12 - B22)
   - M4 = A22(B21 - B11)
   - M5 = (A11 + A12)B22
   - M6 = (A21 - A11)(B11 + B12)
   - M7 = (A12 - A22)(B21 + B22)

3. **Result Computation**
   - C11 = M1 + M4 - M5 + M7
   - C12 = M3 + M5
   - C21 = M2 + M4
   - C22 = M1 - M2 + M3 + M6

---

## ⏱️ Time Complexity
- **Traditional Multiplication:** `O(n³)`
- **Strassen's Algorithm:** `O(n^2.807)`
- **Space Complexity:** `O(n²)`

---

## ⚙️ How to Run

### **Option 1: Run Precompiled Executable**
```bash
./strassen_multiplication
```

### **Option 2: Compile from Source**
```bash
git clone https://github.com/your-username/ADSA.git
cd "Lab 3/Strassen Multiplication"

# Compile
gcc strassen_multiplication.c -o strassen_multiplication -lm

# Run
./strassen_multiplication
```

### Input Example
```bash
Enter size of first matrix (rows cols): 2 2
Enter first matrix (2x2):
1 2
3 4

Enter size of second matrix (rows cols): 2 2
Enter second matrix (2x2):
5 6
7 8
```

### Output Example
```bash
First Matrix (2x2):
1 2
3 4

Second Matrix (2x2):
5 6
7 8

Resultant Matrix (2x2):
19 22
43 50
```

### Note
- Matrix dimensions must be compatible for multiplication (first matrix columns = second matrix rows)
- Program automatically handles non-power-of-2 dimensions by padding with zeros
- Only the relevant portion of the result (excluding padding) is displayed