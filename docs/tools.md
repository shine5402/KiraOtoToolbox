# Tool Reference

KiraOtoToolbox provides 19 tools organized into 5 categories. This document covers each tool's purpose, options, and behavior.

## How Tools Work

Each tool follows the same flow: load an oto.ini file, configure options, and run. The tool transforms the entry list and writes the result back to a file.

Tools that remove entries (Remove Duplicate, CV/VC Part Split) can send removed entries to a **second save file** instead of discarding them. Configure this in the save options.

A few tools can **modify files on disk**: Replace File Name renames WAV files, and JavaScript Scripting can do so if the script calls `renameFile()`. These tools show a confirmation dialog before committing changes.

All tools support the **preset system** — save and load option configurations as JSON. Many tools ship with built-in presets accessible from the preset dropdown.

---

## Entry Operations

Tools that add, remove, merge, or reorganize entries.

### Remove and organize duplicated entries

Detects entries whose aliases differ only by a numeric suffix (e.g., `a`, `a2`, `a3`) and either removes the excess or renumbers them sequentially. Useful when you are adding new oto entries on the fly during tuning, or duplicating entries for usability, but need to keep the numeric suffix order maintainable.

**Options:**
- **Max duplicate count** — keep at most this many duplicates (0 = no limit). Removed entries go to the second save file.
- **Organize duplicate entries** — instead of removing, renumber suffixes sequentially (e.g., `a`, `a3`, `a5` → `a`, `a2`, `a3`).
- **Affix removal** — optionally strip prefixes/suffixes before comparing aliases, then restore them on surviving entries.
- **Consider negative numbers** — treat negative numeric suffixes as duplicates too.
- **Respect original number order** (organize mode) — preserve the relative ordering of original suffixes.
- **Beginning with 1 not 2** (organize mode) — start renumbering from 1 instead of 2.
- **Pitch case** (organize mode) — use UPPER or lower case for pitch notation in renumbered aliases.

### Remove empty entries

Removes entries where all fields are blank (empty alias, zero values). These typically appear when `setParam` creates placeholder entries for WAV files that have no existing oto data. By default, entries with a negative right value are kept as a safety measure. If your oto file uses negative right by default, enable the option below to also remove those blank entries.

**Options:**
- **Ignore negative right value** — when checked, entries with `right ≤ 0` and all other fields zero are also removed.

### Merge oto

Merges entries from a second oto.ini file into the current one. Useful when you've edited a portion of an oto.ini separately and want to fold those changes back in.

**Options:**
- **Second oto file** — load the file to merge from.
- **Merge strategy:**
  - **Replace** — when aliases conflict, the incoming entry overwrites the original.
  - **Skip** — when aliases conflict, keep the original and discard the incoming entry.
  - **Keep all** — append all incoming entries regardless of conflicts.

### Extract CV/VC part

Separates CV (consonant-vowel) and VC (vowel-consonant) entries. By default, entries whose alias contains a space are classified as VC (e.g., `a k`, `a s`); those without are CV. The built-in "Universal" preset adds patterns for start oto entries (`- `, `・`) which would otherwise be misclassified as VC, and `L`-suffixed extracted vowel entries.

**Options:**
- **CV begin patterns** — treat entries whose alias begins with these texts as CV, even if they contain a space.
- **VC end patterns** — treat entries whose alias ends with these texts as VC.
- **Copy CV part to `- CV`** — copy CV entries with a `- ` prefix to create fake start oto entries, for project compatibility when you don't have separately recorded start oto samples.
- VC entries can be saved to a **second save file** for separate editing.

### Remove specific entries

Removes entries whose alias matches a given pattern.

**Options:**
- **Pattern** — the text to match against.
- **Match strategy** — Exact, Partial (substring), or Regex.
- **Case sensitive** — whether matching respects letter case.

### Copy/Replace by alias

Transforms entry aliases using find-and-replace rules. Commonly used for romaji ↔ hiragana conversion, or for reclists that reuse the same recording across multiple aliases.

**Options:**
- **Rules** — a table of find → replace pairs.
- **Behavior:**
  - **Copy** — create a new entry with the transformed alias, keeping the original.
  - **Replace** — modify the alias in place.
- **Strategy:**
  - **Match first then stop** — apply only the first rule that matches.
  - **Match all and replace** — apply all matching rules in sequence.
  - **Match all in parallel and copy** (copy mode only) — create one copy per matching rule.

---

## Value Operations

Tools that modify oto timing parameters (left, consonant, right, preutterance, overlap).

### Set overlap in batch

Sets overlap values using two strategies: fixed values for specific alias patterns, and a proportional fallback for everything else.

**Options:**
- **Set overlap as this** — assign a fixed overlap value to entries whose alias begins with specified patterns.
- **Also match `- ` prefix** — extend start-with matching to entries prefixed with `- ` (start oto entries).
- **Set overlap as 1/3** — for unmatched entries, set overlap to preutterance ÷ 3.
- **Use 1/2 when result is smaller than** — if the 1/3 result is below this threshold, use preutterance ÷ 2 instead.

### Vowel crossfading

Generates crossfading parameters for CV voicebanks. Two independent operations:

**(C)V crossfading** — sets preutterance and overlap for CV entries to specified values. Can either override the original entry or copy it with a `* ` prefix (creating a crossfaded variant).

**VV overlap increase** — for consecutive vowel transitions (e.g., `a i`), sets overlap to preutterance ÷ 2 to smooth the vowel blend.

