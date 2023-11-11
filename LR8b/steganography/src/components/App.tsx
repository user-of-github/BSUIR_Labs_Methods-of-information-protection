import React, { useState } from 'react';
import { UploadButton } from './UploadButton';
import { encode, decode } from '../steganography';

export default function App() {
    const [option, setOption] = useState('home');

    function handleClick(event: any) {
        const {name} = event.currentTarget;
        if (name === 'home') {
            setOption('home');
            document.getElementById('encoded-image')!.style.display = 'none';
        } else if (name === 'encode') {
            setOption('encode');
        } else if (name === 'decode') {
            setOption('decode');
        }
    }

    return (
        <div className="content">
            {option === 'home' && <button style={{margin: '1rem'}} name="encode" onClick={handleClick}>Encode</button>}
            {option === 'home' && <button style={{margin: '1rem'}} name="decode" onClick={handleClick}>Decode</button>}
            {option === 'encode' && <input id="secret" name="secret" placeholder="Enter secret message"/>}
            {option !== 'home' && <UploadButton/>}
            {option === 'encode' && <button style={{margin: '1rem'}} onClick={encode}>Encode</button>}
            {option === 'decode' && <button style={{margin: '1rem'}} onClick={decode}>Decode</button>}
            {option !== 'home' && <button style={{margin: '1rem'}} name="home" onClick={handleClick}>Return</button>}
            <img id="encoded-image" alt="encoded output"></img>
            <canvas id="canvas"></canvas>
        </div>
    );
};
