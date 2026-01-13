import ctypes
import os

# Load DLL
dll_path = os.path.abspath("../../cpp/build/libsudoku.dll")
sudoku = ctypes.CDLL(dll_path)

# Function signature
sudoku.handleRequest.argtypes = [
    ctypes.c_char_p,              # input
    ctypes.c_char_p,              # output buffer
    ctypes.c_int                  # output buffer size
]
sudoku.handleRequest.restype = ctypes.c_int

# int sudokuArr[9][9] = {
# {0, 0, 0, 7, 0, 0, 0, 0, 1},
# {0, 0, 0, 0, 0, 0, 8, 0, 0},
# {0, 2, 0, 8, 6, 0, 0, 5, 0},

# {0, 3, 0, 0, 0, 0, 0, 0, 0},
# {6, 0, 0, 0, 0, 0, 0, 8, 4},
# {0, 1, 2, 6, 0, 7, 0, 3, 0},

# {3, 0, 0, 5, 0, 0, 0, 2, 8},
# {0, 9, 4, 0, 0, 0, 3, 0, 7},
# {0, 7, 0, 0, 0, 0, 0, 0, 0},
# };