# Description:

I built a Star Wars Character Search Engine, a front-end web app in vanilla JavaScript, HTML and CSS that lets users look up any Star Wars character and see a detailed profile pulled live from the SWAPI REST API. 

The app uses async/await and the Fetch API to combine several endpoints into one profile: character stats, species, homeworld and full film appearances.  Homeworld descriptions are generated from raw climate and terrain data with custom formatting logic (correct a/an articles, pluralization and natural-language lists).  The app also supports partial-name search with "Did you mean" suggestions, a random-character feature and a state for no results.  

Each user's search history is persisted in localStorage and shown in a dropdown where users can re-run or clear past searches.  The page is also built as a progressive enhancement, so the search UI only appears when JavaScript is available.