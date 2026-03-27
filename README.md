# Brickstortion (JUCE VST3)

Brickstortion is een FL Studio-compatible VST3 distortion plugin gebouwd met JUCE.

## Features

- Distortion On/Off (automatable)
- Goofy Mode (automatable) met extra wobble/bitcrush-randje
- **Brick Drive** hoofdcontrol (automatable) met custom brick/isometric look
- Extra controls: Tone, Mix, Output, Character
- Modulaire scheiding tussen:
  - audio engine (`/Source/Audio`)
  - parameter model (`/Source/Parameters`)
  - UI componenten (`/Source/UI`)
  - asset/theme systeem (`/Assets` + `Theme`)

## Build instructions

### Vereisten

- CMake 3.22+
- C++17 compiler
- JUCE 8 (automatisch via FetchContent, of via `JUCE_DIR`)

### Windows (Visual Studio)

```powershell
cd <project-root>
cmake -S . -B build -G "Visual Studio 17 2022" -A x64
cmake --build build --config Release
```

VST3 output staat na build in de gegenereerde `VST3` outputmap van JUCE (en met `COPY_PLUGIN_AFTER_BUILD` vaak direct in de lokale VST3-map).

### macOS

```bash
cd <project-root>
cmake -S . -B build
cmake --build build --config Release
```

## Installer / packaging workflow

Er is een basis CPack-setup toegevoegd:

```bash
cmake --install build --config Release --prefix ./package
cpack --config build/CPackConfig.cmake
```

- Dit maakt standaard een ZIP package.
- Op Windows wordt ook NSIS geprobeerd als NSIS beschikbaar is.

Voor een volledige Windows-installatie (met uninstaller) is er een Inno Setup-script beschikbaar in `installer/Brickstortion.iss`. De GitHub Actions workflow bouwt automatisch de VST3 (Release, Ninja), maakt de Inno Setup installer (`Brickstortion-Setup-<versie>.exe`) die naar `C:\Program Files\Common Files\VST3\Brickstortion.vst3` installeert, en publiceert deze als artefact en release asset op tags (`v*`).

## Assets / skin / theme vervangen

- Standaard asset map: `/Assets`
- Het theme-systeem zit in `Source/UI/Theme.*`
- Je kunt later sprites/afbeeldingen toevoegen in `/Assets` en in UI componenten (`BrickSlider`, editor panels, knoppen) ophalen via:

```cpp
auto image = theme.getAsset("my-brick.png");
```

Daardoor kun je visuals vervangen zonder de audio-engine (`Source/Audio`) te wijzigen.
