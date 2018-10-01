from math import log
from itertools import permutations
from functools import *

problemSudoku = [0, 2, 3, 1,
                 0, 0, 2, 0,

                 0, 3, 0, 2,
                 0, 4, 0, 0]

def solve_sudoku(sudoku, currCell, currDigit):

    if currDigit > 

    if sudoku[cell] == 0:
        sudoku[cell] = currDigit;
        solve_sudoku(sudoku, currCell + 1)

solve_sudoku.alphabet = 
