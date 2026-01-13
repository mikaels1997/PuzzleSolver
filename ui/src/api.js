import axios from 'axios';

export async function sendSudoku(payload) {
    let response;
    await axios.post('http://localhost:8000/solve', {grid: payload})
        .then((res) => {response = res.data;})
        .catch((error) => console.error(error));
    return response;
}
