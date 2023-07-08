import "css/SudokuPage.css"

const SIZE = 9;

const SudokuGrid = () => {
  const numArray = [...Array(SIZE/3).keys()];
  return <div className="sudoku-main">
    {
      numArray.map(r => {
      return <div className="boxrow" key={r}>
        <SudokuBox row={r} col={0}/>
        <SudokuBox row={r} col={1}/>
        <SudokuBox row={r} col={2}/>
      </div>})
    }
  </div>;
};
  
const SudokuBox = ({row, col}) => {
  const numArray = [...Array(SIZE/3).keys()];
  return <div className="sudokubox">
    {
      numArray.map(r => {
        return <div className="boxrow" key={r}>
          <SudokuCell row={3*row+r} col={3*col}/>
          <SudokuCell row={3*row+r}  col={3*col+1}/>
          <SudokuCell row={3*row+r}  col={3*col+2}/>
        </div>})
    }
  </div>;
}

const SudokuCell = ({row, col}) => {
  return <input className="sudokucell" 
    maxLength={2}
    onChange={changeInput}
    onClick={handleClick}>
  </input>
}

function changeInput(event) {
  event.target.value = event.target.value.replace(/[^1-9]/g, "")
  if (event.target.value == "") return;
  const input = event.target;
  const inputValue = event.target.value;
  input.value = inputValue[inputValue.length - 1];
}

function handleClick(event) {
  const {value} = event.target;
  const position = value.length;
  event.target.setSelectionRange(position, position);
}

export default SudokuGrid;