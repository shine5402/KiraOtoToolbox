# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project Overview

KiraOtoToolbox is a Qt/C++ desktop application for manipulating oto.ini files — the voicebank labeling format used by UTAU (a singing voice synthesis engine). It provides 18+ tools for batch processing audio voicebank data, with both GUI and JavaScript scripting support.

- **Language:** C++23
- **Framework:** Qt 6 (with Core5Compat for QTextCodec/Shift-JIS)
- **Build system:** CMake (legacy qmake files still present)
- **License:** GPL v3 (with OpenSSL exception)

## Build

```bash
# Configure (uses CMakePresets.json; create CMakeUserPresets.json for local Qt path)
cmake --preset <preset-name>

# Build
cmake --build build --preset <preset-name> -j$(nproc)
```

CMakePresets.json defines macOS (universal binary x86_64;arm64) and Windows presets. Create a `CMakeUserPresets.json` (git-ignored) that inherits from a preset and sets `CMAKE_PREFIX_PATH` to your Qt 6 installation.

### Dependencies

- **dr_wav** — WAV file reading, single-header library in `src/3rdparty/dr_libs/`
- **compact_enc_det** — Google's character encoding detection, in `src/3rdparty/compact_enc_det/`
- **dtl** — Diff Template Library (header-only), in `src/3rdparty/dtl/`
- **QSourceHighlite** — syntax highlighting, in `src/3rdparty/QSourceHighlite/`

## Architecture

### Tool Plugin System

The core architecture is a plugin-style tool system. Each tool consists of three classes following an MVC-like pattern:

1. **`ToolDialogAdapter`** — bridge that provides metadata (name, category, description) and creates instances of the other two components via Qt's MetaObject system (`Q_INVOKABLE` constructors)
2. **`ToolOptionWidget`** (QWidget) — UI for tool-specific options
3. **`OtoListModifyWorker`** (QObject) — business logic that transforms `OtoEntryList` data

**Registration:** Tools are registered in `src/initFuncs.cpp` using `REGISTER_TOOL` macro. `ToolManager` (singleton) holds all registered tools grouped by category.

**Data flow:** oto.ini file -> `OtoEntryList` -> `ToolOptionWidget.getOptions()` -> `OtoListModifyWorker.doWork()` -> modified `OtoEntryList` -> save

### Adding a New Tool

Create a subdirectory under `src/` with three files implementing the adapter, option widget, and worker. Add a `CMakeLists.txt` using `target_sources(KiraOtoToolbox PRIVATE ...)` and `add_subdirectory()` it from `src/CMakeLists.txt`. Register in `initFuncs.cpp`. Each tool needs:
- `getOptions()` / `setOptions()` for runtime option access
- `optionsToJson()` / `jsonToOptions()` for preset serialization
- `optionJsonVersion()` for schema versioning

### Key Subsystems

- **Preset system:** `PresetManager` (singleton) manages built-in presets (compiled as `.qrc` resources) and user presets (JSON, saved to OS app data dirs). Presets support i18n names.
- **Chain tool** (`src/chain/`): Composes multiple tools into sequential action chains.
- **JavaScript tool** (`src/jsScript/`): Embeds QML's JS engine for user-written transformations.
- **`ToolDialog`**: Main UI dialog supporting single-file and batch processing modes.

### Source Layout

- `src/otoUtils/` — oto.ini parsing (`OtoEntry`, `OtoEntryList`, file I/O), absorbed from KiraUTAUUtils
- `src/utils/` — shared utilities absorbed from KiraCommonUtils:
  - `dialogs/` — reusable dialogs (list view, diff view, HTML view, table view, oto list)
  - `widgets/` — reusable widgets (file browse, string list editor, replace rules, etc.)
  - `models/` — Qt model classes for oto data
  - `misc/` — miscellaneous helpers
  - `i18n/` — translation manager
  - `lib_helper/` — WAV duration helper
  - Root: darkmode, filesystem, stringfunc, updatechecker, base64, setoperations
- `src/toolBase/` — base classes for the tool system
- `src/3rdparty/` — third-party libraries (dr_wav, dtl, compact_enc_det, QSourceHighlite)
- `src/<toolName>/` — one directory per tool (18+ tools)

### Key Types

- `OtoEntry` / `OtoEntryList` — core data model (in `src/otoUtils/`)
- `OptionContainer` — `QHash<QString, QVariant>` wrapper for passing options between layers
- `Tool` / `ToolWithOptions` — registered as Qt metatypes for signal/slot usage
- `ToolException` — base exception class with `ConfirmMsg` support for user confirmation dialogs

## CMake Structure

- Root `CMakeLists.txt` — project setup, Qt 6 find_package, C++23
- `src/CMakeLists.txt` — `qt_add_executable()`, links all libs, git info, translations, install rules
- `src/3rdparty/CMakeLists.txt` — dr_wav, dtl, compact_enc_det, QSourceHighlite
- Per-tool `CMakeLists.txt` — each uses `target_sources(KiraOtoToolbox PRIVATE ...)`

## Conventions

- Qt `.ui` files for most tool option widgets (25 total)
- Git info (hash, branch, describe) embedded at compile time via `target_compile_definitions` in CMake
- i18n via Qt `.ts`/`.qm` translation files (`qt_add_translations`); currently English and Simplified Chinese
- Tool categories are translatable strings (via `QCoreApplication::translate`)
- Includes use quoted paths relative to `src/`: `"otoUtils/otoentry.h"`, `"utils/darkmode.h"`
- Use [Conventional Commits](https://www.conventionalcommits.org/) format: `type: description` (e.g., `feat:`, `fix:`, `chore:`, `refactor:`, `docs:`, `style:`, `test:`)
