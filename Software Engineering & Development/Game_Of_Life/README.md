## Game of Life  
### Description:

The Game of Life was invented by John Conway (as you might have gathered). It consists of a collection of cells which, based on a few mathematical rules, can live, die or multiply. The "game" is a zero-player game, meaning that its evolution is determined by its initial state, requiring no further input from humans. One interacts with the Game of Life by creating an initial configuration and observing how it evolves.
The universe of the Game of Life is an infinite two-dimensional orthogonal grid of square cells, each of which is in one of two possible states, live or dead. Every cell interacts with its eight neighbors, which are the cells that are directly horizontally, vertically, or diagonally adjacent. At each step in time, the following transitions occur:  
1.	Any live cell with fewer than two live neighbors dies, as if caused by under-population.  
2.	Any live cell with more than three live neighbors dies, as if by overcrowding.  
3.	Any live cell with two or three live neighbors lives on to the next generation.  
4.	Any dead cell with exactly three live neighbors becomes a live cell.  
Your implementation will not be an infinite two-dimensional orthogonal grid of square cells, but a finite dynamically allocated 2-dimensional array of golCell's (game of life cells). A golCell contains:  
•	isAlive (bool [true,false])  
•	neighborCount (int # of neighbors)  
In class we discussed how to get from our current state to the next state by adding two matrices together, however we are going to use a different method to go from one generation to the next.  
•	If you look below, the far left is the current "state" of the game, where the two values are: isAlive and neighborCount respectively.  
•	You can traverse the game board and count each cells neighbors storing its neighbor-count within the cell.  
•	Once each cell has its neighbors counted, you can apply the rules (killing 2 and spawning 2 in this example) and also reset the neighbor counts to zero.  
State	Calculate Transition	Apply Transition  

### Files

|   #   | File                                | Description                                                |
| :---: | ----------------------------------- | ---------------------------------------------------------- |
|   1   | [main.cpp](./main.cpp)              | solution file.                                             |
|   2   | [GOL_Input_File](./GOL_Input_File)  | Initial state (Generation 0) for game to be played         |
|   3   | [gen_zero](./gen_zero)              | Initial state (Generation 0) for game to be played         |
      
