
# 🌲 Binary Indexed Tree (Fenwick Tree) - A Friendly Introduction

---

## 📌 What is a Binary Indexed Tree?

A **Binary Indexed Tree** (also called **Fenwick Tree**) is a data structure that helps you:

- **Quickly calculate prefix sums**
- **Update values efficiently**

It's **faster than a regular array** for these tasks and is commonly used in competitive programming.

---

## 🚀 Why Do We Need It?

Imagine you have a list of numbers, and you want to:

- **Find the sum of the first `k` numbers** many times
- **Update an element's value** quickly

With a normal array:
- Finding the sum takes **O(n)** time
- Updating a value is **O(1)**

With a **Binary Indexed Tree**:
- Both operations take **O(log n)** time!

---

## 🔍 Quick Review: Prefix Sum

**Prefix Sum** means the sum of elements from the **start of the array** up to a certain index.

For example:

```
Array: [2, 5, 1, 3]
Prefix Sums:
Index 1 → 2
Index 2 → 2+5 = 7
Index 3 → 7+1 = 8
Index 4 → 8+3 = 11
```

---

## 🧱 How the BIT is Built

Let’s say we have an array of size `n`. The BIT is a **separate array** (let’s call it `bit[]`) of size `n+1`.

Why `n+1`?
> Because BITs use **1-based indexing** to simplify calculations.

---

## 📐 BIT Structure - A Visual Idea

Let’s say we have this array:

```
Index:   1   2   3   4   5   6   7   8
Value:   3   2   -1  6   5   4   -3  3
```

In the BIT:
- `bit[1]` stores info about index 1
- `bit[2]` stores info about 1 to 2
- `bit[4]` stores info about 1 to 4
- `bit[8]` stores info about 1 to 8

So it's like:
```
bit[i] stores sum of some range ending at i
```

How does BIT decide which range?
👉 It depends on the **least significant bit** (LSB) of `i`.

---

## ⚙️ How Does It Work?

### ➕ Add Operation (Update)

To **add a value** to index `i` in BIT:

```python
def update(i, value):
    while i <= n:
        bit[i] += value
        i += (i & -i)
```

Explanation:
- `n` is the length of the original array
- `i & -i` gives the **LSB** — the jump size
- You move to the **next responsible node**

## 📊 Prefix Sum Query in Fenwick Tree (Binary Indexed Tree)

To get the **sum from index `1` to `i`** efficiently, use the following function:

```python
def query(i):
    res = 0
    while i > 0:
        res += bit[i]
        i -= (i & -i)
    return res
```

### 🔍 Purpose

The `query(i)` function computes the prefix sum:  
`A[1] + A[2] + ... + A[i]` in **O(log n)** time using the precomputed partial sums in the `bit[]` array.

---

### ⚙️ How It Works

Each `bit[k]` stores the sum of a specific range of the original array.  
That range size is determined by the **Least Significant Bit (LSB)** of `k`:
- `k & -k` gives the size of the range that `bit[k]` covers.

At each step:
1. Add the value of `bit[i]` to the result.
2. Move to the previous contributing index by removing the LSB: `i -= (i & -i)`.

---

### 💡 Example: `query(6)`

Assume we want to compute the prefix sum up to index `6`.

Steps:
| Step | i  | `bit[i]` (Range)    | Operation                    | Result (`res`) |
|------|----|----------------------|-------------------------------|----------------|
| 1    | 6  | `bit[6]` (A[5]+A[6]) | `res += bit[6]`               | res = `bit[6]` |
| 2    | 4  | `bit[4]` (A[1]–A[4]) | `res += bit[4]`               | res += `bit[4]` |
| 3    | 0  | –                    | Stop (loop ends)              | Final sum      |

This adds together the **non-overlapping** segments `A[1–4]` and `A[5–6]`, giving the sum `A[1] + ... + A[6]`.

---

### 📌 Summary

