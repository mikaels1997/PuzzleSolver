import "css/SudokuPage.css";
import { observer } from 'mobx-react';

const SIZE = 9;

const SudokuGrid = ({state}) => {
  const numArray = [...Array(SIZE/3).keys()];
  return <div className="sudoku-grid">
    {
      numArray.map(r => {
      return <div className="boxrow" key={r}>
        <SudokuBox row={r} col={0} state={state}/>
        <SudokuBox row={r} col={1} state={state}/>
        <SudokuBox row={r} col={2} state={state}/>
      </div>})
    }
  </div>;
};
  
const SudokuBox = ({row, col, state}) => {
  const numArray = [...Array(SIZE/3).keys()];
  return <div className="sudokubox">
    {
      numArray.map(r => {
        return <div className="boxrow" key={r}>
          <SudokuCell row={3*row+r} col={3*col} state={state}/>
          <SudokuCell row={3*row+r}  col={3*col+1} state={state}/>
          <SudokuCell row={3*row+r}  col={3*col+2} state={state}/>
        </div>})
    }
  </div>;
}

const SudokuCell = observer(({row, col, state}) => {
  return <input className="sudokucell"
    value={state.numDict[`${row}-${col}`] ?? ""}
    maxLength={2}
    onChange={(e) => changeInput(e, row, col, state)}
    onClick={handleClick}>
  </input>
});

function changeInput(event, row, col, state) {
  event.preventDefault();
  event.target.value = event.target.value.replace(/[^1-9]/g, "");
  if (event.target.value == "") return;
  const input = event.target;
  const inputValue = event.target.value;
  input.value = inputValue[inputValue.length - 1];
  state.updateDigit(`${row}-${col}`, input.value);
}

function handleClick(event) {
  const {value} = event.target;
  const position = value.length;
  event.target.setSelectionRange(position, position);
}

export default SudokuGrid;