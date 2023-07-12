import React, { useEffect, useState } from 'react';
import axios from 'axios';

function PuzzleApi() {
    const [response, setResponse] = useState('');
    useEffect(() => {
    axios.get('http://localhost:8080')
        .then((res) => setResponse(res.data))
        .catch((error) => console.error(error));
    }, []);

    return (
    <div>
        <p>Response from C++ Server:</p>
        <p>{response}</p>
    </div>
    );
}

export default PuzzleApi;