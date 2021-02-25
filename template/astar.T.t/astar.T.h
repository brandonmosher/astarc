#ifndef ASTAR_H
#define ASTAR_H

#include "grid.T.h"
#include "array.coordinate_t.h=path.h"

void path_print(path_t* path);

path_t astar_get_path(
    grid_T_t* grid,
    coordinate_t begin_coordinate,
    coordinate_t end_coordinate,
    int(*is_traversable)(T *));

#endif
