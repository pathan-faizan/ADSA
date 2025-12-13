#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MIN_DEGREE 3  // Minimum degree of B-Tree (t = 3)
#define MAX_KEYS (2 * MIN_DEGREE - 1)  // Maximum number of keys
#define MAX_CHILDREN (2 * MIN_DEGREE)   // Maximum number of children

// B-Tree node structure
typedef struct BTreeNode {
    int keys[MAX_KEYS];                    // Array of keys
    struct BTreeNode* children[MAX_CHILDREN]; // Array of child pointers
    int num_keys;                          // Current number of keys
    bool is_leaf;                          // True if node is leaf
} BTreeNode;

// Function prototypes
BTreeNode* create_node(bool is_leaf);
void insert(BTreeNode** root, int key);
void insert_non_full(BTreeNode* node, int key);
void split_child(BTreeNode* parent, int index);
void delete_key(BTreeNode** root, int key);
void delete_from_node(BTreeNode* node, int key);
int get_predecessor(BTreeNode* node, int index);
int get_successor(BTreeNode* node, int index);
void fill(BTreeNode* node, int index);
void borrow_from_prev(BTreeNode* node, int index);
void borrow_from_next(BTreeNode* node, int index);
void merge(BTreeNode* node, int index);
BTreeNode* search(BTreeNode* node, int key);
void print_tree(BTreeNode* node, int level);
void free_tree(BTreeNode* node);

// Create a new B-Tree node
BTreeNode* create_node(bool is_leaf) {
    BTreeNode* node = (BTreeNode*)malloc(sizeof(BTreeNode));
    if (!node) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    
    node->is_leaf = is_leaf;
    node->num_keys = 0;
    
    // Initialize all pointers to NULL
    for (int i = 0; i < MAX_CHILDREN; i++) {
        node->children[i] = NULL;
    }
    
    return node;
}

// Insert a key into B-Tree
void insert(BTreeNode** root, int key) {
    if (*root == NULL) {
        // Create root if tree is empty
        *root = create_node(true);
        (*root)->keys[0] = key;
        (*root)->num_keys = 1;
        return;
    }
    
    // If root is full, create new root and split
    if ((*root)->num_keys == MAX_KEYS) {
        BTreeNode* new_root = create_node(false);
        new_root->children[0] = *root;
        
        // Split the old root
        split_child(new_root, 0);
        *root = new_root;
    }
    
    insert_non_full(*root, key);
}

// Insert key into non-full node
void insert_non_full(BTreeNode* node, int key) {
    int i = node->num_keys - 1;
    
    if (node->is_leaf) {
        // Insert key in leaf node
        while (i >= 0 && node->keys[i] > key) {
            node->keys[i + 1] = node->keys[i];
            i--;
        }
        node->keys[i + 1] = key;
        node->num_keys++;
    } else {
        // Find child to insert key
        while (i >= 0 && node->keys[i] > key) {
            i--;
        }
        i++;
        
        // Split child if full
        if (node->children[i]->num_keys == MAX_KEYS) {
            split_child(node, i);
            if (node->keys[i] < key) {
                i++;
            }
        }
        insert_non_full(node->children[i], key);
    }
}

// Split child of node at given index
void split_child(BTreeNode* parent, int index) {
    BTreeNode* full_child = parent->children[index];
    BTreeNode* new_child = create_node(full_child->is_leaf);
    
    int mid = MIN_DEGREE - 1;
    new_child->num_keys = MIN_DEGREE - 1;
    
    // Copy keys to new child
    for (int i = 0; i < MIN_DEGREE - 1; i++) {
        new_child->keys[i] = full_child->keys[i + MIN_DEGREE];
    }
    
    // Copy children if not leaf
    if (!full_child->is_leaf) {
        for (int i = 0; i < MIN_DEGREE; i++) {
            new_child->children[i] = full_child->children[i + MIN_DEGREE];
        }
    }
    
    full_child->num_keys = MIN_DEGREE - 1;
    
    // Shift parent's children
    for (int i = parent->num_keys; i >= index + 1; i--) {
        parent->children[i + 1] = parent->children[i];
    }
    parent->children[index + 1] = new_child;
    
    // Shift parent's keys
    for (int i = parent->num_keys - 1; i >= index; i--) {
        parent->keys[i + 1] = parent->keys[i];
    }
    parent->keys[index] = full_child->keys[mid];
    parent->num_keys++;
}

