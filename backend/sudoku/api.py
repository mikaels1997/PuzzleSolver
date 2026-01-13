from fastapi import FastAPI, HTTPException
from pydantic import BaseModel
from solver_wrapper import solve_sudoku
from fastapi.middleware.cors import CORSMiddleware
from typing import List

class SudokuRequest(BaseModel):
    grid: List[int]  # 9x9

class SudokuResponse(BaseModel):
    solution: str

app = FastAPI(title="Sudoku Solver API")

app.add_middleware(
    CORSMiddleware,
    allow_origins=["http://localhost:3000"],  # React dev server
    allow_credentials=True,
    allow_methods=["*"],   # POST, GET, OPTIONS, etc.
    allow_headers=["*"],
)

@app.post("/solve", response_model=SudokuResponse)
def solve(req: SudokuRequest):
    if len(req.grid) != 81:
        raise HTTPException(status_code=400, detail="Grid must be 9x9")

    #flat_input = flatten_grid(req.grid)
    try:
        flat_solution = solve_sudoku(list(req.grid))
    except Exception as e:
        raise HTTPException(status_code=500, detail=str(e))

    return {
        "solution": flat_solution
    }

# def flatten_grid(grid: list[list[int]]) -> str:
#     return ",".join(str(cell) for row in grid for cell in row)

# def unflatten_solution(flat: str) -> list[list[int]]:
#     nums = list(map(int, flat.split(",")))
#     return [nums[i:i+9] for i in range(0, 81, 9)]