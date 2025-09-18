/*
Author: Josh T
File Name: main.js for Project 2
*/

function init()
{
  //create shortcut vars
    
  //get the back button and make it visible
  const backBtn = document.querySelector(".backBtn");
  backBtn.style.display = "inline-block";
    
  //get the next button and make it visible
  const nextBtn = document.querySelector(".nextBtn");
  nextBtn.style.display = "inline-block";

  //get the breakfast gallery button and make it visible
  const bfastBtn = document.querySelector(".bfastBtn");
  bfastBtn.style.display = "inline-block";

  //get the lunch gallery button and make it visible
  const lunchBtn = document.querySelector(".lunchBtn");
  lunchBtn.style.display = "inline-block";
    
  //get the dinner gallery button and make it visible
  const dinnerBtn = document.querySelector(".dinnerBtn");
  dinnerBtn.style.display = "inline-block";
    
  //get the all the galleries that hold the slides, all the slides and the caption
  const allFrames = document.getElementsByClassName("gallery");
  const allSlides = document.getElementsByClassName("slide");
  const caption = document.getElementById("caption");

  console.log(allFrames);
    
  //with JS active, hide all images
  for(i = 0; i < allSlides.length; i++)
  {
      allSlides[i].style.display = "none";
  }

  //with JS active, hide all the galleries
  //I wasn't sure if we had to use a forEach loop, so I revised this section of code
  for(i = 0; i < allFrames.length; i++)
  {
    allFrames[i].style.display = "none";
  }

  //show the first gallery
  allFrames[0].style.display = "block";

  //set the first gallery to the current gallery
  allFrames[0].setAttribute("id", "currentGallery");

  //show the first slide
  allSlides[0].style.display = "block";

  //set the caption to the first slide's caption
  caption.innerHTML = allSlides[0].alt;

  //give this first slide a class of current so that the change slide function can execute
  allSlides[0].setAttribute("class", "current");
    
  //have the slides automatically advance every 5 seconds
  timer = window.setInterval(changeSlide, 5000);
    
  //make next button active
  nextBtn.addEventListener("click", changeSlide);
    
  //make back button active
  backBtn.addEventListener("click", changeSlide);

  //make the breakfast gallery button active
  bfastBtn.addEventListener("click", changeGallery);

  //make the lunch gallery button active
  lunchBtn.addEventListener("click", changeGallery);

  //make dinner gallery button active
  dinnerBtn.addEventListener("click", changeGallery);

  
  
  
}  // end init
  
//this function changes the current slide, shifting the carousel forward or backwards
function changeSlide(e) {
  
    //get the current gallery containing all the images, the images themselves and the figcaption
    const frame = document.getElementById("currentGallery");
    const slides = frame.querySelectorAll("img");
    const caption = document.getElementById("caption");
  
    //shortcut vars
  
    //find the slide that is currently displayed
    let showing = document.querySelector(".current");

    //get the slide that should be before that
    let nextUp = showing.previousElementSibling;
  
    //if this function was called using the next button or the automatic timer,
    if(!e || e.target.getAttribute("class") === "nextBtn")
    {
      //get the slide that should be after that
      nextUp = showing.nextElementSibling;
    }
  
    // deactivate current image
  
    //hide the current image
    showing.style.display = "none";
  
    //remove it's current class and reset it to slide
    showing.setAttribute("class", "slide");
  
    //if the next slide variable is null,
    if (nextUp === null) {

      //reset it to the first slide
      nextUp = slides[0];
    }

    //if the next slide variable has something that isn't a slide,
    if (nextUp.getAttribute("class") != "slide") {

        //reset it to the last slide
        nextUp = slides[slides.length - 1];
    }
  
    // activate next image.

  
    //display the next image
    nextUp.style.display = "block";
  
    //set the class of this element to current
    nextUp.setAttribute("class", "current");

    //if this function was called using the next button or the automatic timer,
    if(!e || e.target.getAttribute("class") === "nextBtn")
    {
      //have it transition from the right
      nextUp.style.animation = "easeInRight 1s ease";
    }
    //otherwise,
    else
    {
      //have it transition from the left
      nextUp.style.animation = "easeInLeft 1s ease";
    }
  
    //update the caption
    caption.innerHTML = nextUp.alt;

    //reset the timer
    clearInterval(timer);
    timer = window.setInterval(changeSlide, 5000);
  
  }


  //this function changes the current gallery
  function changeGallery(e) {

    //get the all the galleries and all the gallery changing buttons
    const allFrames = document.getElementsByClassName("gallery");
    const allGalleryButtons = document.querySelectorAll(".galleryControls button");

    //get the currently showing gallery
    let showingFrame = document.getElementById("currentGallery");

    //create a variable to hold the index of the next frame
    let indexOfNextFrame = 0;

    //find the index of the button that was just pressed and set the indexOfNextFrame variable to that
    for(let i = 0; i < allGalleryButtons.length; i++)
    {
      if(e.target === allGalleryButtons[i])
      {
        indexOfNextFrame = i;
        break;
      }
    }

    //get the frame that is at the desired index
    //this way, the first gallery changing button will change to the first gallery, the second to the second and so on
    let nextFrame = allFrames[indexOfNextFrame];

    //remove the currentGallery id from the currently showing gallery
    showingFrame.setAttribute("id", "");

    //hide the currently showing gallery
    showingFrame.style.display = "none";

    //add the currentGallery id to the next gallery to display
    nextFrame.setAttribute("id", "currentGallery");

    //make this new gallery visible
    nextFrame.style.display = "block";

    //get the slide that was just showing
    let showingSlide = document.querySelector(".current");

    //remove the current class from it and hide it
    showingSlide.setAttribute("class", "slide");
    showingSlide.style.display = "none";

    //get the first slide of the new gallery
    let nextSlide = nextFrame.querySelector("img");

    //set it's class to current, make it visible and have it transition from the right
    nextSlide.setAttribute("class", "current");
    nextSlide.style.display = "block";
    nextSlide.style.animation = "easeInRight 1s ease";

    //get the caption
    const caption = document.getElementById("caption");

    //update the caption
    caption.innerHTML = nextSlide.alt;

    //reset the timer
    clearInterval(timer);
    timer = window.setInterval(changeSlide, 5000);

  }

  
  //call the init function once the DOM loads
  document.addEventListener('DOMContentLoaded', init);