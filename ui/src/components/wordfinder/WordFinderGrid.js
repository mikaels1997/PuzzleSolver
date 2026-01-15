import "css/WordFinderPage.css";
import { observer } from 'mobx-react';

const SIZE = 4;

const WordFinderGrid = ({state}) => {
    const rowArray =  [...Array(SIZE).keys()];
    return <div className="word-finder-grid">
        {
        rowArray.map((r, i) => {
        return <div className="boxrow" key={r}>
            <Tile state={state} row={i} col={0}></Tile>
            <Tile state={state} row={i} col={1}></Tile>
            <Tile state={state} row={i} col={2}></Tile>
            <Tile state={state} row={i} col={3}></Tile>            
        </div>})
    }
    </div>;
};

const Tile = observer(({state, row, col}) => {
    return <input className="word-finder-tile" 
        value={state.input[row][col] ?? ""}
        maxLength={2}
        onChange={(e) => changeInput(e, row, col, state)}>
        </input>
})

function changeInput(event, row, col, state) {
    if (event.target.value !== "") {
      event.target.value = event.target.value.replace(/[^a-zäåö]/g, "");
      event.target.value = event.target.value.toUpperCase()
      if (event.target.value === "") return;
    }
    const input = event.target;
    const inputValue = event.target.value;
    input.value = inputValue[inputValue.length - 1];
    state.updateLetter(row, col, input.value);
  }

export default WordFinderGrid;