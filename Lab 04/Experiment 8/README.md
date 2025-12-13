# 🔤 Longest Common Subsequence (LCS) – Dynamic Programming + All Common Subsequences (C Program)

This program computes the **Longest Common Subsequence (LCS)** between two strings using **Dynamic Programming**  
and prints **all common subsequences** (may include duplicates).

---

## 📌 Features
- Computes **LCS length** using DP table  
- Reconstructs and prints the **actual LCS** string  
- Recursively generates **all common subsequences**  
- Handles strings up to length 100  
- Fully iterative DP implementation

---

## 🧠 How It Works

### ✔ 1. LCS DP Table
A 2D array `dp[m+1][n+1]` is filled using rules:

```
if i == 0 or j == 0 → dp[i][j] = 0
else if X[i-1] == Y[j-1] → dp[i][j] = 1 + dp[i-1][j-1]
else dp[i][j] = max(dp[i-1][j], dp[i][j-1])
```

### ✔ 2. Backtracking to get the LCS
Start from bottom-right cell `(m, n)`:
- If characters match → add to LCS and move diagonally
- Else move to the direction of the larger value

### ✔ 3. All Common Subsequences
A recursive function explores all paths:
- If `X[i] == Y[j]` → include character
- Also explore skipping from each string  
Note: **Duplicates may appear**.

---

## 🚀 Build & Run

### Compile
```bash
gcc lcs.c -o lcs
```

### Run
```bash
./lcs
```

---

## 📊 Example Session
```
Enter first string: ABCBDAB
Enter second string: BDCABA

Longest Common Subsequence (LCS): BCBA
Length of LCS: 4

All Common Subsequences (may include duplicates):
B
BD
BDA
BA
BC
...
```

---

## 🧠 Insight
This program demonstrates:
- Dynamic Programming table computation  
- LCS reconstruction  
- Recursive enumeration of subsequences  
Useful for understanding sequence alignment, text comparison, and DP patterns.

