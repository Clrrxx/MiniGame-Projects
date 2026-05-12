# Raylib C++ Snake Game

![Language](https://img.shields.io/badge/language-C%2B%2B-brightgreen)
![Raylib](https://img.shields.io/badge/raylib-4%20%7C%205%20%7C%206-00d4aa)
![Platform](https://img.shields.io/badge/platform-Windows%2010%20%7C%2011-blue)
![Editor](https://img.shields.io/badge/editor-VS%20Code-007ACC)

A Basic C++ Project game using RayLib to code out Snake

# Key Learning Points from This Snake Game

- C++ Fundamentals
Object-oriented design is demonstrated through the three-class architecture — Snake, Food, and Game — each encapsulating its own state and behavior. The Game class acts as a controller/coordinator, which mirrors the common separation of concerns principle. 

- Memory Management
The game uses raw heap allocation (new/delete) for all three objects, exposing to the responsibility of manual memory management and the consequences of neglecting it such as memory leaks. The Food destructor explicitly calls UnloadTexture(), demonstrating RAII (Resource Acquisition Is Initialization) — tying resource lifetime to object lifetime. The natural next step is learning std::unique_ptr to automate this.

- Data Structures
The snake body uses a std::deque<Vector2>, which is the ideal structure here because snake movement requires O(1) insertion at the front (push_front) and O(1) deletion at the rear (pop_back).

- Game Loop Architecture
The fixed-timestep event trigger (eventTrig) decouples game logic speed from render speed, which is a foundational pattern in game development. Rendering runs at 60 FPS while game state updates at a configurable interval, teaching the distinction between update frequency and render frequency.

<p align="center">
 <img width="1366" height="1096" alt="image" src="https://github.com/user-attachments/assets/ee005f59-92be-4116-9cc1-4465e0823b86" />
  </a>
</p>


