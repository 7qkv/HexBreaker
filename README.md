# HexBreaker

x64 anti-decompiler tool that breaks IDA Pro Hex-Rays decompiler.

## What is this

Single header library that protects your functions from being decompiled in IDA Pro. Inserts compile-time generated stubs with randomized offsets that cause decompilation failures.

Works only on MSVC x64.

## How to use
```cpp
#include "hexbreaker.hpp"

void protected_function() {
    HEXBREAKER;  // add this at the start of any function
    // rest of your code
}
```

There are 3 macros available:

- `HEXBREAKER` - normal protection
- `HXB_MAX` - stronger protection, use for important stuff
- `HXB_MIN` - lighter version, use in loops

## How it works

Adds unreachable instructions with huge stack offsets that IDA can't handle. The stub code never runs but breaks the decompiler when it tries to analyze it. Uses 4 different patterns that change each time you compile based on date/time hash.

## Building
```bash
cl /std:c++17 /O2 main.cpp
```

Requires C++17 or newer.

## Files

- `hexbreaker.hpp` - the header you need to include
- `main.cpp` - simple example
- `LICENSE` - MIT
- `README.md` - this file

## Limits

Only works on Windows x64 with MSVC compiler. Won't stop someone who really wants to reverse your program, just makes it harder.

The stubs don't execute at runtime so there's no performance loss.

## License

MIT

---

made by [7qkv](https://github.com/7qkv)
