# Chapter 5 — Constants & Compile-Time Evaluation (C++)

This document summarizes:

- 5.1 — Constant Variables (Named Constants)  
- 5.2 — Literals  
- 5.3 — Numeral Systems  
- 5.4 — The As-If Rule and Compile-Time Optimization  
- 5.5 — Constant Expressions  
- 5.6 — Constexpr Variables  

---

# 5.1 — Constant Variables (Named Constants)

## What Is a Constant?

A **constant** is a value that cannot be changed during program execution.

C++ supports:

- **Named constants**
- **Literal constants**

Named constants can be created using:

1. Constant variables (**preferred**)
2. Object-like macros (`#define`)
3. Enumerations

> [!important]
> Prefer constant variables over macros. They respect scope, types, and debugging tools.

---

## Constant Variables

A constant variable is a variable whose value cannot change after initialization.

```cpp
const double gravity { 9.8 };
````

### Const Placement

```cpp
const double gravity { 9.8 };   // preferred
double const gravity { 9.8 };   // "east const"
```

> [!tip]  
> Place `const` before the type for consistency and readability.

---

## Const Variables Must Be Initialized

```cpp
const int x;      // error
const int y{5};   // correct
```

- Must be initialized at definition.
    
- Cannot be reassigned afterward.
    

> [!warning]  
> A `const` variable without initialization is a compile-time error.

---

## Initialization From Non-Const

```cpp
int age{};
std::cin >> age;

const int constAge{ age }; // valid
```

The initializer **does not need** to be a constant expression.

> [!note]  
> `const` only guarantees immutability after initialization — not compile-time evaluation.

---

## Naming Conventions

Common styles:

- `EARTH_GRAVITY`
    
- `kEarthGravity`
    
- `earthGravity` (modern C++ style)
    

Const variables behave like normal variables — no special naming rule is required.

---

## Const Function Parameters

```cpp
void printInt(const int x);
```

For value parameters:

- Usually unnecessary.
    
- The parameter is a copy.
    

> [!tip]  
> Avoid `const` for by-value parameters. It matters for references and pointers, not copies.

---

## Const Return Values

```cpp
const int getValue();
```

For fundamental types:

- `const` is ignored.
    

For objects:

- May interfere with move semantics.
    

> [!best-practice]  
> Do not return `const` by value.

---

## Why Use Const?

If a variable can be `const`, it should be.

### Benefits

- Prevents accidental modification
    
- Reduces bugs
    
- Improves optimization potential
    
- Simplifies reasoning
    

> [!quote]  
> Non-const variables are moving parts. Const variables are not.

---

## Object-Like Macros (`#define`)

```cpp
#define MY_NAME "Alex"
```

Problems:

- No scope
    
- No type safety
    
- Harder to debug
    
- Text substitution only
    

> [!danger]  
> Macros do not respect C++ language rules. Prefer typed constants.

---

## Type Qualifiers

A **type qualifier** modifies type behavior.

C++ provides:

- `const`
    
- `volatile`
    

---

# 5.2 — Literals

## What Is a Literal?

A literal is a value written directly in code.

```cpp
5
true
3.4
'a'
"Hello"
```

---

## Default Literal Types

|Literal|Default Type|
|---|---|
|`5`|`int`|
|`true`|`bool`|
|`3.4`|`double`|
|`'a'`|`char`|
|`"Hello"`|`const char[]`|

---

## Literal Suffixes

### Integral Suffixes

|Suffix|Type|
|---|---|
|`u`|unsigned int|
|`L`|long|
|`LL`|long long|
|`z`|signed `std::size_t` (C++23)|

> [!tip]  
> Prefer uppercase `L` to avoid confusion with `1`.

---

### Floating-Point Suffixes

|Suffix|Type|
|---|---|
|`f`|float|
|`L`|long double|

```cpp
float f { 4.1f };
```

Without `f`, `4.1` is a `double`.

---

## Scientific Notation

```cpp
6.02e23
1.6e-19
```

---

## String Literals

```cpp
"Hello"
```

Characteristics:

- Implicit null terminator (`\0`)
    
- Type includes terminator (`const char[n]`)
    
- Created at program start
    
- Exist for entire program duration
    

> [!note]  
> String literals are not modifiable.

---

## Magic Numbers

A **magic number** is a literal with unclear meaning.

Bad:

```cpp
setMax(30);
```

Good:

```cpp
const int maxStudentsPerClass { 30 };
setMax(maxStudentsPerClass);
```

### Benefits

- Clear meaning
    
- Easy maintenance
    
- Prevents search-replace errors
    

> [!exception]  
> Acceptable magic values: `0`, `1`, `-1`, obvious conversion factors.

---

# 5.3 — Numeral Systems

## Base Systems in C++

|System|Base|Prefix|
|---|---|---|
|Decimal|10|none|
|Binary|2|`0b`|
|Octal|8|`0`|
|Hexadecimal|16|`0x`|

