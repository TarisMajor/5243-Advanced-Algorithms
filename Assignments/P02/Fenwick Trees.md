
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

## 🧠 What is `i & -i`?

This magic trick gives the **lowest set bit** in binary.

For example:
- `i = 6` → binary `110` → `i & -i = 10` → `2`
- `i = 8` → binary `1000` → `i & -i = 1000` → `8`

---

## 📦 Real-Life Analogy

Imagine a **warehouse** storing boxes (numbers). Instead of counting every box one by one, BIT stores **running totals** in strategic places.

![image](https://github.com/user-attachments/assets/8073448c-dfee-4f27-b106-567a222e0ac7)


When you need a total, you:
- Visit a few key boxes (nodes)
- Add their labels (totals)
- Done in log time!

---
[Visualgo Fenwick Tree Visualizer](https://visualgo.net/en/fenwicktree)
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

## 📘 Multiple Choice Questions: Fenwick Tree (Binary Indexed Tree)

---

### **1. What is the primary use of a Fenwick Tree?**

A. Sorting arrays in O(log n)  
B. Finding the minimum element in a range  
C. Efficiently computing prefix sums and updates  
D. Storing dynamic graphs  

✅ **Correct Answer:** C

---

### **2. In a Fenwick Tree, what does the expression `i & -i` compute?**

A. The middle index between 0 and i  
B. The number of trailing 1s in i  
C. The Least Significant Bit (LSB) of i  
D. The Most Significant Bit (MSB) of i  

✅ **Correct Answer:** C

---

### **3. What is the time complexity of `update(i, value)` and `query(i)` in a Fenwick Tree of size `n`?**

A. O(n)  
B. O(log n)  
C. O(1)  
D. O(n log n)  

✅ **Correct Answer:** B

---

### **4. Can a Fenwick Tree automatically resize itself when new elements are appended?**

A. Yes, it grows like a dynamic array  
B. No, it requires manual resizing  
C. Yes, if implemented using a segment tree  
D. No, and resizing is not possible  

✅ **Correct Answer:** B

---

### **5. What is the minimum number of nodes visited in a `query(i)` call in a Fenwick Tree?**

A. 1  
B. log₂(i)  
C. i  
D. Depends on the value of `i & -i`  

✅ **Correct Answer:** A  
(*When `i` is a power of two, the query visits only one node.*)

---

