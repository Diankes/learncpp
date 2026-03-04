
# Chapter 4: Fundamental Data Types

## 4.1 — Bits, Bytes, and Memory Addressing
- **Bits**: The smallest unit of memory (0 or 1).
- **Bytes**: A group of bits (standard is 8 bits).
- **Memory Address**: A unique identifier for each byte of memory, allowing the CPU to find data.
- **Data Type**: Tells the compiler how to interpret the bits at a specific address.



---

## 4.2 — Void
- **Meaning**: "No type" or "Incomplete type."
- **Usage**: Primarily used to indicate a function does not return a value.
- > [!NOTE] Best Practice
> In C++, use empty parentheses `int main()` instead of `int main(void)` to indicate no parameters.

---

## 4.3 — Object Sizes and `sizeof`
- **Size vs. Range**: An object with $n$ bits can hold $2^n$ unique values.
- **`sizeof` operator**: A unary operator that returns the size of a type or variable in bytes.
- **Minimum Sizes**:
    - `char`: 1 byte
    - `short`/`int`: 2 bytes
    - `long`: 4 bytes
    - `long long`: 8 bytes

---

## 4.4 — Signed Integers
- **Sign Bit**: Uses one bit to track if the number is positive or negative (usually via **Two's Complement**).
- **Integer Division**: Always drops the fractional part (truncation). `7 / 4 = 1`.

> [!CAUTION] Undefined Behavior
> Assigning a value outside the range of a **signed** integer results in **integer overflow**, which is undefined behavior in C++.

---

## 4.5 — Unsigned Integers
- **Wrap-around**: Unlike signed integers, if an unsigned value goes out of range, it wraps around (modulo arithmetic). `0 - 1` on a 4-byte unsigned int becomes `4,294,967,295`.
- > [!WARNING] Avoid Unsigned for Quantities
> Avoid unsigned integers for holding quantities. Mixing signed and unsigned integers in math/comparisons often leads to bugs where signed values are implicitly converted to huge unsigned numbers.

---

## 4.6 — Fixed-Width Integers & `size_t`
- **Fixed-Width**: Types like `std::int32_t` (from `<cstdint>`) ensure the variable is exactly the same size on every architecture.
- **`size_t`**: An implementation-defined unsigned type used for the size/length of objects.

> [!BUG] The int8_t Trap
> `std::int8_t` and `std::uint8_t` often behave like `char`. Printing them might show an ASCII character instead of a number.

---

## 4.7 & 4.8 — Floating Point Numbers
- **Types**: `float` (4 bytes), `double` (8 bytes), `long double` (8-16 bytes).
- **Scientific Notation**: Useful for very large/small numbers (e.g., $1.2 \times 10^4$ written as `1.2e4`).
- **Precision**: 
    - `float`: ~7 digits.
    - `double`: ~15-18 digits.

> [!DANGER] Rounding Errors
> Many decimal numbers (like `0.1`) cannot be represented exactly in binary. **Never compare floating point numbers directly using `==`.**



---

## 4.9 & 4.10 — Booleans and If Statements
- **Storage**: `bool` stores `true` (1) or `false` (0).
- **Output**: Use `std::boolalpha` to print "true"/"false" instead of 1/0.
- **Implicit Conversion**: Any non-zero integer converts to `true`; zero converts to `false`.

---

## 4.11 — Chars
- **ASCII**: `char` stores a 1-byte integer mapped to a character.
- **Escape Sequences**:
    - `\n`: Newline
    - `\t`: Horizontal tab
    - `\'` / `\"`: Single/Double quotes
- > [!ERROR] Literal Types
> `'a'` is a `char` literal (single quotes). 
> `"a"` is a `string` literal (double quotes).



---

## 4.12 — Type Conversion & `static_cast`
- **Implicit**: Done by compiler (can cause data loss/warnings).
- **Explicit (`static_cast`)**: The programmer manually converts a type.
    - Syntax: `static_cast<new_type>(expression)`
    - Example: `static_cast<int>(myChar)` prints the ASCII value.

---

## Summary Summary (Key Takeaways)
- [ ] Favor `double` over `float` for precision.
- [ ] Favor `int` (signed) over `unsigned` for math.
- [ ] Use `static_cast` when converting to be intentional.
- [ ] Always remember that integer division truncates.