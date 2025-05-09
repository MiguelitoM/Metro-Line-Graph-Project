# Metro Connectivity Index Solver – ASA Project 2 (2024/25)

### 🔍 Overview
This program computes the **metro connectivity index** `mc` of an urban rail network.  
Given an undirected multigraph whose edges are tagged with line identifiers, the index is

```
mc = max_{s1,s2 ∈ stations}  ML(s1, s2)
```

where `ML(s1, s2)` is the minimum number of **line changes** required to travel from
station `s1` to `s2`.  
The project was developed for the *Analysis and Design of Algorithms* course (ASA) at
Instituto Superior Técnico. citeturn3file0

**Special cases**

* Output **`0`** if every pair of stations can be connected *without* switching lines.
* Output **`‑1`** if the network is disconnected (there exist two stations with no route at all).

---

### 💡 Algorithm sketch
1. **Read input** and build, for every line `ℓ`, the set of stations it serves.  
2. **Build the *line graph***  
   * Vertices = metro lines  
   * Edges between two lines if they share at least one common station.
3. For every line, run **BFS** on the line graph to obtain the shortest distances (line‑change
counts) to all other lines and keep the **maximum**.  
4. Return the overall maximum distance as `mc`.  
If the line graph is disconnected the BFS started on one component cannot reach all lines,
which implies at least two unreachable stations → answer **`‑1`**. citeturn3file1

*Time complexity*: `O(L·(L+E))`, where **L** is the number of lines and **E** the edges of the
line graph.<br>
*Memory*: `O(L²)` worst‑case adjacency representation.

---

### 📜 Example
Input file from the statement (excerpt):

```
7 8 3
3 2 1
2 7 1
7 5 1
2 6 2
6 4 2
4 1 2
4 1 3
1 5 3
```

Output produced by the solver:

```
1
```

A single line change is enough between the two “furthest” stations.

---

### ⚙️ Compiling

| Component | Command |
|-----------|---------|
| **Solver** | `g++ -std=c++11 -O3 -Wall proj2.cpp -o solver -lm` |
| **Generator** | `g++ -std=c++11 -O3 -Wall gera.cpp -o generator` |

---

### 🏃‍♂️ Running

#### Solve an instance
```bash
./solver < network.txt
# or, following the original statement:
./a.out < testfile
```

#### Generate a random instance
```bash
# Parameters: V E L [bConnect] [seed]
./generator 30 40 4 1 > network.txt
```
The optional flag `bConnect = 1` forces the generator to produce a **connected**
network, guaranteeing that `mc ≥ 0`. citeturn3file2

---

### 🧪 Testing
A collection of public test cases (small, edge‑case, and stress) is included under
`tests/`.  
Run every test with:

```bash
for f in tests/*.in; do
  ./solver < "$f" > tmp.out
  diff -u "$f.expected" tmp.out || echo "Mismatch on $f"
done
```

---

### 📂 Repository layout
```
.
├── proj2.cpp      # metro connectivity solver
├── gera.cpp       # random instance generator
└── README.md      # (this file)
```

---

### 📚 Learning outcomes
* Modelling transportation networks as multigraphs and line graphs  
* BFS breadth‑first *diameter* computation  
* Efficient set / adjacency management in modern C++11  
* Random instance generation with connectivity guarantees  

---

### 📝 Authors & License
Developed by <author‑name(s)>.  
Released under the MIT License.
