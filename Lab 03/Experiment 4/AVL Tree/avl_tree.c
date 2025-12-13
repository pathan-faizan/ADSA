#include <stdio.h>
#include <stdlib.h>

// Structure for AVL Tree node
struct Node {
    int data;
    struct Node* left;
    struct Node* right;
    int height;
};

// Function to get height of a node
int getHeight(struct Node* node) {
    if (node == NULL)
        return 0;
    return node->height;
}

// Function to get maximum of two integers
int max_int(int a, int b) {
    return (a > b) ? a : b;
}

// Function to create a new node
struct Node* createNode(int data) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    return node;
}

// Function to get balance factor of a node
int getBalance(struct Node* node) {
    if (node == NULL)
        return 0;
    return getHeight(node->left) - getHeight(node->right);
}

// Right rotate
struct Node* rightRotate(struct Node* y) {
    struct Node* x = y->left;
    struct Node* T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update heights
    y->height = max_int(getHeight(y->left), getHeight(y->right)) + 1;
    x->height = max_int(getHeight(x->left), getHeight(x->right)) + 1;

    // Return new root
    return x;
}

// Left rotate
struct Node* leftRotate(struct Node* x) {
    struct Node* y = x->right;
    struct Node* T2 = y->left;

    // Perform rotation
    y->left = x;
    x->right = T2;

    // Update heights
    x->height = max_int(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = max_int(getHeight(y->left), getHeight(y->right)) + 1;

    // Return new root
    return y;
}

// Function to insert a node in AVL tree
struct Node* insert(struct Node* node, int data) {
    // 1. Perform normal BST insertion
    if (node == NULL)
        return createNode(data);

    if (data < node->data)
        node->left = insert(node->left, data);
    else if (data > node->data)
        node->right = insert(node->right, data);
    else // Equal keys not allowed
        return node;

    // 2. Update height of current node
    node->height = 1 + max_int(getHeight(node->left), getHeight(node->right));

    // 3. Get the balance factor
    int balance = getBalance(node);

    // 4. If unbalanced, there are 4 cases

    // Left Left Case
    if (balance > 1 && data < node->left->data)
        return rightRotate(node);

    // Right Right Case
    if (balance < -1 && data > node->right->data)
        return leftRotate(node);

    // Left Right Case
    if (balance > 1 && data > node->left->data) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Right Left Case
    if (balance < -1 && data < node->right->data) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    // Return unchanged node
    return node;
}

// Function to find the node with minimum value
struct Node* findMin(struct Node* node) {
    while (node->left != NULL)
        node = node->left;
    return node;
}

// Function to delete a node from AVL tree
struct Node* deleteNode(struct Node* root, int data) {
    // 1. Perform standard BST delete
    if (root == NULL)
        return root;

    if (data < root->data)
        root->left = deleteNode(root->left, data);
    else if (data > root->data)
        root->right = deleteNode(root->right, data);
    else {
        // Node to be deleted found
        
        // Node with only right child or no child
        if (root->left == NULL) {
            struct Node* temp = root->right;
            free(root);
            return temp;
        }
        // Node with only left child
        else if (root->right == NULL) {
            struct Node* temp = root->left;
            free(root);
            return temp;
        }

        // Node with two children
        struct Node* temp = findMin(root->right);
        
        // Copy the inorder successor's data to this node
        root->data = temp->data;
        
        // Delete the inorder successor
        root->right = deleteNode(root->right, temp->data);
    }

    // If tree had only one node
    if (root == NULL)
        return root;

    // 2. Update height of current node
    root->height = 1 + max_int(getHeight(root->left), getHeight(root->right));

    // 3. Get the balance factor
    int balance = getBalance(root);

    // 4. If unbalanced, there are 4 cases

    // Left Left Case
    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);

    // Left Right Case
    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // Right Right Case
    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);

    // Right Left Case
    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

// Function for inorder traversal
void inorder(struct Node* root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
}

// Function for preorder traversal
void preorder(struct Node* root) {
    if (root != NULL) {
        printf("%d ", root->data);
        preorder(root->left);
        preorder(root->right);
    }
}

// Function to search for a value in AVL tree
struct Node* search(struct Node* root, int data) {
    if (root == NULL || root->data == data)
        return root;
    
    if (data < root->data)
        return search(root->left, data);
    
    return search(root->right, data);
}

// Function to display menu
void displayMenu() {
    printf("\n=== AVL Tree Operations ===\n");
    printf("1. Insert\n");
    printf("2. Delete\n");
    printf("3. Search\n");
    printf("4. Inorder Traversal\n");
    printf("5. Preorder Traversal\n");
    printf("6. Exit\n");
    printf("Enter your choice: ");
}

// Main function
int main() {
    struct Node* root = NULL;
    int choice, value;
    struct Node* result;

    printf("AVL Tree Implementation in C\n");
    printf("============================\n");

    while (1) {
        displayMenu();
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter value to insert: ");
                scanf("%d", &value);
                root = insert(root, value);
                printf("Value %d inserted successfully!\n", value);
                break;

            case 2:
                if (root == NULL) {
                    printf("Tree is empty!\n");
                    break;
                }
                printf("Enter value to delete: ");
                scanf("%d", &value);
                result = search(root, value);
                if (result != NULL) {
                    root = deleteNode(root, value);
                    printf("Value %d deleted successfully!\n", value);
                } else {
                    printf("Value %d not found in the tree!\n", value);
                }
                break;

            case 3:
                if (root == NULL) {
                    printf("Tree is empty!\n");
                    break;
                }
                printf("Enter value to search: ");
                scanf("%d", &value);
                result = search(root, value);
                if (result != NULL) {
                    printf("Value %d found in the tree!\n", value);
                } else {
                    printf("Value %d not found in the tree!\n", value);
                }
                break;

            case 4:
                if (root == NULL) {
                    printf("Tree is empty!\n");
                } else {
                    printf("Inorder Traversal: ");
                    inorder(root);
                    printf("\n");
                }
                break;

            case 5:
                if (root == NULL) {
                    printf("Tree is empty!\n");
                } else {
                    printf("Preorder Traversal: ");
                    preorder(root);
                    printf("\n");
                }
                break;

            case 6:
                printf("Exiting program. Goodbye!\n");
                exit(0);

            default:
                printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}