import "css/SudokuPage.css"

const SIZE = 9;

const SudokuGrid = () => {
  const numArray = [...Array(SIZE/3).keys()];
  return <div className="sudoku-main">
    {
      numArray.map(r => {
      return <div className="boxrow">
        <SudokuBox row={r} col={1}/>
        <SudokuBox row={r} col={2}/>
        <SudokuBox row={r} col={3}/>
      </div>})
    }
  </div>;
};
  
const SudokuBox = ({row, col}) => {
  const numArray = [...Array(SIZE/3).keys()];
  return <div className="sudokubox">
    {
      numArray.map(c => {
        return <div className="boxrow">
          <SudokuCell digit={col}/>
          <SudokuCell digit={col}/>
          <SudokuCell digit={col}/>
        </div>})
    }
  </div>;
}

const SudokuCell = ({digit}) => {
  return <input className="sudokucell" 
    maxLength={1}
    onInput={validateInput}>
  </input>
}

function validateInput(input) {
  input.target.value = input.target.value.replace(/[^0-9]/g, "")
}

export default SudokuGrid;