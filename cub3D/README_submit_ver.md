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