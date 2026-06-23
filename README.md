# atg-client

> **Automatic Trajectory Generator Client** — A cross-platform desktop application for acoustic volumetric displays.
> *(Undergraduate thesis project)*

---

## Table of Contents

- [About the Project](#about-the-project)
- [Tech Stack](#tech-stack)
- [Repository Structure](#repository-structure)
- [Prerequisites](#prerequisites)
- [Building on Arch Linux](#building-on-arch-linux)
- [Building on Windows](#building-on-windows)

---

## About the Project

`atg-client` is a cross-platform GUI client for controlling and visualizing **acoustic volumetric displays** — devices that levitate and move particles in mid-air using ultrasound to create 3D images visible to the naked eye.

The client is responsible for:

- **Generating trajectories** — computing the paths that levitated particles should follow to form 3D shapes or animations.
- **Visualizing the output** — rendering a real-time 3D preview of the trajectories using OpenGL and an ImGui-based interface.
- **Communicating with hardware** — sending trajectory data to the acoustic display hardware.

The project is split into two main parts:

| Directory | Description |
|-----------|-------------|
| `software/` | The desktop GUI client (C++, OpenGL, ImGui) |
| `hardware/` | PCB schematics and hardware design files (KiCad) |

---

## Tech Stack

| Technology | Role |
|------------|------|
| **C++ 14** | Core application language |
| **OpenGL 4.6** | 3D rendering |
| **GLFW** | Cross-platform window and input management |
| **GLAD** | OpenGL function loader |
| **Dear ImGui** | Immediate-mode GUI framework |
| **GNU Make** | Build system |
| **KiCad** | Hardware PCB design |

---

## Repository Structure

```
atg-client/
├── software/               # Desktop client source code
│   ├── src/
│   │   ├── main.cpp        # Entry point — initializes and runs the GUI app
│   │   ├── guiApp.cpp      # Core app class: window, OpenGL, ImGui lifecycle
│   │   ├── shaders/        # GLSL vertex and fragment shaders
│   │   ├── opengltings/    # OpenGL helper utilities (e.g., shader reader)
│   │   ├── window/         # Window abstraction layer
│   │   └── 3rdparty/       # Third-party source files (e.g., glad.c)
│   ├── include/            # Header files and library includes
│   ├── build/              # Compiled output (generated, not tracked)
│   └── Makefile            # Build script (cross-platform: Linux & Windows)
│
├── hardware/               # Hardware design files
│   ├── KiCad/              # PCB schematics and layouts
│   ├── diamond/            # Diamond-pattern transducer array designs
│   ├── lib/                # KiCad component libraries
│   └── docs/               # Hardware documentation
│
├── TODO                    # Active development notes
└── README.md
```

---

## Prerequisites

Before building, ensure your system meets the following requirements:

- **OpenGL 4.6** or higher
- **GCC / G++** with C++14 support
- **GNU Make**
- **GLFW 3**
- **pkg-config**

### Verify your OpenGL version

Install `mesa-utils` and run:

```bash
sudo pacman -S mesa-utils      # Arch Linux
glxinfo | grep "OpenGL version"
```

---

## Building on Arch Linux

### 1. Install dependencies

```bash
sudo pacman -S glfw base-devel
```

### 2. Build and run

Navigate to the `software/` directory and use GNU Make:

```bash
cd ./software/
make clean      # Remove any previous build artifacts
make            # Compile the project
make run        # Build (if needed) and launch the application
```

The compiled binary will be placed at `software/build/example_glfw_opengl3`.

> **Note:** Always run `make clean` before `make` after pulling new changes to avoid stale build artifacts.

---

## Building on Windows

### Prerequisites

- [MinGW-w64](https://www.mingw-w64.org/) (provides `g++`, `gcc`, `make`)
- [GLFW](https://www.glfw.org/download.html) binaries for Windows
- `pkg-config` configured for your MinGW environment

### Build

```powershell
cd .\software\
make clean
make
make run
```

The compiled binary will be placed at `software/build/example_glfw_opengl3.exe`.
