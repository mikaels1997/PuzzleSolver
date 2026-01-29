import { makeObservable, observable, action } from 'mobx';
import toastr from 'toastr';
import { sendWordGrid } from "api"


class WordFinderState {

    input = []
    constructor() {
        this.input = this.load();
        makeObservable(this, {
            input: observable,
            updateLetter: observable
        });
    }

    load() {
        const loaded = JSON.parse(localStorage.getItem("word_finder_grid"));
        return loaded ?? this.getEmptyGrid()
    }

    updateLetter(row, col, value) {
        this.input[row][col] = value != 'undefined' ? value : undefined;
    //    localStorage.setItem("word_finder_grid", JSON.stringify(this.numMatrix));
    }

    reset() {
        this.input = this.getEmptyGrid();
    }

    getEmptyGrid() {
        let arr = new Array(4)
        for(let i = 0;i<4;i++)
            arr[i] = new Array(4)
        return arr;
    } 

    async solve() {
        const flat = this.input.flat();
        await sendWordGrid(flat);
    }
}

export default WordFinderState;