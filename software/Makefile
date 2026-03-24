# Base executable name (without extension)
EXE_BASE = build/example_glfw_opengl3

# Directories based on your new architecture
INC_DIR = ./include
SRC_DIR = ./src
IMGUI_SRC = $(SRC_DIR)/imgui
BACKENDS_SRC = $(SRC_DIR)/imgui-backends
OBJDIR = $(SRC_DIR)/objects

# 1. Grab all C++ files
SOURCES_CPP = $(wildcard $(SRC_DIR)/*.cpp) \
              $(wildcard $(IMGUI_SRC)/*.cpp) \
              $(wildcard $(BACKENDS_SRC)/*.cpp)

# 2. Grab all C files (for glad.c)
SOURCES_C = $(wildcard $(SRC_DIR)/*.c)

# Generate object file paths for both C and C++ files
OBJS_CPP = $(addprefix $(OBJDIR)/, $(notdir $(SOURCES_CPP:.cpp=.o)))
OBJS_C = $(addprefix $(OBJDIR)/, $(notdir $(SOURCES_C:.c=.o)))
OBJS = $(OBJS_CPP) $(OBJS_C)

# Compiler Configuration
CXX = g++
CC = gcc

# Include flags (-I): 
# -I$(INC_DIR) allows `#include "core/guiApp.h"` and `#include <glad/glad.h>`
# -I$(INC_DIR)/imgui allows ImGui files to find `#include "imgui.h"` directly
INCLUDES = -I$(INC_DIR) -I$(INC_DIR)/imgui

CXXFLAGS = -std=c++14 $(INCLUDES) -g -Wall -Wformat
CFLAGS = $(INCLUDES) -g -Wall -Wformat
LIBS =

##---------------------------------------------------------------------
## OS DETECTION & PLATFORM SPECIFIC FLAGS
##---------------------------------------------------------------------
ifeq ($(OS), Windows_NT)
	ECHO_MESSAGE = "MinGW (Windows)"
	LIBS += -lglfw3 -lgdi32 -lopengl32 -limm32
	CXXFLAGS += `pkg-config --cflags glfw3`
	CFLAGS += `pkg-config --cflags glfw3`
	EXE = $(EXE_BASE).exe
	CLEAN_CMD = Remove-Item -Path '$(EXE)', '$(OBJDIR)' -Recurse -Force -ErrorAction SilentlyContinue
else
	UNAME_S := $(shell uname -s)
	ifeq ($(UNAME_S), Linux)
		ECHO_MESSAGE = "Linux"
		LIBS += -lGL `pkg-config --static --libs glfw3`
		CXXFLAGS += `pkg-config --cflags glfw3`
		CFLAGS += `pkg-config --cflags glfw3`
		EXE = $(EXE_BASE)
		CLEAN_CMD = rm -rf $(EXE) $(OBJDIR)
	endif
endif

##---------------------------------------------------------------------
## BUILD RULES
##---------------------------------------------------------------------
.PHONY: all run clean

all: $(EXE)
	@echo Build complete for $(ECHO_MESSAGE)

run: all
	./$(EXE)

# Rule for building your custom C++ source files (main.cpp, guiApp.cpp)
$(OBJDIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

# Rule for building C files (glad.c)
$(OBJDIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c -o $@ $<

# Rule for building core ImGui C++ files
$(OBJDIR)/%.o: $(IMGUI_SRC)/%.cpp
	@mkdir -p $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

# Rule for building ImGui backend C++ files
$(OBJDIR)/%.o: $(BACKENDS_SRC)/%.cpp
	@mkdir -p $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

# Rule to link the final executable
$(EXE): $(OBJS)
	@mkdir -p $(dir $@)
	$(CXX) -o $@ $^ $(CXXFLAGS) $(LIBS)

clean:
	$(CLEAN_CMD)
