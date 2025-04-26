# SimpleMathREPL

A simple command-line math evaluator written in C. This program supports basic arithmetic operations, operator precedence, parentheses, and variables. It allows you to evaluate mathematical expressions interactively.

## Features

- **Basic Arithmetic**: Supports `+`, `-`, `*`, and `/` operations.
- **Operator Precedence**: Follows standard operator precedence (multiplication and division are evaluated before addition and subtraction).
- **Parentheses**: Supports parentheses `()` for grouping expressions and controlling the evaluation order.
- **Variables**: You can store results in variables (single-letter variables, `a-z`), and use them in subsequent expressions.

## Usage

1. **Run the Program**:
   Simply compile and run the program. It will prompt you for input.

   ```bash
   make
   ./smrepl
   ```

2. **Basic Operations**:
   You can enter expressions like:

    ```bash
    > 3 + 5 * 2
    = 13
    > (3 + 5) * 2
    = 16
    ```

3. **Variables**:

    You can assign values to variables using the > symbol.
    Variables are single letters from a to z.

    Example:
    ```bash
    > 1 + 2 > x  # Assigns the result of the expression to variable 'x'
    = 3
    > 3 + 5 > y
    = 8
    > x + y
    = 11
    ```
    Note: in the above example, the '>' at the beginning of a line is a prompt symbol.
          while the one before the variable name is the one used to set the variable value.
    
5. **Exit**:
   To exit the program, use Ctrl+D or Ctrl+Z (depending on your operating system).

## LICENSE

This project is licensed under [GPL V3](LICENSE).
