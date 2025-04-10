/*
Author: Josh T
File Name: main.js for Portfolio
*/

//run init function when page loads
document.addEventListener('DOMContentLoaded', init);



//run this function as soon as the page initializes
function init() {

  //make variables for a collection of all project tiles and a collection of all project text
  const project_tiles = document.getElementsByClassName("project-tile");
  const project_text = document.getElementsByClassName("project-text");

  //for each project tile
  for (let i = 0; i < project_text.length; i++) {

    //hide the project text by default
    project_text[i].style.opacity = "0%";

    //when this project tile is hovered over, call changeTileOpacity to fade it and show the text
    project_tiles[i].addEventListener("mouseover", () => (changeTileOpacity(i, true)));

    //when the mouse is moved off this project tile, call changeTileOpacity to unfade it and hide the text
    project_tiles[i].addEventListener("mouseout", () => (changeTileOpacity(i, false)));

  }



}

//call this function when a project tile is hovered over or off of

//index : the index of the project tile in the project tiles collection
//showText : whether to show the project tile's text or hide it
function changeTileOpacity(index, showText) {

  //make variables for a collection of all project tiles and a collection of all project text
  const project_tiles = document.getElementsByClassName("project-tile");
  const project_text = document.getElementsByClassName("project-text");

  //if we want to show the project tile's text
  if (showText) {

    //fade the project tile image to 50% opacity
    project_tiles[index].children[0].style.opacity = "50%";

    //show the project tile text
    project_text[index].style.opacity = "100%";
  }
  else {

    //unfade the project tile image
    project_tiles[index].children[0].style.opacity = "100%";

    //hide the project tile text
    project_text[index].style.opacity = "0%";
  }
}