- `bit[i]` stores sums of power-of-two-sized blocks of the array.
- The `query(i)` function walks **backwards** through these blocks to gather the total sum.
- Each step removes the LSB of `i`, ensuring O(log n) time complexity.


---

## 🧠 What is `i & -i`?

This magic trick gives the **lowest set bit** in binary.

For example:
- `i = 6` → binary `110` → `i & -i = 10` → `2`
- `i = 8` → binary `1000` → `i & -i = 1000` → `8`

---

## 📦 Real-Life Analogy

Imagine a **warehouse** storing boxes (numbers). Instead of counting every box one by one, BIT stores **running totals** in strategic places.

When you need a total, you:
- Visit a few key boxes (nodes)
- Add their labels (totals)
- Done in log time!

---

## 🧪 Example: Build and Use BIT (Binary Indexed Tree)

Let’s build a Binary Indexed Tree for the following array:

```
arr = [3, 2, -1, 6, 5, 4, -3, 3]
```

This array has `n = 8` elements.

---

### 🔧 Step 1: Create the BIT Array

- Create an array `bit[]` of size `n + 1` (index 0 is unused).
- Initialize it with all zeros:

```
bit = [0, 0, 0, 0, 0, 0, 0, 0, 0]
```

> ⚠️ BIT is 1-indexed: `bit[i]` stores information about a range of values in `arr[]`.

---

### 🔁 Step 2: Build the BIT Using `update()`

For each element in the array, call the `update(index, value)` function.

We loop through the array `arr[0]` to `arr[7]`, and for each `i`, we call:

```
update(i + 1, arr[i])
```

Why `i + 1`? Because the BIT is 1-indexed.

The `update(idx, val)` function works like this (in pseudocode):

```python
def update(idx, val):
    while idx <= n:
        bit[idx] += val
        idx += idx & -idx  # Move to parent
```

This updates the BIT with the value `val` at position `idx` and propagates the change to all relevant ancestors in the tree.

---

### 🔍 Step 3: Query the Prefix Sum with `query(index)`

To get the prefix sum from `arr[0]` to `arr[index - 1]`, use:

```python
def query(idx):
    result = 0
    while idx > 0:
        result += bit[idx]
        idx -= idx & -idx  # Move to parent
    return result
```

#### ✅ Example:

To get the sum of `arr[1]` to `arr[5]` (i.e., `2 + (-1) + 6 + 5 + 4 = 16`), you call:

```
query(6)
```

