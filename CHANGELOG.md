<!-- markdownlint-configure-file {"MD024": { "siblings_only": true } } -->

# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.1.0/), and this project
adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [Unreleased]

### Added

- The game now has a launcher icon on all three platforms. The Windows `freeband.exe` embeds the
  icon as a Win32 resource so it shows in Explorer, the Start Menu, the taskbar, and Alt-Tab. The
  macOS `Freeband.app` bundle ships a multi-resolution `Freeband.icns` referenced from
  `CFBundleIconFile`, so Finder, the Dock, and the App Switcher render the icon. On Linux, an XDG
  `sh.tat.freeband.desktop` launcher and a matching `sh.tat.freeband.png` hicolor icon are now
  installed by CMake itself, so distribution packages (Snap, Flatpak, distro), AppImage builds, and
  manual `make install` all gain a launcher entry without per-packager scripting.
- Windows `freeband.exe` now carries full Win32 VERSIONINFO metadata (FileVersion, ProductVersion,
  CompanyName, FileDescription, ProductName, OriginalFilename, LegalCopyright), so the Explorer
  Properties pane and antivirus inspectors show real values rather than the previous unset
  defaults.

### Changed

- The Linux launcher entry has been renamed from `freeband.desktop` to `sh.tat.freeband.desktop`
  and the icon basename from `freeband` to `sh.tat.freeband`. The reverse-DNS name matches the
  Flatpak app-id and the macOS `CFBundleIdentifier`, and satisfies Flatpak's strict requirement
  that the exported desktop file name match the app-id.

## [0.0.2] - 2026-05-05

### Added

- Windows NSIS installer creates a Start Menu shortcut for `Freeband`, offers an opt-in Desktop
  shortcut checkbox during install, and shows a 'Run Freeband' checkbox on the finish page so the
  game can be launched directly from the installer.
- Windows x86-64 build (UCRT64) is now published alongside the existing 32-bit (MinGW32) and ARM64
  (ClangARM64) Windows artefacts. The v0.0.1 release matrix had the 64-bit rows excluded from
  publishing, so a native Windows x64 binary is shipped here for the first time. UCRT64 supersedes
  MinGW64 for x86-64 because it links against the universal C runtime that ships with Windows 10
  and later.

### Changed

- Windows packages now bundle their runtime DLLs via CMake's recursive runtime dependency walker,
  which resolves indirect dependencies that the previous regex-include filter could miss. Windows
  API set DLLs (`api-ms-`, `ext-ms-`, `kernel32.dll`) and anything under `system32/` are explicitly
  excluded so OS-supplied DLLs are never copied into the package. The walker now applies under any
  Windows toolchain (MinGW32, UCRT64, ClangARM64, and MSVC via vcpkg's app-local deployment),
  rather than the MinGW-only path used before.
- User-visible references to the game now use the branded title `Freeband` (capital `F`)
  consistently. This affects the macOS bundle (`Freeband.app`, `CFBundleName`, and
  `CFBundleDisplayName`), the Snap Store title, the Linux AppImage `.desktop` `Name=` field, the
  Windows installer's product name, install directory under `%LOCALAPPDATA%\Programs\Freeband`,
  Start Menu folder, Add/Remove Programs entry, and the `ProductName`/`FileDescription` resource
  strings in `freeband.exe`. Technical identifiers (binary filename, package IDs, URLs, bundle
  identifier, executable command) remain lowercase.

## [0.0.1] - 2026-05-04

### Added

- Windows NSIS installer with per-user (`$LOCALAPPDATA\Programs`) installation, generated via CPack.
- AppImage build for Linux x86_64.
- Flatpak packaging (`sh.tat.freeband`) for `x86_64` and `aarch64`.
- Snap packaging (strict-confined, `core24`) for `amd64` and `arm64`.
- macOS self-contained `.app` bundle distributed as a DMG and ZIP, for Intel and Apple Silicon.
  Minimum deployment target is macOS 10.13 (High Sierra) for Intel and macOS 11.0 (Big Sur) for
  Apple Silicon, matching the floors supported by Xcode 16.
- 32-bit Windows build targets Windows 2000 (`_WIN32_WINNT=0x0500`); 64-bit and ARM64 builds also
  produced.

### Changed

- The binary now locates its bundled data directory relative to its own path on Linux, macOS, and
  Windows. Running `/usr/bin/freeband` after a system install, double-clicking the macOS `.app`
  bundle, and double-clicking `freeband.exe` from the Windows install directory all work without a
  launcher wrapper or a specific working directory.
- Windows packages bundle their required runtime DLLs (SDL, freeglut, sndfile, portaudio, image
  codecs, MinGW C runtime), so the installer is self-contained.
- `vcpkg.json` now lists `freeglut`, `libsndfile`, `portaudio`, and `sdl12-compat` in addition to
  `sdl1`. SDL1 image and TTF ports are not in vcpkg and remain unlisted.

[unreleased]: https://github.com/Tatsh/freeband/compare/v0.0.2...HEAD
[0.0.2]: https://github.com/Tatsh/freeband/compare/v0.0.1...v0.0.2
