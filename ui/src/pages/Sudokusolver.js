import "./Sudokusolver.css";

const SIZE = 9;

const Sudokusolver = () => {
  const numArray = [...Array(SIZE/3).keys()];
  return <div className="sudoku-main">
    {
      numArray.map(r => {
      return <div className="boxrow">
        <SudokuBox/>
        <SudokuBox/>
        <SudokuBox/>
      </div>})
    }
  </div>;
};
  
const SudokuBox = () => {
  const numArray = [...Array(SIZE/3).keys()];
  return <div className="sudokubox">
    {
      numArray.map(r => {
        return <div className="boxrow">
          <SudokuCell digit={r}/>
          <SudokuCell digit={r}/>
          <SudokuCell digit={r}/>
        </div>})
    }
  </div>;
}

const SudokuCell = ({digit}) => {
  return <input className="sudokucell"></input>
}

  export default Sudokusolver;