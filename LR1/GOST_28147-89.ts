import { textToBytes } from './utils';

const combineFourUInt8ToOneUInt32 = (fourBytes: Uint8Array): any => {
    if (fourBytes.length !== 4) {
        throw Error('combineFourUInt8ToOneUInt32: not 4 bytes');
    }

    return new DataView(fourBytes.buffer).getUint32(0);
};

const convertNumberToBits = ()
const makeTextMultipleOf8Bytes = (text: string): string => {
    let response: string = text;

    while (response.length % 8 !== 0) {
        response += ' ';
    }

    return response;
};

const splitUIntArrayOnBlocks = (array: Uint8Array, blockSize: number): Uint8Array[] => {
  const response: Uint8Array[] = [];

  for (let index = 0; index < array.length; index += blockSize) {
      response.push(array.slice(index, index + blockSize));
  }

  return response;
};

export const encryptByGOST_2814789 = (openText: string, key: Uint8Array) => {
    // split open text to blocks
    const source: string = makeTextMultipleOf8Bytes(openText);
    const textBytes: Uint8Array = textToBytes(source);
    const textBlocks: Uint8Array[] = splitUIntArrayOnBlocks(textBytes, 8);

    // encrypt every block
    const encrypted: Uint8Array = new Uint8Array(textBytes.length).fill(0x00);
    let index: number = 0;

    for (const textBlock of textBlocks) {
        const encryptedBlock = encryptBlock(textBlock, key);

        for (const byte of encryptedBlock) {
            encrypted[index++] = byte;
        }
    }

    return encrypted;
};



const F = (part: Uint8Array, subKey: Uint8Array): Uint8Array => {
    const sumWithModule32 = (combineFourUInt8ToOneUInt32(part) + combineFourUInt8ToOneUInt32(subKey)) % 0b100000000000000000000000000000000;

};

const encryptBlock = (block: Uint8Array, key: Uint8Array): Uint8Array => {
    const left = block.slice(0, 4); // 4 bytes
    const right = block.slice(4); // 4 bytes
    const keyBlocks = splitUIntArrayOnBlocks(key, 8); // 8 subkeys of length 4 bytes each

    for ()
};
