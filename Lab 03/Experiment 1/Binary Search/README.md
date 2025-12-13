# Binary Search Implementation in C

## 📌 Problem Statement
Implement Binary Search using both **iterative** and **recursive** approaches to efficiently search for an element in a sorted array.

---

## ⚙️ Algorithm Explanation

1. **Array Preparation**
   - Get array elements from user
   - Sort array using Bubble Sort
   - Get search key from user

2. **Binary Search Implementation**
   - **Iterative Approach**
     - Maintain two pointers (left and right)
     - Calculate mid point
     - Compare key with middle element
     - Adjust pointers based on comparison
   
   - **Recursive Approach**
     - Recursively divide array into halves
     - Compare key with middle element
     - Recur for appropriate half

3. **Result**
   - Return index if element found
   - Return -1 if element not found

---

## ⏱️ Time Complexity
- **Binary Search:** `O(log n)`
- **Space Complexity:** 
  - Iterative: `O(1)`
  - Recursive: `O(log n)` due to call stack
- **Initial Sorting:** `O(n²)` using Bubble Sort

---

## ⚙️ How to Run

### **Compile and Run**
```bash
gcc binary_search.c -o binary_search
./binary_search
```

### Input Example
```bash
Enter the size of array: 5
Enter 5 elements: 23 45 12 67 34
Enter the element to search: 45
Choose search approach:
1. Iterative
2. Recursive
Enter your choice (1 or 2): 1
```

### Output Example
```bash
Sorted array: 12 23 34 45 67
Element 45 found at index 3
```

### Note
- Array is automatically sorted before searching
- User can choose between iterative and recursive approaches
- Program uses dynamic memory allocation for array
- Returns -1 if element is not found in array