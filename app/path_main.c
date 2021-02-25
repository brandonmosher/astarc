#include "astar.uint8_t.h"

#include <inttypes.h>
#include <stdio.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

void grid_uint8_print(const grid_uint8_t* grid, size_t index, const uint8_t value) {
    printf("%u ", value);
    if((index + 1) % grid->num_cols == 0) {
        printf("\n");
    }
    if(index == grid->num_cells - 1) {
        printf("\n");
    }
}

void grid_uint8_init_file(grid_uint8_t* grid, char * file_path) {
    FILE *f = fopen(file_path, "r");
    assert(f);
    size_t num_rows = 0;
    size_t num_cols = 0;
    fscanf(f, "%lu %lu", &num_rows, &num_cols);
    assert(num_rows && num_cols);

    grid_uint8_init(grid, num_rows, num_cols, NULL);
    uint8_t* occupancy = grid->values;
    while(1){
        if(fscanf(f, "%hhu", occupancy++) != 1) {
            break;
        }
    }
    fclose(f);
}

void grid_uint8_fill_random(grid_uint8_t* grid) {
    for(size_t i = 0; i < grid->num_cells; ++i) {
         grid->values[i] = rand() % 2;
    }
}

int is_traversable(const uint8_t* val) {
    return *val == 0 ? 1 : 0;
}

void print_begin_end(coordinate_t* begin, coordinate_t* end) {
    printf("Finding path from {%lu, %lu} to {%lu, %lu}...\n\n", begin->row, begin->col, end->row, end->col);
}

int main () {
    grid_uint8_t grid;

    {
        printf("Running test 1...\n\n");

        grid_uint8_init(&grid, 10, 10, NULL);
        grid_uint8_for_each(&grid, grid_uint8_print);

        coordinate_t begin = {0, 0};
        coordinate_t end = {3, 3};
        print_begin_end(&begin, &end);

        path_t path = astar_uint8_get_path(&grid, begin, end, is_traversable);
        
        if(path_empty(&path)) {
            printf("No path found!\n");
        }
        else {
            path_for_each_r(&path, coordinate_print);
            printf("\n");
        }

        path_destroy(&path);
        grid_uint8_destroy(&grid);
    }
    
    {
        printf("Running test 2...\n\n");

        grid_uint8_init(&grid, 10, 10, NULL);
        grid_uint8_fill_random(&grid);
        grid_uint8_for_each(&grid, grid_uint8_print);

        coordinate_t begin = {9, 0};
        coordinate_t end = {8, 8};
        print_begin_end(&begin, &end);

        path_t path = astar_uint8_get_path(&grid, begin, end, is_traversable);

        if(path_empty(&path)) {
            printf("No path found!\n");
        }
        else {
            path_for_each_r(&path, coordinate_print);
            printf("\n");
        }

        path_destroy(&path);
        grid_uint8_destroy(&grid);
    }

    {
        printf("Running test 3...\n\n");

        grid_uint8_init_file(&grid, "data/4x4.grid");
        grid_uint8_for_each(&grid, grid_uint8_print);

        coordinate_t begin = {0, 3};
        coordinate_t end = {3, 0};
        print_begin_end(&begin, &end);

        path_t path = astar_uint8_get_path(&grid, begin, end, is_traversable);

        if(path_empty(&path)) {
            printf("No path found!\n");
        }
        else {
            path_for_each_r(&path, coordinate_print);
            printf("\n");
        }

        path_destroy(&path);
        grid_uint8_destroy(&grid);
    }

}