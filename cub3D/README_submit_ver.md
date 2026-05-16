*This project has been created as part of the 42 curriculum by sisung, hama.*

# cub3D - My first RayCaster with miniLibX

## Description
The goal of this project is to create a "realistic" 3D graphical representation of the inside of a maze from a first-person perspective. Inspired by the world-famous Wolfenstein 3D game, this project serves as an introduction to ray-casting principles. The program parses a `.cub` scene description file to construct a closed maze, renders textured walls based on their orientation (North, South, East, West), and allows the user to navigate the environment smoothly using the miniLibX library.

## Instructions
### Compilation
To compile the project and generate the executable, run the following command at the root of the repository:
```bash
make
```

### Execution
The program requires a scene description file (with a `.cub` extension) as its first argument.
```bash
./cub3D maps/map.cub
```

### Usage / Controls
- **W, A, S, D**: Move the point of view (forward, left, backward, right) through the maze.
- **Left / Right Arrow Keys**: Rotate the camera view left or right.
- **ESC / Window 'X' Button**: Close the window and quit the program cleanly.

## Resources
### Classic References
- **Lodev's Raycasting Tutorial**: The fundamental mathematical guide used to understand and implement the Digital Differential Analyzer (DDA) and ray-casting algorithms in this project.

### AI Usage
Artificial Intelligence (LLMs) was utilized as a "Visual Tutor" and debugging assistant during the development of this project.
- **Specific Tasks**:
  1. Identifying and resolving complex floating-point precision bugs (e.g., the "Zero-Vector Infinity" bug that caused vertical rendering gaps).
  2. Refactoring logic to comply with the strict 42 Norminette rules (e.g., compressing boolean checks using logical OR operations without losing performance).
  3. Conceptually visualizing the geometric mapping between screen pixels (0 to SCREEN_W) and the camera plane (-1 to 1).
- **Specific Parts of the Project**: AI assistance was primarily focused on the DDA loop (`perform_dda`), vector initialization (`init_ray`), and the decoupling of movement vectors in the player input logic (`update_player`).

## Technical Choices
As per the core mechanics of the engine, the following technical choices and algorithms were implemented:

### Raycasting Principles
The engine renders the 3D world by sweeping rays across the camera plane for each vertical column (x) of the screen, from left to right.
1. **Camera X and Ray Direction**: The screen x-coordinate (0 to SCREEN_W) is mapped to a ratio between -1 and 1 (`camera_x`). The `ray_dir` vector is calculated by adding the player's direction vector to the camera plane vector scaled by `camera_x`.
2. **Delta Distance (`delta_dist`)**: The absolute distance the ray must travel to cross one full x or y grid square, calculated using `fabs(1 / ray_dir)`.
3. **Side Distance (`side_dist`)**: The distance from the player's exact floating-point position to the very first grid line. We use `floor()` to determine the current grid box and calculate the initial offset.
4. **DDA Algorithm**: The algorithm iteratively jumps to the next closest grid line by comparing `side_dist_x` and `side_dist_y`. To prevent infinite loop crashes at cardinal angles (where a direction vector is 0), a `max_steps` integer counter is used instead of float distance comparisons.
5. **Perpendicular Wall Distance**: To prevent the fisheye effect, `perp_wall_dist` is calculated using the distance projected onto the camera plane, rather than the true Euclidean distance.

### Wall Collision & Sliding Logic
To prevent the player from walking through walls and to implement "wall sliding" (moving smoothly along a wall when pressing diagonally against it), the X and Y movement vectors were heavily decoupled.
By evaluating the X and Y movements independently against the map grid, the player can slide along one axis even if the target coordinate on the other axis is blocked by a wall ('1').

```c
void move_forward(t_game *game)
{
    double new_x = game->player.pos_x + game->player.dir_x * game->player.move_speed;
    double new_y = game->player.pos_y + game->player.dir_y * game->player.move_speed;

    // X-axis collision check: only update X if the target cell is not a wall
    if (game->map.grid[(int)game->player.pos_y][(int)new_x] != '1')
        game->player.pos_x = new_x;

    // Y-axis collision check: only update Y if the target cell is not a wall
    if (game->map.grid[(int)new_y][(int)game->player.pos_x] != '1')
        game->player.pos_y = new_y;
}
```

## Architecture & Program Flow
To maintain a clean and Norm-compliant codebase, the project is structured into clear phases and utilizes centralized data structures.

### High-Level Architecture Diagram
```text
+---------------------------------------------------+
|                      main()                       |
|  (Initializes game struct & starts the program)   |
+---------------------------------------------------+
       |                                |
       v                                v
+-------------+                  +-------------+
| parse_map() |                  | init_game() |
| (Parsing)   |                  | (MLX Setup) |
+-------------+                  +-------------+
       |                                |
       +--------------------------------+
                       |
                       v
+---------------------------------------------------+
|               start_game_loop()                   |
|          (Registers Hooks & Starts loop)          |
+---------------------------------------------------+
       |                                |
       v (mlx_loop_hook)                v (mlx_hook)
+-----------------------+        +--------------------+
|    render_frame()     |        |   key_press() /    |
| (Raycasting Engine)   |        |   key_release()    |
+-----------------------+        +--------------------+
```

