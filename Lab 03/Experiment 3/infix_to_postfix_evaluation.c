#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

#define MAX 100

// Stack structure for characters (used in infix to postfix conversion)
struct CharStack {
    int top;
    unsigned capacity;
    char* array;
};

// Stack structure for integers (used in postfix evaluation)
struct IntStack {
    int top;
    unsigned capacity;
    int* array;
};

// Function prototypes for character stack
struct CharStack* createCharStack(unsigned capacity);
int isCharStackEmpty(struct CharStack* stack);
void pushChar(struct CharStack* stack, char item);
char popChar(struct CharStack* stack);
char peekChar(struct CharStack* stack);
int isOperator(char ch);
int precedence(char operator);

// Function prototypes for integer stack
struct IntStack* createIntStack(unsigned capacity);
int isIntStackEmpty(struct IntStack* stack);
void pushInt(struct IntStack* stack, int item);
int popInt(struct IntStack* stack);

// Infix to postfix conversion
char* infixToPostfix(char* infix);
// Postfix evaluation
int evaluatePostfix(char* postfix);

int main() {
    char infix[MAX];
    char choice;
    
    printf("=== Infix to Postfix Converter and Evaluator ===\n\n");
    
    do {
        printf("Enter an infix expression: ");
        fgets(infix, MAX, stdin);
        
        // Remove newline character
        infix[strcspn(infix, "\n")] = 0;
        
        printf("Infix expression: %s\n", infix);
        
        // Convert to postfix
        char* postfix = infixToPostfix(infix);
        printf("Postfix expression: %s\n", postfix);
        
        // Evaluate the postfix expression
        int result = evaluatePostfix(postfix);
        printf("Result: %d\n\n", result);
        
        free(postfix); // Free allocated memory
        
        printf("Do you want to continue? (y/n): ");
        scanf(" %c", &choice);
        getchar(); // Clear the input buffer
        
    } while (choice == 'y' || choice == 'Y');
    
    printf("Program terminated.\n");
    return 0;
}

// Character Stack Operations (for infix to postfix conversion)
struct CharStack* createCharStack(unsigned capacity) {
    struct CharStack* stack = (struct CharStack*)malloc(sizeof(struct CharStack));
    stack->capacity = capacity;
    stack->top = -1;
    stack->array = (char*)malloc(stack->capacity * sizeof(char));
    return stack;
}

int isCharStackEmpty(struct CharStack* stack) {
    return stack->top == -1;
}

void pushChar(struct CharStack* stack, char item) {
    stack->array[++stack->top] = item;
}

char popChar(struct CharStack* stack) {
    if (!isCharStackEmpty(stack))
        return stack->array[stack->top--];
    return '$'; // Error value
}

char peekChar(struct CharStack* stack) {
    if (!isCharStackEmpty(stack))
        return stack->array[stack->top];
    return '$'; // Error value
}

int isOperator(char ch) {
    return (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^');
}

int precedence(char operator) {
    switch (operator) {
        case '^': return 3;
        case '*':
        case '/': return 2;
        case '+':
        case '-': return 1;
        default: return -1;
    }
}

// Integer Stack Operations (for postfix evaluation)
struct IntStack* createIntStack(unsigned capacity) {
    struct IntStack* stack = (struct IntStack*)malloc(sizeof(struct IntStack));
    stack->capacity = capacity;
    stack->top = -1;
    stack->array = (int*)malloc(stack->capacity * sizeof(int));
    return stack;
}

int isIntStackEmpty(struct IntStack* stack) {
    return stack->top == -1;
}

void pushInt(struct IntStack* stack, int item) {
    stack->array[++stack->top] = item;
}

int popInt(struct IntStack* stack) {
    if (!isIntStackEmpty(stack))
        return stack->array[stack->top--];
    return -1; // Error value
}

// Infix to Postfix Conversion
char* infixToPostfix(char* infix) {
    int i, j;
    int len = strlen(infix);
    struct CharStack* stack = createCharStack(len);
    char* postfix = (char*)malloc((len + 1) * sizeof(char));
    
    if (!stack || !postfix) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    
    j = 0;
    
    for (i = 0; i < len; i++) {
        char current = infix[i];
        
        // If the character is an operand (digit or letter), add it to output
        if (isalnum(current)) {
            postfix[j++] = current;
        }
        // If the character is '(', push it to stack
        else if (current == '(') {
            pushChar(stack, current);
        }
        // If the character is ')', pop and output until '(' is found
        else if (current == ')') {
            while (!isCharStackEmpty(stack) && peekChar(stack) != '(') {
                postfix[j++] = popChar(stack);
            }
            if (!isCharStackEmpty(stack) && peekChar(stack) != '(') {
                printf("Invalid expression: Unbalanced parentheses\n");
                free(postfix);
                return NULL;
            } else {
                popChar(stack); // Remove '(' from stack
            }
        }
        // If the character is an operator
        else if (isOperator(current)) {
            while (!isCharStackEmpty(stack) && precedence(current) <= precedence(peekChar(stack))) {
                postfix[j++] = popChar(stack);
            }
            pushChar(stack, current);
        }
        // Ignore spaces
        else if (current == ' ') {
            continue;
        }
    }
    
    // Pop all remaining operators from stack
    while (!isCharStackEmpty(stack)) {
        if (peekChar(stack) == '(') {
            printf("Invalid expression: Unbalanced parentheses\n");
            free(postfix);
            return NULL;
        }
        postfix[j++] = popChar(stack);
    }
    
    postfix[j] = '\0'; // Null terminate the string
    
    free(stack->array);
    free(stack);
    
    return postfix;
}

// Postfix Evaluation
int evaluatePostfix(char* postfix) {
    int i;
    int len = strlen(postfix);
    struct IntStack* stack = createIntStack(len);
    
    if (!stack) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    
    for (i = 0; i < len; i++) {
        char current = postfix[i];
        
        // If the character is a digit, push it to stack
        if (isdigit(current)) {
            pushInt(stack, current - '0'); // Convert char to int
        }
        // If the character is an operator, pop two operands and perform operation
        else if (isOperator(current)) {
            int operand2 = popInt(stack);
            int operand1 = popInt(stack);
            int result;
            
            switch (current) {
                case '+': 
                    result = operand1 + operand2; 
                    break;
                case '-': 
                    result = operand1 - operand2; 
                    break;
                case '*': 
                    result = operand1 * operand2; 
                    break;
                case '/': 
                    if (operand2 == 0) {
                        printf("Error: Division by zero!\n");
                        return 0;
                    }
                    result = operand1 / operand2; 
                    break;
                case '^': 
                    result = (int)pow(operand1, operand2); 
                    break;
                default: 
                    printf("Invalid operator: %c\n", current);
                    return 0;
            }
            
            pushInt(stack, result);
        }
    }
    
    int finalResult = popInt(stack);
    
    if (!isIntStackEmpty(stack)) {
        printf("Invalid expression\n");
        return 0;
    }
    
    free(stack->array);
    free(stack);
    
    return finalResult;
}