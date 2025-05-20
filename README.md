# Log Hunter MiniGame

Log Hunter MiniGame is a C++-based mini-game that challenges players to hunt and collect virtual logs and potions in a dynamic game environment. This project demonstrates core game development concepts, clean code practices, and effective use of C++ for interactive applications.

---

## 🎮 Game Overview

In Log Hunter MiniGame, players control a character or cursor to track down and "hunt" logs and potions that appear in the game area. The main objective is to collect as many logs as possible and create fire balls.

---

## 🧑‍💻 Technical Details

- **Language**: C++ (100%)
- **Core Features**:
  - Real-time event handling (keyboard/mouse input)
  - Dynamic rendering of game elements
  - Score tracking and game state management
  - Modular code structure
- **Libraries Used**:
  - Standard Template Library (STL)
  - [SFML](https://www.sfml-dev.org/) or [SDL](https://www.libsdl.org/) for graphics and input (if applicable)
- **Project Structure**:
  - Source code organized into logical modules/classes
  - Assets (images, sounds) separated from code for easy management
  - Header files for interface definitions

---

## 🚀 Getting Started

### Prerequisites

- C++17 compatible compiler (e.g., g++, clang++)
- [SFML](https://www.sfml-dev.org/) or [SDL](https://www.libsdl.org/) library (if used)
- CMake or Make for building the project

### Build & Run

```bash
# Clone the repository
git clone https://github.com/3RFUNn/Log-Hunter-MiniGame.git
cd Log-Hunter-MiniGame

# Build (example using g++)
g++ -std=c++17 -o log_hunter main.cpp [other_source_files.cpp] -lsfml-graphics -lsfml-window -lsfml-system

# Run the game
./log_hunter
```

## 🕹️ Gameplay Instructions

1. **Start the Game:** Launch the executable to begin.
2. **Controls:** Use your keyboard (arrow keys/WASD or mouse) to move.
3. **Objective:** Collect as many logs and potions as you can before time runs out!
4. **Gameplay:** Create fire balls and shoot them.


---

## 📚 Features

- **Fun and Challenging Gameplay:** Simple mechanics with increasing complexity.
- **Clean and Readable Code:** Well-commented and modular for easy extension.
- **Cross-Platform:** Designed to run on Windows, Linux, and macOS (dependent on external library support).

---

## 🤝 Contributing

We welcome contributions! To get started:

1. Fork the repository
2. Create a new branch (`git checkout -b feature/your-feature`)
3. Commit your changes
4. Push to the branch (`git push origin feature/your-feature`)
5. Open a Pull Request

---


## 🙌 Acknowledgments

- Inspired by retro arcade games and simple time-based challenges.
- Thanks to open-source libraries like SFML/SDL for making C++ game development accessible.

---

Enjoy hunting logs!
 
