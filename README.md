# Word Frequency Analyzer using AVL Tree & Hash Table (C)

## Overview
This project is a **menu-driven C application** that reads words from a text file, stores them in an **AVL Tree** (self-balancing BST), and then builds a **Hash Table** to support fast lookup of word frequencies.

It supports inserting/deleting words, printing sorted words (in-order traversal), searching in the hash table, and printing frequency statistics.

---

## Features (Menu Options)
1. Load data from file into the AVL tree  
2. Insert a word into the AVL tree  
3. Delete a word from the AVL tree  
4. Print words sorted (in-order) from the AVL tree  
5. Create the hash table (from the AVL tree)  
6. Insert a word into the hash table  
7. Delete a word from the hash table  
8. Search for a word in the hash table and print its frequency  
9. Print words statistics (frequency report)  
10. Exit the application  

---

## Data Structures
### AVL Tree
- Stores each word once and maintains balance using rotations.
- Each node contains:
  - `word`
  - `height`
  - `frequency` (how many times the word appears)

### Hash Table
- Uses **separate chaining** (linked lists) to handle collisions.
- Table size is **53** buckets.
- Each bucket is a linked list of nodes containing:
  - `word`
  - `frequency`

---

## Input File
The program loads words from:
- `input.txt`

Make sure `input.txt` is in the same directory when running the program.

---

## Word Statistics (Option 9)
The statistics report includes:
- A threshold input (show words repeated more than this number)
- Total number of **unique words**
- The **most frequent word** and its frequency

---

## Compile & Run

### Windows (MinGW / gcc)
```bash
gcc Project3.c -o Project3
Project3.exe
```

### Linux / macOS
```bash
gcc Project3.c -o Project3
./Project3
```

---

## Files
- `Project3.c` — main source code
- `input.txt` — input text file (required)

---

## Notes
- Load the file first (Option 1), then create the hash table (Option 5) before using hash operations like search/statistics.
- If you plan to upload to GitHub, include a small `input.txt` sample (optional) to make the repo easy to test.

---

## Author
- Aws Hammad (1221697)
