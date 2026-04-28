# DX3D — C++ 3D Game Engine
 
![C++](https://img.shields.io/badge/C++20-00599C?style=flat&logo=cplusplus&logoColor=white)
![DirectX](https://img.shields.io/badge/DirectX%2011-0078D4?style=flat&logo=microsoft&logoColor=white)
![Visual Studio](https://img.shields.io/badge/Visual%20Studio%202022-5C2D91?style=flat&logo=visualstudio&logoColor=white)
![Windows](https://img.shields.io/badge/Windows-0078D4?style=flat&logo=windows&logoColor=white)
![Status](https://img.shields.io/badge/Status-In%20Development-orange?style=flat)
 
A custom 3D game engine built from the ground up in **C++20** and **DirectX 11**. The engine interfaces directly with computer hardware to render 3D graphics, built on a modular, high-performance architecture following professional software engineering standards — no engine abstractions, no shortcuts.
 
> [!NOTE]
> **Work in Progress** — Actively developed with a focus on understanding modern C++ engine architecture, GPU programming, and low-level graphics systems.

---

## 🏗️ Architecture Overview
 
The engine is divided into six specialised technical systems, each responsible for a distinct layer of the engine stack.

---

### 1. Core Engine Architecture
 
The foundation of the project is a modular framework that manages the full lifecycle of the application.
 
- **Game Loop** — A central synchronisation mechanism handles the continuous cycle of processing input, updating game logic, and triggering the renderer using `PeekMessage` / `TranslateMessage` / `DispatchMessage`
- **Base Class Hierarchy** — Every engine component inherits from a shared `Base` class, ensuring consistent memory management and resource handling across the entire system. The `Base` class defines a virtual destructor for safe polymorphic cleanup

---

### 2. Low-Level Windowing & OS Interfacing
 
Before graphics can be drawn, the engine establishes a direct communication layer with the Windows operating system.
 
- **Win32 API Integration** — Registers window classes and creates a hardware-accelerated window surface
- **Message Dispatching** — A custom Window Procedure (`WndProc`) intercepts OS events — such as closing the window or resizing — and translates them into engine-level commands
- **Error Handling** — `try-catch` blocks in `main` catch and report initialisation failures gracefully

---

### 3. Graphics Subsystem (DirectX 11)
 
The Render System manages all communication with the GPU through the DirectX 11 API.
 
- **Device & Context Creation** — Initialises the Direct3D 11 Device (the virtual representation of the GPU) and the Device Context (the pipeline for sending draw commands to hardware)
- **Feature Level Querying** — The system queries the hardware to determine the highest supported feature level, including shader models and tessellation support
- **COM Resource Management** — `Microsoft::WRL::ComPtr` handles automatic lifetime management of all DirectX COM objects
- **Encapsulated Internals** — The `RenderSystem` implementation is kept private inside `source/` to hide DirectX internals from the public engine API

---

### 4. Advanced Memory & Resource Management
 
The engine adheres to professional C++ standards to guarantee stability and prevent memory leaks.
 
- **Smart Pointers** — `std::unique_ptr` is used throughout to manage object lifetimes automatically, replacing all manual `new` / `delete` patterns
- **COM Pointers** — `Microsoft::WRL::ComPtr` handles GPU resource cleanup automatically
- **Rule of Five** — Copy constructors, move constructors, and their assignment counterparts are explicitly `= delete`d on the `Base` class, preventing accidental shallow copies of hardware resources such as the Window handle or GPU Device

---

### 5. Dependency & Service Management
 
To keep systems clean and decoupled, the engine uses established software design patterns.
 
- **Dependency Injection** — Services such as the Logger are injected into components through constructors rather than accessed via global variables, making the engine modular and easier to debug
- **Descriptor Structs** — Configuration data is grouped into descriptor structures (e.g. `BaseDescriptor`, `WindowDescriptor`), allowing complex systems to be initialised with a single organised package of settings rather than bloated constructor signatures

---

### 6. Debugging & Diagnostics
 
A dedicated logging subsystem monitors the engine's health in real time.
 
- **Logger Subsystem** — Categorises system events into **Info**, **Warning**, and **Error** verbosity levels
- **Console Diagnostic Feed** — Tracks the full engine initialisation and shutdown sequence, making it easy to identify where failures occur

---

## 🗂️ Project Structure
 
```
DX3D/
├── DX3D/
│   ├── include/         # Public engine API (headers exposed to game code)
│   │   └── dx3d/
│   └── source/          # Private implementation (DirectX internals hidden here)
│       └── dx3d/
└── Game/                # Game-specific logic, separate from engine code
```
 
- **`DX3D` (Engine)** — Entry point, window management, graphics subsystem, and all core engine logic. Lives in the `dx3d` namespace
- **`Game`** — Game-specific content that consumes the engine's public API

---

## 🗺️ Roadmap
 
### Phase 1 — Graphics Pipeline Foundations
- [ ] Swap Chain (front/back buffers for flicker-free presentation)
- [ ] Clear screen to a solid colour
- [ ] Input Assembler, Rasterizer, Output Merger configuration
 
### Phase 2 — Drawing & Animation
- [ ] Vertex Buffers & basic shaders — render a triangle
- [ ] Transformation matrices (Translation, Rotation, Scale)
- [ ] Time-based animations
- [ ] Index Buffers — render a 3D cube
 
### Phase 3 — Engine Systems & Interactivity
- [ ] Input System (keyboard & mouse)
- [ ] Camera System (View & Projection matrices)
- [ ] Entity-Component System (ECS) for game objects
 
### Phase 4 — Advanced Visuals & Game World
- [ ] HLSL shaders for lighting, materials, and textures
- [ ] 3D terrain and water rendering
- [ ] Physics / collision detection
