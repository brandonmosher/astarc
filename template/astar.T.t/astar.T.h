#ifndef ASTAR_H
#define ASTAR_H

#include "grid.T.h"
#include "array.coordinate_t.h=path.h"

path_t astar_T_get_path(
    grid_T_t* grid,
    coordinate_t begin_coordinate,
    coordinate_t end_coordinate,
    int(*is_traversable)(const T *));

#endif
