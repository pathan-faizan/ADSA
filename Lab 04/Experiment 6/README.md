# 🌉 Minimum Spanning Tree (MST) — Prim’s & Kruskal’s Algorithms in C

This program reads a weighted graph using **SIF format** and constructs a **Minimum Spanning Tree (MST)** using:  
✔ **Prim’s Algorithm**  
✔ **Kruskal’s Algorithm**  

It prints the selected edges and the total MST cost for both methods.

---

## 📌 Features
- Reads edges using SIF-like format: `U V W`
- Supports up to **100 vertices**
- Undirected weighted graph
- Builds MST using:
  - **Prim’s Algorithm** (greedy, grows one vertex at a time)
  - **Kruskal’s Algorithm** (edge-sorted + union–find)
- Displays:
  - MST edges
  - Total MST cost
- Vertices given as **A, B, C …** (mapped to index 0,1,2...)

---

## 🧾 SIF Input Format
Enter edges as:
```
A B 4
A C 6
B D 5
...
-1 -1 -1   ← to stop
```

Example meaning:
- Edge **A–B** has weight 4
- Edge **A–C** has weight 6

Character names → index mapping:
```
'A' → 0
'B' → 1
'C' → 2
...
```

---

## 🛠️ Algorithms Used

### ✔ Prim’s Algorithm
- Starts from vertex **A**
- Always picks the minimum-weight edge connecting MST → non-MST vertex
- Time complexity: **O(V²)** with adjacency matrix

### ✔ Kruskal’s Algorithm
- Uses **find()** + **union()** for cycle detection
- Picks globally smallest edges
- Time complexity: **O(E log E)**

---

## 🚀 Build & Run

### Compile
```bash
gcc mst.c -o mst
```

### Run
```bash
./mst
```

---

## 📊 Example Output
```
Enter number of vertices: 4
Enter edges in SIF format (u v w), enter -1 -1 -1 to stop:
A B 4
A C 6
B D 5
C D 3
-1 -1 -1

Edges in MST using Prim’s Algorithm:
A - B : 4
B - D : 5
C - D : 3
Total cost of MST (Prim’s): 12

Edges in MST using Kruskal’s Algorithm:
C - D : 3
A - B : 4
B - D : 5
Total cost of MST (Kruskal’s): 12
```

---

## 🧠 Insight
This program clearly shows the difference between:
- **Prim’s:** builds MST by expanding from a root  
- **Kruskal’s:** builds MST by picking globally smallest edges  

Great for studying MST algorithms and union–find data structure.

