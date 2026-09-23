import logo from '../assets/Logo.png';
import eCommerceLogo from "../assets/eCommerceClustering.png";
import fileSystemLogo from "../assets/fileSystem.png";
import starWarsSearchLogo from "../assets/starWarsSearch.png";
import transportationLogo from "../assets/avenueEProjectPrototype.png";
import sevenWondersLogo from "../assets/7WondersScoreSheet.png";
import mipsProjectLogo from "../assets/mipsUtilities.png";

import emailIcon from "../assets/emailIcon.png";
import linkedInIcon from "../assets/linkedInIcon.png";
import githubIcon from "../assets/githubIcon.png";

import ProjectCard from '../components/ProjectCard'
import { useColorContext } from '../contexts/ColorContext.jsx'

function Home() {

    const darkestColor = useColorContext().colorPalette[0] || 'black'
    const secondDarkestColor = useColorContext().colorPalette[1] || 'darkgrey'
    const middleColor = useColorContext().colorPalette[2] || 'grey'
    const secondLightestColor = useColorContext().colorPalette[3] || 'lightgrey'
    const lightestColor = useColorContext().colorPalette[4] || 'white'

    return (
        <div 
        style={{background: `linear-gradient(${darkestColor}, ${secondDarkestColor})`}}>

            <div className="header" 
            style={{backgroundColor: secondDarkestColor}}>
                <img src={logo} alt="Diamond JT Logo" />

                <form>
                    <button type="submit">
                        Change Colors
                    </button>
                </form>

            </div>


            <div className="about-section">
                <div className="name-title">
                    <h1
                    style={{color: darkestColor, background: `radial-gradient(${lightestColor}, transparent)` }}>
                        Hi, I'm Josh T
                    </h1>
                </div>

                <p
                style={{color: middleColor}}>
                    I'm a CS student at UC Davis who builds software across <br/> 
                    web, systems and machine learning. <br/>
                    Here's what I've been working on.
                </p>
                
            </div>

            <div className="projects-section">

                <h1
                style={{color: secondLightestColor}}>
                    Projects:
                </h1>
                
                <ProjectCard title="E-Commerce Customer Analysis" image={eCommerceLogo} link="https://github.com/Life-Trekker/Portfolio/tree/main/projects/eCommerceUnsupervisedModel"/>
                <ProjectCard title="Linux File System Utilities" image={fileSystemLogo} link="https://github.com/Life-Trekker/Portfolio/tree/main/projects/fileSystemUtilities"/>
                <ProjectCard title="Star Wars Character Search Engine" image={starWarsSearchLogo} link=".../projects/starWarsCharacterSearch/"/>
                <ProjectCard title="Avenue E Transportation Project Prototype" image={transportationLogo} link="https://github.com/Life-Trekker/Portfolio/tree/main/projects/avenueETransportationProject"/>
                <ProjectCard title="7 Wonders Virtual Score Sheet" image={sevenWondersLogo} link="https://github.com/Life-Trekker/Portfolio/tree/main/projects/digital7WondersScoreSheet"/>
                <ProjectCard title="MIPS Assembly Utilities Library" image={mipsProjectLogo} link="https://github.com/Life-Trekker/Portfolio/tree/main/projects/mipsAssemblyUtilitiesLibrary"/>


            </div>

            <div className="contact-section">
                
                <h1
                style={{color: secondLightestColor}}>
                    Contact Me:
                </h1>

                <a href="mailto:lifetrekker101@outlook.com"><img src={emailIcon}/></a>

                <a href="https://www.linkedin.com/in/joshtcompsci/"><img src={linkedInIcon}/></a>

                <a href="https://github.com/Life-Trekker"><img src={githubIcon}/></a>
            </div>
        </div>
    );
}


export default Home