---

## Octal

```cpp
int x{012}; // octal
```

`012` (octal) = `10` (decimal)

> [!warning]  
> Avoid octal — leading zero can cause subtle bugs.

---

## Hexadecimal

```cpp
int x{0xF}; // 15
```

Digits:

0–9 and A–F

Used for:

- Memory addresses
    
- Bit manipulation
    
- Raw data representation
    

---

## Binary (C++14+)

```cpp
int x{0b1010};
```

---

## Digit Separators

```cpp
int x{0b1011'0010};
long y{2'132'673'462};
```

Improves readability only.

---

## Output Formatting

```cpp
std::cout << std::hex << x;
std::cout << std::oct << x;
std::cout << std::dec << x;
```

> [!note]  
> Stream manipulators persist until changed.

---

## Printing Binary with `std::bitset`

```cpp
std::bitset<8>{0b10101010};
```

---

# 5.4 — The As-If Rule and Compile-Time Optimization

## Optimization

Optimization improves:

- Speed
    
- Memory usage
    
- Resource efficiency
    

Compilers perform automatic optimization.

---

## The As-If Rule

> [!definition]  
> The compiler may transform a program in any way as long as observable behavior does not change.

This allows:

- Reordering
    
- Rewriting
    
- Removing code
    

---

## Compile-Time Evaluation

The compiler may evaluate expressions at compile-time instead of runtime.

Benefits:

- Faster execution
    
- Smaller binaries
    

---

## Constant Folding

```cpp
3 + 4  →  7
```

Literal expressions are replaced with computed results.

---

## Constant Propagation

```cpp
int x{7};
std::cout << x;
```

Becomes:

```cpp
std::cout << 7;
```

---

## Dead Code Elimination

Unused variables and unreachable code are removed.

---

## Const Improves Optimization

```cpp
const int x{7};
```

Because `x` cannot change, optimizations are more aggressive and reliable.

---

## Optimization vs Debugging

Optimized builds:

- Variables may disappear
    
- Functions may be inlined
    
- Code may not map cleanly to source
    

> [!important]  
> Debug builds typically disable heavy optimizations.

---

# 5.5 — Constant Expressions

## Definition

A **constant expression** is an expression that must be evaluatable at compile-time.

> [!rule]  
> Every part of the expression must be compile-time evaluatable.

---

## Allowed in Constant Expressions

- Literals
    
- Most operators with constant operands
    
- Const integral variables with constant initializer
    
- `constexpr` variables
    
- `constexpr` function calls
    

---

## Not Allowed

- Non-const variables
    
- Const non-integral variables (e.g., `const double`)
    
- Non-constexpr functions
    
- Function parameters
    
- I/O operations
    
- `new`, `delete`, `throw`
    

---

## Examples

```cpp
const int a{5};      // usable
const int b{a};      // usable
const double d{1.2}; // not usable in constant expressions
```

---

## When Are They Evaluated?

Only required to evaluate at compile-time in contexts that demand it.

```cpp
const int x{3+4}; // must evaluate at compile-time
int y{3+4};       // may evaluate at compile-time
```

---

## Likelihood of Compile-Time Evaluation

|Category|Likelihood|
|---|---|
|Non-constant expression|Never|
|Optimizable runtime expression|Possibly|
|Constant expression|Likely|
|Required context|Always|

---

# 5.6 — Constexpr Variables

## The Problem with Const

`const` does not guarantee:

- Compile-time evaluation
    
- Usability in constant expressions
    

It also does not support non-integral constant expressions.

---

## The `constexpr` Keyword

`constexpr` guarantees compile-time constant evaluation.

```cpp
constexpr int sum{4 + 5};
constexpr double gravity{9.8};
```

Rules:

- Must be initialized with a constant expression
    
- Compilation fails otherwise
    

---

## Invalid Examples

```cpp
int age{};
std::cin >> age;

constexpr int x{age};     // error
constexpr int y{five()};  // error if five() is not constexpr
```

---

## Const vs Constexpr

### const

- Immutable after initialization
    
- May be runtime or compile-time initialized
    

### constexpr

- Must be compile-time constant
    
- Must use constant expression
    
- Always usable in constant expressions
    

---

## Benefits of Constexpr

- Guarantees compile-time evaluation
    
- Enables usage in compile-time contexts
    
- Improves correctness
    
- Extends constant expressions beyond integral types
    

---

# Overall Mental Model

Constants in C++ exist on a spectrum:

- Literal → inherently compile-time capable
    
- `const` → immutable after initialization
    
- Constant expression → compile-time evaluatable
    
- `constexpr` → enforced compile-time constant
    

> [!summary]
> 
> 1. Use `const` whenever possible.
>     
> 2. Avoid magic numbers.
>     
> 3. Prefer constant variables over macros.
>     
> 4. Understand compile-time vs runtime evaluation.
>     
> 5. Use `constexpr` when compile-time guarantees are required.
>
