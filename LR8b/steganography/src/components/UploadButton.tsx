import React from 'react';
import { loadImage } from '../steganography';

export const UploadButton = () => {
    return (
        <label htmlFor="upload-photo">
            <input
                id="upload-photo"
                name="upload-photo"
                type="file"
                onChange={loadImage}
            />
            <div>
                <button style={{margin: '1rem'}}>
                    Upload Image
                </button>
            </div>
        </label>
    );
};
