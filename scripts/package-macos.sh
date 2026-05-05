#!/usr/bin/env bash
#
# Build a DMG installer for KiraOtoToolbox on macOS.
# Requires: create-dmg (brew install create-dmg)
#
set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
PROJECT_DIR="$(cd "$SCRIPT_DIR/.." && pwd)"

ARTIFACT_DIR="$PROJECT_DIR/build/artifact"
APP_BUNDLE="$ARTIFACT_DIR/KiraOtoToolbox.app"

if [[ ! -d "$APP_BUNDLE" ]]; then
    echo "Error: $APP_BUNDLE not found."
    echo "Run 'cmake --install build' first."
    exit 1
fi

# Extract version from CMakeLists.txt
VERSION=$(sed -n 's/^project(KiraOtoToolbox VERSION \([^ )]*\).*/\1/p' "$PROJECT_DIR/CMakeLists.txt")
if [[ -z "$VERSION" ]]; then
    echo "Error: Could not extract version from CMakeLists.txt"
    exit 1
fi

DMG_OUTPUT="$PROJECT_DIR/build/KiraOtoToolbox-${VERSION}.dmg"

# Copy LICENSE into the artifact directory so it appears in the DMG
cp "$PROJECT_DIR/LICENSE" "$ARTIFACT_DIR/LICENSE"

# Remove any previous DMG (create-dmg fails if it already exists)
rm -f "$DMG_OUTPUT"

create-dmg \
    --volname "KiraOtoToolbox" \
    --volicon "$PROJECT_DIR/resources/icon/appIcon.icns" \
    --icon "KiraOtoToolbox.app" 140 200 \
    --app-drop-link 400 200 \
    --eula "$PROJECT_DIR/LICENSE" \
    --hide-extension "KiraOtoToolbox.app" \
    --window-size 600 400 \
    --icon-size 80 \
    "$DMG_OUTPUT" \
    "$ARTIFACT_DIR"

echo ""
echo "DMG created: $DMG_OUTPUT"
