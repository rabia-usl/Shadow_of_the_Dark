# Shadow of the Dark

## Table of Contents
- [Introduction](#introduction)
- [Game Objective](#game-objective)
- [Features](#features)
- [Setup and Installation](#setup-and-installation)
- [Gameplay](#gameplay)
- [File Descriptions](#file-descriptions)
- [Contributing](#contributing)
- [License](#license)

## Introduction
**Shadow of the Dark** is an adventurous text-based game where players navigate through mysterious rooms, encounter creatures, collect items, and strategize to reach the final goal. 

## Game Objective
The main objective of the game is to navigate through the rooms, defeat all creatures, collect essential items, and reach the end room to win.

## Features
- Multiple interconnected rooms with unique descriptions.
- A variety of creatures with distinct attributes.
- Inventory management system to collect and use items.
- Save and load game progress.
- Command-based gameplay.

## Setup and Installation
### Prerequisites
- Make sure you have **GCC** and **Make** installed on your system. If not, you can install them using:
  ```bash
  sudo apt update
  sudo apt install build-essential
  ```

### Build Instructions
1. Clone this repository:
   ```bash
   git clone https://github.com/your-username/ShadowOfTheDark.git
   cd ShadowOfTheDark
   ```
2. Build the project using the Makefile:
   ```bash
   make
   ```
3. Run the game:
   ```bash
   ./Game.exe
   ```

## Gameplay
1. **Starting the Game:**
   - Run the `Game.exe` file to start playing.
2. **Commands:**
   - Use text-based commands like `move`, `attack`, `pickup`, `drop`, `use`, `inventory`, and more to interact with the game.
3. **Objective:**
   - Defeat all creatures, collect useful items, and navigate to the end room to win.

## File Descriptions
- **Player.h, Player.c**: Contains player attributes and related functionalities.
- **Room.h, Room.c**: Manages room structures and connections.
- **Item.h, Item.c**: Handles item creation and inventory management.
- **Creature.h, Creature.c**: Defines creatures and their behavior.
- **Command.h, Command.c**: Processes player commands.
- **Main.c**: The entry point of the game.
- **Makefile**: Automates the build process.

## Contributing
Contributions are welcome! Follow these steps:
1. Fork the repository.
2. Create a new branch (`git checkout -b feature-branch-name`).
3. Commit your changes (`git commit -m 'Add a new feature'`).
4. Push to the branch (`git push origin feature-branch-name`).
5. Create a pull request.

## License
This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.


 
