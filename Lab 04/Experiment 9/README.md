# 🔍 Pattern Searching in C — KMP & Rabin–Karp Algorithms

This program implements two powerful string-matching algorithms:  
✔ **Knuth–Morris–Pratt (KMP)** — uses prefix function (LPS array)  
✔ **Rabin–Karp** — uses hashing / fingerprinting  

Both algorithms find occurrences of a pattern inside a larger text.

---

## 📌 Features
- Efficient substring search using **KMP** and **Rabin–Karp**
- Computes the **LPS (Longest Prefix-Suffix)** table
- Rabin–Karp uses rolling hash with:
  - `d = 256` (alphabet size)
  - `q = 101` (prime modulus)
- Reports all matching starting indices
- Works for any ASCII string

---

## 🛠️ Algorithms Used

### ✔ 1. KMP Algorithm
Uses LPS array to avoid re-checking previously matched characters.

LPS table rules:
```
If pat[i] == pat[len] → lps[i] = ++len
Else if len > 0      → len = lps[len - 1]
Else                 → lps[i] = 0
```
Time Complexity: **O(N + M)**  

### ✔ 2. Rabin–Karp Algorithm
Uses rolling hash:
```
t(i+1) = (d * (t(i) - txt[i]*h) + txt[i+M]) % q
```
Only compares characters when hash matches.  
Time Complexity:  
- Average: **O(N + M)**  
- Worst-case: **O(NM)**  

---

## 🚀 Build & Run

### Compile
```bash
gcc pattern_search.c -o pattern_search -lm
```

### Run
```bash
./pattern_search
```

---

## 📊 Example Session
```
Enter the text string: AABAACAADAABAABA
Enter the pattern to search: AABA

--- Knuth-Morris-Pratt (KMP) Algorithm ---
Pattern found at index 0
Pattern found at index 9
Pattern found at index 12

--- Rabin-Karp (Fingerprinting) Algorithm ---
Pattern found at index 0
Pattern found at index 9
Pattern found at index 12
```

---

## ⚠️ Note
`gets()` is unsafe and deprecated.  
Use `fgets()` in real applications.

---

## 🧠 Insight
KMP avoids redundant comparisons using LPS,  
while Rabin–Karp detects matches using efficient hashing.

This program provides a clear comparison between  
**prefix-based** and **hash-based** pattern matching techniques.

