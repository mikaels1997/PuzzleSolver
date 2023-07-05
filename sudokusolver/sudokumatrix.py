import numpy as np

mat = np.zeros((729, 324))
#print(mat)
for r in range(0, 9):
    for c in range(0, 9):
        for v in range(1, 10):
            row = np.zeros((1,324))
            i = 81 *r + 9 *c + v - 1

            cellCons = 9*r + c
            rowCons = 9*r + v
            colCons = 9*c + v
            boxCons = 9*((3*(r//3) + 1) + (c//3) - 1) + v

            row[0][cellCons] = 1
            row[0][80+rowCons] = 1
            row[0][161+colCons] = 1
            row[0][242+boxCons] = 1
            mat[i] = row
            print(f"r{r}c{c}#{v} cell:{cellCons} rowCons: {rowCons} colCons: {colCons} boxCons: {boxCons} col: {i}")
lol = 3