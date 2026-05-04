---
name: utau-voicebank-schemes
description: UTAU voicebank recording and oto schemes — CV, VCV, CVVC, CV-VV (扩张整音), VCCV, and ending breaths (语尾息). Reference when working with tools that process aliases, split entries, or transform voicebank structure, especially for Chinese and Japanese voicebanks.
---

# UTAU Voicebank Schemes

## Overview

UTAU voicebanks come in several recording and oto.ini configuration schemes, each trading off recording effort against synthesis smoothness.

**Important:** UTAU's file formats and alias conventions are **community conventions, not rigid specifications**. There is no formal standard — conventions evolved organically and vary across languages, voicebank creators, and eras. Pitch can be annotated as a suffix (`a かC4`), a prefix (`C4_あ`), or embedded in the filename. Expression/appends systems vary by creator (強/弱, soft/power, etc.). oto.ini is traditionally **Shift-JIS encoded**.

KiraOtoToolbox tools are designed to be convention-agnostic at their core. Where presets exist (like `copyOrReplaceByAlias`'s Syo式→十月式 preset), they target specific de facto standards, but the underlying logic treats aliases and filenames as arbitrary strings and numeric parameters as raw values.

For the field-level format reference, see `.claude/skills/oto-file-format.md`.

---

## Recording / Oto Schemes

### CV — Solo-tone (単独音)

The original and simplest scheme. Each recording captures one consonant-vowel syllable (e.g., か ka, き ki, く ku). The oto entry's fixed region (Consonant) covers the consonant, and the stretchable vowel region starts from the vowel onset.

**Characteristics:**
- Smallest recording set (Japanese: ~50-60 recordings)
- Disjoint transitions between notes — no cross-synthesis smoothing

**oto pattern for vowels and ん (あ, い, う, え, お, ん):**

Note: ん is the moraic nasal — not a vowel phonetically, but it behaves as a full mora in Japanese phonology and follows the vowel oto pattern.

```
Left = waveform start
Overlap = 0
PreUtterance = consonant-vowel boundary (or 0 if no leading consonant)
Consonant = where waveform stabilizes
Right = where waveform stabilizes at end
```

**oto pattern for stops (か, た, ぱ rows):**
```
Left = slightly before waveform start (~0.5-1 consonant length before)
Overlap = 0 (then manually set negative for stops)
PreUtterance = consonant-vowel boundary (where waveform grows larger)
Consonant = where waveform stabilizes
Right = where waveform stabilizes at end
```

**oto pattern for remaining consonants:**
```
Left = waveform start
Overlap = one-third of Left-to-PreUtterance range
PreUtterance = consonant-vowel boundary
Consonant = where waveform stabilizes
Right = where waveform stabilizes at end
```

The key difference across the three sub-patterns is Left placement and Overlap handling. Stops need extra space before the waveform and negative overlap. Non-stop consonants use proportional overlap. Vowels have no leading consonant to account for.

### VCV — Continuous-tone / Triphones (連続音)

Records strings of connected mora pairs. For example, the reclist line `_かんかかきかくか` (the leading `_` signals silence/rest at the phrase start) is a single 8-mora recording (か-ん-か-か-き-か-く-か). Each boundary between morae becomes a VCV entry by splitting at the transition point — the tail vowel of the preceding mora becomes the leading vowel, and the head consonant+vowel of the following mora becomes the target:

```
Recording:  [か] [ん] [か] [か] [き] [か] [く] [か]
oto split:  - か | n か | a か | a き | i か | a く | u か
            ^     ^      ^      ^      ^      ^      ^
            rest→か  ん→か   か→か   か→き   き→か   か→く   く→か
```

Each split point captures the transition between two connected sounds. A single recording thus yields multiple oto entries.

**Alias format:** `{leading vowel} {target kana}{pitch}` — e.g., `a かC3`, `i きC3`. The leading character `-` (dash) indicates rest/silence (phrase start). A word like "aRiGaTo" is covered by entries `- あ`, `a り`, `i が`, `a と`. The leading vowel of each entry overlaps with the trailing vowel of the previous entry.

**Key oto.ini principle:** The Pre-utterance boundary splits the recording so the leading vowel portion is borrowed from the *previous* note. The Consonant boundary marks the end of the consonant transition. The stretchable vowel begins at Consonant.

**Characteristics:**
- Very smooth transitions — gold standard for natural synthesis
- Large recording set (Japanese: typically 100-200+ recordings)
- Higher recording effort and disk space
- Each entry needs the preceding vowel context

### CVVC — Consonant-Vowel + Vowel-Consonant

A hybrid scheme that records both CV (forward) and VC (backward) parts. Instead of recording full triphones like VCV, CVVC composes smooth transitions by concatenating:
- The CV part: the consonant-vowel transition (like solo-tone)
- The VC part: the vowel-to-consonant closing (coda transition)

**Structure:** A CVVC voicebank contains both CV entries (e.g., `か`) and VC entries (e.g., `a k`, `i k`, `u k`). When synthesizing a sequence like "a ka", UTAU uses the `a k` VC entry to provide the closing transition from /a/ into /k/, then the `か` CV entry for the opening.

**Why CVVC exists:** It achieves VCV-like smoothness with significantly fewer recordings than full VCV. Japanese CVVC: ~120-150 recordings vs VCV's ~200+. The VC entries are shared across all CV entries with the same consonant.

**oto.ini for VC entries:** The fixed region covers the vowel-to-consonant transition. The Pre-utterance position is set within the VC recording to control how much of the preceding vowel is heard.

**In our tools:** The `cvvcPartSplit` tool directly operates on CVVC-structured entries to split them into CV and VC parts.

### CV-VV / 拡張整音 (Expanded Solo-tone) — Chinese

**The problem:** UTAU's oto system was designed for Japanese, which has no coda consonants (韵尾) except ん. The system has no "post-fixed region" (後固定) concept — the Consonant only marks a *leading* fixed region. For languages like Chinese, syllables have coda consonants (e.g., -n in "an", -ng in "ang") that must NOT be stretched the way the main vowel is, but they come at the *end* of the syllable.

Since the coda sits in the stretchable vowel region (Consonant to Right) with no post-fixed region to protect it, the resampler treats it as stretchable material. Depending on the resampler and the note length, the coda may be stretched shorter, stretched longer, or truncated — all of which sound unnatural. The behavior is resampler-dependent and therefore unpredictable.

**The CV-VV solution:** Split the syllable into two entries, forcing stable behavior through the oto boundaries themselves rather than leaving it to the resampler:
1. **CV part** (e.g., `lan`) — the consonant + main vowel. The Right Blank is deliberately set before the coda starts, cutting it off deterministically. The stretchable region covers only the main vowel, which handles note-length changes predictably.
2. **VV part** (e.g., `_an`) — the coda, added back as a separate entry. The fixed region (Consonant) covers the transition from the vowel into the coda, and the stretchable region covers the coda body. In practice, the Consonant boundary is often set so the coda body isn't stretched.

**In UTAU usage:** A note `lan` is split into two sub-notes: `lan` + `_an`, with their lengths adjusted so the main vowel fills the note and the coda provides the natural ending.

**Historical note:** 王芳梅 and Syo式 (Syo style) are earlier or independently-developed CV-VV variants by different creators. They use different alias formats with fewer total entries than 扩张整音 because they reuse common CV prefixes — a single `ka` entry can serve for `kan`, `kang`, `kai` etc., since the CV portion sounds identical and only the VV part differs. In modern practice, all three are treated as the same underlying approach and collectively referred to as 扩张整音 (or CVV in OpenUTAU).

**oto.ini setup for Chinese:**
- Main vowel entries: Consonant covers the entire glide (介母/韵头), Right cuts before the coda
- Coda entries (`_ang`, `_an`, etc.): PreUtterance = 70, Consonant = 50, with PreUtterance placed at the vowel-coda boundary

### VCCV — English (Cz method)

Cz's VCCV is the de facto standard for English UTAU voicebanks. Derived from CVVC but adapted for English's consonant-heavy phonology.

**Key differences from CVVC:**
- Three types of VC entries, distinguished by suffix: `VC` (standard), `VC-` (stop release), `V C` (cluster transition)
- CCV clusters are split into `CC` and `_CV` rather than recording the full cluster
- 1066 recordings, 3429 oto lines in the standard reclist
- Base oto is provided — recording according to Cz's tutorial eliminates manual oto work

**Critical oto rule:** Overlap must always be half of Pre-utterance (`Overlap = PreUtterance / 2`). This is stricter than the Japanese 1/3 guideline.

**Phonetic system:** Uses a custom set of phonetic symbols (not X-SAMPA or Arpabet) designed to be intuitive to read.

---

## Supplementary Conventions

### Ending Breaths — 語尾息

A de facto community standard for giving a phrase a natural ending decay. Ending breath entries are aliased with a trailing "R" (standing for **rest note** / 休止符) and are applied to rest notes at the end of a phrase (e.g., `a R`, `ang R`).

**Standard oto values:**
```
PreUtterance = 250, Overlap = 83 (1/3 rule)
PreUtterance = 300, Overlap = 100
```
PreUtterance is placed at the end of the vocalization (or at the breath start if the recording includes breathing).

**Role in Chinese synthesis:** Ending breaths serve double duty — they provide the natural phrase-ending decay AND restore the coda consonant that would otherwise be missing at the end of a phrase. For example, at the end of a phrase ending in "ang", the user would place `ang R` on a rest note after the main `ang` + `_ang` sequence. In CVVC and VCV schemes, coda restoration is handled mid-phrase by the VC part, so ending breaths are only needed at phrase boundaries.

---

## Voicebank Organization

### Multi-Pitch — 多音階 (Multi-tone Scale)

UTAU supports recording the same voicebank at multiple pitches for better range coverage. Instead of stretching a single recording across the entire vocal range (which sounds unnatural at extremes), each pitch covers a sub-range.

**prefix.map format:** A tab-separated file where each line maps a MIDI note name to the pitch suffix that UTAU should append to aliases when that note is encountered. Every semitone is listed explicitly (C1 through B7). Example from a 3-pitch voicebank (C3, F3, A#3):

```
C3  → C3     (notes D3–E3 also → C3)
F3  → F3     (notes F#3–G#3 also → F3)
A3  → A#3    (notes A#3–B7 all → A#3)
```

UTAU finds the matching note name and appends the suffix to the alias being looked up. So a note at C4 resolves to suffix `A#3`, transforming the search from `a か` to `a かA#3`.

**OpenUTAU:** Uses a completely different system — `character.yaml` (YAML format). This defines subbanks, voice colors, phonemizers, encoding, and pitch ranges in a structured schema. Our tools do not process either prefix.map or character.yaml, but understanding the suffix convention is useful for tools that manipulate aliases.

**Recording layout:** Each pitch is recorded as a separate folder within the voicebank, or all WAVs are placed in one folder with pitch suffixes in the filenames. Common pitch spacing: 3-5 semitones between recorded pitches.

**Single-pitch banks:** Voicebanks with only one recorded pitch typically do NOT use pitch suffixes in aliases. The absence of a suffix is itself the convention — the alias is just the plain entry name like `a か`.

**Appends / Voice Colors / 表情音:** Beyond pitch, the prefix.map mechanism also supports alternative expressions (soft, power, whisper, etc.). These use additional prefixes or suffixes (e.g., `a か強`, `a か弱`). The prefix.map selects both pitch and expression simultaneously.

---

## Scheme Comparison

| Scheme | Recordings | Smoothness | Languages | Recording Effort |
|---|---|---|---|---|
| CV (単独音) | ~50-60 | Disjoint | Japanese (original) | Low |
| VCV (連続音) | ~100-200+ | Very smooth | Japanese, some others | High |
| CVVC | ~120-150 | Smooth | Japanese, Chinese, Korean | Medium |
| CV-VV (拡張整音) | ~80-100 | Smooth with coda | Chinese | Medium |
| VCCV | ~1066 | Smooth | English (adaptable) | Very High |

## How This Relates to Our Tools

For the field-level mapping (how tools interact with Left/Consonant/Right/PreUtterance/Overlap/Alias), see the Relevance section in `.claude/skills/oto-file-format.md`. Scheme-specific concerns:

- **cvvcPartSplit**: Identifies CV vs VC entries by alias format (space-separated vs. plain). Must understand VC alias conventions (`a k`, `i k`) and the begin/end pattern matching for CV identification.
- **copyOrReplaceByAlias**: Contains a built-in preset for Syo式→十月式 scheme migration (CV aliases expanded for CV-VV splitting). Rules map `ba→ban`, `bang→bao`, `bie→bian`, etc.
- **mergeOto**: Merges voicebank folders — must handle different schemes coexisting and alias conflicts across schemes.
- **vowelCrossfading**: CVList/VList pattern matching against VCV-style aliases. `removeNumberSuffixWhenMatching` strips digit suffixes for cross-scheme compatibility.
- **removeAffix / addAffix / setAlias**: Alias manipulation used for pitch suffix management, scheme conversion, and alias normalization.
- **CV-VV multi-entry dependency**: `removeDuplicate`/`removeBlank` must not break paired entries like `lan` + `_an` that are required for CV-VV to function.
