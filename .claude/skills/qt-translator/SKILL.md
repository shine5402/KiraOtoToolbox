---
name: qt-translator
description: Know how to translate Qt's translation files (.ts) into different languages
---

## What is a .ts file in Qt?

Translation files in Qt are stored in XML format with the .ts extension. These files contain the original text and its translations for different languages. The structure of a .ts file includes contexts, messages, and various metadata. Each context represents a group of messages, and each message contains the source text, its translation, and optional comments for translators.

For more information on the .ts file format, see [this reference](./ts-format-reference.md).

## Where to find .ts files in a Qt project?

For projects using cmake and opt-in using the standard qt_add_translations() cmake function, the .ts files are located as the TS_FILE_DIR argument passed to qt_add_translations(), and is named after "${TS_FILE_BASE}_${lang}.ts", where if no TS_FILE_BASE is provided, the default base name is the PROJECT_NAME.

Typically, a project would organize the .ts files in a "translations" or "i18n" folder under the project root directory, but it can be configured differently by the project maintainers. You can check the CMakeLists.txt file of the project to find out where the .ts files are located.

## Guidelines when editing .ts files

When editing .ts files, please make sure to keep the XML structure intact, and only modify the text content of the <source> and <translation> tags. 

Unless user explicitly ask you to retranslate the whole .ts file, you should only translate the messages that are not translated yet (i.e. those with empty <translation> tags), or those that are marked as "unfinished" (i.e. those with <translation type="unfinished">). To make review process easier, unless explicitly asked by the user, you should not change the finished status of a message after you translate it, so it can be left to the user or other agents to review/proofread the translation and mark it as finished. You can also add comments in the <translatorcomment> tag to explain your translation choices or to ask for review on certain translations. 

You may met html contents in .ts files, which can be used to format the text in the UI. When translating, you should keep the html structure intact, and only modify the text content. Special characters in html (like <, >, &, etc.) should be properly escaped.

For those projects with qt_add_translations(), a update_translations target is generated, which can be used to update the .ts files with new source strings from the codebase. It will call lupdate and lrelease tool under the hood, and will report any errors encountered during the process. When doing translations, you should try to run the update process to check if the .ts files are still in the correct format, and also to update the .ts files with new source strings if you just started translating.

.ts files tends to be very long and contain many messages, so it can be overwhelming to translate the whole file at once. **NEVER** read the whole .ts file without any range limit!! You can break down the translation task into smaller chunks, for example by translating one context at a time, or by translating a certain number of messages at a time. This way, you can focus on a smaller set of messages and ensure better quality of translation.