#include <stdio.h>
#include <stdlib.h>


int binarySearchIterative(int arr[], int left, int right, int key);
int binarySearchRecursive(int arr[], int left, int right, int key);
void sortArray(int arr[], int size);

int main() {
    int size, key, choice;
    int *arr;
    
    // Get array size
    printf("Enter the size of array: ");
    scanf("%d", &size);
    
    // Dynamically allocate memory
    arr = (int *)malloc(size * sizeof(int));
    if (arr == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }
    
    // Input array elements
    printf("Enter %d elements: ", size);
    for(int i = 0; i < size; i++) {
        scanf("%d", &arr[i]);
    }
    
    // Sort the array (using bubble sort)
    sortArray(arr, size);
    
    printf("\nSorted array: ");
    for(int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    
    // Get search key
    printf("\nEnter the element to search: ");
    scanf("%d", &key);
    
    // Get search approach choice
    printf("\nChoose search approach:\n");
    printf("1. Iterative\n");
    printf("2. Recursive\n");
    printf("Enter your choice (1 or 2): ");
    scanf("%d", &choice);
    
    int result;
    if(choice == 1) {
        result = binarySearchIterative(arr, 0, size-1, key);
    } else if(choice == 2) {
        result = binarySearchRecursive(arr, 0, size-1, key);
    } else {
        printf("Invalid choice!\n");
        free(arr);  // Free memory before exit
        return 1;
    }
    
    if(result == -1) {
        printf("\nElement %d not found in array\n", key);
    } else {
        printf("\nElement %d found at index %d\n", key, result);
    }
    
    // Free allocated memory
    free(arr);
    return 0;
}

// Iterative Binary Search
int binarySearchIterative(int arr[], int left, int right, int key) {
    while(left <= right) {
        int mid = left + (right - left) / 2;
        
        if(arr[mid] == key)
            return mid;
            
        if(arr[mid] < key)
            left = mid + 1;
        else
            right = mid - 1;
    }
    return -1;
}

// Recursive Binary Search
int binarySearchRecursive(int arr[], int left, int right, int key) {
    if(right >= left) {
        int mid = left + (right - left) / 2;
        
        if(arr[mid] == key)
            return mid;
            
        if(arr[mid] > key)
            return binarySearchRecursive(arr, left, mid-1, key);
            
        return binarySearchRecursive(arr, mid+1, right, key);
    }
    return -1;
}

// Function to sort array using bubble sort
void sortArray(int arr[], int size) {
    for(int i = 0; i < size-1; i++) {
        for(int j = 0; j < size-i-1; j++) {
            if(arr[j] > arr[j+1]) {
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}