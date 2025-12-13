# 🔗 Maximum Bipartite Matching (DFS-Based Augmenting Paths) — C Program

This program computes the **maximum bipartite matching** using the standard DFS-based augmenting path algorithm (also called Kuh’s algorithm).

It takes an **n × m adjacency matrix**, where:
- `n` = number of left-side vertices  
- `m` = number of right-side vertices  
- `graph[u][v] = 1` means an edge exists from left node `u` to right node `v`.

---

## 📌 Features
- Finds maximum matching in a **bipartite graph**
- Uses recursive DFS to find augmenting paths
- Tracks:
  - `matchR[v]` → which left node is matched to right node `v`
  - `visited[v]` → aids DFS to avoid revisits
- Prints final matching pairs
- Works for small graphs (max size = 10×10)

---

## 🧠 Algorithm Overview

### ✔ DFS-Based Augmenting Path Search
For each left node `u`, try to match it:

```
findMatch(u):
    for each right v:
        if edge(u, v) exists and v not visited:
            mark v visited
            if v is free OR its matched partner can be reassigned:
                matchR[v] = u
                return true
    return false
```

### ✔ Main Procedure
1. Initialize all right-side nodes as unmatched (`matchR[v] = -1`)
2. For each left vertex:
   - Reset `visited[]`
   - Call `findMatch(u)`
3. Count successful matches → **maximum matching**

Time Complexity: **O(V × E)**  
(acceptable for small graphs)

---

## 🚀 Build & Run

### Compile
```bash
gcc bipartite_matching.c -o bipartite_matching
```

### Run
```bash
./bipartite_matching
```

---

## 📊 Example Input/Output

### Input:
```
Enter number of left vertices: 3
Enter number of right vertices: 3
Enter adjacency matrix (3 x 3):
1 1 0
0 1 1
1 0 1
```

### Output:
```
Maximum matching = 3
Matched pairs (Left -> Right):
0 -> 0
1 -> 1
2 -> 2
```

---

## 🧠 Insight
This implementation demonstrates:
- How augmenting paths improve matchings
- DFS-based matching logic
- One-sided assignment representation `matchR[]`

This is one of the fundamental approaches used in scheduling, assignment problems, and network flow algorithms.

