
// This is the main SDL include file
#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct turtle
{
	int x;
	int y;
	int angle;
	bool pen;
	void pen_up()
	{
		pen = 
	}
	void pen_down()
	{
		pen = 
	}
} turtle;
void pointy(SDL_Renderer *renderer, int width, int height)
{
	int x, y;
	SDL_SetRenderDrawColor(renderer, 255, 125, 125, 255);
	for (x = 10, y = 10; x < width - 10; x += ((width - 20) / 20), y += ((height - 20) / 20))
	{
		SDL_RenderDrawLine(renderer, x, y, x + 15, y + 15);
	}
}
typedef struct RGBcolour
{
	Uint8 r;
	Uint8 g;
	Uint8 b;
} RGBcolour;

void line(SDL_Renderer *renderer, int wdth, int hght, int x0, int y0, int xn, int yn, RGBcolour c)
{
	int dx = abs(xn - x0), sx = x0 < xn ? 1 : -1;
	int dy = abs(yn - y0), sy = y0 < yn ? 1 : -1;
	int error = (dx > dy ? dx : -dy) / 2, e2;
	SDL_SetRenderDrawColor(renderer, c.r, c.g, c.b, 255);
	while (1)
	{
		/* draw point only if coordinate is valid */
		if (x0 >= 0 && x0 < wdth && y0 >= 0 && y0 < hght)
			SDL_RenderDrawPoint(renderer, x0, y0);
		if (x0 == xn && y0 == yn)
			break;
		e2 = error;
		if (e2 > -dx)
		{
			error -= dy;
			x0 += sx;
		}
		if (e2 < dy)
		{
			error += dx;
			y0 += sy;
		}
	}
}
int main(void)
{
	/* These are some variables to help show you what the parameters are for the initialisation function.
	   You can experiment with the numbers to see what they do. */
	int winPosX = 100;
	int winPosY = 100;
	int winWidth = 640;
	int winHeight = 480;
	int go;

	/* This is our initialisation phase

	   SDL_Init is the main initialisation function for SDL
	   It takes a 'flag' parameter which we use to tell SDL what systems we are going to use
	   Here, we want to initialise everything, so we give it the flag for this.
	   This function also returns an error value if something goes wrong,
	   so we can put this straight in an 'if' statement to check and exit if need be */
	if (SDL_Init(SDL_INIT_VIDEO) != 0) /* alternative: SDL_INIT_EVERYTHING */
	{
		/* Something went very wrong in the initialisation, all we can do is exit */
		perror("Whoops! Something went very wrong, cannot initialise SDL :( - ");
		perror(SDL_GetError());
		return -1;
	}

	/* Now we have got SDL initialised, we are ready to create a window! */
	SDL_Window *window = SDL_CreateWindow("My Pointy Window!!!", /* The first parameter is the window title */
										  winPosX, winPosY,
										  winWidth, winHeight,
										  SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
	/* The last parameter lets us specify a number of options.
	   Here, we tell SDL that we want the window to be shown and that it can be resized.
	   You can learn more about SDL_CreateWindow here: https://wiki.libsdl.org/SDL_CreateWindow?highlight=%28\bCategoryVideo\b%29|%28CategoryEnum%29|%28CategoryStruct%29
	   The flags you can pass in for the last parameter are listed here: https://wiki.libsdl.org/SDL_WindowFlags

	   The SDL_CreateWindow function returns an SDL_Window.
	   This is a structure which contains all the data about our window (size, position, etc).
	   We will also need this when we want to draw things to the window.
	   This is therefore quite important we do not lose it! */
	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);
	/* The SDL_Renderer is a structure that handles rendering.
	   It will store all of SDL's internal rendering related settings.
	   When we create it we tell it which SDL_Window we want it to render to.
	   That renderer can only be used for this window (yes, this means we can have multiple windows). */

	/* We are now preparing for our main loop.
	   This loop will keep going round until we exit from our program by changing the int 'go' to the value false (0).
	   This loop is an important concept and forms the basis of most SDL programs you will be writing.
	   Within this loop we generally do the following things:
		 * Check for input from the user (and do something about it!)
		 * Update our graphics
		 * Draw our graphics
	*/
	go = 1;
	while (go)
	{

		/* Here we are going to check for any input events.
			   Basically when you press the keyboard or move the mouse, the parameters are stored as something called an 'event' or 'message'.
			   SDL has a queue of events. We need to check for each event and then do something about it (called 'event handling').
			   The SDL_Event is the data type for the event. */
		SDL_Event incomingEvent;

		/* SDL_PollEvent will check if there is an event in the queue - this is the program's 'message pump'.
		   If there is nothing in the queue it will not sit and wait around for an event to come along (there are functions which do this,
		   and that can be useful too!). Instead for an empty queue it will simply return 'false' (0).
		   If there is an event, the function will return 'true' (!=0) and it will fill the 'incomingEvent' we have given it as a parameter with the event data */
		while (SDL_PollEvent(&incomingEvent))
		{
			/* If we get in here, we have an event and need to figure out what to do with it.
			   For now, we will just use a switch based on the event's type */
			switch (incomingEvent.type)
			{
			case SDL_QUIT:
				/* The event type is SDL_QUIT.
				   This means we have been asked to quit - probably the user clicked on the 'x' at the top right corner of the window.
				   To quit we need to set our 'go' variable to false (0) so that we can escape out of the main loop. */
				go = 0;
				break;

				/* If you want to learn more about event handling and different SDL event types, see:
				  https://wiki.libsdl.org/SDL_Event
				  and also: https://wiki.libsdl.org/SDL_EventType */
			}
		}

		/* Draw our graphics */

		/* Start by clearing what was drawn before */
		/* Set the colour for drawing */
		SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
		/* Clear the entire screen to our selected colour */
		SDL_RenderClear(renderer);

		/* Call our pointy drawing */
		pointy(renderer, winWidth, winHeight);

		/* This tells the renderer to actually show its contents to the screen. */
		SDL_RenderPresent(renderer);

		/* Turns out SDL_WaitEvent just does an SDL_PollEvent and then an SDL_Delay(10) if there is nothing to do! */
		SDL_Delay(10);
	}

	/* If we get outside the main loop, it means our user has requested we exit. */

	/* Our cleanup phase, hopefully fairly self-explanatory ;) */
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}
