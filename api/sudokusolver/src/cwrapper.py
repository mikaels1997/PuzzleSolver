from ctypes import cdll, c_char_p, c_int, create_string_buffer
import os

dll_path = os.path.abspath("libsudoku.dll")
print("Loading:", dll_path)

lib = cdll.LoadLibrary(dll_path)
print("Lib loaded")

lib.handleRequest.argtypes = [c_char_p, c_char_p, c_int]
lib.handleRequest.restype = c_int

buffer = create_string_buffer(4096)

rc = lib.handleRequest(b"[...]", buffer, len(buffer))
if rc == 0:
    print(buffer.value.decode())
