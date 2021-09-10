
#include "terrain.h"
#include "astar.terrain_t.h"
#include <stdlib.h>

void grid_terrain_print(const grid_terrain_t* grid, size_t index, const terrain_t* value) {
    printf("{%.1f, %.1f} ", value->elevation, value->angle_of_elevation);
    if((index + 1) % grid->num_cols == 0) {
        printf("\n");
    }
    if(index == grid->num_cells - 1) {
        printf("\n");
    }
}

void grid_terrain_fill_random(grid_terrain_t* grid) {
    for(size_t i = 0; i < grid->num_cells; ++i) {
         grid->values[i] = (terrain_t){(double)(rand() % 10), (double)(rand() % 10)};
    }
}

int is_traversible(const terrain_t* terrain) {
    return terrain->angle_of_elevation <= 6.0;
}

int main() {
    grid_terrain_t grid;
    grid_terrain_init(&grid, 5, 5, NULL);
    grid_terrain_fill_random(&grid);
    grid_terrain_for_each_r(&grid, grid_terrain_print);

    path_t path = astar_terrain_get_path(
        &grid,
        (coordinate_t){0,0},
        (coordinate_t){0,3},
        is_traversible);
    
    path_for_each_r(&path, coordinate_print);
}