import axios from 'axios';

export async function sendSudoku(payload) {
    let response;
    await axios.post('http://localhost:8000/solve', {grid: payload})
        .then((res) => {response = res.data;})
        .catch((error) => console.error(error));
    return response;
}

export async function sendSudokuFile(file) {
    const formData = new FormData();
    formData.append("file", file);

    axios.post("http://localhost:8000/upload", formData, {
    headers: {
        "Content-Type": "multipart/form-data",
    },
    })
    .then(res => console.log("Server response:", res.data))
    .catch(err => console.error(err));
}    