// Delete a key from B-Tree
void delete_key(BTreeNode** root, int key) {
    if (*root == NULL) {
        printf("Deletion not possible - Tree is empty!\n");
        return;
    }
    
    // First check if key exists before attempting deletion
    if (search(*root, key) == NULL) {
        printf("Deletion not possible - Key %d not found in tree!\n", key);
        return;
    }
    
    delete_from_node(*root, key);
    
    // If root becomes empty, make first child as new root
    if ((*root)->num_keys == 0) {
        BTreeNode* old_root = *root;
        if ((*root)->is_leaf) {
            *root = NULL;
        } else {
            *root = (*root)->children[0];
        }
        free(old_root);
    }
    
    printf("Key %d deleted successfully!\n", key);
}

// Delete key from given node
void delete_from_node(BTreeNode* node, int key) {
    int index = 0;
    
    // Find index of key or child where key might exist
    while (index < node->num_keys && node->keys[index] < key) {
        index++;
    }
    
    if (index < node->num_keys && node->keys[index] == key) {
        // Key found in this node
        if (node->is_leaf) {
            // Case 1: Key in leaf node
            for (int i = index + 1; i < node->num_keys; i++) {
                node->keys[i - 1] = node->keys[i];
            }
            node->num_keys--;
        } else {
            // Case 2: Key in internal node
            if (node->children[index]->num_keys >= MIN_DEGREE) {
                // Case 2a: Left child has enough keys
                int pred = get_predecessor(node, index);
                node->keys[index] = pred;
                delete_from_node(node->children[index], pred);
            } else if (node->children[index + 1]->num_keys >= MIN_DEGREE) {
                // Case 2b: Right child has enough keys
                int succ = get_successor(node, index);
                node->keys[index] = succ;
                delete_from_node(node->children[index + 1], succ);
            } else {
                // Case 2c: Both children have minimum keys
                merge(node, index);
                delete_from_node(node->children[index], key);
            }
        }
    } else {
        // Key not in this node
        if (node->is_leaf) {
            printf("Deletion not possible - Key %d not found in tree!\n", key);
            return;
        }
        
        bool is_last_child = (index == node->num_keys);
        
        if (node->children[index]->num_keys < MIN_DEGREE) {
            fill(node, index);
        }
        
        if (is_last_child && index > node->num_keys) {
            delete_from_node(node->children[index - 1], key);
        } else {
            delete_from_node(node->children[index], key);
        }
    }
}

// Get predecessor key
int get_predecessor(BTreeNode* node, int index) {
    BTreeNode* current = node->children[index];
    while (!current->is_leaf) {
        current = current->children[current->num_keys];
    }
    return current->keys[current->num_keys - 1];
}

// Get successor key
int get_successor(BTreeNode* node, int index) {
    BTreeNode* current = node->children[index + 1];
    while (!current->is_leaf) {
        current = current->children[0];
    }
    return current->keys[0];
}

// Fill child node which has fewer than MIN_DEGREE keys
void fill(BTreeNode* node, int index) {
    // If previous child has more than MIN_DEGREE-1 keys, borrow from it
    if (index != 0 && node->children[index - 1]->num_keys >= MIN_DEGREE) {
        borrow_from_prev(node, index);
    }
    // If next child has more than MIN_DEGREE-1 keys, borrow from it
    else if (index != node->num_keys && node->children[index + 1]->num_keys >= MIN_DEGREE) {
        borrow_from_next(node, index);
    }
    // Merge with sibling
    else {
        if (index != node->num_keys) {
            merge(node, index);
        } else {
            merge(node, index - 1);
        }
    }
}

// Borrow key from previous child
void borrow_from_prev(BTreeNode* node, int index) {
    BTreeNode* child = node->children[index];
    BTreeNode* sibling = node->children[index - 1];
    
    // Move key from parent to child
    for (int i = child->num_keys - 1; i >= 0; i--) {
        child->keys[i + 1] = child->keys[i];
    }
    
    // Move child pointers
    if (!child->is_leaf) {
        for (int i = child->num_keys; i >= 0; i--) {
            child->children[i + 1] = child->children[i];
        }
        child->children[0] = sibling->children[sibling->num_keys];
    }
    
    child->keys[0] = node->keys[index - 1];
    node->keys[index - 1] = sibling->keys[sibling->num_keys - 1];
    
    child->num_keys++;
    sibling->num_keys--;
}

