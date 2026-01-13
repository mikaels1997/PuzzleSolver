import { sendSudokuFile } from 'api';
import { useRef } from 'react'

const SudokuUpload = () => {
  const fileInputRef = useRef();
  
  const handleChange = (event) =>{
    const file = event.target.files[0];
    if (!file) return;
    const allowedExtensions = ["png"];
    const fileExtension = file.name.split(".").pop().toLowerCase();
    if (!allowedExtensions.includes(fileExtension)) {
      alert("Invalid file type!");
      return;
    } else {
      sendSudokuFile(file);
    }
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