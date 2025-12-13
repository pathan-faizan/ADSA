# 🪙 Defective Coin Finder (Using Divide and Conquer)

This project implements an algorithm to **detect the single defective coin** among `n` coins, where all coins are expected to have the same weight except **one coin which is lighter**.  
The algorithm uses a **divide-and-conquer approach** to minimize the number of weight comparisons.

---

## 📌 Problem Statement
You are given `n` coins, all identical in weight except **one defective coin**, which is lighter than the others.  
The task is to **find the index of the defective coin** efficiently.

---

## 🔍 Algorithm Explanation

The code solves the problem as follows:

1. **Divide coins into two halves**:  
   - Compute the total weight of the **left half** and the **right half**.  

2. **Compare sums**:
   - If both halves have the **same weight**, the defective coin (if it exists) must be in the **remaining coins** (if any).  
   - If the **left half is lighter**, the defective coin is in the left half.  
   - If the **right half is lighter**, the defective coin is in the right half.  

3. **Recursive narrowing**:  
   - Repeat the process recursively on the suspected half until only one coin remains.  

4. **Final confirmation**:  
   - Compare the identified coin with a known "normal" coin to confirm that it is indeed defective.  

This ensures that the defective coin is found in **O(log n)** recursive steps instead of checking each coin linearly.

---

## 📂 Code Structure
- `sum()` → Utility function to calculate total weight of coins in a range.  
- `defective_coin()` → Recursive function that uses divide-and-conquer to locate the defective coin.  
- `find_defective()` → Wrapper function that verifies the defective coin.  
- `main()` → Takes user input, runs the algorithm, and prints the result.

---

## ⚙️ How to Run

### **Option 1: Run Precompiled Executable**
If you already have the compiled program:
```bash
./defective_coin.exe
```
### **Option 2: Compile from Source**

```bash
git clone https://github.com/pathan-faizan/ADSA.git
cd Lab 1
cd Defective Coin

# Compile
gcc defective_coin.c -o defective_coin

# Run
./defective_coin

```
### Input

```bash
Enter number of coins: 5
Enter weight of coin 1: 10
Enter weight of coin 2: 10
Enter weight of coin 3: 8
Enter weight of coin 4: 10
Enter weight of coin 5: 10
```
### Output

```bash
Defective coin found at position 3 (1-based indexing), weight = 8
```
