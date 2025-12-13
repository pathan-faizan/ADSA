#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_POINTS 250 
#define MAX_N 5000000 

struct Point {
    int n;
    int comparisons;
};

// --- Recursive Search Functions (These are correct, the test case was flawed) ---

int binarySearchRecursive(int l, int r, int x, int *comparisons) {
    if (r >= l) {
        int mid = l + (r - l) / 2;
        int mid_val = mid;
        (*comparisons)++;
        if (mid_val == x) return mid;
        (*comparisons)++;
        if (mid_val > x) return binarySearchRecursive(l, mid - 1, x, comparisons);
        else return binarySearchRecursive(mid + 1, r, x, comparisons);
    }
    return -1;
}

int ternarySearchRecursive(int l, int r, int x, int *comparisons) {
    if (r >= l) {
        int mid1 = l + (r - l) / 3;
        int mid2 = r - (r - l) / 3;
        int mid1_val = mid1;
        int mid2_val = mid2;
        (*comparisons)++;
        if (mid1_val == x) return mid1;
        (*comparisons)++;
        if (mid2_val == x) return mid2;
        (*comparisons)++;
        if (x < mid1_val) return ternarySearchRecursive(l, mid1 - 1, x, comparisons);
        (*comparisons)++;
        if (x > mid2_val) return ternarySearchRecursive(mid2 + 1, r, x, comparisons);
        else return ternarySearchRecursive(mid1 + 1, mid2 - 1, x, comparisons);
    }
    return -1;
}

int main() {
    FILE *gnuplotPipe = popen("gnuplot -persistent", "w");
    if (gnuplotPipe == NULL) {
        fprintf(stderr, "Error: Could not open pipe to Gnuplot.\n");
        return 1;
    }

    printf("Generating data points for the correct worst-case scenario...\n");
    struct Point bs_data[NUM_POINTS];
    struct Point ts_data[NUM_POINTS];
    int step = MAX_N / NUM_POINTS;

    for (int i = 0; i < NUM_POINTS; i++) {
        int n = (i + 1) * step;

        int bs_comps = 0;
        int ts_comps = 0;

        int element_to_find = n; 

        binarySearchRecursive(0, n - 1, element_to_find, &bs_comps);
        ternarySearchRecursive(0, n - 1,element_to_find, &ts_comps);

        bs_data[i].n = n;
        bs_data[i].comparisons = bs_comps;
        ts_data[i].n = n;
        ts_data[i].comparisons = ts_comps;
    }
    printf("Data generation complete. Plotting...\n");

    fprintf(gnuplotPipe, "set title Binary vs. Ternary Search Comparison'\n");
    fprintf(gnuplotPipe, "set xlabel 'Array Size (n)'\n");
    fprintf(gnuplotPipe, "set ylabel 'Number of Key Comparisons'\n");
    fprintf(gnuplotPipe, "set grid\n");
    fprintf(gnuplotPipe, "set key top left\n");
    fprintf(gnuplotPipe, "plot '-' with lines title 'Binary Search', '-' with lines title 'Ternary Search'\n");

    for (int i = 0; i < NUM_POINTS; i++) {
        fprintf(gnuplotPipe, "%d %d\n", bs_data[i].n, bs_data[i].comparisons);
        printf("data points = %d, comparison= %d, Algorithm = Binary Search\n", bs_data[i].n, bs_data[i].comparisons);
    }
    fprintf(gnuplotPipe, "e\n");

    for (int i = 0; i < NUM_POINTS; i++) {
        fprintf(gnuplotPipe, "%d %d\n", ts_data[i].n, ts_data[i].comparisons);
        printf("data points = %d, comparison= %d, Algorithm = Ternary Search\n", ts_data[i].n, ts_data[i].comparisons);

    }
    fprintf(gnuplotPipe, "e\n");

    fflush(gnuplotPipe);
    pclose(gnuplotPipe);

    return 0;
}