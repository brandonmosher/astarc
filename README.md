# astarc

C implementation of the A* path-finding algorithm. For details and pseudo code, see https://en.wikipedia.org/wiki/A*_search_algorithm#Pseudocode

## Concepts

### Grid
A grid is a fixed-size array representing a contiguous 2D space. Each array value represents arbitrary information about a unit of grid area.  

### Coordinate
A coordinate specifies the unique row and column associated with a unit of grid area.

### Path
A path is an ordered list of coordinates.

### Grid Value Type

This implementation requires the user to specify the grid value type. This is done by inserting the desired type into the include directive. For example, to use a grid of uint8_t, insert the following:

    #include "astar.uint8_t.h"

This allows the user to represent arbitrarily complex information about each grid location. For example, the following struct could be used to represent multiple properties of the grid location.

```
typedef struct  {
    double elevation;
    double angle_of_elevation;
    ...
} terrain_t

#include "astar.terrain_t.h"
```

### Traversability

The user must also define the "is_traversable" function. This function takes a single grid value and returns 1 if traversable and 0 otherwise. This allows the user to specify any arbitrary criteria for the traversability of each grid location.

```
int(*is_traversable)(const T *))
```

# Run Sample Code

    ./install_pyctemp.sh
    make

# Quick Start

## app/main.c
```
// Specifies grid value of uint8_t
#include "astar.uint8_t.h"

// User-defined function to determine traversability of each grid location
int is_traversable(const uint8_t* val) {
    return *val == 0 ? 1 : 0;
}

int main () {
    grid_uint8_t grid;
    grid_uint8_init(&grid, 10, 10, NULL);
    path_t path = astar_uint8_get_path(&grid, {0, 0}, {3, 3}, is_traversable);
}
```
## Install pyctemp

    ./install_pyctemp.sh

## Build

```
pyctemp --typedef-indlude-dirpath uint8_t:inttypes.h --source-dirpath app --target-dirpath include

gcc -I include -lm include/*.c app/*.c
```

# Pyctemp Template Instantiation

This implementation is templated to support arbitrary grid values. pyctemp is used to instantiate the required templates during the build process.

## Generated Files

### grid.T.h grid.T.c

T is the user-specified grid value type. Provides methods to manipulate a grid.

### path_t.h path_t.c

This is simply the pyctemp built-in array.T.t template with T=coordinate_t, and alias=path_t Provides numerous methods to manipulate a path.

### astar.T.h astar.T.c

T is the user-specified grid value type. Provides astar_T_get_path method.

### misc..

Additional boilerplate for map, linked list, array and pair used for the astar algorithm.

# Tips

### Custom Grid Value Types
If using a custom grid value type one of the following conditions must be satisfied to enable pyctemp to generate functioning code:

- type defined in any file in the source-dirpath provided to pyctemp
- type defined in an arbitrary location as long as the one of the following arguments are passed to pyctemp:
        --include-dirpath [arbitrary dirpath]
        --typedef-include-filepath [typename]:[arbitrary filepath]
- type defined in a system header as long as the following argument is passed to pyctemp:
        --typedef-include-filepath [typename]:[include filepath]