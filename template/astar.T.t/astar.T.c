#include "astar.T.h"
#include <stdio.h>
#include <assert.h>
#include <math.h>
#include <float.h>

#include "map.coordinate_t.double.h"
#include "map.coordinate_t.coordinate_t.h"
#include "list.coordinate_t.h"

map_coordinate_double_t g_score; // cost pose->(x,y)
map_coordinate_double_t f_score; // estimated cost pose->(x,y)->goal
map_coordinate_coordinate_t came_from;
list_coordinate_t open_set;

static int f_score_lowest_cost(const coordinate_t* a, const coordinate_t* b) {
    return map_coordinate_double_find(&f_score, *a) > map_coordinate_double_find(&f_score, *b);
}

path_t astar_T_get_path(
    grid_T_t* grid,
    coordinate_t begin_coordinate,
    coordinate_t end_coordinate,
    int(*is_traversable)(const T *))
{
	path_t path;
    path_init(&path, 10);
    assert(
        grid_T_coordinate_inbounds(grid, begin_coordinate) && \
        grid_T_coordinate_inbounds(grid, end_coordinate));

    map_coordinate_coordinate_init(
        &came_from,
        100,
        coordinate_hash,
        coordinate_equal);
    
    map_coordinate_double_init(
        &g_score,
        100,
        coordinate_hash,
        coordinate_equal);
    
    map_coordinate_double_init(
        &f_score,
        100,
        coordinate_hash,
        coordinate_equal);
	
    map_coordinate_double_insert(
        &g_score,
        begin_coordinate,
        0.0);
    
    map_coordinate_double_insert(
        &f_score,
        begin_coordinate,
        coordinate_euclidean_distance(&begin_coordinate, &end_coordinate));
	
    list_coordinate_init(&open_set);
    list_coordinate_push_back_r(&open_set, &begin_coordinate);
    list_coordinate_bubble_sort_r(&open_set, f_score_lowest_cost);
	
	while (!list_coordinate_empty(&open_set)) {
		coordinate_t current = list_coordinate_front(&open_set);
        list_coordinate_pop_front(&open_set);
        
		if (coordinate_equal(current, end_coordinate)) { //successful end            
            while(!coordinate_equal(current, begin_coordinate)) {
                path_push_back_r(&path, &current);
                current = *map_coordinate_coordinate_find(&came_from, current);
            }
            path_push_back_r(&path, &current);
            break;
		}
		
		coordinate_t neighbors[4];
		neighbors[0] = (coordinate_t){current.row + 1, current.col};
		neighbors[1] = (coordinate_t){current.row, current.col + 1};
		neighbors[2] = (coordinate_t){current.row - 1, current.col};
		neighbors[3] = (coordinate_t){current.row, current.col - 1};
        
		size_t i;
		for (i = 0; i < 4; ++i) {
			if (!grid_T_coordinate_inbounds(grid, neighbors[i])) {
				continue;
            }
			if (!is_traversable(grid_T_get_value_coordinate_r(grid, neighbors[i]))) {
				continue;
            }

            double tent_g_score = *map_coordinate_double_find(&g_score, current) + 1.0;
			if (!map_coordinate_double_find(&g_score, neighbors[i])) { //Not in open set. This path is new
                list_coordinate_push_back_r(&open_set, &(neighbors[i]));
                list_coordinate_bubble_sort_r(&open_set, f_score_lowest_cost);
            }
            if(tent_g_score < *map_coordinate_double_find_insert(&g_score, neighbors[i], DBL_MAX)) { //This path is new or better than before
                map_coordinate_coordinate_insert(&came_from, neighbors[i], current);
				map_coordinate_double_insert(&g_score, neighbors[i], tent_g_score);
                map_coordinate_double_insert(
                    &f_score,
                    neighbors[i],
                    tent_g_score + coordinate_euclidean_distance(neighbors + i, &end_coordinate));
            }
		}
	}
    
    map_coordinate_coordinate_destroy(&came_from);
    map_coordinate_double_destroy(&g_score);
    map_coordinate_double_destroy(&f_score);
    list_coordinate_destroy(&open_set);

	return path;
}