**Options:**
- **CV list** — vowel-consonant aliases (e.g., `あ`, `a`).
- **V list** — vowel aliases.
- **Long recording patterns** — patterns using `%a` placeholder for entries that span longer audio.
- **Remove number suffix when matching** — ignore numeric suffixes during alias comparison.
- **Override original** / **Copy as `* (C)V`** — whether to modify in place or create a crossfaded copy.

### Trim around specific value

Rounds parameter values that fall within a tolerance window to an exact target value. For cleaning up values like `249.999` → `250`.

**Options:**
- **Field** — which parameter to operate on (Left, Consonant, Right, Preutterance, Overlap).
- **Target value** — the value to round to.
- **± Range** — values within this distance of the target are snapped to it.

### Convert ± right value

Converts the right bound parameter between its two representations:
- **Positive** — distance from the end of the WAV file (UTAU default for most entries).
- **Negative** — distance from the left bound (used for certain entry types).

This tool reads WAV files from disk to determine audio duration, so the audio files must be present.

**Options:**
- **Positive right (from WAV end)** / **Negative right (from left)** — conversion direction.
- **Interpret filenames by system encoding** — for Shift-JIS filename handling on non-Japanese locales.

### Pre-centered change value

Changes timing parameters while preserving the preutterance's absolute position within the audio. When you change preutterance, the left bound shifts to compensate, keeping the preutterance point fixed relative to the waveform start.

**Options:**
- Each parameter (Consonant, Preutterance, Overlap, Right) has an independent checkbox and spinbox. Only checked parameters are modified.
- **Normalize with tempo** button — a UI helper that calculates normalized values for a given tempo and populates the spinboxes.

### Tempo transform for template

Scales the timing gaps between adjacent entries within each audio file to match a different tempo. When your oto template was made at one BPM but you're using a different BGM, this rescales the note spacing.

**Options:**
- **From tempo** — the original BPM of the template.
- **To tempo** — the target BPM.
- **Offset** — a global shift applied after scaling.
- **Guess from data** button — estimates the source tempo from entry positions.

---

## Alias Operations

Tools that modify entry aliases.

### Remove prefix/suffix in alias

Strips specified text from the beginning or end of aliases. Also supports removing pitch notation (e.g., `C4`, `F#3`) from a configurable pitch range.

**Options:**
- **Remove specific prefixes** — strip matching text from the start of aliases.
- **Remove specific suffixes** — strip matching text from the end of aliases.
- **Remove pitch affix** — remove pitch notation as prefix and/or suffix.
- **Pitch range** — bottom and top note defining which pitch strings to remove.
- **Pitch case** — UPPER or lower case for pitch notation.

### Add affix (prefix/suffix)

Prepends and/or appends text to every entry's alias. Simple string concatenation — both prefix and suffix are optional.

**Options:**
- **Prefix** — text to add before each alias.
- **Suffix** — text to add after each alias.

### Set alias

Transforms aliases using a template with placeholder variables. This is the most flexible alias tool.

**Placeholders:**
- `%a` — original alias.
- `%s` — original numeric suffix (e.g., `_01`), stripped from `%a` when `%s` is used.
- `%f` — corresponding WAV filename (without `.wav` extension).
- `%r` — auto-incrementing number to de-duplicate identical aliases.

**Options:**
- **Renaming rule** — template string using the placeholders above.
- **Only apply to entries with empty alias** — skip entries that already have an alias.
- **Cut head/tail count** — remove N characters from the start or end of the result.
- **String to remove** — remove specific text (literal or regex) from the result.

---

## Filename Actions

### Replace file name (and rename file)

Applies find-and-replace rules to WAV filenames referenced in the oto.ini, then **renames the actual files on disk**. A confirmation dialog shows all pending renames before they are committed.

**Options:**
- **Rules** — find → replace pairs applied to filename basenames (extension excluded).
- **Interpret filenames by system encoding** — for Shift-JIS filename handling on non-Japanese locales.

---

## Meta Actions

Tools that compose, script, or pass through other operations.

### Perform multiple actions

Builds a sequential chain of tools. Each step's output becomes the next step's input. Useful for batch-processing workflows like "remove blanks → set overlap → trim values" in one pass.

**Options:**
- **Steps** — an ordered list of tools with their individual option configurations. Add, remove, reorder, and configure each step independently.
- Supports presets, so you can save and reuse common chains.

### JavaScript scripting

Runs user-written JavaScript to transform entries programmatically. The script has access to:
- `data` — an array of `OtoEntry` objects with all oto parameters.
- `WAVFileAPI.renameFile(fileName, newFileName)` — rename WAV files on disk.
- `WAVFileAPI.getWAVLength(fileName)` — get audio duration in milliseconds.
- `console` API — output messages shown after execution.

**Options:**
- **Script** — JavaScript source code editor.
- **Interpret filenames by system encoding** — for Shift-JIS handling.

### Adjust decimal precision

A pass-through tool that applies no transformation. Its sole purpose is to use the save options' decimal precision setting to round numeric values during file output. Use this when you only need to clean up decimal places without any other processing.

---

## Second Save File

Two tools can direct removed entries to a second output file instead of discarding them:

| Tool | What goes to the second file |
|------|------------------------------|
| Remove and organize duplicated entries | Entries removed for exceeding the max duplicate count |
| Extract CV/VC part | VC entries (when a second save path is set) |

Enable this in the save options by checking "Save to second file" and setting a path.

## Tools That Modify Files on Disk

| Tool | What it modifies |
|------|-----------------|
| Replace file name | Renames WAV files to match updated oto filenames |
| JavaScript scripting | Renames WAV files if the script calls `renameFile()` |

Both show a confirmation dialog listing all changes before they are applied.
