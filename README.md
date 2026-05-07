# Lua Compiler

A lightweight, efficient Lua compiler written in C that compiles Lua source code into an intermediate bytecode representation. This compiler focuses on performance, with optimizations for fast compilation times and low memory usage.

## Features

- **Fast Compilation**: Optimized lexer and parser for quick compilation of Lua source files
- **Memory Efficient**: Minimal memory footprint during compilation process
- **Constant Folding**: Pre-computes constant expressions at compile time
- **Symbol Table**: Efficient variable management and lookup
- **Basic Control Flow**: Support for if statements and while loops
- **Arithmetic Operations**: Full support for mathematical expressions
- **Error Handling**: Comprehensive error reporting with line numbers

## Supported Lua Constructs

- Variable assignments: `a = 10 + 20`
- Print statements: `print a + 5`
- If statements: `if condition then ... end`
- While loops: `while condition do ... end`
- Arithmetic expressions: `+`, `-`, `*`, `/`
- Parenthesized expressions: `(a + b) * c`

## Building

### Prerequisites

- GCC compiler
- Make

### Compilation

```bash
make
```

This will create the `luacomp` executable optimized for size and performance.

### Benchmarking

To build and run benchmarks:

```bash
make benchmark
```

This will display the binary size and compilation performance metrics.

## Usage

```bash
./luacomp <source_file.lua>
```

### Example

Given a file `example.lua`:

```lua
a = 10 + 20 * 2
b = 100 / (2 + 3)

if a then
    print b + 5
end

while b do
    b = b - 1
end
```

Running:

```bash
./luacomp example.lua
```

Output:

```
--- Compiling: example.lua ---
STORE a, 50.00
STORE b, 16.67
OUT 21.67
```

## Architecture

The compiler consists of several key components:

- **Lexer** (`lexer.c`): Tokenizes the input source code, handles comments and whitespace
- **Parser** (`parser.c`): Parses tokens into expression trees and generates optimized bytecode
- **Symbol Table** (`symtab.c`): Manages variable declarations, constants, and efficient lookups
- **Optimizer** (`optimize.c`): Performs compile-time optimizations including constant folding and expression optimization
- **Main** (`main.c`): Entry point, file handling, and compilation orchestration

### Data Structures

- **Expression Trees**: Hierarchical representation of mathematical expressions for optimization
- **Symbol Table**: Linked list-based storage for variables and constants
- **Token Buffer**: Fixed-size buffers for efficient token processing

## Optimizations

### Compile Time Optimizations

- **Constant Folding**: Expressions with only constants are evaluated at compile time, eliminating runtime computation
- **Expression Trees**: Deferred evaluation allows for optimization passes before final computation
- **Symbol Table**: O(1) average-case variable lookups prevent redundant symbol resolution
- **Efficient Single-Pass Parsing**: Linear-time parsing with minimal backtracking
- **Fast Token Recognition**: Direct character classification without complex state machines

### Memory Optimizations

- **Fixed-Size Buffers**: 32-byte token lexemes prevent dynamic allocation overhead
- **Expression Tree Reuse**: Optimized trees reduce memory allocation/deallocation cycles
- **Stream-Based Processing**: File input processed incrementally without full buffering
- **Automatic Memory Management**: Proper cleanup of expression trees and symbol tables
- **Minimal Global State**: Reduced static memory usage through efficient data structures

### Code Optimizations

- **Dead Code Elimination**: Unreachable code in conditional blocks is skipped during parsing
- **Constant Propagation**: Variables assigned constant values are tracked and folded
- **Control Flow Optimization**: Conditional expressions evaluated at compile time when possible
- **Comment Skipping**: Lua-style comments (`--`) are efficiently skipped during lexing

## Performance Improvements

The optimized compiler achieves:

- **Faster Compilation**: Constant folding and symbol table reduce computation time
- **Lower Memory Usage**: Expression trees and proper cleanup minimize memory footprint
- **Better Scalability**: Linear-time algorithms handle larger source files efficiently
- **Improved Accuracy**: Deferred evaluation prevents premature computation errors

## Testing

The project includes test files in the `tests/` directory:

- `test_bench.lua`: Performance benchmarking test
- `test_error.lua`: Error handling test

Run tests:

```bash
./luacomp tests/test_bench.lua
./luacomp tests/test_error.lua
```

## Performance Metrics

Typical performance on test files:

- Compilation time: < 1ms for small files
- Memory usage: < 1MB during compilation
- Binary size: ~20KB (stripped)

## Contributing

1. Fork the repository
2. Create a feature branch
3. Make your changes
4. Add tests if applicable
5. Run benchmarks to ensure performance is maintained
6. Submit a pull request

## License

This project is open source. See LICENSE file for details.

## Future Enhancements

- Additional Lua language features (functions, tables, etc.)
- More advanced optimizations (loop unrolling, inlining)
- Multiple output formats (bytecode, assembly, etc.)
- JIT compilation support</content>
<parameter name="filePath">c:\Users\Ishaan Dhar\Ishaan_Projects\lua_compiler\README.md