### 1. Core Data Structures (Structs)
All context is bundled into a root structure to minimize function arguments:
- `t_game`: The monolithic root structure that holds all game data (MLX pointers, map, player, textures).
- `t_player`: Holds floating-point position coordinates, directional vectors (`dir_x`, `dir_y`), camera plane vectors (`plane_x`, `plane_y`), and active key states for smooth multi-key movement.
- `t_ray`: Stores mathematical context for a single vertical rendering strip (e.g., DDA variables like `side_dist`, `delta_dist`, and `perp_wall_dist`).
- `t_map`: Holds the parsed 2D grid matrix, dimensions, texture paths, and floor/ceiling RGB values.
- `t_img`: Stores the miniLibX image pointer, data memory address, and metadata (`bpp`, `line_len`, `endian`) needed for direct and fast pixel manipulation.

### 2. Error & Exception Handling
Strict and robust error handling is implemented during the `.cub` parsing phase to prevent crashes or memory leaks:
- **Enum-based Error Tracking**: Defined `t_error` in `cub3d.h` to classify every possible fail state (e.g., `ERR_MALLOC`, `ERR_INV_TEX`, `ERR_WALL`, `ERR_PLAYER`).
- **Centralized Cleanup**: `cleanup.c` centralizes error messaging (`print_error_and_return`) and memory deallocation.
- **Validation**: The parser strictly checks for unclosed map walls (Flood Fill or ray checks), invalid RGB formats, duplicate configurations, invalid characters, separated map lines, and unopenable texture files.

### 3. MLX Utilization & Optimization
miniLibX is a lightweight but rudimentary graphics library. To achieve a playable frame rate:
- **Image Buffer Rendering**: Using the default `mlx_pixel_put` directly on the window is too slow for a 3D engine. Instead, a full-screen image buffer (`t_img`) is created using `mlx_new_image`.
- **Direct Memory Access**: Pixel colors are calculated and written directly to the image's memory address pointer (`mlx_get_data_addr`).
- **Frame Pushing**: Once a frame is fully drawn on the buffer, `mlx_put_image_to_window` pushes the entire image to the display in one operation.
- **Event Hooks**: `mlx_hook` is utilized with X11 masks to capture `KeyPress` (2) and `KeyRelease` (3) for lag-free continuous movement, and `DestroyNotify` (17) to cleanly exit when the window is closed.

### 4. Raycasting Pipeline (Function Level)
The core of the program resides in `render_frame()` (`raycasting.c`), which is executed continuously by `mlx_loop_hook`. The pipeline flows as follows:

1. **`update_player()`**: Evaluates active key states and updates the player's spatial position and view vectors before rendering starts.
2. **`init_ray()`**: For every `x` pixel column on the screen, it computes the ray's initial direction and the currently occupied map grid coordinates.
3. **`calculate_step()`**: Determines the grid step direction (+1 or -1) and calculates the initial `side_dist` to the very first grid boundary.
4. **`perform_dda()`**: Executes the DDA loop. A safety counter (`max_steps = 1000`) is used instead of float distances to prevent infinite loops when a vector component is identically zero. The loop steps through the grid until it hits `'1'`.
5. **`calculate_wall_dims()`**: Computes `perp_wall_dist` (perpendicular distance) to avoid fisheye distortion, and derives the `draw_start` and `draw_end` vertical bounds for the wall on the screen.
6. **`draw_wall_line()`**: Maps the correct texture based on the hit side (North, South, East, West), calculates the exact `tex_x` column, reads the pixel colors from the loaded texture buffer, and draws the vertical line into the main image buffer.

### 5. Function Call Graph & Prototypes
Below is the execution flow of the primary functions, outlining how they are called and their signatures:

```text
main(int argc, char **argv)
 │
 ├── parse_map(const char *file_path, t_game *game)
 │    ├── parse_line(...)                   -> Reads .cub configs & map strings
 │    ├── convert_map_list_to_array(...)    -> Builds the 2D character grid
 │    └── validate_map_and_player(...)      -> Checks for map enclosures and player spawn
 │
 ├── init_game(t_game *game)
 │    └── load_textures(t_game *game)       -> Loads .xpm files into memory
 │
 ├── start_game_loop(t_game *game)
 │    ├── mlx_hook(..., key_press, ...)     -> Registers Input (Press)
 │    ├── mlx_hook(..., key_release, ...)   -> Registers Input (Release)
 │    ├── mlx_hook(..., close_window, ...)  -> Registers Window Close (Red Cross)
 │    └── mlx_loop_hook(..., render_frame, ...) -> Registers continuous render loop
 │
 └── render_frame(t_game *game)             <-- Runs continuously every frame
      ├── update_player(t_game *game)       -> Moves/Rotates based on active keys
      ├── draw_background(t_game *game)     -> Fills floor & ceiling with memory mapping
      │
      └── while (x < SCREEN_W)              <-- Raycasting Loop
           ├── init_ray(int x, t_ray *ray, t_player *player)
           ├── calculate_step(t_ray *ray, t_player *player)
           ├── perform_dda(t_ray *ray, t_map *map)
           ├── calculate_wall_dims(t_ray *ray)
           └── draw_wall_line(t_game *game, int x, t_ray *ray, ...)
```
