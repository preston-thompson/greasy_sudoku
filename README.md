# greasy_sudoku
Sudoku solver written in C.

I've never solved a Sudoku puzzle in my life.

# Why?
This is for a competition between a friend and I. We are seeing who can write a faster Sudoku solver. The rules are:
 * The program must read the puzzle in as a file. Format is detailed below.
 * The program must print the solution out to stdout in the same format.
 * The program must execute deterministically (no random numbers).
 * The program must be called from the shell by the form `sudoku puzzle.txt`.

# File format
0's represent empty cells. Example puzzle:
```
000700000
100000000
000430200
000000006
000509000
000000418
000081000
002000050
040000300
```

# My attempts at optimization
 * Use bits and bitwise operations to deal with possible numbers in an empty cell.
 * Use the gcc builtin `int __builtin_popcount(unsigned)` function to determine the number of set bits in an integer.
 * Exit loops as soon as possible if a solution doesn't exist.
 * Everything is written in one function.
 * Don't bother finishing recursion if a solution is found. Print the solution and exit the program immediately.

# Future ideas
 * Get rid of the recursion (function calls are overhead!).
 * Try multithreading.
 * Try POSIX file I/O instead of C file I/O.
 * Think of a more sophisticated algorithm than bruteforcing with possible numbers.
