import ctypes
import os

# Load DLL
dll_path = os.path.abspath(r"D:\Koodiohjelmat\Scripts\Cpp\PuzzleSolver\cpp\build\libwordfinder.dll")
word_finder = ctypes.CDLL(dll_path)

# Function signature
word_finder.handleRequest.argtypes = [
    ctypes.c_char_p,              # input
    ctypes.c_char_p,              # output buffer
    ctypes.c_int                  # output buffer size
]
word_finder.handleRequest.restype = ctypes.c_int
