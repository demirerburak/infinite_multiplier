# infinite_multiplier
# Infinite Precision Multiplication Using Linked Lists

This program multiplies two arbitrarily large numbers (theoretically infinite) by representing each number as a **linked list** of digits. It simulates traditional long multiplication, overcoming the limitations of primitive data types in C.

---

## Key Features

- Handles numbers of **arbitrary size and precision**, including decimal points.
- Uses **four linked lists** to manage the input and intermediate multiplication results.
- Written entirely in **C**, using only standard libraries.
- Measures execution time and manages memory effectively.

---

## How It Works

1. **Input Handling**:
   - Two numbers are read from an input file.
   - Each digit is stored in a node of a doubly linked list.
   - If a decimal point is present, its position is stored for later adjustment.

2. **Multiplication Process**:
   - Each digit of the first number is multiplied with all digits of the second number.
   - Results are stored in a temporary linked list.
   - Intermediate results are left-shifted (simulating multiplication by powers of 10).
   - These are cumulatively added to the final result using the `sum()` function.

3. **Finalization**:
   - After all multiplications, the correct decimal point position is restored.
   - Trailing zeros are removed.
   - Result is written to the output file and printed to console.
   - All linked lists are freed using `freeList()` to avoid memory leaks.

---

## Functions

### `main()`
- Handles file I/O, timing, linked list construction, multiplication, and output.

### `sum(head, sum)`
- Adds an intermediate product to the cumulative result.
- Handles digit shifting automatically.
- If the result is empty (`NULL`), it initializes the result from the sum list.

### `freeList(head)`
- Frees all nodes in a given linked list.
