from fastapi import FastAPI, HTTPException, UploadFile, File
from pydantic import BaseModel
from solver_wrapper import solve_sudoku
from fastapi.middleware.cors import CORSMiddleware
from typing import List
from num_parser import analyze_numbers

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
    try:
        flat_solution = solve_sudoku(list(req.grid))
    except Exception as e:
        raise HTTPException(status_code=500, detail=str(e))

    return {
        "solution": flat_solution
    }

@app.post("/upload")
async def upload_file(file: UploadFile = File(...)):
    print("File received...")
    if file.content_type not in ["image/png", "image/jpeg", "image/jpg"]:
        raise HTTPException(status_code=400, detail="Only PNG or JPEG images are allowed")
    file_location = file.filename
    with open(file_location, "wb") as f:
        f.write(await file.read())  # binary write
    numbers = analyze_numbers(file_location)
    return {"filename": file.filename, "path": str(file_location), "numbers": numbers}