<!-- markdownlint-configure-file {"MD024": { "siblings_only": true } } -->

# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.1.0/), and this project
adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [Unreleased]

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

[unreleased]: https://github.com/Tatsh/freeband/compare/v0.0.1...HEAD
