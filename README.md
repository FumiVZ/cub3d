<p align="center">
  <img src="https://github.com/ayogun/42-project-badges/raw/main/badges/cub3dm.png" alt="cub3d badge"/>
</p>

<h1 align="center">cub3D</h1>

<p align="center">
  <img src="https://img.shields.io/badge/42_Lyon-cub3D-blue?style=for-the-badge&logo=42" alt="42 Lyon"/>
  <img src="https://img.shields.io/badge/Score-109%2F100-success?style=for-the-badge" alt="Score"/>
  <img src="https://img.shields.io/badge/Language-C-00599C?style=for-the-badge&logo=c" alt="C"/>
</p>

<p align="center">
  A 3D game engine using raycasting, inspired by Wolfenstein 3D.
</p>

---

## About

**cub3D** is a 42 school project that creates a dynamic 3D maze exploration game using raycasting techniques. The project is inspired by the legendary Wolfenstein 3D, considered the first true "First Person Shooter" in gaming history.

The engine renders a 3D perspective view from a 2D map, implementing:
- Real-time raycasting for 3D rendering
- Textured walls with different textures per orientation (N/S/E/W)
- Smooth player movement and rotation
- Collision detection
- Minimap display
- Configurable floor and ceiling colors

## Features

| Feature | Description |
|---------|-------------|
| Raycasting Engine | Real-time 3D rendering using DDA algorithm |
| Texture Mapping | XPM texture support for walls (N/S/E/W) |
| Player Movement | WASD movement with arrow key rotation |
| Collision Detection | Wall collision prevention |
| Minimap | Real-time minimap display |
| Map Parser | Robust .cub file parsing with error handling |

## Functions

### Core Functions

| Function | File | Description |
|----------|------|-------------|
| `start_game` | `main.c` | Initialize and start the game loop |
| `init_game` | `init.c` | Initialize all game structures |
| `ft_render_map` | `minimap.c` | Main render loop function |

### Raycasting

| Function | File | Description |
|----------|------|-------------|
| `draw_line` | `raycasting.c` | Cast ray and draw wall slice |
| `wall_touch` | `raycasting.c` | Check if ray hits a wall |
| `init_ray` | `raycasting.c` | Initialize ray parameters |
| `get_texture_color` | `ray_utils.c` | Get pixel color from texture |

### Movement

| Function | File | Description |
|----------|------|-------------|
| `ft_move_player` | `movement.c` | Handle player movement |
| `ft_up_and_down` | `movement.c` | Forward/backward movement |
| `ft_strafe_player` | `movement.c` | Left/right strafing |
| `check_collision` | `movement.c` | Collision detection |

### Parsing

| Function | File | Description |
|----------|------|-------------|
| `parse_file` | `parse.c` | Parse .cub configuration file |
| `check_map` | `map.c` | Validate map structure |
| `parse_textures` | `parse_utils.c` | Parse texture paths |
| `parse_color` | `texture.c` | Parse RGB color values |

### Memory Management

| Function | File | Description |
|----------|------|-------------|
| `ft_free_all` | `free.c` | Free all allocated memory |
| `free_map` | `free.c` | Free map structure |
| `free_data` | `free.c` | Free data structure |
| `ft_close_game` | `free.c` | Clean exit handler |

## Compilation

```bash
# Clone the repository
git clone git@github.com:FumiVZ/cub3d.git
cd cub3d

# Compile the project
make

# Clean object files
make clean

# Full clean (including binary)
make fclean

# Recompile
make re
```

## Usage

```bash
./cub3d <map.cub>
```

### Example

```bash
./cub3d map/map.cub
```

### Controls

| Key | Action |
|-----|--------|
| `W` | Move forward |
| `S` | Move backward |
| `A` | Strafe left |
| `D` | Strafe right |
| `←` | Rotate left |
| `→` | Rotate right |
| `ESC` | Exit game |

### Map Format

Maps must be `.cub` files with the following format:

```
NO ./path_to_north_texture.xpm
SO ./path_to_south_texture.xpm
WE ./path_to_west_texture.xpm
EA ./path_to_east_texture.xpm

F 220,100,0
C 225,30,0

        1111111111111111111111111
        1000000000110000000000001
1111111111011000001110000000000001
100000000011000001110111111111111
11110111111111011100000010001
11110111111111011101010010001
1100000011010101011100001110001
10000000001100000111010001000001
10000000001101010101111010001
11000001110101011101101010100101
11110111 1110101 101111010001
11111111 1111111 111111111111
```

## Contributors

<table>
  <tr>
    <td align="center">
      <a href="https://github.com/FumiVZ">
        <img src="https://github.com/FumiVZ.png" width="100px;" alt="FumiVZ"/><br />
        <sub><b>Vincent Zuccarello</b></sub>
      </a>
    </td>
    <td align="center">
      <a href="https://github.com/Denos-soneD">
        <img src="https://github.com/Denos-soneD.png" width="100px;" alt="Denos-soneD"/><br />
        <sub><b>Mateo Christol</b></sub>
      </a>
    </td>
  </tr>
</table>

---

<p align="center">
  Made with dedication at <a href="https://42lyon.fr/">42 Lyon</a>
</p>
