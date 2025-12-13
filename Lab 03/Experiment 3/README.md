# Infix to Postfix Converter and Evaluator in C

## 📌 Problem Statement
This program implements a comprehensive solution for handling mathematical expressions using stack operations. It performs two main tasks:

1) Conversion: Transforms infix expressions (human-readable) to postfix expressions    (computer-friendly)

2) Evaluation: Calculates the result of postfix expressions using stack operations

---

## ⚙️ Algorithm Explanation

1. **Stack Data Structures**
     - The program uses two specialized stack implementations:
     - Character Stack (for infix to postfix conversion):
            - Stores operators and parentheses during conversion
            - Handles operator precedence and associativity

     - Integer Stack (for postfix evaluation):
          - Stores operands during evaluation
          - Performs arithmetic operations when operators are encountered

2. **Infix to Postfix Conversion Algorithm**
   - The conversion follows the Shunting Yard Algorithm:
    1. Initialize empty stack and output string
    2. Scan each character in infix expression:
    - If operand: Add to output
    - If '(': Push to stack
    - If ')': Pop from stack to output until '(' is found
    - If operator:
            While stack has operators with higher/equal precedence:
                Pop operator to output
            Push current operator to stack
    3. Pop all remaining operators to output

3. **Postfix Evaluation Algorithm**
    1. Initialize empty stack
    2. Scan each character in postfix expression:
    - If operand: Push to stack
    - If operator:
            Pop two operands from stack
            Perform operation: operand1 operator operand2
            Push result back to stack
    3. Final result is the only element remaining in stack


 

## ⏱️ Time Complexity
- **Infix to Postfix:** `O(n)`
- **Postfix Evaluation:** `O(n)`
- **Overall Program:** `O(n)`

---



### Example
```bash
=== Infix to Postfix Converter and Evaluator ===

Enter an infix expression: (2+3)*4-5
Infix expression: (2+3)*4-5
Postfix expression: 23+4*5-
Result: 15

Do you want to continue? (y/n): y

Enter an infix expression: 2^3+4*5
Infix expression: 2^3+4*5
Postfix expression: 23^45*+
Result: 28

Do you want to continue? (y/n): n
Program terminated.
```
