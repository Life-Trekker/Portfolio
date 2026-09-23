import './App.css'
import Home from './pages/Home.jsx'

import { ColorProvider } from './contexts/ColorContext.jsx'

function App() {


  return (
    <ColorProvider>
      <Home/>
    </ColorProvider>
  );
}


export default App
