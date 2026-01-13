import ctypes
from solver import sudoku

OUTPUT_BUFFER_SIZE = 4096

def solve_sudoku(flat_input: list) -> str:
    input_bytes = str(flat_input).encode()

    output_buffer = ctypes.create_string_buffer(OUTPUT_BUFFER_SIZE)

    result = sudoku.handleRequest(
        ctypes.c_char_p(input_bytes),
        output_buffer,
        OUTPUT_BUFFER_SIZE
    )

    if result != 0:
        raise RuntimeError("Sudoku solver failed or output buffer too small")
    return output_buffer.value.decode()