This gives you the sum of the first 6 elements (because it's 1-indexed).

---

### ✏️ Step 4: Update an Element

Suppose you want to add `4` to `arr[3]` (which is `-1` originally). You’d call:

```
update(4, 4)
```

This will:
- Update `arr[3]` to `3`
- Update the BIT to reflect this change

Then `query(6)` would now return `20` instead of `16`.

---
## 🌲 Visualizing a Binary Indexed Tree (Fenwick Tree)

Given the array:

```
arr = [3, 2, -1, 6, 5, 4, -3, 3]
```

We build a **BIT** (1-indexed) to support efficient prefix sum queries.

---

### 🧠 BIT Index Responsibilities

Each `bit[i]` stores the sum of a specific range of elements from `arr[]`:

| Index | Binary | Covers Range     | bit[i] Value       |
|-------|--------|------------------|--------------------|
| 1     | 0001   | a[0]             | 3                  |
| 2     | 0010   | a[1]             | 2                  |
| 3     | 0011   | a[2]             | -1                 |
| 4     | 0100   | a[0] to a[3]     | 3 + 2 - 1 + 6 = 10 |
| 5     | 0101   | a[4]             | 5                  |
| 6     | 0110   | a[4] to a[5]     | 5 + 4 = 9          |
| 7     | 0111   | a[6]             | -3                 |
| 8     | 1000   | a[0] to a[7]     | sum(arr) = 19      |

> 📌 `bit[i]` stores the sum of elements ending at index `i` and going back `LSB(i)` elements, where `LSB(i)` is the least significant bit of `i`.

---

### 📊 BIT Array in ASCII

```
bit (1-indexed):

   Index:     1     2     3     4     5     6     7     8
   Content:  [3]  [2]  [-1]  [10]  [5]  [9]  [-3]  [19]
              ↑    ↑     ↑     ↑     ↑     ↑     ↑     ↑
            a[0] a[1]  a[2] a[0–3] a[4] a[4–5] a[6] a[0–7]
```

---

### 🔁 How It Works

- `update(i, val)` updates the BIT at index `i` and all relevant parent ranges.
- `query(i)` gives the **sum from `arr[0]` to `arr[i-1]`** by walking up the BIT using `i -= i & -i`.

---

### ⏱️ Time & Space Complexity

- `update()` and `query()` both run in **O(log n)**
- Space used: **O(n)**

This makes Fenwick Trees perfect for scenarios where you frequently need:
- Prefix sums
- Point updates
- Efficient performance

---
## ⏱️ Time Complexity

| Operation | Time     |
|-----------|----------|
| Update    | O(log n) |
| Query     | O(log n) |
| Build     | O(n log n) |

---

## ✅ Pros and Cons

### ✅ Pros:
- Fast updates & queries
- Easy to implement

### ❌ Cons:
- Only works for **associative** operations like sum, min, max (not general-purpose)
- Slightly tricky to understand at first

---
## ✅ BIT vs BST
| Feature                     | BIT                  | BST                     |
|----------------------------|----------------------|--------------------------|
| Prefix sum queries         | ✅ Fast (O(log n))    | ❌ Slower (O(log n), more overhead) |
| Point updates              | ✅ Fast (O(log n))    | ✅ Fast (O(log n))       |
| Insert/delete any value    | ❌ Not supported      | ✅ Fully supported       |
| Range queries (e.g., sums) | ✅ Easy               | ⚠️ Requires augmentation |
| Memory usage               | ✅ Compact            | ❌ Higher (pointers, nodes) |
| Order statistics           | ❌ Not supported      | ✅ With augmentation     |
---

## 🧩 Summary

| Concept              | Summary                                 |
|----------------------|------------------------------------------|
| BIT / Fenwick Tree   | Data structure for prefix sums           |
| Key Operations       | `update(i, x)` and `query(i)`            |
| Magic Formula        | `i & -i` → move through tree             |
| Speeds               | Update/query in O(log n)                 |

---

# 🧪 Questions to Test Understanding of Binary Indexed Trees

---

### 🧠 1. Concept Check
**Q: What’s the difference between using a normal array and a Binary Indexed Tree for prefix sums?**  
✅ *Expected Answer:* Normal arrays take **O(n)** time for prefix sums, while BIT takes **O(log n)**. BIT also allows faster updates.

---

### 🧩 2. Hands-On Thought
**Q: If `bit[4]` stores some range of prefix sums, can you guess which elements it covers in the original array?**  
✅ *Expected Answer:* `bit[4]` covers the range from **index 1 to 4**.

Try asking about other values too, like `bit[6]` or `bit[8]`.

---

### 🔍 3. Binary Logic
**Q: Why do we use `i & -i` in BIT, and what does it tell us about the index?**  
✅ *Expected Answer:* It gives us the **least significant bit** (LSB), which tells us the size of the range that `bit[i]` is responsible for.

---

### 💡 4. Real-World Analogy
**Q: If BIT is like a warehouse storing box counts in sections, what would happen if we add 2 boxes to one section—how does the rest of the system update?**  
✅ *Expected Answer:* That section and all larger sections including it will update their totals.

---

### 🛠️ 5. Code Connection
**Q: In the `update()` function, why do we keep adding `i & -i` to the index `i` in a loop?**  
✅ *Expected Answer:* So we move to the **next BIT node** that is responsible for including this index in its prefix range.

---
