#ifndef PATTERNS_H
#define PATTERNS_H

#include <stddef.h>

typedef struct {
    int dx;
    int dy;
} CellOffset;

// Define a Glider (5 cells)
static const CellOffset GLIDER[] = {
    {1, 0}, {2, 1}, {0, 2}, {1, 2}, {2, 2}
};
static const size_t GLIDER_SIZE = sizeof(GLIDER) / sizeof(GLIDER[0]);

// Define a Lightweight Spaceship (9 cells)
static const CellOffset LWSS[] = {
    {1, 0}, {2, 0}, {0, 1}, {3, 1}, {4, 1}, {0, 2}, {4, 2}, {1, 3}, {4, 3}
};
static const size_t LWSS_SIZE = sizeof(LWSS) / sizeof(LWSS[0]);

// Define an Acorn (7 cells)
static const CellOffset ACORN[] = {
    {1, 0}, {3, 1}, {0, 2}, {1, 2}, {4, 2}, {5, 2}, {6, 2}
};
static const size_t ACORN_SIZE = sizeof(ACORN) / sizeof(ACORN[0]);

// The Gosper Glider Gun (36 cells of pure mechanics)
static const CellOffset GLIDER_GUN[] = {
    {24, 0},
    {22, 1}, {24, 1},
    {12, 2}, {13, 2}, {20, 2}, {21, 2}, {34, 2}, {35, 2},
    {11, 3}, {15, 3}, {20, 3}, {21, 3}, {34, 3}, {35, 3},
    {0, 4},  {1, 4},  {10, 4}, {16, 4}, {20, 4}, {21, 4},
    {0, 5},  {1, 5},  {10, 5}, {14, 5}, {16, 5}, {17, 5}, {22, 5}, {24, 5},
    {10, 6}, {16, 6}, {24, 6},
    {11, 7}, {15, 7},
    {12, 8}, {13, 8}
};
static const size_t GLIDER_GUN_SIZE = sizeof(GLIDER_GUN) / sizeof(GLIDER_GUN[0]);

static const CellOffset PENTADECATHLON[] = {
    {0, 1}, {1, 1}, {2, 0}, {2, 2}, {3, 1}, {4, 1}, {5, 1}, {6, 1}, {7, 0}, {7, 2}, {8, 1}, {9, 1}
};
static const size_t PENTADECATHLON_SIZE = sizeof(PENTADECATHLON) / sizeof(PENTADECATHLON[0]);

static const CellOffset HWSS[] = {
    {1, 0}, {2, 0}, {3, 0}, {4, 0},
    {0, 1}, {5, 1},
    {0, 2},
    {0, 3}, {4, 3},
    {2, 4}, {3, 4}
};
static const size_t HWSS_SIZE = sizeof(HWSS) / sizeof(HWSS[0]);

static const CellOffset DIEHARD[] = {
    {6, 0},
    {0, 1}, {1, 1},
    {1, 2}, {5, 2}, {6, 2}, {7, 2}
};
static const size_t DIEHARD_SIZE = sizeof(DIEHARD) / sizeof(DIEHARD[0]);

static const CellOffset INFINITE_GROWTH[] = {
    {0, 0}, {1, 0}, {2, 0}, {4, 0},
    {0, 1},
    {3, 2}, {4, 2},
    {1, 3}, {2, 3}, {4, 3}
};
static const size_t INFINITE_GROWTH_SIZE = sizeof(INFINITE_GROWTH) / sizeof(INFINITE_GROWTH[0]);

#endif