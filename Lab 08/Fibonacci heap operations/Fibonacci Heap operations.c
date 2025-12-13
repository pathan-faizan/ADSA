/* fib_heap_correct.c
   Menu-driven Fibonacci Heap (fixed root-list & safe operations)
   Key type: long long
   NOTE: This implementation focuses on correctness & safety (not micro-optimized).
*/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>

typedef struct FibNode {
    long long key;
    int degree;
    int mark;
    struct FibNode *parent;
    struct FibNode *child;
    struct FibNode *left;
    struct FibNode *right;
} FibNode;

typedef struct FibHeap {
    FibNode *min;
    int n;
} FibHeap;

/* ---------- Helpers ---------- */
FibNode* create_node(long long key) {
    FibNode *x = (FibNode*)malloc(sizeof(FibNode));
    if (!x) { perror("malloc"); exit(1); }
    x->key = key;
    x->degree = 0;
    x->mark = 0;
    x->parent = x->child = NULL;
    x->left = x->right = x;
    return x;
}

FibHeap* make_heap(void) {
    FibHeap *H = (FibHeap*)malloc(sizeof(FibHeap));
    if (!H) { perror("malloc"); exit(1); }
    H->min = NULL;
    H->n = 0;
    return H;
}

/* Insert node x into root list (safe for empty root list too) */
void root_list_insert(FibHeap *H, FibNode *x) {
    if (!H->min) {
        x->left = x->right = x;
        H->min = x;
    } else {
        x->right = H->min->right;
        x->left = H->min;
        H->min->right->left = x;
        H->min->right = x;
        if (x->key < H->min->key) H->min = x;
    }
}

/* Remove a node from its circular list (used for root list & child lists) */
void remove_from_list(FibNode *x) {
    x->left->right = x->right;
    x->right->left = x->left;
    x->left = x->right = x;
}

/* ---------- Core ops ---------- */
FibNode* fib_insert(FibHeap *H, long long key) {
    FibNode *x = create_node(key);
    root_list_insert(H, x);
    H->n++;
    return x;
}

/* link y under x (y becomes child of x). Assumes y is a root (removed from root list by caller). */
void fib_link(FibHeap *H, FibNode *y, FibNode *x) {
    /* y is removed from whichever list it was in by caller */
    y->parent = x;
    if (!x->child) {
        x->child = y;
        y->left = y->right = y;
    } else {
        y->right = x->child->right;
        y->left = x->child;
        x->child->right->left = y;
        x->child->right = y;
    }
    x->degree++;
    y->mark = 0;
}

/* Consolidate root list after extract-min */
void consolidate(FibHeap *H) {
    if (!H->min) return;
    /* max degree bound: floor(log2(n)) + 1 is safe; use +5 margin */
    int maxDeg = (int)(floor(log2(H->n > 0 ? H->n : 1))) + 5;
    FibNode **A = (FibNode**)calloc(maxDeg + 1, sizeof(FibNode*));
    if (!A) { perror("calloc"); exit(1); }

    /* Collect current root list nodes (because we'll be changing the root list) */
    int rootCount = 0;
    FibNode *start = H->min;
    FibNode *w = start;
    do { rootCount++; w = w->right; } while (w != start);

    FibNode **roots = (FibNode**)malloc(rootCount * sizeof(FibNode*));
    w = start;
    for (int i = 0; i < rootCount; ++i) { roots[i] = w; w = w->right; }

    for (int i = 0; i < rootCount; ++i) {
        FibNode *x = roots[i];
        int d = x->degree;
        /* ensure x is a standalone circular node before manipulating A */
        x->left = x->right = x;
        while (d <= maxDeg && A[d]) {
            FibNode *y = A[d];
            if (x->key > y->key) {
                FibNode *tmp = x; x = y; y = tmp;
            }
            /* link y under x */
            A[d] = NULL;
            /* remove y from whatever list (it's currently standalone or in A) */
            y->left = y->right = y;
            fib_link(H, y, x);
            d++;
        }
        if (d > maxDeg) {
            /* rare: resize (very unlikely with margin), but for safety skip linking */
            d = maxDeg;
        }
        A[d] = x;
    }

    /* rebuild root list and reset min */
    H->min = NULL;
    for (int i = 0; i <= maxDeg; ++i) {
        if (A[i]) {
            A[i]->parent = NULL;
            A[i]->mark = 0;
            A[i]->left = A[i]->right = A[i];
            root_list_insert(H, A[i]);
        }
    }

    free(A);
    free(roots);
}

/* Extract min node z and return it (caller should free the returned node if desired) */
FibNode* fib_extract_min(FibHeap *H) {
    FibNode *z = H->min;
    if (!z) return NULL;

    /* move each child of z to root list */
    if (z->child) {
        /* collect children first */
        FibNode *cstart = z->child;
        FibNode *w = cstart;
        int cnt = 0;
        do { cnt++; w = w->right; } while (w != cstart);

        FibNode **children = (FibNode**)malloc(cnt * sizeof(FibNode*));
        w = cstart;
        for (int i = 0; i < cnt; ++i) { children[i] = w; w = w->right; }

        for (int i = 0; i < cnt; ++i) {
            FibNode *x = children[i];
            /* remove x from child list */
            remove_from_list(x);
            x->parent = NULL;
            /* insert into root list */
            root_list_insert(H, x);
        }
        free(children);
        z->child = NULL;
    }

    /* remove z from root list */
    if (z->right == z) {
        /* z was the only root */
        H->min = NULL;
    } else {
        FibNode *nr = z->right;
        remove_from_list(z);
        H->min = nr;
        consolidate(H);
    }
    H->n--;
    return z;
}

