import { makeObservable, observable, action } from 'mobx';

class SudokuState {
  numDict = {};

  constructor() {
    this.numDict = {};
    makeObservable(this, {
        numDict: observable,
        updateDigit: action,
        resetDigits: action
    });
  }

  updateDigit(key, value) {
    this.numDict[key] = value;
  }

  resetDigits() {
    this.numDict = {};
  }
}

export default SudokuState;