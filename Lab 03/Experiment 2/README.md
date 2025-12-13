# Binary Search Tree Operations in C

## 📌 Problem Statement
A Binary Search Tree (BST) is a hierarchical data structure where each node has at most two children, maintaining the property that for any node, all values in its left subtree are smaller and all values in its right subtree are larger. This program implements comprehensive BST operations including creation, insertion, deletion, and various traversal methods.

---

## ⚙️ Algorithm Explanation

1. **BST Structure**
   - Each node contains:
        - data: The integer value stored in the node
        - left: Pointer to the left child node
        - right: Pointer to the right child node

2. **Operations Implemented**
   - Creation
         - Initializes an empty BST
         - Creates the first node when the first value is inserted

   - Insertion
         - If tree is empty, create root node
         - Compare new value with current node:
              - If smaller, recursively insert in left subtree
              - If larger, recursively insert in right subtree
              - If equal, do nothing (BSTs typically don't allow duplicates)

   - Deletion
         - Three cases handled:  
              - No children: Simply remove the node
              - One child: Replace node with its child
              - Two children: Find inorder successor (minimum in right subtree), replace node's     value, then delete the successor

   - Traversal
         - Inorder: Left → Root → Right (produces sorted output)
         - Preorder: Root → Left → Right
         - Postorder: Left → Right → Root
 

## ⏱️ Time Complexity
- **Insertion:** `O(log n) average case, O(n) worst case (unbalanced tree)`
- **Deletion:** `O(log n) average case, O(n) worst case`
- **Traversal:** `O(n) for all types (must visit every node)`
- **Space Complexity:** `O(n) for storing the tree`


---



### Input Example
```bash
Menu:
1. Create/Insert Node
2. Delete Node
3. Inorder Traversal
4. Preorder Traversal
5. Postorder Traversal
6. Display Tree Structure
7. Exit
Enter your choice: 1
Enter value to insert: 50
```

### Output Example
```bash
BST created with root: 50

Inorder Traversal: 20 30 40 50 60 70 80 

Tree Structure (rotated 90° clockwise):

         80

     70

         60

50

         40

     30

         20
```