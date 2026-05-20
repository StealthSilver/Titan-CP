# Time Complexity Analysis

**Time complexity** measures how the **running time** of an algorithm grows as the **input size** `n` increases. We ignore constants and low-order terms and focus on the **dominant term** at large `n`.

---

## Two ways to study time

| Approach | What we measure | Example |
|----------|-----------------|---------|
| **Experimental** | Actual seconds on a machine | Run code for many values of `n`, record time (`a.cpp`) |
| **Theoretical** | Growth as a function of `n` | Count operations / loops → Big O |

Experimental results depend on CPU, compiler flags (`-O2`), and RAM. Theoretical Big O describes **scalability** and is what we use to compare algorithms in contests.

---

## Big O notation

We write **O(expression)** to mean: for large enough `n`, time grows **at most** like that expression (upper bound).

- **O(1)** — constant time (fixed number of steps).
- **O(log n)** — logarithmic (halving the problem each step).
- **O(n)** — linear (one pass over input).
- **O(n log n)** — common for efficient sorting.
- **O(n²)** — quadratic (nested loops over `n`).

**Rules of thumb**

1. Drop constants: `3n → O(n)`.
2. Keep only the largest term: `n² + 100n → O(n²)`.
3. Nested work multiplies: loop inside loop → multiply complexities.
4. Sequential blocks add: do A then B → take the **maximum** of the two.

---

## Experimental analysis (`a.cpp`)

We sort a descending array with `std::sort` (typically **O(n log n)**) and print time for:

`n = 100, 1000, 100000, 10000000, 100000000`

**What to observe**

- Time should **not** grow like `n²` (that would mean ~10,000× slower when `n` grows 100×).
- When `n` increases by a large factor, time grows faster than linear but slower than quadratic — consistent with **O(n log n)**.

Run:

```bash
g++ -std=c++17 -O2 -o a a.cpp && ./a
```

---

## Nested loops → O(n²)

```cpp
for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
        // O(1) work
    }
}
```

- Outer loop: `n` iterations.
- Inner loop: `n` iterations per outer step.
- Total operations ≈ `n × n = n²` → **Time: O(n²)**.

Same idea for `i` and `j` up to `n`: printing an `n × n` grid, checking all pairs `(i, j)`, brute-force on arrays.

---

## Bubble sort

Repeatedly swap adjacent elements if they are out of order until the array is sorted.

| Case | When | What happens | Time |
|------|------|--------------|------|
| **Best** | Already sorted | One pass, no swaps (with early exit) | **O(n)** |
| **Average** | Random order | Many swaps | **O(n²)** |
| **Worst** | Reverse sorted | Maximum swaps per pass | **O(n²)** |

- Two nested loops over the array → about `n²` comparisons/swaps in worst case.
- **Best case** is only **O(n)** if you **stop early** when no swap happens in a pass; without that optimization, even a sorted array is often analyzed as **O(n²)** in the basic version.

Bubble sort is used for learning, not for large `n` in contests.

---

## Binary search

**Precondition:** array (or range) is **sorted**.

```cpp
// Each step cuts the search interval in half
while (lo <= hi) {
    int mid = (lo + hi) / 2;
    if (a[mid] == target) return mid;
    else if (a[mid] < target) lo = mid + 1;
    else hi = mid - 1;
}
```

- Interval size: `n → n/2 → n/4 → … → 1`
- Number of steps ≈ log₂(n) → **Time: O(log n)**
- **Space:** O(1) iterative, O(log n) recursive (call stack).

Works on answer spaces too (“binary search on answer”) — still **O(log n)** steps if each check is O(1).

---

## Merge sort

**Idea:** split array in half, sort each half recursively, **merge** two sorted halves.

| Phase | Work per level | Levels |
|-------|----------------|--------|
| Split | O(1) per element to divide | O(log n) levels |
| Merge two halves of total size `n` | O(n) | O(log n) merges |

Total: **O(n log n)** time in all cases (best, average, worst).

