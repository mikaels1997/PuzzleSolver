import { makeObservable, observable, action } from 'mobx';

class SudokuState {
  numMatrix = [];

  constructor() {
    this.numMatrix = this.getEmptyMat();
    makeObservable(this, {
      numMatrix: observable,
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
}

export default SudokuState;