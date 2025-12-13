#include <stdio.h>
#include <stdlib.h>

// Function to swap two elements
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Function to find the median of three elements
int medianOfThree(int arr[], int low, int high) {
    int mid = low + (high - low) / 2;
    
    // Order the three elements: arr[low], arr[mid], arr[high]
    if (arr[low] > arr[mid])
        swap(&arr[low], &arr[mid]);
    if (arr[low] > arr[high])
        swap(&arr[low], &arr[high]);
    if (arr[mid] > arr[high])
        swap(&arr[mid], &arr[high]);
    
    // Return the index of the median (middle element)
    return mid;
}

// Partition function using median as pivot
int partition(int arr[], int low, int high) {
    // Get the median index and use it as pivot
    int pivotIndex = medianOfThree(arr, low, high);
    int pivot = arr[pivotIndex];
    
    // Move pivot to the end temporarily
    swap(&arr[pivotIndex], &arr[high]);
    
    int i = low - 1;
    
    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    
    // Move pivot to its correct position
    swap(&arr[i + 1], &arr[high]);
    return i + 1;
}

// Quick Sort implementation
void quickSort(int arr[], int low, int high) {
    if (low < high) {
        // Partition the array and get the pivot index
        int pi = partition(arr, low, high);
        
        // Recursively sort elements before and after partition
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// Function to print the array
void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

// Main function
int main() {
    int n;
    
    printf("Enter the number of elements: ");
    scanf("%d", &n);
    
    int* arr = (int*)malloc(n * sizeof(int));
    if (arr == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }
    
    printf("Enter %d integers:\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
    
    printf("Original array: ");
    printArray(arr, n);
    
    quickSort(arr, 0, n - 1);
    
    printf("Sorted array (Quick Sort with median pivot): ");
    printArray(arr, n);
    
    free(arr);
    return 0;
}