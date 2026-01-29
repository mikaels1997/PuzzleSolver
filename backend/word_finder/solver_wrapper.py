import ctypes
from .solver import word_finder

OUTPUT_BUFFER_SIZE = 4096

def find_words(flat_input: str) -> str:
    input_bytes = str("".join(flat_input)).lower().encode()
    output_buffer = ctypes.create_string_buffer(OUTPUT_BUFFER_SIZE)

    result = word_finder.handleRequest(
        ctypes.c_char_p(input_bytes),
        output_buffer,
        OUTPUT_BUFFER_SIZE
    )

    if result != 0:
        raise RuntimeError("Sudoku solver failed or output buffer too small")
    return output_buffer.value.decode()