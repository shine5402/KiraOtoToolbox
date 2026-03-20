# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project Overview

KiraOtoToolbox is a Qt/C++ desktop application for manipulating oto.ini files — the voicebank labeling format used by UTAU (a singing voice synthesis engine). It provides 18+ tools for batch processing audio voicebank data, with both GUI and JavaScript scripting support.

- **Language:** C++20
- **Framework:** Qt 5.15+ / Qt 6 (with core5compat)
- **Build system:** qmake
- **License:** GPL v3 (with OpenSSL exception)

## Build

Prerequisites: KFR audio library must be built and installed separately (CMake). All other dependencies are git subtrees in `lib/`.

```bash
# Open in Qt Creator and build, or:
qmake KiraOtoToolbox.pro
make
```

The project uses a `subdirs` template: root `.pro` builds `src/` and all libraries under `lib/`. The main app config is in `src/src.pro`, which includes `lib.pri` (internal libs) and `external-lib.pri` (KFR config, copied from `external-lib_template.pri`).

## Architecture

### Tool Plugin System

The core architecture is a plugin-style tool system. Each tool consists of three classes following an MVC-like pattern:

1. **`ToolDialogAdapter`** — bridge that provides metadata (name, category, description) and creates instances of the other two components via Qt's MetaObject system (`Q_INVOKABLE` constructors)
2. **`ToolOptionWidget`** (QWidget) — UI for tool-specific options
3. **`OtoListModifyWorker`** (QObject) — business logic that transforms `OtoEntryList` data

**Registration:** Tools are registered in `src/initFuncs.cpp` using `REGISTER_TOOL` macro. `ToolManager` (singleton) holds all registered tools grouped by category.

**Data flow:** oto.ini file -> `OtoEntryList` -> `ToolOptionWidget.getOptions()` -> `OtoListModifyWorker.doWork()` -> modified `OtoEntryList` -> save

### Adding a New Tool

Create a subdirectory under `src/` with three files implementing the adapter, option widget, and worker. Register in `initFuncs.cpp`. Each tool needs:
- `getOptions()` / `setOptions()` for runtime option access
- `optionsToJson()` / `jsonToOptions()` for preset serialization
- `optionJsonVersion()` for schema versioning

### Key Subsystems

- **Preset system:** `PresetManager` (singleton) manages built-in presets (compiled as `.qrc` resources) and user presets (JSON, saved to OS app data dirs). Presets support i18n names.
- **Chain tool** (`src/chain/`): Composes multiple tools into sequential action chains.
- **JavaScript tool** (`src/jsScript/`): Embeds QML's JS engine for user-written transformations.
- **`ToolDialog`**: Main UI dialog supporting single-file and batch processing modes.

### Library Dependencies (git subtrees in `lib/`)

- **KiraUTAUUtils** — oto.ini parsing (`OtoEntry`, `OtoEntryList`, file I/O)
- **KiraCommonUtils** — dark mode, i18n (`TranslationManager`), and misc utilities
- **compact_enc_det** — Google's character encoding detection
- **QSourceHighlite** — syntax highlighting for JS editor
- **FunctionalPlus** — header-only functional programming utilities

### Key Types

- `OtoEntry` / `OtoEntryList` — core data model (from KiraUTAUUtils)
- `OptionContainer` — `QHash<QString, QVariant>` wrapper for passing options between layers
- `Tool` / `ToolWithOptions` — registered as Qt metatypes for signal/slot usage
- `ToolException` — base exception class with `ConfirmMsg` support for user confirmation dialogs

## Conventions

- Qt `.ui` files for most tool option widgets (25 total)
- Git info (hash, branch, describe) embedded at compile time via `DEFINES` in `src.pro`
- i18n via Qt `.ts`/`.qm` translation files; currently English and Simplified Chinese
- Tool categories are translatable strings (via `QCoreApplication::translate`)
