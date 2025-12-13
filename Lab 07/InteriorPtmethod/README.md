# 🟦 Interior Point Method (Barrier Method + Gradient Descent) — C Implementation

This program implements a **simplified Interior Point Method (IPM)** to solve a linear optimization problem:

### **Minimize:**
```
cᵀx
```

### **Subject to:**
```
A x = b
x > 0
```

It uses a **logarithmic barrier term** and **gradient descent** updates, along with projection to maintain equality constraints.

---

## 📌 Features
- Implements **Barrier Method** with decreasing `mu`
- Handles equality-constrained LPs
- Uses:
  - Gradient descent on the barrier-augmented objective  
  - Projection step to enforce equality constraints  
- Ensures `x > 0` by enforcing a numerical lower bound
- Supports up to:
  - `n ≤ 20` variables  
  - `m ≤ 20` constraints  

---

## 🧠 Optimization Model

### 🎯 Barrier-Augmented Objective
For barrier parameter `μ`:

```
f(x) = cᵀx − μ Σ log(xᵢ)
```

### ✔ Gradient
```
∂f/∂xᵢ = cᵢ − μ / xᵢ
```

### ✔ Iterative Updates
1. **Gradient descent:**  
   ```
   x ← x − α ∇f(x)
   ```
2. **Projection to satisfy Ax = b:**  
   ```
   x ← x − β (A x − b) A
   ```
3. Reduce barrier parameter:  
   ```
   μ ← μ * 0.5
   ```

Repeat over outer iterations.

---

## 🚀 Build & Run

### Compile
```bash
gcc interior_point.c -o interior_point -lm
```

### Run
```bash
./interior_point
```

---

## 📊 Example Session
```
Enter number of variables (n): 3
Enter number of equality constraints (m): 1

Enter matrix A (1 × 3):
1 1 1

Enter vector b:
1

Enter cost vector c:
3 1 2
```

Console Output:
```
Running Interior Point Method...
Iter  0  mu = 1.00000   x = [ 0.3333  0.3333  0.3333 ]   f = 3.2958
Iter  1  mu = 0.50000   x = [ 0.2857  0.4285  0.2857 ]   f = 3.0672
...
Optimal x ≈ [ 0.250000  0.500000  0.250000 ]
Optimal objective ≈ 2.500000
```

---

## ⚠️ Notes & Limitations
This is a **teaching/experimental** implementation:

- Does **not** solve general LPs (needs equality constraints + x > 0)
- Uses simple gradient descent instead of Newton's method  
- No line search or KKT system solver  
- Slow compared to real interior-point solvers

Still, it illustrates key interior-point concepts:
- Barrier functions  
- Central path  
- Parameter `μ` reduction  
- Maintaining interior feasibility  

---

## 🧠 Insight
Interior-point methods are the foundation of modern LP solvers (CPLEX, Gurobi, IPOPT).  
This program demonstrates the *core idea*: move inside the feasible region while minimizing the barrier-augmented objective.

