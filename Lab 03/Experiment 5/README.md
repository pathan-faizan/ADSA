# 🌐 Graph Algorithms in C (SIF Input + Dijkstra + Floyd-Warshall)

This program reads a graph in **SIF (Simple Input Format)** and performs:  
✔ Dijkstra’s Single-Source Shortest Path  
✔ Floyd-Warshall All-Pairs Shortest Paths  
✔ Displays adjacency matrix  

It supports up to **20 vertices** and uses an adjacency matrix representation.

---

## 📌 Features
- Read weighted graph from **SIF format**  
- Supports **undirected** (modifiable) or **directed** graph  
- Compute:
  - **Dijkstra** (shortest path from a source node)
  - **Floyd-Warshall** (shortest distances between all pairs)
- Handles **INF** (no edge) using value 99999
- Interactive menu-driven interface

---

## 🧾 SIF Input Format

Example:
```
A B 4
A C 2
B C 5
B D 10
C D 3
END
```

Meaning:
- Edge A–B has weight 4  
- Edge A–C has weight 2  
- Input ends on `END`

The program maps node names to indices (`0,1,2,...`).

---

## 🛠️ Algorithms Used

### ✔ Dijkstra (Single-Source)
- Works with non-negative weights
- Uses greedy selection of nearest unvisited node
- Time complexity: **O(V²)** due to adjacency matrix

### ✔ Floyd–Warshall (All Pairs)
- Dynamic programming algorithm
- Computes shortest path between **every pair**
- Time complexity: **O(V³)**  
- Updates `dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j])`

---

## 🚀 Build & Run

### Compile
```bash
gcc graph_sif.c -o graph_sif
```

### Run
```bash
./graph_sif
```

---

## 📊 Example Session
```
--- Graph Algorithms ---
1. Read Graph (SIF)
2. Dijkstra (Single Source)
3. Floyd-Warshall (All Pairs)
4. Exit
Choice: 1
Enter edges in SIF format (u v w). Type END to stop:
A B 4
A C 2
C D 3
END

Graph adjacency matrix:
  0   4   2 INF
  4   0   5  10
  2   5   0   3
INF  10   3   0

Choice: 2
Enter source vertex index (0–3): 0
Dijkstra (source 0):
Node 0: 0
Node 1: 4
Node 2: 2
Node 3: 5

Choice: 3
Floyd-Warshall All-Pairs Shortest Paths:
  0   4   2   5
  4   0   5   8
  2   5   0   3
  5   8   3   0
```

---

## 🧠 Insight
This program demonstrates:
- How to read named nodes dynamically  
- How shortest-path algorithms work on adjacency matrices  
- Differences between **single-source** and **all-pairs** approaches  

Perfect for learning graph algorithms and experimenting with custom inputs.

