import "css/SudokuPage.css"
import SudokuUpload from "./SudokuUpload";

const SudokuButtons = ({state}) => {
    return <div className="sudoku-button-div">
        <button className="sudoku-button" onClick={() => state.solveSudoku()}>SOLVE</button>
        <button className="sudoku-button" onClick={() => state.resetDigits()}>RESET</button>
        <SudokuUpload></SudokuUpload>
    </div>;
};

export default SudokuButtons;