| Case | Time |
|------|------|
| Best | **O(n log n)** |
| Average | **O(n log n)** |
| Worst | **O(n log n)** |

**Space:** O(n) for the temporary merge buffer (typical implementation).

Compared to bubble sort **O(n²)**, merge sort scales to large `n`; same class as `std::sort` (**O(n log n)** average).

---

## Quick reference (time only)

| Pattern / algorithm | Time complexity |
|---------------------|-----------------|
| Single loop over `n` | O(n) |
| Nested loops, both `n` | O(n²) |
| Binary search | O(log n) |
| Bubble sort (worst / average) | O(n²) |
| Bubble sort (best, with early exit) | O(n) |
| Merge sort | O(n log n) |
| `std::sort` | O(n log n) average |

---

## How to analyze code yourself

1. Find **input size** `n` (array length, number of nodes, etc.).
2. Count **loops** and **recursion depth** in terms of `n`.
3. **Multiply** nested costs, **add** sequential blocks (keep max).
4. State **best / average / worst** if they differ (e.g. bubble sort).
5. Express the dominant growth using **Big O**.

---

## Avoiding TLE (Time Limit Exceeded)

On most competitive programming judges, a problem gives about **1 second** per test case. A typical machine can execute on the order of **~10⁸ operations per second** (we round this to **~100 million operations**).

So before you submit, estimate:

$$\text{operations} \approx n \text{ (or } n^k, 2^n, n!\text{, etc.)} \times \text{constant factor}$$

If that count is **much larger than 10⁸**, the program will likely get **TLE** even if the logic is correct.

The table below is a **rule of thumb**: for each worst-case time complexity, what is the **largest `n` you can usually afford** so that operations stay around **≤ 10⁸**?

| Max `n` (approx.) | Worst-case time | Why it fits (~10⁸ ops) | Example algorithm / pattern |
|-------------------|-----------------|-------------------------|-----------------------------|
| **< 11** | **O(n!)** | 10! ≈ 3.6×10⁶; 11! ≈ 4×10⁷ | Brute force all permutations (e.g. small TSP by trying every order) |
| **< 18** | **O(2ⁿ · n²)** | 2¹⁷·17² ≈ 3.5×10⁷ | DP over subsets with O(n²) per state (e.g. Held–Karp style) |
| **< 22** | **O(2ⁿ · n)** | 2²¹·21 ≈ 4.4×10⁷ | Subset DP: 2ⁿ subsets, O(n) work per subset |
| **< 100** | **O(n⁴)** | 100⁴ = 10⁸ | Four nested loops each up to `n` |
| **< 400** | **O(n³)** | 400³ = 6.4×10⁷ | Floyd–Warshall (all-pairs shortest paths), triple loop on matrix |
| **< 2k** | **O(n² log n)** | 2000²·log₂(2000) ≈ 4.4×10⁷ | Sorting many pairs, or O(n²) with a `log n` factor per step |
| **< 10k** | **O(n²)** | 10⁴² = 10⁸ | Naive LCS, bubble sort, check all pairs `(i, j)`, 2D DP with `n × n` states |
| **< 1M** | **O(n log n)** | 10⁶·log₂(10⁶) ≈ 2×10⁷ | `std::sort`, merge sort, building a segment tree from array |
| **≤ 100M** | **O(n)**, **O(log n)**, **O(1)** | 10⁸·1 = 10⁸ | One pass over array, binary search, hash map lookup, prefix sums |

**How to use this in contests**

1. Read constraints: maximum `n` (or `N`, `m`, etc.) from the problem statement.
2. Write your solution’s **worst-case** Big O.
3. Find the row in the table that matches your complexity → check if problem `n` is below that limit.
4. If not, you need a **better algorithm** (lower Big O), not a faster language trick.

**Note:** Constants matter a little (fast I/O, tight loops), but **complexity class** decides TLE when `n` is large. Always optimize the algorithm first.