<p align="center">
  <img src="assets/stowaway.svg" width="140" alt="Stowaway Logo">
</p>

<h1 align="center">Stowaway</h1>

**Stowaway** is a lightweight Wayland clipboard manager and emoji/character picker overlay for the **AstraSuite** ecosystem, built with Qt 6 and QML.

## Features

- Dynamic cursor-anchored overlay with boundary clamping and edge flipping
- Rich clipboard history with auto-categorization (Text, Code, URLs, Colors, Images)
- Persistent JSON storage with pinning support
- Unicode emoji picker with fuzzy search
- Kaomoji and Unicode symbol pickers
- Auto-paste via `wtype`
- Material 3 Expressive UI with Caelestia color palette integration

## Dependencies

### Build

- C++20 compiler (GCC 11+ or Clang 14+)
- CMake 3.19+
- Ninja
- pkg-config
- Qt 6.5+ (Core, Qml, Quick, QuickControls2, QuickEffects, Svg)

### Runtime

- `qt6-base`, `qt6-declarative`, `qt6-svg`
- `quickshell`
- `wtype` (for auto-paste)

### Optional

- `caelestia-cli`: dynamic color palette and accent syncing

## Installation

### Arch Linux / AUR

```bash
# Release (builds from source)
paru -S astra-stowaway

# Latest git development
paru -S astra-stowaway-git
```

### Manual Installation (From Source)

```bash
cmake -B build -S . -DCMAKE_BUILD_TYPE=Release
cmake --build build
sudo cmake --install build
```

This installs the `stowaway` binary to `/usr/bin/stowaway`.

## Usage

```bash
stowaway --toggle           # Toggle clipboard overlay anchored beside cursor
stowaway --emoji            # Open the emoji picker
stowaway --kaomoji          # Open the kaomoji picker
stowaway --symbols          # Open the symbols picker
stowaway --width 480        # Set popup width in pixels
stowaway --height 620       # Set popup height in pixels
stowaway --size 480x620     # Set popup dimensions (WxH)
stowaway --scale 1.25       # Set UI scaling factor (scales text, icons, cards)
stowaway --reset-size       # Reset popup dimensions and scale to default (390x500, 1.0x)
stowaway --clear            # Clear unpinned clipboard history
stowaway --hide             # Hide open clipboard overlay
```

### Sizing & UI Scaling

Stowaway provides full control over window dimensions and content scaling (fonts, icons, card sizes, and padding):

1. **Keyboard Shortcuts & Zooming**:
   - `Ctrl` + `+` or `Ctrl` + `=`: Enlarge popup size and zoom in UI scale (increases font and icon sizes)
   - `Ctrl` + `-`: Shrink popup size and zoom out UI scale (decreases font and icon sizes)
   - `Ctrl` + `0`: Reset popup size and scale to default (390x500, 1.0x)

2. **Configuration File**:
   Specify custom dimensions and UI scale in `~/.config/caelestia/stowaway.json` or `~/.config/stowaway/config.json`:
   ```json
   {
     "width": 480,
     "height": 620,
     "scale": 1.25
   }
   ```
   Or integrate into `~/.config/caelestia/shell-tokens.json`:
   ```json
   {
     "scale": 1.25,
     "sizes": {
       "stowaway": {
         "width": 480,
         "height": 620
       }
     }
   }
   ```

3. **Command-Line & Environment Variables**:
   - Launch with `-W <width>` / `-H <height>`, `--size <WxH>`, and `--scale <factor>` (e.g. `--scale 1.3`).
   - Or set `STOWAWAY_WIDTH`, `STOWAWAY_HEIGHT`, and `STOWAWAY_SCALE` environment variables.

### Hyprland Animations

Add to `~/.config/caelestia/hypr-user.lua`:

```lua
hl.layer_rule({
    match = {
        namespace = "stowaway",
    },
    no_anim = true,
})

```

## Credits and Licensing

This project is licensed under the GNU General Public License v3.0 (GPLv3).

Stowaway incorporates design tokens, QML components, and styling derived from [Caelestia Shell](https://github.com/caelestia-dots/shell).
