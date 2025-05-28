# QSfml

A demonstration of integrating SFML (Simple and Fast Multimedia Library) within a Qt5 application framework.

## About

This project showcases how to embed SFML rendering capabilities inside a Qt widget. It creates a Qt application with a main window that hosts an SFML render window, allowing for hardware-accelerated graphics rendering within a Qt GUI application.

**Note:** This is an old personal project created as a learning exercise. The code was originally written for Windows and has been adapted to build on Linux and macOS through the Makefile.

## Features

- Qt5-based main window with UI elements
- SFML render window embedded as a Qt widget
- Frame rate control (default: 120 FPS)
- Input handling through Qt events
- Cross-platform build system using Make

## Requirements

- C++11 compatible compiler (GCC, Clang, or MSVC)
- Qt5 development libraries (Qt5Core, Qt5Gui, Qt5Widgets)
- SFML 2.x development libraries
- Make build tool
- pkg-config (for automatic Qt5 configuration)

## Installation

### Ubuntu/Debian

```bash
sudo apt-get update
sudo apt-get install build-essential qt5-default libsfml-dev pkg-config
```

### Fedora/RHEL

```bash
sudo dnf install gcc-c++ qt5-qtbase-devel SFML-devel pkgconfig make
```

### macOS (using Homebrew)

```bash
brew install qt@5 sfml pkg-config
export PKG_CONFIG_PATH="/usr/local/opt/qt@5/lib/pkgconfig:$PKG_CONFIG_PATH"
```

### Windows

1. Install Qt5 from the official installer
2. Download and install SFML
3. Use MinGW or MSVC compiler
4. You may need to adjust the Makefile for Windows paths

## Building

The project uses a Makefile for building. Available commands:

```bash
# Build the project (release mode by default)
make

# Build in debug mode
make debug

# Build in release mode
make release

# Clean build artifacts
make clean

# Build and run
make run

# Show help
make help
```

The compiled executable will be placed in the `build/` directory.

## Project Structure

- `main.cpp` - Application entry point
- `MainWindow.hpp/cpp` - Qt main window implementation
- `MainWindow.ui` - Qt Designer UI file
- `QSFML.hpp/cpp` - Base class for Qt-SFML integration
- `RenderWindow.hpp/cpp` - SFML render window widget implementation
- `Makefile` - Build configuration

## Usage

After building, run the application:

```bash
./build/QSfml
```

The application will display a Qt window with an embedded SFML rendering area. The SFML area currently displays a black background and can be extended to render graphics, sprites, or other SFML content.
