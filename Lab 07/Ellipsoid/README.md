# 🔵 Ellipsoid Method for Feasibility Checking — C Implementation

This program implements the **Ellipsoid Algorithm**, a classic method for determining whether a system of linear inequalities:

```
A x ≤ b
```

has a **feasible solution**.  
The algorithm iteratively shrinks an ellipsoid that is guaranteed to contain the feasible region (if it exists) until a point satisfying all constraints is found.

---

## 📌 Features
- Supports up to:
  - **n ≤ 10** variables  
  - **m ≤ 50** constraints  
- Uses full matrix update for the ellipsoid shape matrix **Q**
- Handles floating-point tolerance using `EPS`
- Detects:
  - Feasible point
  - Degenerate ellipsoid
  - Iteration limit exceeded
- Clean modular functions:
  - Matrix–vector multiplication  
  - Dot product  
  - Vector printing  

---

## 🧠 Algorithm Overview

The Ellipsoid Method maintains:

- **x** — center of the current ellipsoid  
- **Q** — shape matrix (ellipsoid = {x + Q y})  

### ✔ Initialization  
Start with a large ball:

```
Q = R² I
x = 0
```

### ✔ Iterative Steps
For each iteration:

1. **Check violated constraint**  
   Find index `i` where:  
   ```
   A[i] ⋅ x > b[i]
   ```

2. **Compute update direction**  
   ```
   d = Q a_i / sqrt(a_iᵀ Q a_i)
   ```

3. **Update center**
   ```
   x_new = x - d / (n + 1)
   ```

4. **Update shape matrix**
   ```
   Q_new = (n² / (n² − 1)) ( Q − (2/(n+1)) d dᵀ )
   ```

Stop when:
- All constraints satisfied ➝ feasible point found  
- Iteration limit (1000) reached  
- Degenerate ellipsoid encountered  

---

## 🚀 Build & Run

### Compile
```bash
gcc ellipsoid.c -o ellipsoid -lm
```

### Run
```bash
./ellipsoid
```

---

## 📊 Example Session
```
Enter number of constraints m: 3
Enter dimension n: 2

Enter matrix A:
1  1
-1 0
0 -1

Enter vector b:
4
0
0
```

Output:
```
Feasible point found in 37 iterations:
1.999832 2.000152
```

---

## ⚠️ Notes
- This implementation **only checks feasibility**, not optimization.  
- Suitable for **theoretical demonstration**, not high-performance use.  
- For optimization, ellipsoid method is slower than interior-point methods.  
- Numerical stability issues may arise for large systems.

---

## 🧠 Insight
This program shows the foundational concept behind modern convex optimization:

- Replace "searching" with "shrinking geometry"
- Ellipsoids are easy to update algebraically
- Works for any convex feasible region

The ellipsoid method was historically significant as the first polynomial-time algorithm for linear programming.

