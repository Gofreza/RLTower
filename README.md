# RLTower Rogue-like Game Project

## Disclaimer

This project is provided as-is, without any warranty or guarantee. No license is granted for usage, distribution, or modification unless explicitly agreed upon.

## Currently on this project

I may have paused coding this, I'm currently developping a 2D engine that will probably be able to replace the UIManager here and do a lot of things (like an engine does). It uses the same tech so that will be doable. Maybe one day I'll change it, for now I only want to at least finish adding the level system to at least have a playable game.
Next I'd like to resume working on the tunneling algorithm I wanted to, I hope I take the time to do that.

There are a lot of things missing here, so for the me of the future stop starting new projects and finish this one 😉.

## 🧙‍♂️ About the Project

This is a rogue-like game built in C++, inspired by classic and modern dungeon crawlers like COGMIND. The game emphasizes procedural generation, turn-based mechanics, and deep gameplay customization. The ultimate goal is to create a challenging yet rewarding experience for players who enjoy exploration, strategy, and a bit of luck.

The goal here is to roam inside a tower and try to get to the top.

This is the first step of this project. I aim to build a working version of the game with a lot of what I want to implement. Then I will review what I have done and rebuild everything, with a better architecture.

## 🛠️ Technologies Used

- **Programming Language**: C++
- **Libraries and Frameworks**:
  - [SDL2](https://www.libsdl.org/): for graphics and input handling
  - [nlohmann-json](https://github.com/nlohmann/json): for json parsing
  - Custom procedural generation algorithms for dungeon creation
  - Basic AI for enemy behaviors
- **Development Tools**:
  - CMake: for project build and management
  - Git: for version control
  - IDE: Visual Studio Code

## ⚙ How to run

On Windows, just download the release and run the .exe. For macOs you can try to build the project yourself first (you just have to download the dependencies 😉, I'll do a release for it one day 😅) and for Linux I didn't try so good luck 👍.

## 🖥️ How to Build

To build the project (for macOs), you have a **CMakeLists.txt** file. You just have to update the path to the given dependencies. <br>
Then just, inside a build folder:
```
cmake ..
make
./RLTower
```
Or if you're in VSCode, you can use the CMakeTools extension.

## 📜 Roadmap

### ✅ Completed Features

- Basic UI
- Localization system
- Items, Characters (Player, Enemies)
- Effects
- Basic Map generation (BSP)
- FOV

### 🚧 In-Progress Features

- Combat system
- Enemy AI ([RogueBasin](https://roguebasin.com/index.php/A_Better_Monster_AI))

### 🛠️ Planned Features

- Add sound and musics
- Better map generation (Tunneling algorithm)
- Code refactor (Menus ...)

## 🔮 Future Modifications

- Maybe change from JSON to a database to store all data

## 🧝‍♂️ Lore and Story

*Here is a basic overview of the story*

You are a convicted prisoner, given a choice: serve your sentence behind bars or attempt the perilous challenge of conquering the infamous **Prisoner Tower**. Legend has it that anyone who reaches the top will earn their freedom. But beware—the tower is no ordinary place. It teems with deadly monsters and the desperate souls of those who tried and failed before you, transforming it into a living dungeon.

Will you face the tower's horrors alone, or seek allies to increase your chances of survival? The choice is yours.


## 💬 Contact

For questions or feedback, feel free to reach out:

- **GitHub**: [Gofreza](https://github.com/Gofreza)
