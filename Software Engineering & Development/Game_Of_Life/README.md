## Game of Life  
### Description:

The Game of Life was invented by John Conway. It consists of a collection of cells which, based on a few mathematical rules, can live, die or multiply. The "game" is a zero-player game, meaning that its evolution is determined by its initial state, requiring no further input from humans. One interacts with the Game of Life by creating an initial configuration and observing how it evolves.
The universe of the Game of Life is an infinite two-dimensional orthogonal grid of square cells, each of which is in one of two possible states, live or dead. Every cell interacts with its eight neighbors, which are the cells that are directly horizontally, vertically, or diagonally adjacent. At each step in time, the following transitions occur:  
1.	Any live cell with fewer than two live neighbors dies, as if caused by under-population.  
2.	Any live cell with more than three live neighbors dies, as if by overcrowding.  
3.	Any live cell with two or three live neighbors lives on to the next generation.  
4.	Any dead cell with exactly three live neighbors becomes a live cell.  
    

### Files

|   #   | File                                    | Description                                                |
| :---: | --------------------------------------- | ---------------------------------------------------------- |
|   1   | [main.cpp](./main.cpp)                  | Solution file                                              |
|   2   | [GOL_Input_File](./GOL_Input_File.txt)  | Initial state (Generation 0) for game to be played         |
|   3   | [gen_zero](./gen_zero.txt)              | Smaller test initial state (Generation 0) for game         |
      
