# ⚡ Huffman Coding in C — Min-Heap Based Implementation

This program implements **Huffman Encoding** using a **Min-Heap** and binary tree construction.  
It reads characters from **input.txt**, computes frequencies, builds the Huffman Tree, and writes the character codes to **encoded_output.txt**.

---

## 📌 Features
- Reads text from `input.txt`
- Counts frequency of all characters (0–255 ASCII)
- Builds **Huffman Tree** using:
  - Min-Heap
  - Repeated extraction of two minimum nodes
- Generates optimal variable-length codes
- Outputs codes both on screen and into `encoded_output.txt`
- Supports up to **256 unique characters**

---

## 🛠️ How Huffman Coding Works

### 1️⃣ Count character frequencies  
Example:  
```
AABBC → A:2, B:2, C:1
```

### 2️⃣ Build Min-Heap  
Each node contains:
```
data (char), freq, left, right
```

### 3️⃣ Build Huffman Tree  
Repeat:
- Extract two smallest nodes
- Create parent with combined frequency
- Insert back into Min-Heap  
Until only one node remains → **root** of Huffman Tree.

### 4️⃣ Generate Codes  
Traverse tree:
- Left = `0`
- Right = `1`  
Print code when reaching a leaf node.

---

## 🚀 Build & Run

### Compile
```bash
gcc huffman.c -o huffman
```

### Run
```bash
./huffman
```

Make sure `input.txt` exists in the same directory.

---

## 📄 Input Example (input.txt)
```
HELLO WORLD
```

## 📤 Output Example (encoded_output.txt)
```
H: 010
E: 110
L: 00
O: 111
 : 10
W: 0110
R: 0111
D: 101
```

(Actual codes depend on frequencies and tree structure.)

---

## 📊 Sample Console Output
```
H: 010
E: 110
L: 00
O: 111
 : 10
W: 0110
R: 0111
D: 101

Huffman Encoding Completed! Check encoded_output.txt
```

---

## 🧠 Insight
Huffman Coding is optimal for prefix-free compression, used in:
- ZIP, GZIP
- JPEG
- Multimedia compressors

This implementation demonstrates:
- Min-Heap structure
- Tree merging
- Recursion for binary code generation

A full, clean example of file-based Huffman encoding in C.

