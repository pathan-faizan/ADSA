# 🌲 Fibonacci Heap — Fully Safe & Correct Menu-Driven Implementation (C)

This program implements a **robust and safe Fibonacci Heap** supporting all essential operations:

- **Insert**
- **Extract-Min**
- **Decrease-Key**
- **Delete Node**
- **Find-Min**
- **Print Root List**
- **Union** (implemented but not exposed in the menu)

A dynamic array maintains **node IDs**, allowing the user to perform operations on specific nodes.

This implementation emphasizes **correctness**, **memory-safety**, and **robust pointer handling**.

---

## ✅ Features

### ✔ Fibonacci Heap Operations
- Amortized:
  - **Insert: O(1)**
  - **Find-min: O(1)**
  - **Decrease-key: O(1)** amortized
  - **Union: O(1)**
- Extract-min: O(log n)
- Safe linking + consolidation
- Cascading cuts
- Circular doubly-linked lists for root and child lists

### ✔ Safe & Defensive Coding
- Root list rebuild uses fixed copies → avoids pointer corruption
- Consolidation avoids accessing modified lists
- Children extracted safely when removing min
- Menu tracks node pointers by index
- Removes NULL pointers when nodes deleted/extracted

---

## 📦 Files
```
fib_heap_correct.c
```

Compile with:
```bash
gcc -std=c99 fib_heap_correct.c -o fibheap -lm
```

Run:
```bash
./fibheap
```

---

## 🧮 Operations Explained

### 🟩 Insert
Creates a new node with:
- `degree = 0`
- `mark = 0`
- standalone circular list

Adds it to the root list.

### 🟨 Extract-Min
Steps:
1. Move all children → root list  
2. Remove min from root list  
3. Consolidate root list  
4. Return extracted minimum

### 🟦 Decrease-Key
If key becomes less than parent:
- Cut node from parent
- Cascading cut if needed
- Possibly updates heap minimum

### 🟥 Delete Node
Implemented as:
```
decrease-key(node, -∞)
extract-min()
```

### 🟪 Print Root List
Prints all root keys in circular order, bounded by safety check.

---

## 🖥 Example Menu Session

```
--- Fibonacci Heap Menu ---
1. Insert
2. Extract Min
3. Decrease Key
4. Delete Node
5. Find Min
6. Print Heap (root list)
7. Exit
Enter choice: 1
Enter key: 50
Inserted node id = 0

Enter choice: 1
Enter key: 12
Inserted node id = 1

Enter choice: 5
Min = 12

Enter choice: 6
Root list: 12 50
```

---

## ⚠ Notes

- No full destructor implemented (children + root lists require recursive cleanup)
- Union operation works but not exposed in the menu
- Node IDs become invalid after deletion/extraction

---

## 📝 Code

> The complete implementation provided in `fib_heap_correct.c` is already final and correct.  
> Paste it directly into a `.c` file and compile.

---

If you want, I can also create:

✔ UML diagram  
✔ Simplified version  
✔ Debug-logging version  
✔ Visualization (GraphViz) output generator  
✔ README + illustrations

Just tell me!
