# ☕ Java DSA Notes — Interview Ready Reference

> **Author's Note:** These notes are structured for interview preparation. Each section covers concepts, Java-specific implementation, complexity analysis, C++ vs Java differences, and practice questions.

---

## 📚 Table of Contents

1. [Java Fundamentals for DSA](#1-java-fundamentals-for-dsa)
2. [Arrays](#2-arrays)
3. [Strings](#3-strings)
4. [Linked Lists](#4-linked-lists)
   - [Singly Linked List](#41-singly-linked-list)
   - [Doubly Linked List](#42-doubly-linked-list)
   - [Circular Linked List](#43-circular-linked-list)
5. [Stacks](#5-stacks)
6. [Queues](#6-queues)
7. [Priority Queues (Heaps)](#7-priority-queues-heaps)
8. [Hash Tables & Maps](#8-hash-tables--maps)
9. [Trees](#9-trees)
   - [Binary Tree](#91-binary-tree)
   - [Binary Search Tree (BST)](#92-binary-search-tree-bst)
   - [AVL Tree](#93-avl-tree)
   - [Heaps](#94-heaps)
10. [Tries](#10-tries)
11. [Graphs](#11-graphs)
12. [Sorting Algorithms](#12-sorting-algorithms)
13. [Searching Algorithms](#13-searching-algorithms)
14. [Recursion & Backtracking](#14-recursion--backtracking)
15. [Dynamic Programming](#15-dynamic-programming)
16. [Greedy Algorithms](#16-greedy-algorithms)
17. [Graph Algorithms](#17-graph-algorithms)
    - [BFS & DFS](#171-bfs--dfs)
    - [Dijkstra's Algorithm](#172-dijkstras-algorithm)
    - [Kruskal's Algorithm](#173-kruskals-algorithm)
    - [Prim's Algorithm](#174-prims-algorithm)
18. [Interview Patterns](#18-interview-patterns)
    - [Sliding Window](#181-sliding-window)
    - [Two Pointers](#182-two-pointers)
    - [Fast & Slow Pointers](#183-fast--slow-pointers)
    - [Cycle Detection](#184-cycle-detection)
    - [Top K Elements](#185-top-k-elements)
    - [Matrix Traversal](#186-matrix-traversal)
19. [Complexity Cheat Sheet](#19-complexity-cheat-sheet)

---

## 1. Java Fundamentals for DSA

### Key Differences: Java vs C++

| Feature | C++ | Java |
|---|---|---|
| Arrays | `int arr[]` or `int* arr` | `int[] arr` |
| Dynamic Array | `vector<int>` | `ArrayList<Integer>` |
| HashMap | `unordered_map<K,V>` | `HashMap<K,V>` |
| Set | `unordered_set<T>` | `HashSet<T>` |
| Priority Queue (min) | `priority_queue<int, vector<int>, greater<int>>` | `PriorityQueue<Integer>()` |
| Priority Queue (max) | `priority_queue<int>` | `PriorityQueue<>(Collections.reverseOrder())` |
| Stack | `stack<T>` | `Deque<T>` (preferred) or `Stack<T>` |
| Queue | `queue<T>` | `Queue<T>` / `LinkedList<T>` |
| Pair | `pair<T1, T2>` | `int[]` or custom class or `Map.Entry` |
| Sorting | `sort(arr, arr+n)` | `Arrays.sort(arr)` |
| String | `string` (mutable) | `String` (immutable), use `StringBuilder` |
| Infinity | `INT_MAX` | `Integer.MAX_VALUE` |
| Null | `nullptr` | `null` |

### Essential Imports

```java
import java.util.*;          // ArrayList, HashMap, PriorityQueue, etc.
import java.util.stream.*;   // Stream API
import java.util.Arrays;     // Arrays.sort, Arrays.fill
import java.util.Collections;// Collections.sort, reverse, etc.
```

### Java Collections Hierarchy (Quick Reference)

```
Collection
├── List (ordered, duplicates allowed)
│   ├── ArrayList    → O(1) get, O(n) insert middle
│   └── LinkedList   → O(1) insert/delete ends, O(n) get
├── Set (no duplicates)
│   ├── HashSet      → O(1) avg add/remove/contains
│   ├── LinkedHashSet→ O(1) + insertion order
│   └── TreeSet      → O(log n), sorted
└── Queue / Deque
    ├── PriorityQueue→ O(log n) add/poll, O(1) peek
    └── ArrayDeque   → O(1) add/remove both ends (stack + queue)

Map (key-value pairs)
├── HashMap          → O(1) avg get/put
├── LinkedHashMap    → O(1) + insertion order
└── TreeMap          → O(log n), sorted by key
```

### Useful Utility Methods

```java
// Arrays
int[] arr = new int[n];
Arrays.fill(arr, 0);                    // fill with default value
Arrays.sort(arr);                       // sort ascending
Arrays.sort(arr, (a, b) -> b - a);     // sort descending (Integer[] only)
int[] copy = Arrays.copyOf(arr, n);
int[] range = Arrays.copyOfRange(arr, l, r); // [l, r)

// Collections
List<Integer> list = new ArrayList<>(Arrays.asList(3,1,2));
Collections.sort(list);
Collections.sort(list, (a, b) -> b - a);  // descending
Collections.reverse(list);
Collections.max(list);
Collections.min(list);
Collections.frequency(list, val);

// Math
Math.max(a, b);
Math.min(a, b);
Math.abs(a);
Math.pow(base, exp);   // returns double
Math.sqrt(n);          // returns double
Math.log(n);           // natural log
(int) Math.ceil(a/b);  // ceiling division
```

---

## 2. Arrays

### Concept
An array stores elements of the same type in **contiguous memory**. Java arrays are **fixed-size** and **zero-indexed**.

### Key Properties
- **Access:** O(1) by index
- **Search:** O(n) linear, O(log n) binary (if sorted)
- **Insert/Delete:** O(n) — requires shifting
- **Space:** O(n)

### Java vs C++
- Java arrays are objects; they have `.length` (not `.length()` or `.size()`)
- Java arrays are always heap-allocated; no stack arrays
- Use `ArrayList<Integer>` for dynamic resizing

### Code Examples

```java
// ─── 1. Basic Array Operations ───────────────────────────────────────────
int[] arr = {5, 3, 1, 4, 2};

// Traversal
for (int x : arr) System.out.print(x + " ");

// Find max/min
int max = arr[0];
for (int x : arr) max = Math.max(max, x);

// Reverse in-place
int l = 0, r = arr.length - 1;
while (l < r) {
    int temp = arr[l];
    arr[l++] = arr[r];
    arr[r--] = temp;
}

// ─── 2. Dynamic Array (ArrayList) ────────────────────────────────────────
List<Integer> list = new ArrayList<>();
list.add(10);            // O(1) amortized
list.add(0, 5);          // O(n) insert at index
list.remove(0);          // O(n) remove by index
list.get(1);             // O(1)
list.size();
list.contains(10);       // O(n)
Collections.sort(list);  // O(n log n)

// Convert array ↔ list
Integer[] boxed = {1, 2, 3};
List<Integer> fromArr = new ArrayList<>(Arrays.asList(boxed));
Integer[] backToArr = fromArr.toArray(new Integer[0]);

// ─── 3. 2D Arrays ────────────────────────────────────────────────────────
int[][] matrix = new int[3][4];          // 3 rows, 4 cols
int[][] grid = {{1,2},{3,4},{5,6}};
int rows = grid.length;
int cols = grid[0].length;

// Transpose
int n = 3;
int[][] mat = new int[n][n];
for (int i = 0; i < n; i++)
    for (int j = i+1; j < n; j++) {
        int t = mat[i][j];
        mat[i][j] = mat[j][i];
        mat[j][i] = t;
    }

// ─── 4. Prefix Sum ───────────────────────────────────────────────────────
// Problem: Given array, answer range sum queries in O(1)
int[] nums = {1, 3, 5, 2, 4};
int[] prefix = new int[nums.length + 1];
for (int i = 0; i < nums.length; i++)
    prefix[i+1] = prefix[i] + nums[i];

// Sum from index l to r (inclusive) = prefix[r+1] - prefix[l]
int sumLR = prefix[4] - prefix[1]; // sum of nums[1..3] = 3+5+2 = 10
```

**Example — Rotate Array by k:**
```java
// Input: [1,2,3,4,5], k=2 → Output: [4,5,1,2,3]
public void rotate(int[] nums, int k) {
    k %= nums.length;
    reverse(nums, 0, nums.length - 1); // [5,4,3,2,1]
    reverse(nums, 0, k - 1);           // [4,5,3,2,1]
    reverse(nums, k, nums.length - 1); // [4,5,1,2,3]
}
private void reverse(int[] a, int l, int r) {
    while (l < r) { int t = a[l]; a[l++] = a[r]; a[r--] = t; }
}
```

### Practice Questions
1. Two Sum (LC #1)
2. Best Time to Buy and Sell Stock (LC #121)
3. Product of Array Except Self (LC #238)
4. Maximum Subarray / Kadane's Algorithm (LC #53)
5. Rotate Array (LC #189)
6. Merge Intervals (LC #56)

---

## 3. Strings

### Concept
In Java, `String` is **immutable**. Every modification creates a new object. Use `StringBuilder` for mutable operations.

### Key Properties
- **Immutable** — `String s = "hello"; s += " world";` creates a new object each time
- **StringBuilder** — mutable, O(1) amortized append
- **String comparison** — use `.equals()`, not `==` (which compares references)
- Characters accessed via `.charAt(i)` — O(1)

### Java vs C++
- C++ `std::string` is mutable; Java `String` is not
- Java has no `char*` — use `char[]` or `String`
- `s.length()` in Java (method call), vs `s.size()` in C++
- Use `Character` class for utility: `Character.isDigit()`, `Character.toLowerCase()`

### Code Examples

```java
// ─── String Basics ────────────────────────────────────────────────────────
String s = "Hello, World!";
s.length();                  // 13
s.charAt(0);                 // 'H'
s.substring(7, 12);          // "World"
s.indexOf('o');              // 4
s.lastIndexOf('o');          // 8
s.toLowerCase();
s.toUpperCase();
s.trim();                    // removes leading/trailing whitespace
s.replace('l', 'r');         // "Herro, Worrd!"
s.split(", ");               // ["Hello", "World!"]
s.contains("World");         // true
s.startsWith("Hello");       // true
s.equals("Hello, World!");   // true (use this, NOT ==)
s.equalsIgnoreCase("hello, world!"); // true

// ─── StringBuilder ────────────────────────────────────────────────────────
StringBuilder sb = new StringBuilder();
sb.append("Hello");          // O(1) amortized
sb.append(' ');
sb.append("World");
sb.insert(5, ",");           // insert at index
sb.delete(5, 6);             // delete range [5,6)
sb.reverse();                // reverse in-place
sb.toString();               // convert to String

// ─── char[] operations ───────────────────────────────────────────────────
char[] chars = s.toCharArray();
String back = new String(chars);

// Frequency count (lowercase English letters)
int[] freq = new int[26];
for (char c : s.toCharArray())
    if (Character.isLetter(c))
        freq[c - 'a']++;

// ─── Common Patterns ─────────────────────────────────────────────────────

// Check palindrome
boolean isPalindrome(String s) {
    int l = 0, r = s.length() - 1;
    while (l < r) {
        if (s.charAt(l++) != s.charAt(r--)) return false;
    }
    return true;
}

// Check anagram
boolean isAnagram(String s, String t) {
    if (s.length() != t.length()) return false;
    int[] count = new int[26];
    for (char c : s.toCharArray()) count[c - 'a']++;
    for (char c : t.toCharArray()) count[c - 'a']--;
    for (int x : count) if (x != 0) return false;
    return true;
}

// Reverse words
String reverseWords(String s) {
    String[] words = s.trim().split("\\s+");
    StringBuilder sb = new StringBuilder();
    for (int i = words.length - 1; i >= 0; i--) {
        sb.append(words[i]);
        if (i > 0) sb.append(" ");
    }
    return sb.toString();
}
```

**Example — Longest Substring Without Repeating Characters:**
```java
// Input: "abcabcbb" → Output: 3 ("abc")
public int lengthOfLongestSubstring(String s) {
    Map<Character, Integer> map = new HashMap<>();
    int max = 0;
    for (int l = 0, r = 0; r < s.length(); r++) {
        char c = s.charAt(r);
        if (map.containsKey(c))
            l = Math.max(l, map.get(c) + 1); // shrink window
        map.put(c, r);
        max = Math.max(max, r - l + 1);
    }
    return max;
}
```

### Practice Questions
1. Valid Anagram (LC #242)
2. Longest Substring Without Repeating Characters (LC #3)
3. Longest Palindromic Substring (LC #5)
4. Group Anagrams (LC #49)
5. String to Integer / atoi (LC #8)
6. Valid Parentheses (LC #20)

---

## 4. Linked Lists

### 4.1 Singly Linked List

#### Concept
A sequence of nodes where each node holds data and a pointer to the **next** node. No random access.

#### Key Properties
- **Access:** O(n)
- **Insert/Delete at head:** O(1)
- **Insert/Delete at tail:** O(n) without tail pointer, O(1) with
- **Search:** O(n)
- **Space:** O(n)

#### Java vs C++
- C++: `Node* next`; Java: `Node next` (reference, not pointer)
- Java handles memory automatically (garbage collection) — no `delete` needed
- Java `LinkedList<T>` is a doubly linked list implementing `List`, `Deque`

```java
// ─── Node Definition ─────────────────────────────────────────────────────
class ListNode {
    int val;
    ListNode next;
    ListNode(int val) { this.val = val; this.next = null; }
}

// ─── Singly Linked List Implementation ───────────────────────────────────
class SinglyLinkedList {
    ListNode head;

    // Insert at head — O(1)
    void insertAtHead(int val) {
        ListNode node = new ListNode(val);
        node.next = head;
        head = node;
    }

    // Insert at tail — O(n)
    void insertAtTail(int val) {
        ListNode node = new ListNode(val);
        if (head == null) { head = node; return; }
        ListNode cur = head;
        while (cur.next != null) cur = cur.next;
        cur.next = node;
    }

    // Delete by value — O(n)
    void delete(int val) {
        if (head == null) return;
        if (head.val == val) { head = head.next; return; }
        ListNode cur = head;
        while (cur.next != null && cur.next.val != val)
            cur = cur.next;
        if (cur.next != null) cur.next = cur.next.next;
    }

    // Reverse — O(n)
    ListNode reverse(ListNode head) {
        ListNode prev = null, cur = head;
        while (cur != null) {
            ListNode next = cur.next;
            cur.next = prev;
            prev = cur;
            cur = next;
        }
        return prev; // new head
    }

    // Print
    void print() {
        ListNode cur = head;
        while (cur != null) { System.out.print(cur.val + " -> "); cur = cur.next; }
        System.out.println("null");
    }
}

// ─── Merge Two Sorted Lists ───────────────────────────────────────────────
// Input: 1->3->5, 2->4->6  →  Output: 1->2->3->4->5->6
ListNode mergeTwoLists(ListNode l1, ListNode l2) {
    ListNode dummy = new ListNode(0), cur = dummy;
    while (l1 != null && l2 != null) {
        if (l1.val <= l2.val) { cur.next = l1; l1 = l1.next; }
        else                  { cur.next = l2; l2 = l2.next; }
        cur = cur.next;
    }
    cur.next = (l1 != null) ? l1 : l2;
    return dummy.next;
}

// ─── Find Middle Node (Fast & Slow Pointer) ───────────────────────────────
ListNode findMiddle(ListNode head) {
    ListNode slow = head, fast = head;
    while (fast != null && fast.next != null) {
        slow = slow.next;
        fast = fast.next.next;
    }
    return slow; // middle (or second middle for even length)
}
```

### 4.2 Doubly Linked List

```java
// ─── Node Definition ─────────────────────────────────────────────────────
class DNode {
    int val;
    DNode prev, next;
    DNode(int val) { this.val = val; }
}

class DoublyLinkedList {
    DNode head, tail;

    void insertAtHead(int val) {
        DNode node = new DNode(val);
        if (head == null) { head = tail = node; return; }
        node.next = head;
        head.prev = node;
        head = node;
    }

    void insertAtTail(int val) {
        DNode node = new DNode(val);
        if (tail == null) { head = tail = node; return; }
        tail.next = node;
        node.prev = tail;
        tail = node;
    }

    void deleteNode(DNode node) {
        if (node.prev != null) node.prev.next = node.next;
        else head = node.next;               // was head
        if (node.next != null) node.next.prev = node.prev;
        else tail = node.prev;               // was tail
    }
}
```

### 4.3 Circular Linked List

```java
class CircularLinkedList {
    ListNode head;

    void insert(int val) {
        ListNode node = new ListNode(val);
        if (head == null) { head = node; node.next = head; return; }
        ListNode cur = head;
        while (cur.next != head) cur = cur.next;
        cur.next = node;
        node.next = head;
    }

    void print() {
        if (head == null) return;
        ListNode cur = head;
        do {
            System.out.print(cur.val + " -> ");
            cur = cur.next;
        } while (cur != head);
        System.out.println("(head)");
    }
}
```

### Practice Questions
1. Reverse Linked List (LC #206)
2. Merge Two Sorted Lists (LC #21)
3. Linked List Cycle (LC #141)
4. Remove Nth Node From End (LC #19)
5. Reorder List (LC #143)
6. LRU Cache (LC #146) — uses DoublyLinkedList + HashMap

---

## 5. Stacks

### Concept
A **LIFO** (Last-In-First-Out) data structure. Think of a stack of plates.

### Key Properties
- **Push/Pop/Peek:** O(1)
- **Search:** O(n)
- Java: prefer `Deque<T>` over `Stack<T>` (Stack is synchronized/legacy)

### Java vs C++
- C++: `stack<T>` from `<stack>`
- Java: `Deque<Integer> stack = new ArrayDeque<>()` (recommended)
- `push()` → `stack.push()` | `pop()` → `stack.pop()` | `peek()` → `stack.peek()`

```java
// ─── Stack using Deque (recommended) ─────────────────────────────────────
Deque<Integer> stack = new ArrayDeque<>();
stack.push(10);       // push to top
stack.push(20);
stack.peek();         // 20 — view top without removing
stack.pop();          // 20 — remove top
stack.isEmpty();
stack.size();

// ─── Valid Parentheses ────────────────────────────────────────────────────
// Input: "()[]{}"  → true  |  "([)]" → false
boolean isValid(String s) {
    Deque<Character> stack = new ArrayDeque<>();
    for (char c : s.toCharArray()) {
        if (c == '(' || c == '[' || c == '{') {
            stack.push(c);
        } else {
            if (stack.isEmpty()) return false;
            char top = stack.pop();
            if (c == ')' && top != '(') return false;
            if (c == ']' && top != '[') return false;
            if (c == '}' && top != '{') return false;
        }
    }
    return stack.isEmpty();
}

// ─── Next Greater Element ──────────────────────────────────────────────────
// Input: [2,1,2,4,3]  → Output: [4,2,4,-1,-1]
int[] nextGreaterElement(int[] nums) {
    int n = nums.length;
    int[] result = new int[n];
    Arrays.fill(result, -1);
    Deque<Integer> stack = new ArrayDeque<>(); // stores indices
    for (int i = 0; i < n; i++) {
        while (!stack.isEmpty() && nums[i] > nums[stack.peek()])
            result[stack.pop()] = nums[i];
        stack.push(i);
    }
    return result;
}

// ─── Min Stack — O(1) getMin ──────────────────────────────────────────────
class MinStack {
    Deque<Integer> stack = new ArrayDeque<>();
    Deque<Integer> minStack = new ArrayDeque<>();

    void push(int val) {
        stack.push(val);
        int min = minStack.isEmpty() ? val : Math.min(val, minStack.peek());
        minStack.push(min);
    }
    void pop() { stack.pop(); minStack.pop(); }
    int top() { return stack.peek(); }
    int getMin() { return minStack.peek(); }
}

// ─── Evaluate Reverse Polish Notation ─────────────────────────────────────
// Input: ["2","1","+","3","*"] → Output: 9
int evalRPN(String[] tokens) {
    Deque<Integer> stack = new ArrayDeque<>();
    for (String t : tokens) {
        if ("+-*/".contains(t)) {
            int b = stack.pop(), a = stack.pop();
            switch (t) {
                case "+": stack.push(a + b); break;
                case "-": stack.push(a - b); break;
                case "*": stack.push(a * b); break;
                case "/": stack.push(a / b); break;
            }
        } else stack.push(Integer.parseInt(t));
    }
    return stack.pop();
}
```

### Practice Questions
1. Valid Parentheses (LC #20)
2. Min Stack (LC #155)
3. Daily Temperatures (LC #739)
4. Largest Rectangle in Histogram (LC #84)
5. Decode String (LC #394)

---

## 6. Queues

### Concept
A **FIFO** (First-In-First-Out) data structure. Think of a line at a ticket counter.

### Key Properties
- **Enqueue (offer):** O(1)
- **Dequeue (poll):** O(1)
- **Peek:** O(1)
- Use `Queue` interface with `LinkedList` or `ArrayDeque` as implementation

```java
// ─── Queue using LinkedList ───────────────────────────────────────────────
Queue<Integer> queue = new LinkedList<>();
queue.offer(1);       // enqueue (preferred over add — returns false instead of throwing)
queue.offer(2);
queue.offer(3);
queue.peek();         // 1 — view front
queue.poll();         // 1 — remove and return front
queue.isEmpty();
queue.size();

// ─── Deque (Double-Ended Queue) ───────────────────────────────────────────
Deque<Integer> deque = new ArrayDeque<>();
deque.offerFirst(1);  // add to front
deque.offerLast(2);   // add to back
deque.peekFirst();    // view front
deque.peekLast();     // view back
deque.pollFirst();    // remove from front
deque.pollLast();     // remove from back

// ─── BFS using Queue (Level Order Tree Traversal) ─────────────────────────
// Input: root of binary tree → Output: level-by-level values
List<List<Integer>> levelOrder(TreeNode root) {
    List<List<Integer>> result = new ArrayList<>();
    if (root == null) return result;
    Queue<TreeNode> q = new LinkedList<>();
    q.offer(root);
    while (!q.isEmpty()) {
        int size = q.size();             // nodes at current level
        List<Integer> level = new ArrayList<>();
        for (int i = 0; i < size; i++) {
            TreeNode node = q.poll();
            level.add(node.val);
            if (node.left  != null) q.offer(node.left);
            if (node.right != null) q.offer(node.right);
        }
        result.add(level);
    }
    return result;
}

// ─── Sliding Window Maximum (Monotonic Deque) ────────────────────────────
// Input: [1,3,-1,-3,5,3,6,7], k=3 → Output: [3,3,5,5,6,7]
int[] maxSlidingWindow(int[] nums, int k) {
    int n = nums.length;
    int[] result = new int[n - k + 1];
    Deque<Integer> deque = new ArrayDeque<>(); // stores indices, decreasing values
    for (int i = 0; i < n; i++) {
        // Remove indices outside window
        while (!deque.isEmpty() && deque.peekFirst() < i - k + 1)
            deque.pollFirst();
        // Remove smaller elements (they'll never be max)
        while (!deque.isEmpty() && nums[deque.peekLast()] < nums[i])
            deque.pollLast();
        deque.offerLast(i);
        if (i >= k - 1) result[i - k + 1] = nums[deque.peekFirst()];
    }
    return result;
}
```

### Practice Questions
1. Implement Queue using Stacks (LC #232)
2. Number of Islands (LC #200) — BFS
3. Word Ladder (LC #127)
4. Sliding Window Maximum (LC #239)
5. Rotting Oranges (LC #994)

---

## 7. Priority Queues (Heaps)

### Concept
A **heap** is a complete binary tree where the parent is always greater (max-heap) or smaller (min-heap) than its children. Java's `PriorityQueue` is a **min-heap** by default.

### Key Properties
- **Insert (offer):** O(log n)
- **Remove min/max (poll):** O(log n)
- **Peek:** O(1)
- **Build heap from array:** O(n)

### Java vs C++
- C++ max-heap: `priority_queue<int>`
- C++ min-heap: `priority_queue<int, vector<int>, greater<int>>`
- Java min-heap: `new PriorityQueue<>()`
- Java max-heap: `new PriorityQueue<>(Collections.reverseOrder())`

```java
// ─── Min Heap ─────────────────────────────────────────────────────────────
PriorityQueue<Integer> minHeap = new PriorityQueue<>();
minHeap.offer(5);
minHeap.offer(2);
minHeap.offer(8);
minHeap.peek();          // 2 — minimum
minHeap.poll();          // 2 — remove minimum

// ─── Max Heap ─────────────────────────────────────────────────────────────
PriorityQueue<Integer> maxHeap = new PriorityQueue<>(Collections.reverseOrder());
// Or: new PriorityQueue<>((a, b) -> b - a);

// ─── Custom Comparator (e.g., sort int[] by first element) ────────────────
PriorityQueue<int[]> pq = new PriorityQueue<>((a, b) -> a[0] - b[0]);
pq.offer(new int[]{3, 1});
pq.offer(new int[]{1, 5});
pq.offer(new int[]{2, 3});
int[] top = pq.poll(); // [1, 5]

// ─── K Closest Points to Origin ──────────────────────────────────────────
// Input: points=[[1,3],[-2,2]], k=1 → Output: [[-2,2]]
int[][] kClosest(int[][] points, int k) {
    // Max-heap of size k — evict farthest
    PriorityQueue<int[]> maxHeap = new PriorityQueue<>(
        (a, b) -> (b[0]*b[0]+b[1]*b[1]) - (a[0]*a[0]+a[1]*a[1])
    );
    for (int[] p : points) {
        maxHeap.offer(p);
        if (maxHeap.size() > k) maxHeap.poll(); // remove farthest
    }
    return maxHeap.toArray(new int[0][]);
}

// ─── Merge K Sorted Lists ─────────────────────────────────────────────────
ListNode mergeKLists(ListNode[] lists) {
    PriorityQueue<ListNode> pq = new PriorityQueue<>((a, b) -> a.val - b.val);
    for (ListNode node : lists)
        if (node != null) pq.offer(node);
    ListNode dummy = new ListNode(0), cur = dummy;
    while (!pq.isEmpty()) {
        cur.next = pq.poll();
        cur = cur.next;
        if (cur.next != null) pq.offer(cur.next);
    }
    return dummy.next;
}

// ─── Find Kth Largest Element ─────────────────────────────────────────────
// Input: [3,2,1,5,6,4], k=2 → Output: 5
int findKthLargest(int[] nums, int k) {
    PriorityQueue<Integer> minHeap = new PriorityQueue<>();
    for (int num : nums) {
        minHeap.offer(num);
        if (minHeap.size() > k) minHeap.poll(); // evict smallest
    }
    return minHeap.peek(); // k-th largest
}
```

### Practice Questions
1. Kth Largest Element in an Array (LC #215)
2. K Closest Points to Origin (LC #973)
3. Merge K Sorted Lists (LC #23)
4. Task Scheduler (LC #621)
5. Find Median from Data Stream (LC #295)

---

## 8. Hash Tables & Maps

### Concept
A hash table maps **keys to values** using a hash function. Provides O(1) average-case operations.

### Key Properties
- **Get/Put/Remove:** O(1) average, O(n) worst (hash collisions)
- **Contains key/value:** O(1) average
- Java `HashMap` does **not** maintain insertion order
- Use `LinkedHashMap` for insertion order, `TreeMap` for sorted keys

### Java vs C++
- C++ `unordered_map` ≈ Java `HashMap`
- C++ `map` (sorted) ≈ Java `TreeMap`
- Java: iterate with `map.entrySet()`, `map.keySet()`, `map.values()`

```java
// ─── HashMap Basics ───────────────────────────────────────────────────────
Map<String, Integer> map = new HashMap<>();
map.put("apple", 3);
map.put("banana", 1);
map.get("apple");             // 3
map.getOrDefault("grape", 0); // 0 — safe default
map.containsKey("apple");     // true
map.containsValue(3);         // true
map.remove("banana");
map.size();

// Iterate
for (Map.Entry<String, Integer> entry : map.entrySet())
    System.out.println(entry.getKey() + " -> " + entry.getValue());

for (String key : map.keySet()) System.out.println(key);
for (int val : map.values())   System.out.println(val);

// Useful methods
map.putIfAbsent("cherry", 5);
map.computeIfAbsent("date", k -> 0);
map.merge("apple", 1, Integer::sum); // apple = 3 + 1 = 4
map.getOrDefault("grape", 0);

// ─── Frequency Count Pattern ──────────────────────────────────────────────
int[] nums = {1, 2, 2, 3, 3, 3};
Map<Integer, Integer> freq = new HashMap<>();
for (int n : nums)
    freq.merge(n, 1, Integer::sum); // or: freq.put(n, freq.getOrDefault(n, 0) + 1)

// ─── HashSet ──────────────────────────────────────────────────────────────
Set<Integer> set = new HashSet<>();
set.add(1);
set.add(2);
set.add(2);     // duplicate — ignored
set.contains(2); // true
set.remove(1);
set.size();      // 1

// ─── Two Sum using HashMap ────────────────────────────────────────────────
// Input: [2,7,11,15], target=9 → Output: [0,1]
int[] twoSum(int[] nums, int target) {
    Map<Integer, Integer> map = new HashMap<>(); // value → index
    for (int i = 0; i < nums.length; i++) {
        int complement = target - nums[i];
        if (map.containsKey(complement))
            return new int[]{map.get(complement), i};
        map.put(nums[i], i);
    }
    return new int[]{};
}

// ─── Group Anagrams ───────────────────────────────────────────────────────
// Input: ["eat","tea","tan","ate","nat","bat"] → Output: [["bat"],["nat","tan"],["ate","eat","tea"]]
List<List<String>> groupAnagrams(String[] strs) {
    Map<String, List<String>> map = new HashMap<>();
    for (String s : strs) {
        char[] c = s.toCharArray();
        Arrays.sort(c);                        // canonical form
        String key = new String(c);
        map.computeIfAbsent(key, k -> new ArrayList<>()).add(s);
    }
    return new ArrayList<>(map.values());
}

// ─── TreeMap (sorted keys) ────────────────────────────────────────────────
TreeMap<Integer, String> treeMap = new TreeMap<>();
treeMap.put(3, "three");
treeMap.put(1, "one");
treeMap.put(2, "two");
treeMap.firstKey();          // 1
treeMap.lastKey();           // 3
treeMap.floorKey(2);         // 2 — largest key ≤ 2
treeMap.ceilingKey(2);       // 2 — smallest key ≥ 2
treeMap.headMap(3);          // {1="one", 2="two"}
treeMap.subMap(1, 3);        // {1="one", 2="two"} [1,3)
```

### Practice Questions
1. Two Sum (LC #1)
2. Group Anagrams (LC #49)
3. Top K Frequent Elements (LC #347)
4. Longest Consecutive Sequence (LC #128)
5. Subarray Sum Equals K (LC #560)
6. LRU Cache (LC #146)

---

## 9. Trees

### 9.1 Binary Tree

#### Concept
A tree where each node has **at most two children** (left and right).

#### Key Properties
- **Height:** O(log n) balanced, O(n) skewed
- **Space:** O(n)

```java
// ─── TreeNode Definition ──────────────────────────────────────────────────
class TreeNode {
    int val;
    TreeNode left, right;
    TreeNode(int val) { this.val = val; }
}

// ─── Tree Traversals ──────────────────────────────────────────────────────

// Inorder: Left → Root → Right  [gives sorted order for BST]
void inorder(TreeNode root) {
    if (root == null) return;
    inorder(root.left);
    System.out.print(root.val + " ");
    inorder(root.right);
}

// Preorder: Root → Left → Right  [used for serialization]
void preorder(TreeNode root) {
    if (root == null) return;
    System.out.print(root.val + " ");
    preorder(root.left);
    preorder(root.right);
}

// Postorder: Left → Right → Root  [used for deletion]
void postorder(TreeNode root) {
    if (root == null) return;
    postorder(root.left);
    postorder(root.right);
    System.out.print(root.val + " ");
}

// Iterative Inorder (no recursion)
List<Integer> inorderIterative(TreeNode root) {
    List<Integer> result = new ArrayList<>();
    Deque<TreeNode> stack = new ArrayDeque<>();
    TreeNode cur = root;
    while (cur != null || !stack.isEmpty()) {
        while (cur != null) { stack.push(cur); cur = cur.left; }
        cur = stack.pop();
        result.add(cur.val);
        cur = cur.right;
    }
    return result;
}

// ─── Height of Tree ───────────────────────────────────────────────────────
int height(TreeNode root) {
    if (root == null) return 0;
    return 1 + Math.max(height(root.left), height(root.right));
}

// ─── Diameter of Binary Tree ──────────────────────────────────────────────
// Longest path between any two nodes (may not pass through root)
int maxDiameter = 0;
int diameter(TreeNode root) {
    diameterHelper(root);
    return maxDiameter;
}
int diameterHelper(TreeNode node) {
    if (node == null) return 0;
    int left = diameterHelper(node.left);
    int right = diameterHelper(node.right);
    maxDiameter = Math.max(maxDiameter, left + right);
    return 1 + Math.max(left, right);
}

// ─── Invert Binary Tree ───────────────────────────────────────────────────
TreeNode invertTree(TreeNode root) {
    if (root == null) return null;
    TreeNode temp = root.left;
    root.left = invertTree(root.right);
    root.right = invertTree(temp);
    return root;
}

// ─── Lowest Common Ancestor ───────────────────────────────────────────────
TreeNode lowestCommonAncestor(TreeNode root, TreeNode p, TreeNode q) {
    if (root == null || root == p || root == q) return root;
    TreeNode left = lowestCommonAncestor(root.left, p, q);
    TreeNode right = lowestCommonAncestor(root.right, p, q);
    if (left != null && right != null) return root; // p and q on different sides
    return left != null ? left : right;
}
```

### 9.2 Binary Search Tree (BST)

#### Concept
A binary tree where for every node: **left subtree < node < right subtree**.

#### Key Properties
- **Search/Insert/Delete:** O(log n) average, O(n) worst (unbalanced)
- **Inorder traversal** gives sorted sequence

```java
class BST {
    TreeNode root;

    // Insert — O(log n) average
    TreeNode insert(TreeNode root, int val) {
        if (root == null) return new TreeNode(val);
        if (val < root.val)      root.left = insert(root.left, val);
        else if (val > root.val) root.right = insert(root.right, val);
        return root;
    }

    // Search — O(log n) average
    boolean search(TreeNode root, int val) {
        if (root == null) return false;
        if (val == root.val) return true;
        return val < root.val ? search(root.left, val) : search(root.right, val);
    }

    // Delete — O(log n) average
    TreeNode delete(TreeNode root, int val) {
        if (root == null) return null;
        if (val < root.val)      root.left = delete(root.left, val);
        else if (val > root.val) root.right = delete(root.right, val);
        else {
            if (root.left == null) return root.right;   // no left child
            if (root.right == null) return root.left;   // no right child
            // Two children: replace with inorder successor (min of right subtree)
            TreeNode minNode = findMin(root.right);
            root.val = minNode.val;
            root.right = delete(root.right, minNode.val);
        }
        return root;
    }

    TreeNode findMin(TreeNode root) {
        while (root.left != null) root = root.left;
        return root;
    }

    // Validate BST
    boolean isValidBST(TreeNode root) {
        return validate(root, Long.MIN_VALUE, Long.MAX_VALUE);
    }
    boolean validate(TreeNode node, long min, long max) {
        if (node == null) return true;
        if (node.val <= min || node.val >= max) return false;
        return validate(node.left, min, node.val) && validate(node.right, node.val, max);
    }

    // Kth Smallest in BST (inorder)
    int kthSmallest(TreeNode root, int k) {
        Deque<TreeNode> stack = new ArrayDeque<>();
        TreeNode cur = root;
        while (cur != null || !stack.isEmpty()) {
            while (cur != null) { stack.push(cur); cur = cur.left; }
            cur = stack.pop();
            if (--k == 0) return cur.val;
            cur = cur.right;
        }
        return -1;
    }
}
```

### 9.3 AVL Tree

#### Concept
A **self-balancing** BST where for every node, the height difference between left and right subtrees (balance factor) is at most **1**.

#### Key Properties
- **All operations:** O(log n) guaranteed
- Rotations restore balance after insert/delete
- More complex to implement than BST; in interviews, know the concept + rotation types

```java
class AVLNode {
    int val, height;
    AVLNode left, right;
    AVLNode(int val) { this.val = val; this.height = 1; }
}

class AVLTree {
    int height(AVLNode n) { return n == null ? 0 : n.height; }

    int balanceFactor(AVLNode n) {
        return n == null ? 0 : height(n.left) - height(n.right);
    }

    // Right Rotation (for Left-Left case)
    AVLNode rightRotate(AVLNode y) {
        AVLNode x = y.left, T2 = x.right;
        x.right = y;
        y.left = T2;
        y.height = 1 + Math.max(height(y.left), height(y.right));
        x.height = 1 + Math.max(height(x.left), height(x.right));
        return x; // new root
    }

    // Left Rotation (for Right-Right case)
    AVLNode leftRotate(AVLNode x) {
        AVLNode y = x.right, T2 = y.left;
        y.left = x;
        x.right = T2;
        x.height = 1 + Math.max(height(x.left), height(x.right));
        y.height = 1 + Math.max(height(y.left), height(y.right));
        return y;
    }

    AVLNode insert(AVLNode node, int val) {
        // Standard BST insert
        if (node == null) return new AVLNode(val);
        if (val < node.val)      node.left = insert(node.left, val);
        else if (val > node.val) node.right = insert(node.right, val);
        else return node; // duplicates not allowed

        // Update height
        node.height = 1 + Math.max(height(node.left), height(node.right));
        int bf = balanceFactor(node);

        // 4 imbalance cases:
        if (bf > 1 && val < node.left.val)   return rightRotate(node);       // LL
        if (bf < -1 && val > node.right.val) return leftRotate(node);        // RR
        if (bf > 1 && val > node.left.val) {                                  // LR
            node.left = leftRotate(node.left); return rightRotate(node);
        }
        if (bf < -1 && val < node.right.val) {                               // RL
            node.right = rightRotate(node.right); return leftRotate(node);
        }
        return node;
    }
}
```

### 9.4 Heaps

#### Concept
A **complete binary tree** stored as an array. Parent at index `i` has children at `2i+1` and `2i+2`.

```java
// ─── Manual Min Heap Implementation ──────────────────────────────────────
class MinHeap {
    int[] heap;
    int size, capacity;

    MinHeap(int capacity) {
        this.capacity = capacity;
        heap = new int[capacity];
    }

    int parent(int i) { return (i - 1) / 2; }
    int left(int i)   { return 2 * i + 1; }
    int right(int i)  { return 2 * i + 2; }

    void insert(int val) {
        if (size == capacity) throw new RuntimeException("Heap full");
        heap[size] = val;
        int i = size++;
        // Heapify up
        while (i > 0 && heap[i] < heap[parent(i)]) {
            swap(i, parent(i));
            i = parent(i);
        }
    }

    int extractMin() {
        if (size == 0) throw new RuntimeException("Heap empty");
        int min = heap[0];
        heap[0] = heap[--size];
        heapifyDown(0);
        return min;
    }

    void heapifyDown(int i) {
        int smallest = i, l = left(i), r = right(i);
        if (l < size && heap[l] < heap[smallest]) smallest = l;
        if (r < size && heap[r] < heap[smallest]) smallest = r;
        if (smallest != i) { swap(i, smallest); heapifyDown(smallest); }
    }

    void swap(int i, int j) { int t = heap[i]; heap[i] = heap[j]; heap[j] = t; }

    int peek() { return heap[0]; }
}
```

### Practice Questions
1. Maximum Depth of Binary Tree (LC #104)
2. Invert Binary Tree (LC #226)
3. Diameter of Binary Tree (LC #543)
4. Validate Binary Search Tree (LC #98)
5. Kth Smallest Element in a BST (LC #230)
6. Serialize and Deserialize Binary Tree (LC #297)

---

## 10. Tries

### Concept
A **prefix tree** used for efficient string retrieval. Each node represents a character; paths from root to leaf form words.

### Key Properties
- **Insert/Search:** O(m) where m = word length
- **Space:** O(ALPHABET_SIZE × m × n) worst case
- Great for: autocomplete, spell check, prefix queries

```java
// ─── Trie Implementation ──────────────────────────────────────────────────
class TrieNode {
    TrieNode[] children = new TrieNode[26];
    boolean isEnd = false;
}

class Trie {
    TrieNode root = new TrieNode();

    // Insert — O(m)
    void insert(String word) {
        TrieNode cur = root;
        for (char c : word.toCharArray()) {
            int idx = c - 'a';
            if (cur.children[idx] == null)
                cur.children[idx] = new TrieNode();
            cur = cur.children[idx];
        }
        cur.isEnd = true;
    }

    // Search exact word — O(m)
    boolean search(String word) {
        TrieNode cur = root;
        for (char c : word.toCharArray()) {
            int idx = c - 'a';
            if (cur.children[idx] == null) return false;
            cur = cur.children[idx];
        }
        return cur.isEnd;
    }

    // Prefix exists — O(m)
    boolean startsWith(String prefix) {
        TrieNode cur = root;
        for (char c : prefix.toCharArray()) {
            int idx = c - 'a';
            if (cur.children[idx] == null) return false;
            cur = cur.children[idx];
        }
        return true;
    }
}

// ─── Word Search II (Trie + Backtracking) ────────────────────────────────
// Find all words from a dictionary in a board — uses Trie for pruning
// (Full solution reference: LC #212)

// ─── Using HashMap children (generic alphabet) ───────────────────────────
class FlexTrieNode {
    Map<Character, FlexTrieNode> children = new HashMap<>();
    boolean isEnd = false;
}
```

**Example:**
```
Insert: ["apple", "app", "apply"]
search("app")     → true
search("ap")      → false
startsWith("appl") → true
```

### Practice Questions
1. Implement Trie (LC #208)
2. Search Suggestions System (LC #1268)
3. Word Search II (LC #212)
4. Design Add and Search Words Data Structure (LC #211)

---

## 11. Graphs

### Concept
A set of **vertices (nodes)** connected by **edges**. Can be directed/undirected, weighted/unweighted, cyclic/acyclic.

### Representation

```java
// ─── Adjacency List (most common in interviews) ───────────────────────────
int n = 6; // number of vertices
List<List<Integer>> graph = new ArrayList<>();
for (int i = 0; i < n; i++) graph.add(new ArrayList<>());

// Add undirected edge between u and v
graph.get(0).add(1);
graph.get(1).add(0);

// Weighted graph
List<List<int[]>> wGraph = new ArrayList<>(); // [neighbor, weight]
for (int i = 0; i < n; i++) wGraph.add(new ArrayList<>());
wGraph.get(0).add(new int[]{1, 5}); // edge 0->1 weight 5

// ─── Adjacency Matrix ─────────────────────────────────────────────────────
int[][] matrix = new int[n][n];
matrix[0][1] = 1; // edge 0→1 (directed)
matrix[1][0] = 1; // also add for undirected

// ─── Graph from Edge List ─────────────────────────────────────────────────
int[][] edges = {{0,1},{0,2},{1,3},{2,4}};
List<List<Integer>> g = new ArrayList<>();
for (int i = 0; i < n; i++) g.add(new ArrayList<>());
for (int[] e : edges) {
    g.get(e[0]).add(e[1]);
    g.get(e[1]).add(e[0]); // omit for directed
}
```

---

## 12. Sorting Algorithms

### Complexity Summary

| Algorithm | Best | Average | Worst | Space | Stable |
|---|---|---|---|---|---|
| Bubble Sort | O(n) | O(n²) | O(n²) | O(1) | Yes |
| Selection Sort | O(n²) | O(n²) | O(n²) | O(1) | No |
| Insertion Sort | O(n) | O(n²) | O(n²) | O(1) | Yes |
| Merge Sort | O(n log n) | O(n log n) | O(n log n) | O(n) | Yes |
| Quick Sort | O(n log n) | O(n log n) | O(n²) | O(log n) | No |
| Heap Sort | O(n log n) | O(n log n) | O(n log n) | O(1) | No |

### Implementations

```java
// ─── Bubble Sort ──────────────────────────────────────────────────────────
void bubbleSort(int[] arr) {
    int n = arr.length;
    for (int i = 0; i < n - 1; i++) {
        boolean swapped = false;
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j+1]) {
                int t = arr[j]; arr[j] = arr[j+1]; arr[j+1] = t;
                swapped = true;
            }
        }
        if (!swapped) break; // already sorted — O(n) best case
    }
}

// ─── Selection Sort ───────────────────────────────────────────────────────
void selectionSort(int[] arr) {
    int n = arr.length;
    for (int i = 0; i < n - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < n; j++)
            if (arr[j] < arr[minIdx]) minIdx = j;
        int t = arr[i]; arr[i] = arr[minIdx]; arr[minIdx] = t;
    }
}

// ─── Insertion Sort ───────────────────────────────────────────────────────
void insertionSort(int[] arr) {
    int n = arr.length;
    for (int i = 1; i < n; i++) {
        int key = arr[i], j = i - 1;
        while (j >= 0 && arr[j] > key) { arr[j+1] = arr[j]; j--; }
        arr[j+1] = key;
    }
}

// ─── Merge Sort — O(n log n), O(n) space ─────────────────────────────────
void mergeSort(int[] arr, int l, int r) {
    if (l >= r) return;
    int mid = l + (r - l) / 2;
    mergeSort(arr, l, mid);
    mergeSort(arr, mid + 1, r);
    merge(arr, l, mid, r);
}

void merge(int[] arr, int l, int mid, int r) {
    int n1 = mid - l + 1, n2 = r - mid;
    int[] left = Arrays.copyOfRange(arr, l, mid + 1);
    int[] right = Arrays.copyOfRange(arr, mid + 1, r + 1);
    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2)
        arr[k++] = (left[i] <= right[j]) ? left[i++] : right[j++];
    while (i < n1) arr[k++] = left[i++];
    while (j < n2) arr[k++] = right[j++];
}

// ─── Quick Sort — O(n log n) avg, O(n²) worst ─────────────────────────────
void quickSort(int[] arr, int l, int r) {
    if (l >= r) return;
    int pivot = partition(arr, l, r);
    quickSort(arr, l, pivot - 1);
    quickSort(arr, pivot + 1, r);
}

int partition(int[] arr, int l, int r) {
    int pivot = arr[r]; // choose last element as pivot
    int i = l - 1;
    for (int j = l; j < r; j++) {
        if (arr[j] <= pivot) {
            i++;
            int t = arr[i]; arr[i] = arr[j]; arr[j] = t;
        }
    }
    int t = arr[i+1]; arr[i+1] = arr[r]; arr[r] = t;
    return i + 1;
}

// ─── Heap Sort — O(n log n), in-place ────────────────────────────────────
void heapSort(int[] arr) {
    int n = arr.length;
    // Build max-heap
    for (int i = n/2 - 1; i >= 0; i--) heapify(arr, n, i);
    // Extract elements from heap
    for (int i = n - 1; i > 0; i--) {
        int t = arr[0]; arr[0] = arr[i]; arr[i] = t; // move max to end
        heapify(arr, i, 0);
    }
}

void heapify(int[] arr, int n, int i) {
    int largest = i, l = 2*i+1, r = 2*i+2;
    if (l < n && arr[l] > arr[largest]) largest = l;
    if (r < n && arr[r] > arr[largest]) largest = r;
    if (largest != i) {
        int t = arr[i]; arr[i] = arr[largest]; arr[largest] = t;
        heapify(arr, n, largest);
    }
}

// ─── Java Built-in Sort (use in interviews!) ─────────────────────────────
Arrays.sort(arr);                              // primitives — quicksort variant
Arrays.sort(strArr);                           // objects — TimSort (stable)
Arrays.sort(arr, (a, b) -> b[0] - a[0]);      // custom: Integer[] or int[][]
Collections.sort(list);                        // List — TimSort
```

**Example — Sort Colors (Dutch National Flag):**
```java
// Input: [2,0,2,1,1,0]  →  Output: [0,0,1,1,2,2]
void sortColors(int[] nums) {
    int low = 0, mid = 0, high = nums.length - 1;
    while (mid <= high) {
        if (nums[mid] == 0)      { swap(nums, low++, mid++); }
        else if (nums[mid] == 1) { mid++; }
        else                     { swap(nums, mid, high--); }
    }
}
```

### Practice Questions
1. Sort an Array (LC #912)
2. Sort Colors (LC #75)
3. Merge Intervals (LC #56)
4. Largest Number (LC #179)
5. Count Inversions (merge sort variant)

---

## 13. Searching Algorithms

```java
// ─── Linear Search — O(n) ─────────────────────────────────────────────────
int linearSearch(int[] arr, int target) {
    for (int i = 0; i < arr.length; i++)
        if (arr[i] == target) return i;
    return -1; // not found
}

// ─── Binary Search — O(log n), requires sorted array ─────────────────────
int binarySearch(int[] arr, int target) {
    int l = 0, r = arr.length - 1;
    while (l <= r) {
        int mid = l + (r - l) / 2; // prevents integer overflow vs (l+r)/2
        if (arr[mid] == target)      return mid;
        else if (arr[mid] < target)  l = mid + 1;
        else                         r = mid - 1;
    }
    return -1; // not found
}

// ─── Search in Rotated Sorted Array ──────────────────────────────────────
// Input: [4,5,6,7,0,1,2], target=0 → Output: 4
int searchRotated(int[] nums, int target) {
    int l = 0, r = nums.length - 1;
    while (l <= r) {
        int mid = l + (r - l) / 2;
        if (nums[mid] == target) return mid;
        // Left half is sorted
        if (nums[l] <= nums[mid]) {
            if (target >= nums[l] && target < nums[mid]) r = mid - 1;
            else l = mid + 1;
        } else { // Right half is sorted
            if (target > nums[mid] && target <= nums[r]) l = mid + 1;
            else r = mid - 1;
        }
    }
    return -1;
}

// ─── Find First and Last Position ────────────────────────────────────────
// Input: [5,7,7,8,8,10], target=8 → Output: [3,4]
int[] searchRange(int[] nums, int target) {
    return new int[]{findFirst(nums, target), findLast(nums, target)};
}

int findFirst(int[] nums, int t) {
    int l = 0, r = nums.length - 1, idx = -1;
    while (l <= r) {
        int mid = l + (r - l) / 2;
        if (nums[mid] == t) { idx = mid; r = mid - 1; } // keep searching left
        else if (nums[mid] < t) l = mid + 1;
        else r = mid - 1;
    }
    return idx;
}

int findLast(int[] nums, int t) {
    int l = 0, r = nums.length - 1, idx = -1;
    while (l <= r) {
        int mid = l + (r - l) / 2;
        if (nums[mid] == t) { idx = mid; l = mid + 1; } // keep searching right
        else if (nums[mid] < t) l = mid + 1;
        else r = mid - 1;
    }
    return idx;
}

// ─── Binary Search on Answer (Search Space) ───────────────────────────────
// Pattern: when the answer has a monotonic property (feasibility condition)
// Example: Minimum capacity to ship packages within D days
int shipWithinDays(int[] weights, int days) {
    int l = Arrays.stream(weights).max().getAsInt(); // min possible: max weight
    int r = Arrays.stream(weights).sum();            // max possible: all at once
    while (l < r) {
        int mid = l + (r - l) / 2;
        if (canShip(weights, days, mid)) r = mid;    // try smaller capacity
        else l = mid + 1;
    }
    return l;
}

boolean canShip(int[] weights, int days, int cap) {
    int daysNeeded = 1, current = 0;
    for (int w : weights) {
        if (current + w > cap) { daysNeeded++; current = 0; }
        current += w;
    }
    return daysNeeded <= days;
}
```

### Practice Questions
1. Binary Search (LC #704)
2. Search in Rotated Sorted Array (LC #33)
3. Find First and Last Position (LC #34)
4. Koko Eating Bananas (LC #875)
5. Median of Two Sorted Arrays (LC #4)

---

## 14. Recursion & Backtracking

### Recursion
A function that calls itself with a **smaller subproblem**, converging toward a **base case**.

```java
// ─── Fibonacci — O(2^n) naive, O(n) with memoization ─────────────────────
int fib(int n) {
    if (n <= 1) return n;
    return fib(n - 1) + fib(n - 2);
}

// Memoized
int fib(int n, int[] memo) {
    if (n <= 1) return n;
    if (memo[n] != 0) return memo[n];
    return memo[n] = fib(n-1, memo) + fib(n-2, memo);
}

// ─── Power Function (Fast Exponentiation) — O(log n) ─────────────────────
double myPow(double x, int n) {
    if (n == 0) return 1;
    if (n < 0) { x = 1/x; n = -n; }
    if (n % 2 == 0) return myPow(x * x, n / 2);
    return x * myPow(x * x, n / 2);
}
```

### Backtracking
Explore all possibilities, **undo** choices that don't lead to a solution.

**Template:**
```java
void backtrack(state, choices) {
    if (isGoal(state)) { result.add(state); return; }
    for (choice : choices) {
        if (isValid(choice)) {
            makeChoice(choice);
            backtrack(newState, newChoices);
            undoChoice(choice);     // ← the "back" in backtracking
        }
    }
}
```

```java
// ─── Subsets ──────────────────────────────────────────────────────────────
// Input: [1,2,3] → Output: [[],[1],[2],[1,2],[3],[1,3],[2,3],[1,2,3]]
List<List<Integer>> subsets(int[] nums) {
    List<List<Integer>> result = new ArrayList<>();
    backtrackSubsets(nums, 0, new ArrayList<>(), result);
    return result;
}
void backtrackSubsets(int[] nums, int start, List<Integer> path, List<List<Integer>> result) {
    result.add(new ArrayList<>(path)); // every state is a valid subset
    for (int i = start; i < nums.length; i++) {
        path.add(nums[i]);
        backtrackSubsets(nums, i + 1, path, result);
        path.remove(path.size() - 1); // undo
    }
}

// ─── Permutations ─────────────────────────────────────────────────────────
// Input: [1,2,3] → Output: all 6 permutations
List<List<Integer>> permute(int[] nums) {
    List<List<Integer>> result = new ArrayList<>();
    backtrackPermute(nums, new boolean[nums.length], new ArrayList<>(), result);
    return result;
}
void backtrackPermute(int[] nums, boolean[] used, List<Integer> path, List<List<Integer>> result) {
    if (path.size() == nums.length) { result.add(new ArrayList<>(path)); return; }
    for (int i = 0; i < nums.length; i++) {
        if (used[i]) continue;
        used[i] = true;
        path.add(nums[i]);
        backtrackPermute(nums, used, path, result);
        path.remove(path.size() - 1);
        used[i] = false;
    }
}

// ─── Combination Sum ──────────────────────────────────────────────────────
// Input: candidates=[2,3,6,7], target=7 → Output: [[2,2,3],[7]]
List<List<Integer>> combinationSum(int[] candidates, int target) {
    List<List<Integer>> result = new ArrayList<>();
    Arrays.sort(candidates);
    backtrackComb(candidates, target, 0, new ArrayList<>(), result);
    return result;
}
void backtrackComb(int[] c, int remain, int start, List<Integer> path, List<List<Integer>> result) {
    if (remain == 0) { result.add(new ArrayList<>(path)); return; }
    for (int i = start; i < c.length; i++) {
        if (c[i] > remain) break; // pruning
        path.add(c[i]);
        backtrackComb(c, remain - c[i], i, path, result); // i (not i+1) to reuse
        path.remove(path.size() - 1);
    }
}

// ─── N-Queens ─────────────────────────────────────────────────────────────
// Place n queens on n×n board so no two queens attack each other
List<List<String>> solveNQueens(int n) {
    List<List<String>> result = new ArrayList<>();
    char[][] board = new char[n][n];
    for (char[] row : board) Arrays.fill(row, '.');
    nQueensHelper(board, 0, result);
    return result;
}
void nQueensHelper(char[][] board, int row, List<List<String>> result) {
    if (row == board.length) {
        List<String> solution = new ArrayList<>();
        for (char[] r : board) solution.add(new String(r));
        result.add(solution);
        return;
    }
    for (int col = 0; col < board.length; col++) {
        if (isQueenSafe(board, row, col)) {
            board[row][col] = 'Q';
            nQueensHelper(board, row + 1, result);
            board[row][col] = '.'; // undo
        }
    }
}
boolean isQueenSafe(char[][] board, int row, int col) {
    // Check column, upper-left diagonal, upper-right diagonal
    for (int i = 0; i < row; i++) {
        if (board[i][col] == 'Q') return false;
        int d = row - i;
        if (col - d >= 0 && board[i][col - d] == 'Q') return false;
        if (col + d < board.length && board[i][col + d] == 'Q') return false;
    }
    return true;
}
```

### Practice Questions
1. Subsets (LC #78) / Subsets II (LC #90)
2. Permutations (LC #46)
3. Combination Sum (LC #39)
4. Word Search (LC #79)
5. N-Queens (LC #51)
6. Sudoku Solver (LC #37)

---

## 15. Dynamic Programming

### Concept
Break a problem into **overlapping subproblems**, solve each once, and store results (**memoization** or **tabulation**).

### Approaches
- **Top-Down (Memoization):** recursion + cache
- **Bottom-Up (Tabulation):** iterative, fill dp table

### Common Patterns

```java
// ─── 1. 1D DP — Climbing Stairs / Fibonacci ───────────────────────────────
// Input: n=5 → Output: 8 (ways to climb)
int climbStairs(int n) {
    if (n <= 2) return n;
    int prev2 = 1, prev1 = 2;
    for (int i = 3; i <= n; i++) {
        int cur = prev1 + prev2;
        prev2 = prev1;
        prev1 = cur;
    }
    return prev1;
}

// ─── 2. Knapsack (0/1) ────────────────────────────────────────────────────
// Maximize value with weight limit W
// Time: O(n*W), Space: O(n*W) → can optimize to O(W)
int knapsack(int[] weights, int[] values, int W) {
    int n = weights.length;
    int[][] dp = new int[n+1][W+1];
    for (int i = 1; i <= n; i++) {
        for (int w = 0; w <= W; w++) {
            dp[i][w] = dp[i-1][w]; // skip item i
            if (weights[i-1] <= w)
                dp[i][w] = Math.max(dp[i][w], dp[i-1][w-weights[i-1]] + values[i-1]);
        }
    }
    return dp[n][W];
}

// ─── 3. Longest Common Subsequence (LCS) ─────────────────────────────────
// Input: "abcde", "ace" → Output: 3
int lcs(String s1, String s2) {
    int m = s1.length(), n = s2.length();
    int[][] dp = new int[m+1][n+1];
    for (int i = 1; i <= m; i++)
        for (int j = 1; j <= n; j++)
            dp[i][j] = (s1.charAt(i-1) == s2.charAt(j-1))
                ? dp[i-1][j-1] + 1
                : Math.max(dp[i-1][j], dp[i][j-1]);
    return dp[m][n];
}

// ─── 4. Longest Increasing Subsequence (LIS) ─────────────────────────────
// Input: [10,9,2,5,3,7,101,18] → Output: 4 ([2,3,7,101])
// O(n²) DP:
int lis(int[] nums) {
    int n = nums.length;
    int[] dp = new int[n];
    Arrays.fill(dp, 1);
    int max = 1;
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < i; j++)
            if (nums[j] < nums[i])
                dp[i] = Math.max(dp[i], dp[j] + 1);
        max = Math.max(max, dp[i]);
    }
    return max;
}

// ─── 5. Coin Change — Minimum Coins ──────────────────────────────────────
// Input: coins=[1,5,11], amount=15 → Output: 3 (5+5+5)
int coinChange(int[] coins, int amount) {
    int[] dp = new int[amount + 1];
    Arrays.fill(dp, amount + 1);   // sentinel: "infinity"
    dp[0] = 0;
    for (int i = 1; i <= amount; i++)
        for (int c : coins)
            if (c <= i)
                dp[i] = Math.min(dp[i], dp[i - c] + 1);
    return dp[amount] > amount ? -1 : dp[amount];
}

// ─── 6. Edit Distance ─────────────────────────────────────────────────────
// Minimum insertions, deletions, replacements to convert s1 to s2
// Input: "horse", "ros" → Output: 3
int editDistance(String s1, String s2) {
    int m = s1.length(), n = s2.length();
    int[][] dp = new int[m+1][n+1];
    for (int i = 0; i <= m; i++) dp[i][0] = i;
    for (int j = 0; j <= n; j++) dp[0][j] = j;
    for (int i = 1; i <= m; i++)
        for (int j = 1; j <= n; j++)
            dp[i][j] = (s1.charAt(i-1) == s2.charAt(j-1))
                ? dp[i-1][j-1]
                : 1 + Math.min(dp[i-1][j-1], Math.min(dp[i-1][j], dp[i][j-1]));
    return dp[m][n];
}

// ─── 7. House Robber ──────────────────────────────────────────────────────
// Cannot rob adjacent houses; maximize total
// Input: [2,7,9,3,1] → Output: 12 (2+9+1)
int rob(int[] nums) {
    int prev2 = 0, prev1 = 0;
    for (int n : nums) {
        int cur = Math.max(prev1, prev2 + n);
        prev2 = prev1;
        prev1 = cur;
    }
    return prev1;
}

// ─── 8. Maximum Subarray — Kadane's Algorithm ────────────────────────────
// Input: [-2,1,-3,4,-1,2,1,-5,4] → Output: 6 ([4,-1,2,1])
int maxSubArray(int[] nums) {
    int maxSum = nums[0], curSum = nums[0];
    for (int i = 1; i < nums.length; i++) {
        curSum = Math.max(nums[i], curSum + nums[i]);
        maxSum = Math.max(maxSum, curSum);
    }
    return maxSum;
}

// ─── 9. Unique Paths (Grid DP) ────────────────────────────────────────────
// Count paths from top-left to bottom-right (only right or down)
int uniquePaths(int m, int n) {
    int[][] dp = new int[m][n];
    for (int[] row : dp) Arrays.fill(row, 1); // edge cases: 1 path along edges
    for (int i = 1; i < m; i++)
        for (int j = 1; j < n; j++)
            dp[i][j] = dp[i-1][j] + dp[i][j-1];
    return dp[m-1][n-1];
}

// ─── 10. Palindrome Substrings / Longest Palindromic Substring ────────────
String longestPalindrome(String s) {
    int start = 0, maxLen = 1;
    for (int i = 0; i < s.length(); i++) {
        // Odd length palindromes
        int len1 = expandAroundCenter(s, i, i);
        // Even length palindromes
        int len2 = expandAroundCenter(s, i, i + 1);
        int len = Math.max(len1, len2);
        if (len > maxLen) {
            maxLen = len;
            start = i - (len - 1) / 2;
        }
    }
    return s.substring(start, start + maxLen);
}
int expandAroundCenter(String s, int l, int r) {
    while (l >= 0 && r < s.length() && s.charAt(l) == s.charAt(r)) { l--; r++; }
    return r - l - 1;
}
```

### Practice Questions
1. Climbing Stairs (LC #70)
2. Coin Change (LC #322)
3. Longest Common Subsequence (LC #1143)
4. Longest Increasing Subsequence (LC #300)
5. Edit Distance (LC #72)
6. House Robber I & II (LC #198, #213)
7. Maximum Product Subarray (LC #152)
8. Target Sum (LC #494)
9. Word Break (LC #139)
10. Burst Balloons (LC #312)

---

## 16. Greedy Algorithms

### Concept
Make the **locally optimal** choice at each step, hoping it leads to a globally optimal solution. Works when the problem has the **greedy choice property** and **optimal substructure**.

```java
// ─── Activity Selection (Interval Scheduling) ─────────────────────────────
// Maximize number of non-overlapping activities
// Sort by end time, greedily pick earliest-ending
int activitySelection(int[][] intervals) {
    Arrays.sort(intervals, (a, b) -> a[1] - b[1]); // sort by end time
    int count = 1, lastEnd = intervals[0][1];
    for (int i = 1; i < intervals.length; i++) {
        if (intervals[i][0] >= lastEnd) { // no overlap
            count++;
            lastEnd = intervals[i][1];
        }
    }
    return count;
}

// ─── Jump Game ────────────────────────────────────────────────────────────
// Input: [2,3,1,1,4] → true (can reach last index)
boolean canJump(int[] nums) {
    int maxReach = 0;
    for (int i = 0; i < nums.length; i++) {
        if (i > maxReach) return false; // can't reach index i
        maxReach = Math.max(maxReach, i + nums[i]);
    }
    return true;
}

// ─── Gas Station ─────────────────────────────────────────────────────────
// Find starting station for circular route
int canCompleteCircuit(int[] gas, int[] cost) {
    int totalGas = 0, curGas = 0, start = 0;
    for (int i = 0; i < gas.length; i++) {
        totalGas += gas[i] - cost[i];
        curGas   += gas[i] - cost[i];
        if (curGas < 0) { start = i + 1; curGas = 0; } // reset
    }
    return totalGas >= 0 ? start : -1;
}

// ─── Fractional Knapsack ──────────────────────────────────────────────────
double fractionalKnapsack(int[] weights, int[] values, int W) {
    int n = weights.length;
    double[][] items = new double[n][2]; // [value/weight, weight]
    for (int i = 0; i < n; i++) items[i] = new double[]{(double)values[i]/weights[i], weights[i]};
    Arrays.sort(items, (a, b) -> Double.compare(b[0], a[0])); // sort by ratio desc
    double totalValue = 0;
    for (double[] item : items) {
        if (W >= item[1]) { totalValue += item[0] * item[1]; W -= item[1]; }
        else              { totalValue += item[0] * W; break; }
    }
    return totalValue;
}

// ─── Meeting Rooms II (Min Rooms Needed) ──────────────────────────────────
// Input: [[0,30],[5,10],[15,20]] → Output: 2
int minMeetingRooms(int[][] intervals) {
    Arrays.sort(intervals, (a, b) -> a[0] - b[0]);
    PriorityQueue<Integer> minHeap = new PriorityQueue<>(); // stores end times
    for (int[] interval : intervals) {
        if (!minHeap.isEmpty() && minHeap.peek() <= interval[0])
            minHeap.poll(); // reuse room
        minHeap.offer(interval[1]);
    }
    return minHeap.size();
}
```

### Practice Questions
1. Jump Game I & II (LC #55, #45)
2. Gas Station (LC #134)
3. Non-overlapping Intervals (LC #435)
4. Assign Cookies (LC #455)
5. Minimum Number of Arrows to Burst Balloons (LC #452)

---

## 17. Graph Algorithms

### 17.1 BFS & DFS

```java
// ─── BFS (Breadth-First Search) ───────────────────────────────────────────
// Explores level by level; shortest path in unweighted graphs
void bfs(List<List<Integer>> graph, int start, int n) {
    boolean[] visited = new boolean[n];
    Queue<Integer> queue = new LinkedList<>();
    visited[start] = true;
    queue.offer(start);
    while (!queue.isEmpty()) {
        int node = queue.poll();
        System.out.print(node + " ");
        for (int neighbor : graph.get(node)) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                queue.offer(neighbor);
            }
        }
    }
}

// ─── DFS (Depth-First Search) — Recursive ────────────────────────────────
void dfs(List<List<Integer>> graph, int node, boolean[] visited) {
    visited[node] = true;
    System.out.print(node + " ");
    for (int neighbor : graph.get(node))
        if (!visited[neighbor])
            dfs(graph, neighbor, visited);
}

// ─── DFS — Iterative ─────────────────────────────────────────────────────
void dfsIterative(List<List<Integer>> graph, int start, int n) {
    boolean[] visited = new boolean[n];
    Deque<Integer> stack = new ArrayDeque<>();
    stack.push(start);
    while (!stack.isEmpty()) {
        int node = stack.pop();
        if (visited[node]) continue;
        visited[node] = true;
        System.out.print(node + " ");
        for (int neighbor : graph.get(node))
            if (!visited[neighbor]) stack.push(neighbor);
    }
}

// ─── Number of Islands (DFS on Grid) ─────────────────────────────────────
// Input: 2D grid of '1'(land) and '0'(water) → count islands
int numIslands(char[][] grid) {
    int count = 0;
    for (int i = 0; i < grid.length; i++)
        for (int j = 0; j < grid[0].length; j++)
            if (grid[i][j] == '1') { dfsIsland(grid, i, j); count++; }
    return count;
}
void dfsIsland(char[][] grid, int i, int j) {
    if (i < 0 || i >= grid.length || j < 0 || j >= grid[0].length || grid[i][j] != '1') return;
    grid[i][j] = '0'; // mark visited
    dfsIsland(grid, i+1, j); dfsIsland(grid, i-1, j);
    dfsIsland(grid, i, j+1); dfsIsland(grid, i, j-1);
}

// ─── Detect Cycle (Directed Graph — DFS + recStack) ──────────────────────
boolean hasCycleDirected(List<List<Integer>> graph, int n) {
    boolean[] visited = new boolean[n];
    boolean[] recStack = new boolean[n]; // nodes in current DFS path
    for (int i = 0; i < n; i++)
        if (!visited[i] && dfsCycle(graph, i, visited, recStack)) return true;
    return false;
}
boolean dfsCycle(List<List<Integer>> g, int node, boolean[] visited, boolean[] recStack) {
    visited[node] = recStack[node] = true;
    for (int neighbor : g.get(node)) {
        if (!visited[neighbor] && dfsCycle(g, neighbor, visited, recStack)) return true;
        if (recStack[neighbor]) return true;
    }
    recStack[node] = false;
    return false;
}

// ─── Topological Sort (Kahn's BFS Algorithm) ─────────────────────────────
List<Integer> topoSort(List<List<Integer>> graph, int n) {
    int[] inDegree = new int[n];
    for (int u = 0; u < n; u++)
        for (int v : graph.get(u)) inDegree[v]++;
    Queue<Integer> queue = new LinkedList<>();
    for (int i = 0; i < n; i++) if (inDegree[i] == 0) queue.offer(i);
    List<Integer> order = new ArrayList<>();
    while (!queue.isEmpty()) {
        int node = queue.poll();
        order.add(node);
        for (int neighbor : graph.get(node))
            if (--inDegree[neighbor] == 0) queue.offer(neighbor);
    }
    return order.size() == n ? order : new ArrayList<>(); // empty if cycle
}
```

### 17.2 Dijkstra's Algorithm

**Shortest path in a weighted graph (non-negative weights). Time: O((V+E) log V)**

```java
// Input: weighted adjacency list, source → returns dist[] from source
int[] dijkstra(List<List<int[]>> graph, int src, int n) {
    int[] dist = new int[n];
    Arrays.fill(dist, Integer.MAX_VALUE);
    dist[src] = 0;

    // PriorityQueue: [distance, node]
    PriorityQueue<int[]> pq = new PriorityQueue<>((a, b) -> a[0] - b[0]);
    pq.offer(new int[]{0, src});

    while (!pq.isEmpty()) {
        int[] cur = pq.poll();
        int d = cur[0], u = cur[1];
        if (d > dist[u]) continue; // stale entry

        for (int[] edge : graph.get(u)) {
            int v = edge[0], weight = edge[1];
            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                pq.offer(new int[]{dist[v], v});
            }
        }
    }
    return dist;
}
```

### 17.3 Kruskal's Algorithm

**Minimum Spanning Tree using Union-Find. Time: O(E log E)**

```java
// Sort edges by weight, add edge if it doesn't form a cycle (Union-Find)
int kruskal(int n, int[][] edges) {
    Arrays.sort(edges, (a, b) -> a[2] - b[2]); // sort by weight
    int[] parent = new int[n], rank = new int[n];
    for (int i = 0; i < n; i++) parent[i] = i;

    int totalWeight = 0, edgesUsed = 0;
    for (int[] edge : edges) {
        int u = edge[0], v = edge[1], w = edge[2];
        if (find(parent, u) != find(parent, v)) { // different components
            union(parent, rank, u, v);
            totalWeight += w;
            if (++edgesUsed == n - 1) break; // MST complete
        }
    }
    return totalWeight;
}

int find(int[] parent, int x) {
    if (parent[x] != x) parent[x] = find(parent, parent[x]); // path compression
    return parent[x];
}

void union(int[] parent, int[] rank, int x, int y) {
    int px = find(parent, x), py = find(parent, y);
    if (rank[px] < rank[py]) parent[px] = py;
    else if (rank[px] > rank[py]) parent[py] = px;
    else { parent[py] = px; rank[px]++; }
}
```

### 17.4 Prim's Algorithm

**Minimum Spanning Tree using a Greedy approach + Min-Heap. Time: O(E log V)**

```java
// Input: adjacency list [neighbor, weight], n nodes
int prim(List<List<int[]>> graph, int n) {
    boolean[] visited = new boolean[n];
    PriorityQueue<int[]> pq = new PriorityQueue<>((a, b) -> a[0] - b[0]); // [weight, node]
    pq.offer(new int[]{0, 0}); // start from node 0 with weight 0
    int totalWeight = 0;

    while (!pq.isEmpty()) {
        int[] cur = pq.poll();
        int w = cur[0], u = cur[1];
        if (visited[u]) continue;
        visited[u] = true;
        totalWeight += w;

        for (int[] edge : graph.get(u)) {
            if (!visited[edge[0]])
                pq.offer(new int[]{edge[1], edge[0]});
        }
    }
    return totalWeight;
}
```

### Practice Questions
1. Number of Islands (LC #200)
2. Clone Graph (LC #133)
3. Course Schedule I & II (LC #207, #210)
4. Network Delay Time (LC #743) — Dijkstra
5. Minimum Spanning Tree (LC #1584)
6. Word Ladder (LC #127)
7. Pacific Atlantic Water Flow (LC #417)

---

## 18. Interview Patterns

### 18.1 Sliding Window

**Use when:** contiguous subarray/substring with a constraint.

```java
// ─── Fixed-size window: max sum of k elements ─────────────────────────────
int maxSumFixed(int[] nums, int k) {
    int sum = 0;
    for (int i = 0; i < k; i++) sum += nums[i];     // initial window
    int maxSum = sum;
    for (int i = k; i < nums.length; i++) {
        sum += nums[i] - nums[i - k];                // slide: add right, remove left
        maxSum = Math.max(maxSum, sum);
    }
    return maxSum;
}

// ─── Variable-size window: smallest subarray with sum ≥ target ───────────
int minSubarrayLen(int target, int[] nums) {
    int sum = 0, l = 0, minLen = Integer.MAX_VALUE;
    for (int r = 0; r < nums.length; r++) {
        sum += nums[r];
        while (sum >= target) {                       // shrink from left
            minLen = Math.min(minLen, r - l + 1);
            sum -= nums[l++];
        }
    }
    return minLen == Integer.MAX_VALUE ? 0 : minLen;
}

// ─── Longest Substring with At Most K Distinct Characters ────────────────
int longestSubstringKDistinct(String s, int k) {
    Map<Character, Integer> map = new HashMap<>();
    int l = 0, maxLen = 0;
    for (int r = 0; r < s.length(); r++) {
        char c = s.charAt(r);
        map.merge(c, 1, Integer::sum);
        while (map.size() > k) {                      // shrink
            char lc = s.charAt(l++);
            map.merge(lc, -1, Integer::sum);
            if (map.get(lc) == 0) map.remove(lc);
        }
        maxLen = Math.max(maxLen, r - l + 1);
    }
    return maxLen;
}
```

### 18.2 Two Pointers

**Use when:** working with sorted arrays, or pairs/triplets.

```java
// ─── Two Sum (sorted array) ───────────────────────────────────────────────
int[] twoSumSorted(int[] nums, int target) {
    int l = 0, r = nums.length - 1;
    while (l < r) {
        int sum = nums[l] + nums[r];
        if (sum == target) return new int[]{l+1, r+1}; // 1-indexed
        else if (sum < target) l++;
        else r--;
    }
    return new int[]{-1, -1};
}

// ─── Three Sum ────────────────────────────────────────────────────────────
// Input: [-1,0,1,2,-1,-4] → Output: [[-1,-1,2],[-1,0,1]]
List<List<Integer>> threeSum(int[] nums) {
    Arrays.sort(nums);
    List<List<Integer>> result = new ArrayList<>();
    for (int i = 0; i < nums.length - 2; i++) {
        if (i > 0 && nums[i] == nums[i-1]) continue; // skip duplicates
        int l = i + 1, r = nums.length - 1;
        while (l < r) {
            int sum = nums[i] + nums[l] + nums[r];
            if (sum == 0) {
                result.add(Arrays.asList(nums[i], nums[l], nums[r]));
                while (l < r && nums[l] == nums[l+1]) l++; // skip duplicates
                while (l < r && nums[r] == nums[r-1]) r--;
                l++; r--;
            } else if (sum < 0) l++;
            else r--;
        }
    }
    return result;
}

// ─── Container with Most Water ────────────────────────────────────────────
// Input: [1,8,6,2,5,4,8,3,7] → Output: 49
int maxArea(int[] height) {
    int l = 0, r = height.length - 1, maxWater = 0;
    while (l < r) {
        maxWater = Math.max(maxWater, Math.min(height[l], height[r]) * (r - l));
        if (height[l] < height[r]) l++;
        else r--;
    }
    return maxWater;
}
```

### 18.3 Fast & Slow Pointers

**Use when:** detecting cycles, finding middle of linked list.

```java
// ─── Find Middle of Linked List ───────────────────────────────────────────
ListNode findMiddle(ListNode head) {
    ListNode slow = head, fast = head;
    while (fast != null && fast.next != null) {
        slow = slow.next;       // moves 1 step
        fast = fast.next.next;  // moves 2 steps
    }
    return slow; // slow is at middle
}

// ─── Happy Number ─────────────────────────────────────────────────────────
// Input: n=19 → true (1² + 9² = 82 → ... → 1)
boolean isHappy(int n) {
    int slow = n, fast = getNext(n);
    while (fast != 1 && slow != fast) {
        slow = getNext(slow);
        fast = getNext(getNext(fast));
    }
    return fast == 1;
}
int getNext(int n) {
    int sum = 0;
    while (n > 0) { int d = n % 10; sum += d * d; n /= 10; }
    return sum;
}
```

### 18.4 Cycle Detection

**Floyd's Tortoise and Hare:**

```java
// ─── Linked List Cycle Detection ─────────────────────────────────────────
boolean hasCycle(ListNode head) {
    ListNode slow = head, fast = head;
    while (fast != null && fast.next != null) {
        slow = slow.next;
        fast = fast.next.next;
        if (slow == fast) return true; // cycle detected
    }
    return false;
}

// ─── Find Cycle Start ─────────────────────────────────────────────────────
ListNode detectCycle(ListNode head) {
    ListNode slow = head, fast = head;
    while (fast != null && fast.next != null) {
        slow = slow.next;
        fast = fast.next.next;
        if (slow == fast) {
            // Move slow to head, keep fast at meeting point; same speed
            slow = head;
            while (slow != fast) { slow = slow.next; fast = fast.next; }
            return slow; // cycle start
        }
    }
    return null; // no cycle
}

// ─── Find Duplicate Number (Floyd's on array) ─────────────────────────────
// Input: [1,3,4,2,2] → Output: 2
int findDuplicate(int[] nums) {
    int slow = nums[0], fast = nums[0];
    do { slow = nums[slow]; fast = nums[nums[fast]]; } while (slow != fast);
    slow = nums[0];
    while (slow != fast) { slow = nums[slow]; fast = nums[fast]; }
    return slow;
}
```

### 18.5 Top K Elements

```java
// ─── Top K Frequent Elements ──────────────────────────────────────────────
// Input: [1,1,1,2,2,3], k=2 → Output: [1,2]
int[] topKFrequent(int[] nums, int k) {
    Map<Integer, Integer> freq = new HashMap<>();
    for (int n : nums) freq.merge(n, 1, Integer::sum);

    // Min-heap of size k
    PriorityQueue<Integer> pq = new PriorityQueue<>((a, b) -> freq.get(a) - freq.get(b));
    for (int key : freq.keySet()) {
        pq.offer(key);
        if (pq.size() > k) pq.poll(); // remove least frequent
    }

    int[] result = new int[k];
    for (int i = k - 1; i >= 0; i--) result[i] = pq.poll();
    return result;
}

// ─── Bucket Sort approach — O(n) ─────────────────────────────────────────
int[] topKFrequentBucket(int[] nums, int k) {
    Map<Integer, Integer> freq = new HashMap<>();
    for (int n : nums) freq.merge(n, 1, Integer::sum);

    List<Integer>[] buckets = new List[nums.length + 1];
    for (int key : freq.keySet()) {
        int f = freq.get(key);
        if (buckets[f] == null) buckets[f] = new ArrayList<>();
        buckets[f].add(key);
    }

    List<Integer> result = new ArrayList<>();
    for (int i = buckets.length - 1; i >= 0 && result.size() < k; i--)
        if (buckets[i] != null) result.addAll(buckets[i]);

    return result.stream().mapToInt(Integer::intValue).toArray();
}
```

### 18.6 Matrix Traversal

```java
// ─── Directions array (4-directional) ────────────────────────────────────
int[][] dirs = {{0,1},{0,-1},{1,0},{-1,0}};           // right, left, down, up
int[][] dirs8 = {{0,1},{0,-1},{1,0},{-1,0},{1,1},{1,-1},{-1,1},{-1,-1}}; // 8 directions

// ─── BFS on Matrix ────────────────────────────────────────────────────────
int bfsMatrix(int[][] grid, int startR, int startC) {
    int rows = grid.length, cols = grid[0].length;
    boolean[][] visited = new boolean[rows][cols];
    Queue<int[]> queue = new LinkedList<>();
    queue.offer(new int[]{startR, startC, 0}); // {row, col, distance}
    visited[startR][startC] = true;

    while (!queue.isEmpty()) {
        int[] cur = queue.poll();
        int r = cur[0], c = cur[1], dist = cur[2];
        // Process cur...
        for (int[] d : dirs) {
            int nr = r + d[0], nc = c + d[1];
            if (nr >= 0 && nr < rows && nc >= 0 && nc < cols && !visited[nr][nc]) {
                visited[nr][nc] = true;
                queue.offer(new int[]{nr, nc, dist + 1});
            }
        }
    }
    return -1;
}

// ─── Spiral Matrix ────────────────────────────────────────────────────────
// Input: [[1,2,3],[4,5,6],[7,8,9]] → Output: [1,2,3,6,9,8,7,4,5]
List<Integer> spiralOrder(int[][] matrix) {
    List<Integer> result = new ArrayList<>();
    int top = 0, bottom = matrix.length - 1, left = 0, right = matrix[0].length - 1;
    while (top <= bottom && left <= right) {
        for (int i = left; i <= right; i++)  result.add(matrix[top][i]);    top++;
        for (int i = top; i <= bottom; i++)  result.add(matrix[i][right]);  right--;
        if (top <= bottom)
            for (int i = right; i >= left; i--)  result.add(matrix[bottom][i]);  bottom--;
        if (left <= right)
            for (int i = bottom; i >= top; i--)  result.add(matrix[i][left]);    left++;
    }
    return result;
}

// ─── Rotate Matrix 90° Clockwise (in-place) ───────────────────────────────
// Transpose then reverse each row
void rotate(int[][] matrix) {
    int n = matrix.length;
    // Transpose
    for (int i = 0; i < n; i++)
        for (int j = i+1; j < n; j++) {
            int t = matrix[i][j]; matrix[i][j] = matrix[j][i]; matrix[j][i] = t;
        }
    // Reverse each row
    for (int[] row : matrix) {
        int l = 0, r = n - 1;
        while (l < r) { int t = row[l]; row[l++] = row[r]; row[r--] = t; }
    }
}
```

### Practice Questions (Patterns)
1. Minimum Window Substring (LC #76) — Sliding Window
2. Find All Anagrams in a String (LC #438) — Sliding Window
3. 3Sum (LC #15) — Two Pointers
4. Linked List Cycle II (LC #142) — Fast & Slow Pointers
5. Top K Frequent Words (LC #692) — Top K
6. Search a 2D Matrix (LC #74) — Matrix
7. Spiral Matrix (LC #54) — Matrix Traversal
8. Find the Duplicate Number (LC #287) — Floyd's Cycle

---

## 19. Complexity Cheat Sheet

### Data Structures

| Structure | Access | Search | Insert | Delete | Space |
|---|---|---|---|---|---|
| Array | O(1) | O(n) | O(n) | O(n) | O(n) |
| ArrayList | O(1) | O(n) | O(1)* | O(n) | O(n) |
| LinkedList | O(n) | O(n) | O(1) | O(1)† | O(n) |
| Stack (Deque) | O(n) | O(n) | O(1) | O(1) | O(n) |
| Queue | O(n) | O(n) | O(1) | O(1) | O(n) |
| HashMap | O(1)* | O(1)* | O(1)* | O(1)* | O(n) |
| TreeMap | O(log n) | O(log n) | O(log n) | O(log n) | O(n) |
| HashSet | — | O(1)* | O(1)* | O(1)* | O(n) |
| PriorityQueue | O(1) peek | O(n) | O(log n) | O(log n) | O(n) |
| BST (avg) | O(log n) | O(log n) | O(log n) | O(log n) | O(n) |
| BST (worst) | O(n) | O(n) | O(n) | O(n) | O(n) |
| AVL Tree | O(log n) | O(log n) | O(log n) | O(log n) | O(n) |
| Trie | — | O(m) | O(m) | O(m) | O(n·m·α) |

`*` = amortized/average  `†` = given a reference to the node  `m` = key/word length

### Algorithms

| Algorithm | Best | Average | Worst | Space |
|---|---|---|---|---|
| Linear Search | O(1) | O(n) | O(n) | O(1) |
| Binary Search | O(1) | O(log n) | O(log n) | O(1) |
| Bubble Sort | O(n) | O(n²) | O(n²) | O(1) |
| Insertion Sort | O(n) | O(n²) | O(n²) | O(1) |
| Selection Sort | O(n²) | O(n²) | O(n²) | O(1) |
| Merge Sort | O(n log n) | O(n log n) | O(n log n) | O(n) |
| Quick Sort | O(n log n) | O(n log n) | O(n²) | O(log n) |
| Heap Sort | O(n log n) | O(n log n) | O(n log n) | O(1) |
| BFS | — | O(V+E) | O(V+E) | O(V) |
| DFS | — | O(V+E) | O(V+E) | O(V) |
| Dijkstra | — | O((V+E) log V) | O((V+E) log V) | O(V) |
| Kruskal | — | O(E log E) | O(E log E) | O(V) |
| Prim | — | O(E log V) | O(E log V) | O(V) |

### Quick Interview Reminders

```
✅ Use int[] over Integer[] for primitives (no boxing overhead)
✅ Use StringBuilder for string concatenation in loops
✅ Prefer ArrayDeque over Stack and LinkedList for stack/queue
✅ Use Collections.unmodifiableList() for read-only views
✅ Watch for integer overflow: use long, or check before adding
✅ mid = l + (r - l) / 2  — avoids overflow in binary search
✅ Arrays.sort() on objects uses TimSort (stable); on primitives uses dual-pivot quicksort
✅ HashMap operations are O(1) average but O(n) worst case (hash collisions)
✅ Recursion depth → may cause StackOverflowError; prefer iterative when depth > 10^4
✅ null checks before accessing .next or node methods in linked list problems
```

---

*📌 These notes cover the full spectrum of DSA topics commonly tested in software engineering interviews at top tech companies. Practice each concept on LeetCode, HackerRank, or similar platforms for best retention.*

*Good luck with your interviews! 🚀*
