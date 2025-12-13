# AVL Tree Implementation in C

## 📌 Problem Statement
An **AVL Tree** is a self-balancing binary search tree where the heights of the two child subtrees of any node differ by at most one. It automatically maintains balance through rotations during insertions and deletions, ensuring optimal search performance with O(log n) time complexity.

---

## ⚙️ Algorithm Explanation

### 1. **AVL Tree Properties**
   - **Balance Factor**: For any node, |height(left) - height(right)| ≤ 1
   - **Self-Balancing**: Automatically rebalances after insertions/deletions
   - **Binary Search Tree**: Maintains BST ordering property

### 2. **Rotation Operations**
   - **Right Rotation (LL Case)**: Used when left subtree is heavier
   - **Left Rotation (RR Case)**: Used when right subtree is heavier  
   - **Left-Right Rotation (LR Case)**: Left rotation on left child, then right rotation on root
   - **Right-Left Rotation (RL Case)**: Right rotation on right child, then left rotation on root

### 3. **Insertion Algorithm**
```
1. Perform standard BST insertion
2. Update height of current node
3. Calculate balance factor
4. If unbalanced, perform appropriate rotation:
   - LL Case: Right rotation
   - RR Case: Left rotation
   - LR Case: Left-Right rotation
   - RL Case: Right-Left rotation
```

### 4. **Deletion Algorithm**
```
1. Perform standard BST deletion
2. Update height of current node
3. Calculate balance factor
4. If unbalanced, perform appropriate rotation
5. Handle three cases:
   - Node with no children
   - Node with one child
   - Node with two children (replace with inorder successor)
```

---

## ⏱️ Time Complexity
- **Search:** `O(log n)`
- **Insertion:** `O(log n)`
- **Deletion:** `O(log n)`
- **Space Complexity:** `O(n)`

---

## 🚀 Features

- ✅ **Insert Operation**: Add new nodes while maintaining AVL property
- ✅ **Delete Operation**: Remove nodes with automatic rebalancing
- ✅ **Search Operation**: Find specific values efficiently
- ✅ **Tree Traversals**: Inorder and Preorder traversal methods
- ✅ **Interactive Menu**: User-friendly command-line interface
- ✅ **Balance Maintenance**: Automatic rotations to keep tree balanced

---

## 📝 How to Run

### Compilation
```bash
gcc -o avl_tree avl_tree.c
```

### Execution
```bash
./avl_tree
```

---

## 💡 Usage Examples

### Input Example
```bash
=== AVL Tree Operations ===
1. Insert
2. Delete
3. Search
4. Inorder Traversal
5. Preorder Traversal
6. Exit
Enter your choice: 1
Enter value to insert: 10

Enter your choice: 1
Enter value to insert: 20

Enter your choice: 1
Enter value to insert: 30
```

### Output Example
```bash
Value 10 inserted successfully!
Value 20 inserted successfully!
Value 30 inserted successfully!

Enter your choice: 4
Inorder Traversal: 10 20 30

Enter your choice: 5
Preorder Traversal: 20 10 30
```

### Deletion Example
```bash
Enter your choice: 2
Enter value to delete: 10
Value 10 deleted successfully!

Enter your choice: 4
Inorder Traversal: 20 30
```

### Search Example
```bash
Enter your choice: 3
Enter value to search: 20
Value 20 found in the tree!

Enter your choice: 3
Enter value to search: 15
Value 15 not found in the tree!
```

---

## 🔧 Key Functions

| Function | Description |
|----------|-------------|
| `insert()` | Inserts a new node and rebalances the tree |
| `deleteNode()` | Removes a node and maintains AVL property |
| `search()` | Searches for a value in the tree |
| `getHeight()` | Returns the height of a node |
| `getBalance()` | Calculates the balance factor of a node |
| `rightRotate()` | Performs right rotation for LL case |
| `leftRotate()` | Performs left rotation for RR case |
| `inorder()` | Displays tree in ascending order |
| `preorder()` | Displays tree in preorder traversal |

---

## 🌟 Advantages of AVL Trees

- **Guaranteed Balance**: Height difference never exceeds 1
- **Predictable Performance**: All operations are O(log n)
- **Automatic Maintenance**: No manual balancing required
- **Efficient for Frequent Searches**: Optimal for read-heavy applications

---

## 📋 Note
- Duplicate values are not allowed in this implementation
- The tree automatically handles all balancing operations
- Empty tree operations are handled gracefully with appropriate messages
- Memory is properly managed with dynamic allocation and deallocation