// Borrow key from next child
void borrow_from_next(BTreeNode* node, int index) {
    BTreeNode* child = node->children[index];
    BTreeNode* sibling = node->children[index + 1];
    
    // Move key from parent to child
    child->keys[child->num_keys] = node->keys[index];
    
    // Move child pointer
    if (!child->is_leaf) {
        child->children[child->num_keys + 1] = sibling->children[0];
    }
    
    node->keys[index] = sibling->keys[0];
    
    // Shift keys in sibling
    for (int i = 1; i < sibling->num_keys; i++) {
        sibling->keys[i - 1] = sibling->keys[i];
    }
    
    // Shift child pointers in sibling
    if (!sibling->is_leaf) {
        for (int i = 1; i <= sibling->num_keys; i++) {
            sibling->children[i - 1] = sibling->children[i];
        }
    }
    
    child->num_keys++;
    sibling->num_keys--;
}

// Merge child with its sibling
void merge(BTreeNode* node, int index) {
    BTreeNode* child = node->children[index];
    BTreeNode* sibling = node->children[index + 1];
    
    // Pull key from parent and merge with sibling
    child->keys[MIN_DEGREE - 1] = node->keys[index];
    
    // Copy keys from sibling
    for (int i = 0; i < sibling->num_keys; i++) {
        child->keys[i + MIN_DEGREE] = sibling->keys[i];
    }
    
    // Copy child pointers from sibling
    if (!child->is_leaf) {
        for (int i = 0; i <= sibling->num_keys; i++) {
            child->children[i + MIN_DEGREE] = sibling->children[i];
        }
    }
    
    // Shift keys in parent
    for (int i = index + 1; i < node->num_keys; i++) {
        node->keys[i - 1] = node->keys[i];
    }
    
    // Shift child pointers in parent
    for (int i = index + 2; i <= node->num_keys; i++) {
        node->children[i - 1] = node->children[i];
    }
    
    child->num_keys += sibling->num_keys + 1;
    node->num_keys--;
    
    free(sibling);
}

// Search for a key in B-Tree
BTreeNode* search(BTreeNode* node, int key) {
    if (node == NULL) {
        return NULL;
    }
    
    int i = 0;
    while (i < node->num_keys && key > node->keys[i]) {
        i++;
    }
    
    if (i < node->num_keys && key == node->keys[i]) {
        return node;
    }
    
    if (node->is_leaf) {
        return NULL;
    }
    
    return search(node->children[i], key);
}

// Print B-Tree structure
void print_tree(BTreeNode* node, int level) {
    if (node != NULL) {
        printf("Level %d: ", level);
        for (int i = 0; i < node->num_keys; i++) {
            printf("%d ", node->keys[i]);
        }
        printf("\n");
        
        if (!node->is_leaf) {
            for (int i = 0; i <= node->num_keys; i++) {
                print_tree(node->children[i], level + 1);
            }
        }
    }
}

// Free memory allocated for B-Tree
void free_tree(BTreeNode* node) {
    if (node != NULL) {
        if (!node->is_leaf) {
            for (int i = 0; i <= node->num_keys; i++) {
                free_tree(node->children[i]);
            }
        }
        free(node);
    }
}

// Main function to demonstrate B-Tree operations
int main() {
    BTreeNode* root = NULL;
    int choice, key;
    
    printf("B-Tree Operations (Minimum Degree = %d)\n", MIN_DEGREE);
    printf("========================================\n");
    
    while (1) {
        printf("\n1. Insert key\n");
        printf("2. Delete key\n");
        printf("3. Search key\n");
        printf("4. Print tree\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                printf("Enter key to insert: ");
                scanf("%d", &key);
                insert(&root, key);
                printf("Key %d inserted successfully!\n", key);
                break;
                
            case 2:
                printf("Enter key to delete: ");
                scanf("%d", &key);
                delete_key(&root, key);
                break;
                
            case 3:
                printf("Enter key to search: ");
                scanf("%d", &key);
                if (root == NULL) {
                    printf("Search not possible - Tree is empty!\n");
                } else if (search(root, key) != NULL) {
                    printf("Key %d found in the tree!\n", key);
                } else {
                    printf("Search not possible - Key %d not found in the tree!\n", key);
                }
                break;
                
            case 4:
                if (root == NULL) {
                    printf("Tree is empty!\n");
                } else {
                    printf("\nB-Tree structure:\n");
                    print_tree(root, 0);
                }
                break;
                
            case 5:
                free_tree(root);
                printf("Memory freed. Exiting...\n");
                return 0;
                
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }
    
    return 0;
}