import React, { useEffect, useState } from 'react';
import axios from 'axios';

export function sendSudoku(state) {
    const payload = JSON.stringify(state.numMatrix);
    let response;
    axios.post('http://localhost:8080/', payload)
        .then((res) => {response = res.data; console.log(response, "RESPONSE")})
        .catch((error) => console.error(error));
    return response;
}


function PuzzleApi({state}) {
    const [response, setResponse] = useState('');
    const payload = JSON.stringify(state.numMatrix);
    useEffect(() => {
        axios.post('http://localhost:8080/', payload)
            .then((res) => setResponse(res.data))
            .catch((error) => console.error(error));
    }, []);
    return (
    <div>
        <p>{response}</p>
    </div>
    );
}

export default PuzzleApi;