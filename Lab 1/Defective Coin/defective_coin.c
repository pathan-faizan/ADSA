#include <stdio.h>
#include <stdlib.h>

// Function to calculate sum of weights in arr[l..r]
int sum(int arr[], int left, int right) {
    int s = 0;
    for (int i = left; i <= right; i++) {
        s += arr[i];
    }
    return s;
}

// Recursive function to find defective coin index
int defective_coin(int arr[], int left, int right) {
    int n = right - left + 1;
    if (n == 1) {
        return left;
    }

    int k = n / 2;
    int left_weight = sum(arr, left, left + k - 1);
    int right_weight = sum(arr, left + k, left + 2 * k - 1);

    if (left_weight == right_weight) {
        // possible defective in remainder
        if (left + 2 * k <= right) {
            return defective_coin(arr, left + 2 * k, right);
        } else {
            return -1;  // no remainder → no defective coin
        }
    } else if (left_weight < right_weight) {
        return defective_coin(arr, left, left + k - 1);
    } else {
        return defective_coin(arr, left + k, left + 2 * k - 1);
    }
}

// Wrapper to check and confirm defective coin
int find_defective(int arr[], int n) {
    if (n <= 1) return -1;

    int idx = defective_coin(arr, 0, n - 1);
    if (idx == -1) return -1;

    // final check: compare with a "normal" coin
    int normal_weight = (idx != 0) ? arr[0] : arr[1];
    if (arr[idx] < normal_weight) {
        return idx;
    }
    return -1;
}

int main() {
    int n;
    printf("Enter number of coins: ");
    scanf("%d", &n);

    if (n <= 0) {
        printf("Invalid number of coins.\n");
        return 0;
    }

    int *arr = (int *)malloc(n * sizeof(int));  // dynamic array
    if (arr == NULL) {
        printf("Memory allocation failed.\n");
        return 0;
    }

    for (int i = 0; i < n; i++) {
        printf("Enter weight of coin %d: ", i + 1);
        scanf("%d", &arr[i]);
    }

    int defective_index = find_defective(arr, n);
    if (defective_index == -1) {
        printf("No defective coin found.\n");
    } else {
        printf("Defective coin found at position %d (1-based indexing), weight = %d\n",
               defective_index + 1, arr[defective_index]);
    }

    free(arr); // free memory
    return 0;
}
