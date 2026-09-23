import { useColorContext } from '../contexts/ColorContext.jsx'


function ProjectCard({ title, image, link }) {

  const darkestColor = useColorContext().colorPalette[0] || 'black'
  const secondLightestColor = useColorContext().colorPalette[3] || 'lightgrey'
  const lightestColor = useColorContext().colorPalette[4] || 'white'

  return (
    <>
      <a className="project-tile" href={link} target="_blank">
        <div className="movie-poster">
          <img src={image} alt={title} />
        </div>
        <div className="tile-overlay"
        style={{background: darkestColor, 'border-color': secondLightestColor}}>
        </div>

        <div className="project-text">
                <h3
                style={{color: secondLightestColor, 'text-shadow': `0px 1px 20px ${lightestColor}`}}>
                    {title}
                </h3>
        </div>

      </a>
    </>
  );
}


export default ProjectCard
