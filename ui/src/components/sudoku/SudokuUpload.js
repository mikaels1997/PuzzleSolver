import { sendSudokuFile } from 'api';
import { useRef } from 'react'

const SudokuUpload = ({ state }) => {
  const fileInputRef = useRef();
  
  const handleChange = async (event) =>{
    const file = event.target.files[0];
    if (!file) return;
    const allowedExtensions = ["png", "jpg"];
    const fileExtension = file.name.split(".").pop().toLowerCase();
    if (!allowedExtensions.includes(fileExtension)) {
      alert("Invalid file type!");
      return;
    } else {
      const response = await sendSudokuFile(file);
      formGrid(response.numbers);
    }
  }

  const formGrid = (numbers) => {
    if (!Array.isArray(numbers) || numbers.length !== 81) {
      throw new Error("Input must be an array of length 81");
    }

    const grid = [];
    for (let i = 0; i < 9; i++) {
      const row = numbers.slice(i * 9, (i + 1) * 9);
      const noZeros = row.map(n => n === 0 ? null : n);
      grid.push(noZeros);
    }
    state.setGrid(grid)
  }
  
  return(
    <>
      <button className="sudoku-button" onClick={()=>fileInputRef.current.click()}>
        UPLOAD
      </button>
      <input onChange={handleChange} multiple={false} ref={fileInputRef} type='file'hidden/>
    </>
  )
}

export default SudokuUpload;