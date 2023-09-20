import "css/SudokuPage.css"
import { sendSudoku } from "api"

const SudokuButtons = ({state}) => {
    console.log(state, "JUU")
    return <div className="sudoku-button-div">
        <button className="sudoku-button" onClick={() => sendSudoku(state)}>SOLVE</button>
        <button className="sudoku-button" onClick={() => state.resetDigits()}>RESET</button>
    </div>;
};

export default SudokuButtons;