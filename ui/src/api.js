import axios from 'axios';

export async function sendSudoku(state) {
    const payload = JSON.stringify(state.numMatrix);
    let response;
    await axios.post('http://localhost:8080/', payload)
        .then((res) => {response = res.data;})
        .catch((error) => console.error(error));
    return response;
}
