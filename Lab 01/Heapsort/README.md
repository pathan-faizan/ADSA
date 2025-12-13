# Heap Sort Algorithm in C

## 📌 Problem Statement
Heap Sort is a popular **comparison-based sorting algorithm** that uses the properties of a **binary heap**.  
The idea is to first build a **Max Heap** from the given array, then repeatedly extract the maximum element from the heap and place it at the end of the array until the array is sorted.

---

## ⚙️ Algorithm Explanation

1. **Build Max Heap**  
   - Treat the array as a binary tree.
   - Convert it into a **Max Heap** (a complete binary tree where every parent is greater than its children).

2. **Heapify Process**  
   - Starting from the last non-leaf node, adjust the heap so the parent is always larger than its children.
   - If not, swap the parent with the larger child and recursively fix the heap.

3. **Extract Maximum & Sort**  
   - Swap the root (maximum element) with the last element in the heap.
   - Reduce the heap size by one.
   - Heapify the root again.
   - Repeat until all elements are sorted.

---

## ⏱️ Time Complexity
- **Building Heap:** `O(n)`  
- **Heapify per element:** `O(log n)`  
- **Total Heap Sort:** `O(n log n)`  
- **Space Complexity:** `O(1)` (in-place sorting)

---

## ⚙️ How to Run

### **Option 1: Run Precompiled Executable**
If you already have the compiled program:
```bash
./heapsort
```
### **Option 2: Compile from Source**

```bash
git clone https://github.com/pathan-faizan/ADSA.git
cd Lab 2

# Compile
gcc heapsort.c -o heapsort

# Run
./heapsort

```
### Input

```bash

Enter number of elements: 6
Enter 1 element: 12
Enter 2 element: 11
Enter 3 element: 13
Enter 4 element: 5
Enter 5 element: 6
Enter 6 element: 7

```
### Output

```bash

Original array:
12 11 13 5 6 7 
Sorted array:
5 6 7 11 12 13

```
