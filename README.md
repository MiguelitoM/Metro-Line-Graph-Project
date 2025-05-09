# Metro Connectivity – ASA Project 2 (2024/25)

## 🔍 Overview
This program computes the **metro connectivity index** `mc` of an urban rail network.  
Given an undirected multigraph whose edges are tagged with line identifiers, the index is

```
mc = max_{s1,s2 ∈ stations}  ML(s1, s2)
```

where `ML(s1, s2)` is the minimum number of **line changes** required to travel from
station `s1` to `s2`.  
The project was developed for the *Analysis and Design of Algorithms* course (ASA) at
Instituto Superior Técnico.

**Special cases**

* Output **`0`** if every pair of stations can be connected *without* switching lines.
* Output **`‑1`** if the network is disconnected (there exist two stations with no route at all).

## ⚙️ Compiling
| Component | Command |
|-----------|---------|
| **Solver** | `g++ -std=c++11 -O3 -Wall proj2.cpp -o solver -lm` |
| **Generator** | `g++ -std=c++11 -O3 -Wall gera.cpp -o generator` |

## 🧪 Testing
### Generate a random instance
```bash
# Parameters: V E L [bConnect] [seed]
./generator 30 40 4 1 > network.txt
```
The optional flag `bConnect = 1` forces the generator to produce a **connected**
network, guaranteeing that `mc ≥ 0`.

### Solve an instance
```bash
./solver < network.txt
```
