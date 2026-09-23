import {createContext, useState, useContext, useEffect} from "react"
import { getRandomColorPalette } from '../services/api'

const ColorContext = createContext()

export const useColorContext = () => useContext(ColorContext)

export const ColorProvider = ({children}) => {
    const [colorPalette, setColorPalette] = useState([])

    useEffect(() => {
        const fetchColorPalette = async () => {
            const colorData = await getRandomColorPalette()
            const pallette = colorData.map(color => color.hex.value) // Extract hex values from the color objects
            setColorPalette(pallette)
        }
        fetchColorPalette()
    }, [])

    const value = {
        colorPalette
    }

    return <ColorContext.Provider value={value}>
        {children}
    </ColorContext.Provider>
}