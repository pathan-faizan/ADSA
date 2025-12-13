# Binary Search vs. Ternary Search – Comparison of Key Comparisons

This project compares the **number of key comparisons** made by **Binary Search** and **Ternary Search** in their **worst-case scenarios**.  
The results are visualized using **Gnuplot graphs** for different input sizes.

---

## 📖 Algorithm Explanation

### 🔹 Binary Search (Recursive)
- Binary Search divides the search space into **two halves** at each step.  
- It compares the middle element with the target.  
- Worst-case comparisons ≈ **O(log₂ n)**.  

### 🔹 Ternary Search (Recursive)
- Ternary Search divides the search space into **three parts**.  
- It performs up to **two comparisons per step** (mid1 and mid2).  
- Worst-case comparisons ≈ **O(log₃ n)**,  
  but since it does **more comparisons per recursion**, Binary Search is often better.

---

## 🔍 How the Code Compares Them

The program does the following:

1. Defines two recursive functions:
   - `binarySearchRecursive()`  
   - `ternarySearchRecursive()`  

2. For each test array size `n` (up to 5,000,000, sampled at 250 points):
   - It chooses the **last element `n`** as the target (worst-case position).  
   - Runs **Binary Search** on the range `[0 … n-1]` and counts comparisons.  
   - Runs **Ternary Search** on the same range and counts comparisons.  

3. Stores results in two arrays:
   - `bs_data[]` for Binary Search.  
   - `ts_data[]` for Ternary Search.  

4. Sends these results to **Gnuplot** via a pipe:
   - X-axis → Array size `n`.  
   - Y-axis → Number of comparisons.  
   - Plots both curves on the same graph.  

5. Prints details in the console:


This way, you can directly see from both the **console output** and the **graph** that Binary Search requires fewer comparisons than Ternary Search.

---

##  Requirements
- **C Compiler** (GCC, MinGW, etc.)  
- **Gnuplot** (must be installed and accessible in your system PATH)  

---

##  How to Run

You have two options:

## **Option 1: Run Precompiled Executable**
If `comparison_counter.exe` is already available:
```bash
./comparison_counter.exe
```

### **Option 2: Compile from Source**

```bash
git clone https://github.com/pathan-faizan/ADSA.git
cd Lab 1
cd Comparison between Ternary search and Binary Search

# Compile
gcc comparison_counter.c -o comparison_counter

# Run
./comparison_counter

```

### Graphical Output (Generated via Gnuplot)
<p> <img src="images/Comparison of Binary search and ternary search.png" alt="Binary vs. Ternary Search Comparisons" width="700"/> <br> <em>Binary Search vs. Ternary Search – Number of Comparisons</em> </p>




