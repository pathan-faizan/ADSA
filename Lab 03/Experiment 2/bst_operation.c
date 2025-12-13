#include <stdio.h>
#include <stdlib.h>

// Structure for BST node
struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

// Function to create a new node
struct Node* createNode(int value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = value;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Function to insert a node in BST
struct Node* insertNode(struct Node* root, int value) {
    if (root == NULL) {
        return createNode(value);
    }
    
    if (value < root->data) {
        root->left = insertNode(root->left, value);
    } else if (value > root->data) {
        root->right = insertNode(root->right, value);
    }
    
    return root;
}

// Function to find the minimum value node
struct Node* findMin(struct Node* root) {
    while (root != NULL && root->left != NULL) {
        root = root->left;
    }
    return root;
}

// Function to delete a node from BST
struct Node* deleteNode(struct Node* root, int value) {
    if (root == NULL) {
        return root;
    }
    
    // Find the node to be deleted
    if (value < root->data) {
        root->left = deleteNode(root->left, value);
    } else if (value > root->data) {
        root->right = deleteNode(root->right, value);
    } else {
        // Node found - now delete it
        
        // Case 1: No child or one child
        if (root->left == NULL) {
            struct Node* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            struct Node* temp = root->left;
            free(root);
            return temp;
        }
        
        // Case 2: Two children
        struct Node* temp = findMin(root->right);
        root->data = temp->data;
        root->right = deleteNode(root->right, temp->data);
    }
    return root;
}

// Inorder traversal (Left, Root, Right)
void inorderTraversal(struct Node* root) {
    if (root != NULL) {
        inorderTraversal(root->left);
        printf("%d ", root->data);
        inorderTraversal(root->right);
    }
}

// Preorder traversal (Root, Left, Right)
void preorderTraversal(struct Node* root) {
    if (root != NULL) {
        printf("%d ", root->data);
        preorderTraversal(root->left);
        preorderTraversal(root->right);
    }
}

// Postorder traversal (Left, Right, Root)
void postorderTraversal(struct Node* root) {
    if (root != NULL) {
        postorderTraversal(root->left);
        postorderTraversal(root->right);
        printf("%d ", root->data);
    }
}

// Function to display the BST structure
void displayTree(struct Node* root, int space) {
    if (root == NULL) {
        return;
    }
    
    space += 5;
    
    displayTree(root->right, space);
    
    printf("\n");
    for (int i = 5; i < space; i++) {
        printf(" ");
    }
    printf("%d\n", root->data);
    
    displayTree(root->left, space);
}

// Function to free the entire tree
void freeTree(struct Node* root) {
    if (root != NULL) {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}

int main() {
    struct Node* root = NULL;
    int choice, value;
    
    printf("=== Binary Search Tree Operations ===\n");
    
    while (1) {
        printf("\nMenu:\n");
        printf("1. Create/Insert Node\n");
        printf("2. Delete Node\n");
        printf("3. Inorder Traversal\n");
        printf("4. Preorder Traversal\n");
        printf("5. Postorder Traversal\n");
        printf("6. Display Tree Structure\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                printf("Enter value to insert: ");
                scanf("%d", &value);
                if (root == NULL) {
                    root = createNode(value);
                    printf("BST created with root: %d\n", value);
                } else {
                    root = insertNode(root, value);
                    printf("Value %d inserted successfully.\n", value);
                }
                break;
                
            case 2:
                if (root == NULL) {
                    printf("Tree is empty!\n");
                } else {
                    printf("Enter value to delete: ");
                    scanf("%d", &value);
                    root = deleteNode(root, value);
                    printf("Value %d deleted successfully.\n", value);
                }
                break;
                
            case 3:
                if (root == NULL) {
                    printf("Tree is empty!\n");
                } else {
                    printf("Inorder Traversal: ");
                    inorderTraversal(root);
                    printf("\n");
                }
                break;
                
            case 4:
                if (root == NULL) {
                    printf("Tree is empty!\n");
                } else {
                    printf("Preorder Traversal: ");
                    preorderTraversal(root);
                    printf("\n");
                }
                break;
                
            case 5:
                if (root == NULL) {
                    printf("Tree is empty!\n");
                } else {
                    printf("Postorder Traversal: ");
                    postorderTraversal(root);
                    printf("\n");
                }
                break;
                
            case 6:
                if (root == NULL) {
                    printf("Tree is empty!\n");
                } else {
                    printf("Tree Structure (rotated 90° clockwise):\n");
                    displayTree(root, 0);
                }
                break;
                
            case 7:
                freeTree(root);
                printf("Program exited. Memory freed.\n");
                exit(0);
                
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }
    
    return 0;
}