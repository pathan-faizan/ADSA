# Quick Sort with Median-of-Three Pivot in C

## 📌 Problem Statement
Quick Sort is a **divide-and-conquer sorting algorithm** that works by partitioning an array around a pivot element and recursively sorting the subarrays.This implementation improves the standard Quick Sort by selecting the **median of the first, middle, and last elements** as the pivot, reducing the chances of worst-case performance on already sorted or nearly sorted data.

---

## ⚙️ Algorithm Explanation

1. **Median-of-Three Pivot Selection**
   - Compute the middle index: `mid = low + (high - low) / 2`
   - Sort the values at `arr[low]`, `arr[mid]`, `arr[high]` so that `arr[mid]` becomes the median
   - Use this median as the pivot element

2. **Partitioning**
   - Temporarily move pivot to the end
   - Rearrange elements so that all elements `<= pivot` are on the left and all `> pivot` are on the right
   - Place pivot in its correct sorted position

3. **Recursion**
   - Recursively apply Quick Sort to the left and right subarrays until the entire array is sorted


---

## ⏱️ Time Complexity
- **Best / Average Case:** `O(n log n)`  
- **Worst Case:** `O(n²)` (very rare with median-of-three pivot)
- **Space Complexity:** `O(log n)` (due to recursion stack)

---


### Input Example
```bash
Enter the number of elements: 6
Enter 6 integers:
45 12 67 3 19 8
```

### Output Example
```bash
Original array: 45 12 67 3 19 8
Sorted array (Quick Sort with median pivot): 3 8 12 19 45 67
```

### Note
- Median-of-three pivot selection helps avoid worst-case performance on sorted or reverse-sorted arrays.
- Program dynamically allocates memory for input array and frees it after use.
- Sorting is done in-place, requiring no extra arrays.