/* cut x from its parent y and move x to root list */
void cut(FibHeap *H, FibNode *x, FibNode *y) {
    if (!x || !y) return;
    /* remove x from y's child circular list */
    if (x->right == x) {
        y->child = NULL;
    } else {
        if (y->child == x) y->child = x->right;
        remove_from_list(x);
    }
    y->degree--;
    x->parent = NULL;
    x->mark = 0;
    root_list_insert(H, x);
}

/* cascading cut */
void cascading_cut(FibHeap *H, FibNode *y) {
    FibNode *z = y->parent;
    if (z) {
        if (!y->mark) y->mark = 1;
        else { cut(H, y, z); cascading_cut(H, z); }
    }
}

/* decrease key */
void fib_decrease_key(FibHeap *H, FibNode *x, long long k) {
    if (!x) { printf("Error: node pointer is NULL\n"); return; }
    if (k > x->key) { printf("Error: new key is greater than current key\n"); return; }

    x->key = k;
    FibNode *y = x->parent;
    if (y && x->key < y->key) {
        cut(H, x, y);
        cascading_cut(H, y);
    }
    if (!H->min || x->key < H->min->key) H->min = x;
}

/* delete node: decrease to -inf then extract */
void fib_delete(FibHeap *H, FibNode *x) {
    if (!x) return;
    fib_decrease_key(H, x, LLONG_MIN);
    FibNode *z = fib_extract_min(H);
    if (z) free(z);
}

/* find-min */
FibNode* fib_find_min(FibHeap *H) {
    return H->min;
}

/* union (merge) two heaps - returns new heap (frees H1/H2 structs but not nodes) */
FibHeap* fib_union(FibHeap *H1, FibHeap *H2) {
    FibHeap *H = make_heap();
    if (!H1->min) H->min = H2->min;
    else if (!H2->min) H->min = H1->min;
    else {
        /* splice the two root lists */
        FibNode *a = H1->min->right;
        FibNode *b = H2->min->left;
        H1->min->right = H2->min;
        H2->min->left = H1->min;
        a->left = b;
        b->right = a;
        H->min = (H1->min->key < H2->min->key) ? H1->min : H2->min;
    }
    H->n = H1->n + H2->n;
    free(H1);
    free(H2);
    return H;
}

/* print root list safely (guard by n to avoid infinite loops if corruption) */
void print_root_list(FibHeap *H) {
    if (!H->min) { printf("Heap empty\n"); return; }
    printf("Root list: ");
    FibNode *w = H->min;
    int printed = 0;
    do {
        printf("%lld ", w->key);
        w = w->right;
        printed++;
        if (printed > H->n + 5) { printf("[stopped - possible corruption]\n"); return; }
    } while (w != H->min);
    printf("\n");
}

/* ---------- Main: menu-driven interface ---------- */
int main(void) {
    FibHeap *H = make_heap();
    /* keep an array of node pointers so user can refer by id; expand if needed */
    size_t cap = 1024;
    FibNode **nodes = malloc(cap * sizeof(FibNode*));
    if (!nodes) { perror("malloc"); return 1; }
    size_t node_count = 0;

    while (1) {
        printf("\n--- Fibonacci Heap Menu ---\n");
        printf("1. Insert\n");
        printf("2. Extract Min\n");
        printf("3. Decrease Key\n");
        printf("4. Delete Node\n");
        printf("5. Find Min\n");
        printf("6. Print Heap (root list)\n");
        printf("7. Exit\n");
        printf("Enter choice: ");
        int ch;
        if (scanf("%d", &ch) != 1) break;

        if (ch == 1) {
            long long key;
            printf("Enter key: ");
            scanf("%lld", &key);
            if (node_count >= cap) {
                cap *= 2;
                nodes = realloc(nodes, cap * sizeof(FibNode*));
                if (!nodes) { perror("realloc"); return 1; }
            }
            nodes[node_count] = fib_insert(H, key);
            printf("Inserted node id = %zu\n", node_count);
            node_count++;
        } else if (ch == 2) {
            FibNode *m = fib_extract_min(H);
            if (m) {
                printf("Extracted min = %lld\n", m->key);
                /* Mark pointers in nodes[] to NULL if this node was stored there */
                for (size_t i = 0; i < node_count; ++i) if (nodes[i] == m) nodes[i] = NULL;
                free(m);
            } else printf("Heap empty\n");
        } else if (ch == 3) {
            size_t id;
            long long newkey;
            printf("Enter node id to decrease: ");
            if (scanf("%zu", &id) != 1 || id >= node_count) { printf("Invalid id\n"); continue; }
            if (!nodes[id]) { printf("Node id %zu is deleted or invalid\n", id); continue; }
            printf("Enter new key: ");
            scanf("%lld", &newkey);
            fib_decrease_key(H, nodes[id], newkey);
        } else if (ch == 4) {
            size_t id;
            printf("Enter node id to delete: ");
            if (scanf("%zu", &id) != 1 || id >= node_count) { printf("Invalid id\n"); continue; }
            if (!nodes[id]) { printf("Node id %zu is already deleted or invalid\n", id); continue; }
            fib_delete(H, nodes[id]);
            nodes[id] = NULL;
            printf("Deleted node id %zu\n", id);
        } else if (ch == 5) {
            if (H->min) printf("Min = %lld\n", H->min->key);
            else printf("Heap empty\n");
        } else if (ch == 6) {
            print_root_list(H);
        } else if (ch == 7) {
            break;
        } else {
            printf("Invalid choice\n");
        }
    }

    /* free remaining nodes and structures (best effort) */
    /* Note: a full safe free of all nodes requires traversing root list & children recursively.
       For brevity and focus on heap ops, we omit a full destructor here. */
    free(nodes);
    free(H);
    return 0;
}
