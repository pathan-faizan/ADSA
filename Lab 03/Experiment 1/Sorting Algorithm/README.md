# Sorting Algorithms in C (Quick Sort, Merge Sort, Heap Sort)

## 📌 Problem Statement
Sorting is one of the most fundamental problems in computer science. This program allows the user to:
- Input an array of integers
- Choose one of three popular sorting algorithms: Quick Sort, Merge Sort, or Heap Sort
- Get the sorted output

The goal is to demonstrate different algorithmic approaches to sorting and compare their behaviors.

---

## ⚙️ Algorithm Explanation

### 1. Quick Sort
- Approach: Divide-and-conquer
- Steps:
  1. Select a pivot (last element in this code)
  2. Partition the array: smaller elements left, larger right
  3. Recursively sort left and right subarrays

### 2. Merge Sort
- Approach: Divide-and-conquer (stable sort)
- Steps:
  1. Recursively divide array into halves until single elements remain
  2. Merge subarrays in sorted order
- Uses auxiliary arrays L[] and R[] for merging

### 3. Heap Sort
- Approach: Heap-based selection sort
- Steps:
  1. Convert array into a max-heap
  2. Swap root (max element) with last element
  3. Reduce heap size and re-heapify
  4. Repeat until array is sorted

---

## ⏱️ Time Complexity

| Algorithm      | Best Case    | Average Case | Worst Case   | Space Complexity |
|---------------|-------------|-------------|-------------|----------------|
| Quick Sort    | O(n log n)  | O(n log n)  | O(n²)       | O(log n)       |
| Merge Sort    | O(n log n)  | O(n log n)  | O(n log n)  | O(n)           |
| Heap Sort     | O(n log n)  | O(n log n)  | O(n log n)  | O(1)           |

---

## ⚙️ How to Run

**Option 1: Run Precompiled Executable**  
`./sorting_algorithms`

**Option 2: Compile from Source**  
1. Clone the repository:  
   `git clone https://github.com/pathan-faizan/ADSA.git`  
2. Navigate to the folder:  
   `cd "Lab 3/Sorting Algorithms"`  
3. Compile the code:  
   `gcc sorting_algorithms.c -o sorting_algorithms`  
4. Run the executable:  
   `./sorting_algorithms`

---

## 📝 Input and Output Example

Enter the size of the array: 6  
Enter 6 integers: 10 7 8 9 1 5  

Choose sorting method:  
1. Quick Sort  
2. Merge Sort  
3. Heap Sort  
Enter your choice (1-3): 1  

Original array: 10 7 8 9 1 5  
Sorted array (Quick Sort): 1 5 7 8 9 10

---

## 🗒️ Notes
- The program dynamically allocates memory for input and its copy  
- Handles all three sorting methods in a single program  
- Merge Sort is stable, Quick Sort and Heap Sort are not stable  
- Heap Sort uses in-place sorting, requiring no extra memory
