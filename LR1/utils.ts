export const textToBytes = (text: string): Uint8Array => {
    return new TextEncoder().encode(text);
};
