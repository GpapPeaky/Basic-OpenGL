# ==========================================================
# Compiler
# ==========================================================

CXX := g++
CC  := gcc

# ==========================================================
# Directories
# ==========================================================

SRCDIR := src
SHDDIR := shaders
OBJDIR := obj
BINDIR := bin

TARGET := $(BINDIR)/win.exe

# ==========================================================
# Compiler / Linker Flags
# ==========================================================

CPPFLAGS := \
    -IThirdParty/SDL2/include \
    -IThirdParty/GLAD/include \
    -IThirdParty/freetype-2.14.3/include \
    -MMD -MP

CXXFLAGS := -Wall -Wextra -std=c++17
CFLAGS   := -Wall -Wextra

LDFLAGS := -LThirdParty/SDL2/lib

LDLIBS := \
    -lmingw32 \
    -lSDL2main \
    -lSDL2 \
    -lSDL2_image \
    -LThirdParty/freetype-2.14.3/objs \
    -lfreetype
    # RENAME GENERATED freetype.a TO libfreetype.a


# ==========================================================
# Source Files
# ==========================================================

CPP_SRCS := \
    $(wildcard $(SRCDIR)/*.cpp) \
    $(wildcard $(SHDDIR)/*.cpp)

C_SRCS := \
    ThirdParty/GLAD/src/glad.c

# ==========================================================
# Object Files
# ==========================================================

CPP_OBJS := $(patsubst %.cpp,$(OBJDIR)/%.o,$(CPP_SRCS))
C_OBJS   := $(patsubst %.c,$(OBJDIR)/%.o,$(C_SRCS))

OBJS := $(CPP_OBJS) $(C_OBJS)

# ==========================================================
# Targets
# ==========================================================

.PHONY: all clean run

all: $(TARGET)

# ----------------------------------------------------------
# Link
# ----------------------------------------------------------

$(TARGET): $(OBJS)
	@if not exist "$(BINDIR)" mkdir "$(BINDIR)"
	$(CXX) $(OBJS) $(LDFLAGS) $(LDLIBS) -o $@

# ----------------------------------------------------------
# Compile C++
# ----------------------------------------------------------

$(OBJDIR)/%.o: %.cpp
	@if not exist "$(dir $@)" mkdir "$(dir $@)"
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

# ----------------------------------------------------------
# Compile C
# ----------------------------------------------------------

$(OBJDIR)/%.o: %.c
	@if not exist "$(dir $@)" mkdir "$(dir $@)"
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

# ----------------------------------------------------------
# Run
# ----------------------------------------------------------

run: all
	$(TARGET)

# ----------------------------------------------------------
# Clean
# ----------------------------------------------------------

clean:
	@if exist "$(OBJDIR)" rmdir /S /Q "$(OBJDIR)"
	@if exist "$(BINDIR)" rmdir /S /Q "$(BINDIR)"

# ==========================================================
# Auto-generated dependencies
# ==========================================================

-include $(OBJS:.o=.d)