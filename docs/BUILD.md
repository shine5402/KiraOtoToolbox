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

The project requires C++23. Tested compilers:

- **macOS:** Apple Clang 21 (Xcode 26.5)
- **Windows:** MSVC with `/std:c++latest`
- **Linux:** Clang 18+ or GCC 14+

The CMake preset sets `CMAKE_CXX_STANDARD=23` automatically.

## Configure

Create `CMakeUserPresets.json` in the project root (git-ignored) that inherits from a preset in `CMakePresets.json` and sets your local paths:

### macOS

```json
{
    "version": 8,
    "configurePresets": [
        {
            "name": "my-debug",
            "inherits": "macos-debug-template",
            "cacheVariables": {
                "CMAKE_PREFIX_PATH": "/path/to/Qt/6.10.2/macos",
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
            "inherits": "windows-debug-template",
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

The `macos-relwithdebinfo-template` preset builds a deployable `.app` bundle:

```bash
cmake --preset default-relwithdebinfo
cmake --build build --preset default-relwithdebinfo
cmake --install build --prefix build/artifact
```
