const BASE_URL = 'https://www.thecolorapi.com/'

const getRandomHex = () => {
    const letters = '0123456789ABCDEF';
    let color = '';
    for (let i = 0; i < 6; i++) {
        color += letters[Math.floor(Math.random() * 16)];
    }
    return color;
}

export const getRandomColorPalette = async () => {
    const color = getRandomHex();
    const response = await fetch(`${BASE_URL}scheme?hex=${color}&mode=monochrome-light&count=5`)
    const data = await response.json()
    console.log('Color palette data:', data.colors) // Log the entire response for debugging
    return data.colors;
}