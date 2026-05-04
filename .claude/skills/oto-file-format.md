---
name: oto-file-format
description: Domain knowledge about UTAU oto.ini file format — what each field means, how they interact in voice synthesis, and how they map to the OtoEntry type. Reference this when working with oto entry processing, especially for tools that modify left/consonant/right/preUtterance/overlap values.
---

# oto.ini File Format

## Overview

oto.ini is the voicebank configuration file format used by UTAU, a singing voice synthesis engine. Each line defines one "voice block" — a slice of a WAV file that UTAU uses to synthesize a specific syllable or phoneme.

For how these fields are used across different voicebank schemes (CV, VCV, CVVC, CV-VV, VCCV), see `.claude/skills/utau-voicebank-schemes.md`.

**On-disk format:**
```
[filename].wav=alias,left,consonant,right,preUtterance,overlap
```

**Encoding:** oto.ini is traditionally **Shift-JIS encoded**. Our codebase uses `QTextCodec` (via Qt Core5Compat) for reading and writing Shift-JIS oto files. Some modern tools also use UTF-8. When writing tests, be aware that alias and filename strings may contain multi-byte characters.

**In our codebase:** `OtoEntry` (defined in `src/otoUtils/OtoEntry.h`) holds these six fields plus the filename. `OtoEntryList` = `QList<OtoEntry>`.

## The Six Fields

All numeric values are in **milliseconds**, relative to the WAV file's sample timeline. Some fields accept negative values: Overlap is commonly negative for stop consonants (creating a silence gap); PreUtterance and Right may occasionally be negative depending on voicebank conventions. Negative values shift the boundary in the opposite timeline direction.

### Left (左边界)
Where this voice block **starts** in the WAV file. Everything before this point in the WAV is ignored for this entry.

### Right (右边界)
Where this voice block **ends** in the WAV file. Everything after this point is ignored.

Left and Right together define the usable slice of the WAV sample.

### Consonant / Fixed (固定)
The boundary between the **unstretched** region and the **stretchable** region. The span from Left to Consonant is NOT stretched during synthesis (unless the user explicitly sets consonant velocity). The span from Consonant to Right should be a stable vowel region suitable for looping/stretching.

**What goes in the fixed region:**
- The consonant itself
- The consonant-to-vowel transition
- Diphthong glides / on-glides (e.g., the `i` in Chinese `bie`, or the `w`-glide in English `we`)
- Anything at the start of the sound that should NOT get longer when the note gets longer

**Critical implication for tools:** If a note's computed vowel length ends up shorter than the fixed region, UTAU truncates the fixed region and discards the stretchable region entirely. This means moving the Consonant value changes which part of the audio is considered "stable vowel" vs "transitional."

### Pre-utterance (先行发声)
The point within this voice block where the **note actually begins**. The portion from Left to Pre-utterance is borrowed from the **previous** note's time slot.

**Why this exists — rhythm alignment:** Human listeners perceive rhythm beats at **consonant-end / vowel-start** boundaries (the syllable nucleus onset). But different consonants have different lengths. If the entire consonant sat inside its own note, the vowel onset would land at `note_start + consonant_length`, which varies per consonant — breaking rhythmic alignment. By placing the consonant in the *previous* note's tail (via Pre-utterance), the vowel onset always aligns with the note start.

**Typical placement:** Pre-utterance is usually set at or near the end of the consonant, i.e., close to the Consonant value. The Left-to-PreUtterance region is the "borrowed" prefix.

### Overlap (重叠)
The length of the **crossfade** between the end of the previous note and the consonant of this note. During this region, both notes sound simultaneously and are crossfaded.

**Why this exists:** In real singing, consonants and vowels have natural overlap transitions. Overlap simulates this by blending the tail of the previous note with the head of the current note.

**Negative overlap:** Creates a small **gap** (silence) before the consonant. This is used to simulate stop consonants (e.g., /p/, /t/, /k/) and affricates, where there's a brief closure/silence before the release.

**In coordinates:** Overlap is measured from the end of the previous note backward. The overlap region starts at `previous_note_end - overlap` and ends at `previous_note_end + (PreUtterance - Left)` for the current note.

### Alias (别名)
The lyric string the user types in UTAU's note editor to invoke this voice block. Called "alias" because it *replaces* the WAV filename as the lookup key.

If no alias is set (empty string), UTAU falls back to matching by filename.

## Coordinate Diagram

The diagram below shows how the six fields relate spatially on the WAV timeline and how they map to the UTAU note timeline during synthesis:

```
WAV file timeline for one entry:
|-------[Left]-------[PreUtterance]---[Consonant]--------------[Right]------|
        |<-- borrowed -->|<-- fixed,   -->|<-- stretchable vowel -->|
        |  by prev note  |   unstretched  |                          |
        
Note timeline (how it sounds in UTAU):
[prev note end - Overlap]...[prev note end]|[note start = PreUtterance point]...[note end]
                          |<-- crossfade -->|<-- this note's audible portion -->|
```

## Relevance to Our Tools

UTAU's oto system was designed for **solo-tone (单独音)** synthesis — each voice block is a complete syllable, with a single Consonant→Right stretchable vowel region and no post-fixed region for coda consonants (see `.claude/skills/utau-voicebank-schemes.md` for how CV-VV works around this). Pre-utterance happens to support continuous-tone schemes (VCV, CVVC) by letting the consonant borrow time from the previous note. Three assumptions shape all oto tool design:

1. There is a single stable vowel region (Consonant to Right) suitable for stretching
2. The fixed region contains transitional material that shouldn't stretch
3. The consonant belongs rhythmically to the *previous* note, not its own note

- **Value operation tools** (overlapBatchSet, tempoTransform, preCenteredChangeValue, etc.) modify Left, Consonant, Right, PreUtterance, or Overlap — understanding the semantic meaning of each field is essential for correct transformations
- **Entry operation tools** (removeDuplicate, removeBlank, mergeOto, etc.) add, remove, or reorganize entries — they operate on the list structure rather than individual field values
- **Alias operation tools** (addAffix, removeAffix, setAlias) modify the Alias field — they need to understand alias naming conventions (pitch prefixes/suffixes, number suffixes, etc.)
- **Filename tools** (replaceFileName) rename the WAV files and update references
- When a tool shifts PreUtterance, it's changing rhythm timing; when it shifts Consonant, it's changing what counts as "fixed" vs "stretchable"
