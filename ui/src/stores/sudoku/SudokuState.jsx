import { makeObservable, observable, action } from 'mobx';
import { sendSudoku } from "api"
import toastr from 'toastr';

class SudokuState {
  numMatrix = [];
  solution = [];

  constructor() {
    this.numMatrix = this.load();
    makeObservable(this, {
      numMatrix: observable,
      solution: observable,
      setGrid: action,
      updateDigit: action,
      resetDigits: action
    });
  }

  load() {
    const loaded = JSON.parse(localStorage.getItem("sudoku_grid"));
    return loaded ?? this.getEmptyMat()
  }

  updateDigit(row, col, value) {
    this.numMatrix[row][col] = value != 'undefined' ? Number.parseInt(value) : undefined;
    localStorage.setItem("sudoku_grid", JSON.stringify(this.numMatrix));
  }

  resetDigits() {
    this.numMatrix = this.getEmptyMat();
    localStorage.clear();
  }

  setGrid(grid) {
    this.numMatrix = grid; 
    localStorage.setItem("sudoku_grid", JSON.stringify(this.numMatrix));
  }

  getEmptyMat() {
    let arr = new Array(9)
    for(let i = 0;i<9;i++)
        arr[i] = new Array(9)
    return arr;
  }

  getPayload() {
    return this.numMatrix.flat().map(a => a == null ? 0 : a)
  }

  async solveSudoku() {
    const result = await sendSudoku(this.getPayload());
    const nums = result.solution.split(" ");
    let solution = this.getEmptyMat();
    let found = false;
    for (let i=0;i<81;i++) {
      const num = Number.parseInt(nums[i]);
      solution[Math.floor(i/9)][i%9]=num;
      if (num !== 0) {
        found = true;
      }
    }
    this.numMatrix = found ? solution : this.numMatrix;
    if (!found) {
      toastr.error("Solution not found!")
    }
  }
}

export default SudokuState;