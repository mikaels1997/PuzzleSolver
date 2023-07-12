import "css/SudokuPage.css"

const SudokuButtons = ({state}) => {
    return <div className="sudoku-button-div">
        <button className="sudoku-button">SOLVE</button>
        <button className="sudoku-button" onClick={() => state.resetDigits()}>RESET</button>
    </div>;
};

export default SudokuButtons;