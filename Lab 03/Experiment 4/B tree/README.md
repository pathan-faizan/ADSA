# B-Tree Insert and Delete Operations in C

## 📌 Problem Statement
A **B-Tree** is a self-balancing tree data structure that maintains sorted data and allows searches, sequential access, insertions, and deletions in logarithmic time. This implementation provides complete **insert** and **delete** operations while maintaining all B-Tree properties.

---

## ⚙️ Algorithm Explanation

### 1. **B-Tree Properties**
   - All leaves are at the same level
   - Internal nodes have at least ⌈t/2⌉ keys (except root)
   - Internal nodes have at most 2t-1 keys
   - Keys are stored in sorted order within each node
   - Each internal node has one more child than keys

### 2. **Insertion Algorithm**
   - **Step 1:** If tree is empty, create root with the key
   - **Step 2:** If root is full, create new root and split old root
   - **Step 3:** Insert into non-full node:
     - If leaf node: Insert key in sorted position
     - If internal node: Find appropriate child, split if full, then recurse
   - **Node Splitting:** When a node becomes full (2t-1 keys):
     - Create new node and move half the keys
     - Promote middle key to parent
     - Update child pointers accordingly

### 3. **Deletion Algorithm**
   - **Case 1 (Leaf Node):** Simply remove the key and shift remaining keys
   - **Case 2 (Internal Node):**
     - **Case 2a:** If left child has ≥t keys, replace with predecessor
     - **Case 2b:** If right child has ≥t keys, replace with successor  
     - **Case 2c:** If both children have t-1 keys, merge and recurse
   - **Case 3 (Key not in node):** Recurse to appropriate child
     - If child has only t-1 keys, ensure it has ≥t keys by:
       - **Borrowing** from sibling (if sibling has ≥t keys)
       - **Merging** with sibling (if both have t-1 keys)

---

## ⏱️ Time Complexity
- **Search:** `O(log n)`
- **Insertion:** `O(log n)`
- **Deletion:** `O(log n)`
- **Space Complexity:** `O(n)`

**Where:**
- `n` = number of keys in the tree
- `t` = minimum degree (t = 3 in this implementation)

---

## 🛠️ Key Functions

| Function | Description |
|----------|-------------|
| `insert()` | Main insertion function with root splitting |
| `delete_key()` | Main deletion function with error checking |
| `search()` | Searches for a key in the B-Tree |
| `split_child()` | Splits a full child node during insertion |
| `merge()` | Merges nodes during deletion |
| `borrow_from_prev()/borrow_from_next()` | Borrows keys from siblings |
| `print_tree()` | Displays tree structure level by level |

---

## 📋 Configuration
```c
#define MIN_DEGREE 3              // Minimum degree (t = 3)
#define MAX_KEYS (2 * MIN_DEGREE - 1)    // Maximum keys = 5
#define MAX_CHILDREN (2 * MIN_DEGREE)    // Maximum children = 6
```

---

## 🎮 Menu Options
1. **Insert key** - Add a new key to the B-Tree
2. **Delete key** - Remove a key from the B-Tree
3. **Search key** - Find if a key exists in the tree
4. **Print tree** - Display the complete tree structure
5. **Exit** - Free memory and terminate program

---

## 💻 Sample Input/Output

### Input Example
```bash
B-Tree Operations (Minimum Degree = 3)
========================================

1. Insert key
2. Delete key
3. Search key
4. Print tree
5. Exit
Enter your choice: 1
Enter key to insert: 10
Key 10 inserted successfully!

Enter your choice: 1
Enter key to insert: 20
Key 20 inserted successfully!

Enter your choice: 4
```

### Output Example
```bash
B-Tree structure:
Level 0: 10 20

Enter your choice: 2
Enter key to delete: 5
Deletion not possible - Key 5 not found in tree!

Enter your choice: 3
Enter key to search: 10
Key 10 found in the tree!

Enter your choice: 3
Enter key to search: 15
Search not possible - Key 15 not found in the tree!
```

---

## 🚨 Error Handling

### Deletion Errors
- **Empty Tree:** `"Deletion not possible - Tree is empty!"`
- **Key Not Found:** `"Deletion not possible - Key X not found in tree!"`
- **Success:** `"Key X deleted successfully!"`

### Search Errors
- **Empty Tree:** `"Search not possible - Tree is empty!"`
- **Key Not Found:** `"Search not possible - Key X not found in the tree!"`
- **Success:** `"Key X found in the tree!"`

---

## 🔧 Features
- ✅ Complete B-Tree implementation with all edge cases handled
- ✅ Automatic node splitting and merging
- ✅ Key borrowing between sibling nodes
- ✅ Memory management with proper cleanup
- ✅ Interactive menu-driven interface
- ✅ Comprehensive error handling
- ✅ Tree visualization with level-wise printing

### Note
- The minimum degree `t = 3` means each node can have 2-5 keys and 3-6 children
- All B-Tree properties are maintained after every insert/delete operation
- Memory is automatically managed with proper allocation and deallocation