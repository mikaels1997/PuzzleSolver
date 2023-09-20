import React, { useEffect, useState } from 'react';
import axios from 'axios';

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