#include "Camera.h"

Camera::Camera(int width, int height)
{
   
    this->width = width;
    this->height = height;

    //initalise the viewport
    viewport.x = 0; 
    viewport.y = 0;
    viewport.w = this->width; 
    viewport.h = this->height;
}

SDL_Rect Camera::getViewport()
{
	return viewport;
}


//how to use in main below

/* 

Camera camera(800, 600);
SDL_Rect viewport = camera.getViewport(); 

*/

//then use that created variable to set for example SDL_RenderSetViewport(renderer, &viewport);

