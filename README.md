# A* Algorithm for Letter Arrangement Puzzle  

## Description  
This project implements the **A* search algorithm** in C++ to solve a letter arrangement puzzle on an `n x n` board. The board consists of letters (`A-Z`) and empty spaces (`-`). The goal is to move the letters to match a given target configuration while minimizing the number of moves.  

## Features  
- Reads the initial and goal states from a text file.  
- Uses **A* search** with a heuristic to efficiently find the solution.  
- Outputs the sequence of moves required to reach the goal.  
- Displays the total number of states expanded.  

## Input Format  
The input text file should contain:  
1. An integer `n` (board size).  
2. `n` lines representing the **initial state** of the board.  
3. `n` lines representing the **goal state** of the board.  

Example (`input.txt`):  
```
3
A-B
-C-
D--
AB-
C--
D--
```  

## Output Example  
```
A right  
C down  
D right  
No. of states expanded: 12  
```  
