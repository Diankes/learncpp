# Chapter 6 — Operator Precedence

# 6.1 — Operator Precedence and Associativity

## What is an Operation?

- **Operation**: A mathematical process that produces a value.
    
- **Operands**: Input values.
    
- **Operator**: Symbol specifying the operation.
    

Example:

```cpp
2 + 3
```

- Operands: `2`, `3`
    
- Operator: `+`
    
- Result: `5`
    

---

## Evaluation of Compound Expressions

Example:

```cpp
4 + 2 * 3
```

Two possible groupings:

- `(4 + 2) * 3 = 18`
    
- `4 + (2 * 3) = 10`
    

C++ uses:

- **Operator precedence**
    
- **Associativity**
    

---

## Operator Precedence

- Determines **which operators group first**.
    
- Lower number = higher precedence.
    
- Example:
    
    - `*` has higher precedence than `+`
        
    - So: `4 + 2 * 3` → `4 + (2 * 3)`
        

---

## Operator Associativity

Used when operators share same precedence.

Example:

```cpp
7 - 4 - 1
```

- Subtraction has **left-to-right associativity**
    
- So:
    
    ```cpp
    (7 - 4) - 1
    ```
    

---

## Key Precedence Highlights

|Level|Operators|Associativity|
|---|---|---|
|1|`::`|L→R|
|2|`()`, `[]`, `.`, `->`, postfix `++ --`, casts, `sizeof`|L→R|
|3|unary `+ -`, prefix `++ --`, `!`, `~`, `*`, `&`, `new`, `delete`|R→L|
|5|`* / %`|L→R|
|6|`+ -`|L→R|
|7|`<< >>`|L→R|
|9|`< <= > >=`|L→R|
|10|`== !=`|L→R|
|14|`&&`|L→R|
|15|`||
|16|`?:`, `=`, `+=`, etc.|R→L|
|17|`,`|L→R|

---

## No Exponent Operator

- `^` is **bitwise XOR**, not exponent.
    
- Use:
    
    ```cpp
    #include <cmath>
    std::pow(base, exponent);
    ```
    

---

## Parentheses Best Practices

Use parentheses to:

- Clarify intent
    
- Avoid reliance on precedence table
    
- Improve readability
    

### Rule of Thumb

> Parenthesize everything except addition, subtraction, multiplication, and division.

### Exception

Single assignment expressions do NOT require wrapping:

```cpp
x = y + z;        // OK
x = (y + z);      // Also OK but unnecessary
```

---

## Value Computation vs Evaluation

- **Value computation** → executing operators to produce value.
    
- **Evaluation** → evaluating operands.
    

---

## Order of Evaluation (Critical Concept)

> C++ does NOT specify the order of evaluation of operands or function arguments.

Example:

```cpp
printCalculation(getValue(), getValue(), getValue());
```

Different compilers may evaluate arguments in different orders.

### Key Insight

- Precedence determines grouping.
    
- It does NOT determine operand evaluation order.
    

### Avoid

Expressions dependent on evaluation order.

---

# 6.2 — Arithmetic Operators

## Unary Operators

|Operator|Meaning|
|---|---|
|`+x`|Value of x|
|`-x`|Negation of x|

Note:

- Unary `-` ≠ subtraction operator.
    

---

## Binary Arithmetic Operators

|Operator|Meaning|
|---|---|
|`+`|Addition|
|`-`|Subtraction|
|`*`|Multiplication|
|`/`|Division|
|`%`|Remainder|

---

## Division Modes

### Floating Point Division

Occurs if either operand is floating point:

```cpp
7.0 / 4 → 1.75
```

### Integer Division

Occurs if both operands are integers:

```cpp
7 / 4 → 1
-7 / 4 → -1
```

Fraction is discarded.

---

## Using `static_cast` to Force Floating Division

```cpp
static_cast<double>(x) / y
```

---

## Division by Zero

- Integer `/ 0` → **Undefined behavior**
    
- Floating `/ 0.0` → Implementation-defined (NaN or Inf on IEEE754 systems)
    

---

## Arithmetic Assignment Operators

|Operator|Meaning|
|---|---|
|`+=`|Add and assign|
|`-=`|Subtract and assign|
|`*=`|Multiply and assign|
|`/=`|Divide and assign|
|`%=`|Remainder and assign|

Example:

```cpp
x += 4;
```

---

## Modifying Operators

Operators that modify left operand:

- Assignment operators (`=`, `+=`, etc.)
    
- Increment/decrement (`++`, `--`)
    

---

# 6.3 — Remainder and Exponentiation

## Remainder Operator `%`

- Returns remainder of integer division.
    
- Works only with integers.
    

Examples:

```cpp
7 % 4 → 3
25 % 7 → 4
```

If divisor > dividend:

```cpp
2 % 4 → 2
```

---

## Negative Operands

Result takes sign of first operand:

```cpp
-6 % 4 → -2
6 % -4 → 2
```

---

## Best Practice

Compare against 0:

```cpp
(x % 2) != 0
```

Avoid:

```cpp
(x % 2) == 1   // fails for negative odd numbers
```

---

## No Exponent Operator

Use:

```cpp
std::pow(3.0, 4.0);
```

Note:

- Returns `double`
    
- Subject to floating point rounding errors
    

---

## Integer Exponentiation

Custom `powint()` implementation:

- Uses exponentiation by squaring
    
- May overflow
    
- `constexpr` capable
    

Safer version:

- Checks overflow
    
- Returns `std::numeric_limits<std::int64_t>::max()` on overflow
    

---

# 6.4 — Increment/Decrement Operators and Side Effects

## Prefix vs Postfix

|Operator|Behavior|
|---|---|
|`++x`|Increment then return|
|`x++`|Return copy, then increment|

Example:

```cpp
int y = ++x;  // y gets incremented value
int y = x++;  // y gets original value
```

---

## Best Practice

> Prefer prefix (`++x`) over postfix (`x++`) when either works.

---

## Side Effects

A side effect changes state beyond returning a value.

Examples:

```cpp
x = 5;      // modifies x
++x;        // modifies x
std::cout << x;  // modifies console state
```

---

## Critical Warning

C++ does NOT define:

- Order of function argument evaluation
    
- Order of operand evaluation
    

Avoid:

```cpp
add(x, ++x);   // Undefined behavior
x + ++x;       // Unspecified behavior
```

### Rule

> Do not use a variable with a side effect more than once in a statement.

---

# 6.5 — The Comma Operator

## Behavior

```cpp
x, y
```

- Evaluate `x`
    
- Evaluate `y`
    
- Return value of `y`
    

Example:

```cpp
(++x, ++y)
```

---

## Precedence

Lowest precedence in C++.

Example:

```cpp
z = (a, b);   // z = b
z = a, b;     // (z = a), b
```

---

## Best Practice

> Avoid comma operator except inside `for` loops.

---

## Separator Commas

Used in:

- Function parameters
    
- Function arguments
    
- Variable declarations
    

These are NOT comma operator usage.

---

# 6.6 — The Conditional Operator `?:`

## Syntax

```cpp
condition ? expression1 : expression2
```

If condition true → expression1  
Else → expression2

---

## Example

```cpp
max = (x > y) ? x : y;
```

---

## Usage Cases

- Initialization
    
- Assignment
    
- Return values
    
- Function arguments
    
- Printing
    

---

## Parenthesization Rules

When used inside compound expression:

```cpp
std::cout << (condition ? x : y);
```

Best practice:

- Parenthesize entire conditional when in compound expression.
    
- Consider parenthesizing condition if it contains operators.
    

---

## Type Rules

Second and third operands must:

- Match types, or
    
- Be convertible to common type
    

Example of surprising result:

```cpp
(true ? -1 : 2u)
```

May convert `-1` to unsigned → large value.

---

## Avoid in Complex Expressions

> Prefer clarity over compactness.

---

# 6.7 — Relational Operators & Floating Point Comparisons

## Relational Operators

|Operator|Meaning|
|---|---|
|`>`|Greater than|
|`<`|Less than|
|`>=`|Greater or equal|
|`<=`|Less or equal|
|`==`|Equal|
|`!=`|Not equal|

Return `true` or `false`.

---

## Boolean Condition Best Practice

Avoid:

```cpp
if (b == true)
```

Use:

```cpp
if (b)
if (!b)
```

---

## Floating Point Comparison Issues

Floating point numbers are imprecise:

```cpp
0.3 == 0.2 + 0.1  // false
```

### Why?

Rounding errors.

---

## Rules

### Safe:

- Comparing literal with same literal.
    
- When values are not extremely close.
    

### Dangerous:

- `==` and `!=` with calculated floating point values.
    

---

## Warning

> Avoid `==` and `!=` for floating point values if they were calculated.

# 6.x — Chapter 6 Summary and Quiz

---

## Quick Review

### 1. Parentheses and Precedence

- Always use parentheses to disambiguate operator precedence if there is any opportunity for confusion.
    
- Precedence determines grouping, not evaluation order.
    

> Best practice: Prefer clarity over relying on precedence rules.

---

### 2. Arithmetic Operators

- Work like normal mathematics.
    
- Remainder operator `%` returns the remainder of integer division.
    

---

### 3. Increment and Decrement Operators

- `++` and `--` increment or decrement by 1.
    
- Prefer **prefix versions** over postfix when possible.
    

> Avoid postfix versions unless necessary.

---

### 4. Side Effects and Evaluation Order

- Side effects modify program state.
    
- C++ does **not define the order of evaluation** of function arguments.
    
- Do not use a variable that has a side effect applied more than once in a statement.
    

Example to avoid:

```cpp
add(x, ++x);  // Undefined behavior
```

---

### 5. Comma Operator

- Evaluates left operand, then right operand.
    
- Returns value of right operand.
    
- Rarely needed outside `for` loops.
    

> Writing separate statements is usually better.

---

### 6. Conditional Operator (`?:`)

Ternary operator form:

```cpp
condition ? expression1 : expression2
```

If `condition` is true → evaluate `expression1`  
Else → evaluate `expression2`

### Parenthesizing Rules

- Parenthesize the **entire conditional operator** when used in a compound expression.
    
- For readability, parenthesize the condition if it contains operators (excluding function calls).
    

Example:

```cpp
std::cout << (condition ? x : y);
```

---

### 7. Relational Operators

- Used to compare values.
    
- Return `true` or `false`.
    

When using floating point values:

- `<`, `>`, `<=`, `>=` are usually reliable unless values are extremely close.
    
- Avoid `==` and `!=` with calculated floating point values.
    

---

### 8. Logical Operators

Logical operators allow formation of compound conditional statements.

(Previously covered in chapter.)


---

# High-Yield Chapter 6 Takeaways

1. Precedence ≠ evaluation order.
    
2. Parenthesize for clarity.
    
3. Avoid side effects in compound expressions.
    
4. Prefer prefix increment.
    
5. Avoid comma operator.
    
6. Avoid `==` for calculated floating point values.
    
7. Conditional operator is best for simple binary value selection.
    
8. Do not mix signed and unsigned carelessly.
    
9. `%` result takes sign of left operand.
    
10. Do not depend on argument evaluation order.
    

---
# Core Concepts to Remember

1. Precedence determines grouping, not evaluation order.
    
2. Evaluation order of operands is mostly unspecified.
    
3. Side effects + unspecified evaluation = bugs.
    
4. Prefer clarity and parentheses.
    
5. Avoid mixing signed and unsigned.
    
6. Avoid `==` for floating point calculations.
    
7. Prefer prefix increment.
    
8. Avoid comma operator.
    
9. Use remainder comparisons against 0.
    
10. Conditional operator should be parenthesized in compound expressions.
    

