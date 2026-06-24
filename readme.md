# Conway's Game of Life

A simple implementation of Conway's Game of Life written in **C** using **SDL3**.

The project focuses on clarity and simplicity while remaining fast enough to simulate thousands of cells in real time.

## Preview

Features several well-known patterns:

* Gosper Glider Gun
* Diehard
* Infinite Growth

## Features

* Written in pure C
* SDL3 rendering
* Fixed-size grid simulation
* Double-buffered updates
* Pattern spawning system
* Easy to add custom patterns
* Lightweight and dependency-free (except SDL3)

## Project Structure

```text
.
├── bin/
│   └── main
├── main.c
└── patterns.h
```

### Files

| File         | Description                                                         |
| ------------ | ------------------------------------------------------------------- |
| `main.c`     | Main application, rendering, simulation loop and Game of Life logic |
| `patterns.h` | Collection of predefined patterns and entity definitions            |
| `bin/main`   | Compiled executable                                                 |

## Rules of the Game

For every generation:

1. A live cell with fewer than 2 neighbors dies.
2. A live cell with 2 or 3 neighbors survives.
3. A live cell with more than 3 neighbors dies.
4. A dead cell with exactly 3 neighbors becomes alive.

### Requirements

* GCC or Clang
* SDL3 development libraries

### Compile

```bash
gcc main.c -o bin/main `pkg-config --cflags --libs sdl3`
```

### Run

```bash
./bin/main
```

Or compile and run in one command:

```bash
gcc main.c -o bin/main `pkg-config --cflags --libs sdl3` && ./bin/main
```

## Configuration

The simulation parameters can be modified in `main.c`:

```c
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

#define CELL_SIZE 8
```

Changing `CELL_SIZE` automatically changes the grid dimensions:

```c
#define GRID_WIDTH (SCREEN_WIDTH / CELL_SIZE)
#define GRID_HEIGHT (SCREEN_HEIGHT / CELL_SIZE)
```

## Adding New Patterns

Patterns are defined in `patterns.h` as relative coordinates:

```c
static const CellOffset GLIDER[] = {
    {1, 0},
    {2, 1},
    {0, 2},
    {1, 2},
    {2, 2}
};
```

Spawn them using:

```c
SpawnEntity(
    grid,
    GRID_WIDTH,
    GRID_HEIGHT,
    x,
    y,
    GLIDER,
    GLIDER_SIZE
);
```

## Implementation Notes

The simulation uses a temporary update buffer to ensure all cells are evaluated from the same generation before applying changes.

This prevents newly updated cells from affecting calculations during the current tick.

## License

MIT License.
