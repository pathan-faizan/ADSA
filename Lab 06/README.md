# 📈 Simplex Algorithm (Basic Implementation in C)

This program implements a **basic Simplex Method** for solving Linear Programming Problems (LPPs) of the form:

### **Maximize:**  
```
Z = c₁x₁ + c₂x₂ + ... + cₙxₙ
```

### **Subject to constraints:**  
```
a₁₁x₁ + a₁₂x₂ + ... + a₁ₙxₙ ≤ b₁
a₂₁x₁ + a₂₂x₂ + ... + a₂ₙxₙ ≤ b₂
...
aₘ₁x₁ + aₘ₂x₂ + ... + aₘₙxₙ ≤ bₘ
```

This implementation uses a basic tableau approach (not full simplex), suitable for academic demonstration.

---

## 📌 Features
- Implements **Simplex method** using pivot operations  
- Accepts:
  - Coefficient matrix **A**
  - RHS vector **b**
  - Objective function **c**
- Computes:
  - Pivot column (entering variable)
  - Pivot row (leaving variable)
  - Performs Gauss–Jordan pivoting
- Stops when all reduced costs `Zj - Cj ≥ 0`
- Prints the **optimal values** of variables

---

## 🧠 How the Algorithm Works

### ✦ Step 1 — Compute Reduced Costs  
```
Zj = Σ(a[i][j] * x[i])
Zj - Cj
```

### ✦ Step 2 — Find the Most Negative (Entering Variable)  
If none are negative → optimal solution reached.

### ✦ Step 3 — Compute Ratios for Leaving Variable  
```
ratio[i] = b[i] / a[i][pivot_col]
```

### ✦ Step 4 — Pivot Operation  
Normalize pivot row and eliminate pivot column from others.

### ✦ Step 5 — Final Output  
Print basic variable values (`b[i]` after pivoting).

---

## 🚀 Build & Run

### Compile
```bash
gcc simplex.c -o simplex
```

### Run
```bash
./simplex
```

---

## 📊 Example Session
```
Enter number of constraints: 2
Enter number of variables: 2

Enter A matrix:
1 2
3 2

Enter RHS values:
4 6

Enter objective function coefficients:
3 2
```

### Output:
```
Optimal solution:
x1 = 2.00
x2 = 1.00
```

---

## ⚠️ Note
- This is a **simplified simplex** — not a full tableau implementation.  
- Only works for standard **≤ constraints** with **non-negative variables**.  
- Does not handle:
  - Artificial variables
  - Big-M method
  - Two-phase simplex
  - Unbounded/infeasible cases detection

Use this version for **educational purposes**, not large-scale optimization.

---

## 🧠 Insight
This program provides a minimal working example of the simplex pivot method, demonstrating:
- Reduced cost computation  
- Pivot element selection  
- Iterative tableau updates  

Excellent for learning the mathematical flow behind the Simplex Algorithm.

