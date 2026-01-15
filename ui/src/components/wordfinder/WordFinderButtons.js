import "css/WordFinderPage.css"

const WordFinderButtons = ({state}) => {
    return <div className="word-finder-button-div">
        <button className="word-finder-button" onClick={() => state.solve()}>SOLVE</button>
        <button className="word-finder-button" onClick={() => state.reset()}>RESET</button>
    </div>;
};

export default WordFinderButtons;