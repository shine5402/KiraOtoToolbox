# Build KiraOtoToolbox

## Prerequisites

- **Qt 6** — framework for GUI, networking, QML scripting (recommended: 6.10+)
- **CMake** — build system (recommended: 3.20+)
- **Ninja** — recommended generator
- **Git** — for submodules

### Clone and initialize submodules

```bash
git clone <repo-url>
cd KiraOtoToolbox
git submodule update --init --recursive
```

The KFR audio library is managed as a git submodule at `src/3rdparty/kfr`.

## Compiler

### macOS

**LLVM Clang 22+ is required.** The project uses C++23 features including `std::views::zip` and `std::views::adjacent<N>` (P2321R2). Apple Clang (as of Xcode 26.4.1 / Apple Clang 21.0.0) does not yet include these features.

Install LLVM Clang via Homebrew:

```bash
brew install llvm
```

The two compilers are ABI-compatible for pure C++ (same libc++, Itanium ABI, Mach-O target), so you can mix LLVM Clang-built code with Qt 6 frameworks built against Apple Clang.

### Windows

MSVC with C++23 support (`/std:c++latest`). The CMake preset enables C++23 automatically.

### Linux

Clang 22+ or GCC with full C++23 ranges support (including P2321R2).

## Configure

Create `CMakeUserPresets.json` in the project root (git-ignored) that inherits from a preset in `CMakePresets.json` and sets your local paths:

### macOS

```json
{
    "version": 8,
    "configurePresets": [
        {
            "name": "my-debug",
            "inherits": "macos-debug",
            "cacheVariables": {
                "CMAKE_PREFIX_PATH": "/path/to/Qt/6.10.2/macos",
                "CMAKE_CXX_COMPILER": "/opt/homebrew/opt/llvm/bin/clang++",
                "CMAKE_EXPORT_COMPILE_COMMANDS": "ON"
            }
        }
    ],
    "buildPresets": [
        {"name": "my-debug", "configurePreset": "my-debug", "jobs": 14}
    ]
}
```

### Windows

```json
{
    "version": 8,
    "configurePresets": [
        {
            "name": "my-debug",
            "inherits": "windows-debug",
            "cacheVariables": {
                "CMAKE_PREFIX_PATH": "C:/Qt/6.10.2/msvc2022_64",
                "CMAKE_EXPORT_COMPILE_COMMANDS": "ON"
            }
        }
    ],
    "buildPresets": [
        {"name": "my-debug", "configurePreset": "my-debug", "jobs": 14}
    ]
}
```

### Configure

```bash
cmake --preset my-debug
```

## Build

```bash
cmake --build build --preset my-debug
```

## Test

```bash
cd build && ctest --output-on-failure
```

All 21 test targets should pass.

## Install (macOS)

The `macos-relwithdebinfo` preset builds a deployable `.app` bundle:

```bash
cmake --preset default-relwithdebinfo
cmake --build build --preset default-relwithdebinfo
cmake --install build --prefix build/artifact
```
