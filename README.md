# RCVRP
## Risk-constrainted Cash-in-transit Vehicle Routing Problem

Solver using Simulated Annealing.  
By Manuel Weitzman.  
Under the GNU GPLv3.0 only license.

## Requirements
- `Linux` based OS is recommended.
- GNU `g++` version 7 or any capable of compiling the `gnu++11` standard.
- GNU `make` version 4.

## Installation

1. `./configure`
1. `make`
1. `make install` (requires sudoer privileges)

Aditionally the following `make` rules are included:
- `make clean`: Clean intermediate binaries
- `make distclean`: Clean final binaries
- `make cleanall`: `clean`+`distclean`

## Execution

```bash
# Redirect the input to STDIN
rcvrp < input.txt

# You may configure some parameters using environment variables
LOOPTIME=1000 rcvrp < input.txt
```

### Available environment variables

- `MULTIPLIER`: Sets the temperature multiplier. This operation is done after a
  fixed amount of iterations. (Default = 0.98).
- `TEMPERATURE`: Sets the initial temperature. (Default = 128.0).
- `ITERATIONS`: How many iterations before the temperature is multiplied and
  cooled down. (Default = 128).
- `LOOPTIME`: Sets in milliseconds how long the program will be iterating.
  (Default = 256).
- `THREADS`: Sets how many threads will be used during the execution. (Default =
  OS detected).

## Removal

1. `make uninstall` (requires sudoer privileges)

## Additional notes

None. Yet.
