import { makeObservable, observable, action } from 'mobx';
import { sendSudoku } from "api"

class SudokuState {
  numMatrix = [];
  solution = [];

  constructor() {
    this.numMatrix = this.getEmptyMat();
    makeObservable(this, {
      numMatrix: observable,
      solution: observable,
      updateDigit: action,
      resetDigits: action
    });
  }

  updateDigit(row, col, value) {
    this.numMatrix[row][col] = Number.parseInt(value);
  }

  resetDigits() {
    this.numMatrix = this.getEmptyMat();
  }

  getEmptyMat() {
    let arr = new Array(9)
    for(let i = 0;i<9;i++)
        arr[i] = new Array(9)
    return arr;
  }

  async solveSudoku() {
    const solutionStr = await sendSudoku(this);
    //const solutionStr = "9 8 6 7 3 5 2 4 1 7 4 5 9 2 1 8 6 3 1 2 3 8 6 4 7 5 9 4 3 9 1 5 8 6 7 2 6 5 7 3 9 2 1 8 4 8 1 2 6 4 7 9 3 5 3 6 1 5 7 9 4 2 8 5 9 4 2 8 6 3 1 7 2 7 8 4 1 3 5 9 6"
    const nums = solutionStr.split(" ");
    let solution = this.getEmptyMat();
    for (let i=0;i<81;i++) {
      solution[Math.floor(i/9)][i%9]=Number.parseInt(nums[i]);
    }
    this.numMatrix = solution;
  }
}

export default SudokuState;