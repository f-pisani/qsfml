# QSfml Makefile
# A Qt5 application with SFML integration

# Detect OS
UNAME_S := $(shell uname -s)

# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++11 -Wall -fPIC
MOC = moc
UIC = uic

# Platform-specific settings
ifeq ($(UNAME_S),Linux)
    # Linux uses X11 window handles
    CXXFLAGS += -DHWND='unsigned long long'
endif
ifeq ($(UNAME_S),Darwin)
    # macOS
    CXXFLAGS += -DHWND='void*'
endif

# Qt5 configuration
QT_CFLAGS = $(shell pkg-config --cflags Qt5Core Qt5Gui Qt5Widgets)
QT_LIBS = $(shell pkg-config --libs Qt5Core Qt5Gui Qt5Widgets)

# SFML configuration
SFML_LIBS = -lsfml-graphics -lsfml-window -lsfml-system

# Include paths
INCLUDES = $(QT_CFLAGS)

# Source files
SOURCES = main.cpp \
          MainWindow.cpp \
          QSFML.cpp \
          RenderWindow.cpp

HEADERS = MainWindow.hpp \
          QSFML.hpp \
          RenderWindow.hpp

FORMS = MainWindow.ui

# Object files
OBJECTS = $(SOURCES:.cpp=.o)
MOC_HEADERS = MainWindow.hpp QSFML.hpp
MOC_SOURCES = $(addprefix moc_,$(MOC_HEADERS:.hpp=.cpp))
MOC_OBJECTS = $(MOC_SOURCES:.cpp=.o)
UI_HEADERS = ui_$(FORMS:.ui=.h)

# Build directory
BUILD_DIR = build

# Target executable
TARGET = $(BUILD_DIR)/QSfml

# Build type (debug or release)
BUILD_TYPE ?= release

ifeq ($(BUILD_TYPE),debug)
    CXXFLAGS += -g -O0
    SFML_LIBS = -lsfml-graphics-d -lsfml-window-d -lsfml-system-d
else
    CXXFLAGS += -O2
endif

# Main target
all: $(UI_HEADERS) $(BUILD_DIR) $(TARGET)

# Create build directory
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Link the executable
$(TARGET): $(addprefix $(BUILD_DIR)/,$(OBJECTS)) $(addprefix $(BUILD_DIR)/,$(MOC_OBJECTS))
	$(CXX) $^ -o $@ $(QT_LIBS) $(SFML_LIBS)

# Compile source files
$(BUILD_DIR)/%.o: %.cpp $(UI_HEADERS) | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# Generate UI headers
ui_%.h: %.ui
	$(UIC) $< -o $@

# Generate MOC sources
moc_%.cpp: %.hpp
	$(MOC) $< -o $@

# Compile MOC sources
$(BUILD_DIR)/moc_%.o: moc_%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# Clean build artifacts
clean:
	rm -rf $(BUILD_DIR)
	rm -f $(MOC_SOURCES)
	rm -f $(UI_HEADERS)

# Run the application
run: all
	./$(TARGET)

# Debug build
debug:
	$(MAKE) BUILD_TYPE=debug

# Release build
release:
	$(MAKE) BUILD_TYPE=release

# Help
help:
	@echo "QSfml Makefile"
	@echo ""
	@echo "Targets:"
	@echo "  all      - Build the project (default)"
	@echo "  run      - Build and run the application"
	@echo "  debug    - Build with debug symbols"
	@echo "  release  - Build with optimizations"
	@echo "  clean    - Remove all build artifacts"
	@echo "  help     - Show this help message"
	@echo ""
	@echo "Variables:"
	@echo "  BUILD_TYPE - Set to 'debug' or 'release' (default: release)"

.PHONY: all clean run debug release help