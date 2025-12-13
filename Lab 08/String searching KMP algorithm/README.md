# 🔍 KMP (Knuth–Morris–Pratt) Pattern Matching in C

This program implements the **KMP String Search Algorithm**, an efficient pattern-matching technique with **O(n + m)** complexity.

It uses:
- **LPS Array (Longest Prefix Suffix)** for preprocessing  
- Efficient skipping during mismatches  
- `fgets()` for safe string input  

---

## ✅ Features

- Builds the **LPS table** for the pattern  
- Performs **fast pattern matching**  
- Prints all occurrences  
- Handles multi-word input  

---

## 🧪 Compile & Run

### Compile:
```bash
gcc kmp.c -o kmp
```

### Run:
```bash
./kmp
```

---

## 📌 Full KMP Code (Clean & Commented)

```c
#include <stdio.h>
#include <string.h>

// Function to build LPS (Longest Prefix Suffix) array
void buildLPS(char pattern[], int m, int lps[])
{
    int len = 0; // length of the previous longest prefix suffix
    lps[0] = 0;  // lps[0] is always 0
    int i = 1;

    while (i < m)
    {
        if (pattern[i] == pattern[len])
        {
            len++;
            lps[i] = len;
            i++;
        }
        else
        {
            if (len != 0)
            {
                len = lps[len - 1];
            }
            else
            {
                lps[i] = 0;
                i++;
            }
        }
    }
}

// KMP search function
void KMPsearch(char text[], char pattern[])
{
    int n = strlen(text);
    int m = strlen(pattern);

    int lps[m];
    buildLPS(pattern, m, lps);

    int i = 0; // index for text
    int j = 0; // index for pattern
    int found = 0;

    while (i < n)
    {
        if (pattern[j] == text[i])
        {
            i++;
            j++;
        }

        if (j == m)
        {
            printf("Pattern found at index %d\n", i - j);
            j = lps[j - 1];
            found = 1;
        }
        else if (i < n && pattern[j] != text[i])
        {
            if (j != 0)
                j = lps[j - 1];
            else
                i++;
        }
    }

    if (!found)
        printf("Pattern not found in text.\n");
}

int main()
{
    char text[200], pattern[50];

    printf("Enter the text: ");
    fgets(text, sizeof(text), stdin);
    text[strcspn(text, "\n")] = '\0';

    printf("Enter the pattern: ");
    fgets(pattern, sizeof(pattern), stdin);
    pattern[strcspn(pattern, "\n")] = '\0';

    printf("\n--- KMP String Search Results ---\n");
    KMPsearch(text, pattern);

    return 0;
}
```

---

If you want, I can also generate:

📘 **LPS Table explanation**  
📊 **Dry run examples**  
📝 **Flowchart / ASCII diagram**  

Just tell me!
