# 🎮 so_long

<div align="center">

  <img src="https://img.shields.io/badge/language-C-blue.svg" alt="Language">
  <img src="https://img.shields.io/badge/42-School-lightgrey.svg" alt="42 School">
  <img src="https://img.shields.io/badge/graphics-MLX-yellow.svg" alt="MiniLibX">
  <img src="https://img.shields.io/badge/status-active-green.svg" alt="Status">

</div>

## 📜 About

`so_long` is a small 2D maze game implemented in C using the MiniLibX graphics library. The player navigates a tile-based map, collects items (berries), and reaches the exit. This project is commonly used as an exercise in the 42 School curriculum to practice C, memory management, file parsing and simple graphical programming.

This repository contains the game binary, helper utilities (get_next_line, ft_printf), map files and textures.

## 🔧 Requirements

- A Unix-like system (Linux or macOS)
- A C compiler (gcc/clang)
- MiniLibX installed or available for your platform
- Standard build tools (make)

On Ubuntu, you may need these packages:
```bash
sudo apt-get install build-essential libx11-dev libxext-dev libbsd-dev
```

## 📥 Build

The project includes a `Makefile`. From the repository root:

```bash
# Build the executable
make

# Or clean and rebuild
make re
```

The produced executable is `so_long`.

## ▶️ Run

Maps are stored in the `maps/` directory and use the `.ber` format. Example:

```bash
# Run the game with a map
./so_long maps/map.ber
```

If you compiled on macOS or Linux with the correct MiniLibX, the window should open and the game will render the level.

## 🎮 Controls

- W — Move forward (up)
- A — Move left
- S — Move backward (down)
- D — Move right
- ESC — Exit the game (or click the window close button)

## 📁 Map format (`.ber`)

Each `.ber` map is a text file that describes a rectangular tile map. Typical tiles used by `so_long` are:
- `1` = wall
- `0` = floor / empty tile
- `P` = player start position (exactly one required)
- `E` = exit (exactly one required)
- `C` = collectible (berries; at least one required)

Rules and constraints:
- The map must be rectangular (every line the same length)
- The map must be surrounded by walls (no leaks)
- Exactly one player `P` and one exit `E`.
- At least one collectible `C`.

See `maps/` for many example maps and edge cases used for validation.

## 💡 Features

- Tile-based 2D rendering using MiniLibX
- Map parsing and validation with helpful error messages
- Collectibles counting and win condition
- Keyboard controls and simple collision detection
- Centralized cleanup to avoid memory leaks

## 🧭 Project structure

```
so_long/
├── include/                	# Project headers (so_long.h)
├── src/                    	# Source files
│   ├── so_long.c           	# main and initialization
│   ├── so_long_utils.c     	# movement & input handlers
│   ├── so_long_fts_map.c   	# map parsing and validation
│   ├── so_long_fts_clean.c 	# cleanup helpers
│   ├── get_next_line.c     	# line reader
│   ├── get_next_line_utils.c
│   └── ft_*.c              	# ft_printf and helpers
├── maps/                   	# Example maps (.ber)
├── textures/               	# XPM texture files
├── obj/                    	# object files (build)
├── Makefile
└── README.md
```

## 🧪 Testing & Memory checks

You can run the program under Valgrind to check for leaks (Linux):

```bash
valgrind --leak-check=full --show-leak-kinds=all -s ./so_long maps/map.ber
```
The codebase aims to free all program-owned memory before exit.

## 🛠️ Development notes

- Centralize allocation and cleanup: use `init` and `close_window` / `ft_clean_map` to keep resource handling consistent across exit paths.
- Keep error paths calling the same cleanup to avoid leaks.
- Use Valgrind locally while iterating on parsing and cleanup.

## ✍️ Contributor guide

- Fork the repository and create a branch per feature/bugfix
- Follow the existing coding style and header prototypes
- Run `make` and test on the example maps
- Open a Pull Request describing the changes

## 📄 License & Attribution

This project follows the academic guidelines of the 42 School curriculum. If you reuse code or assets from other sources, please attribute accordingly.

---

<p align="center">Created with ❤️ and C by 42 School students</p>
