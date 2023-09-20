import SudokuGrid from "components/sudoku/SudokuGrid";
import SudokuButtons from "components/sudoku/SudokuButtons";
import SudokuState from "stores/sudoku/SudokuState";
import PuzzleApi from "api";

const sudokuState = new SudokuState();

const SudokuPage = () => {
  return <div className="sudoku-main">
    <h2>SUDOKU SOLVER</h2>
    <div className="sudoku-view">
      <SudokuGrid state={sudokuState}/>
      <SudokuButtons state={sudokuState}/>
      <PuzzleApi state={sudokuState}></PuzzleApi>
    </div>
  </div>
};

export default SudokuPage;