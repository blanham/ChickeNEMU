#include <stdio.h>
#include "libchicken.h"
#include <strings.h>

//TODO: add palette funtionality

Screen *screen_init(char *name, int subsystems, int height, int width, int bpp, int scale)
{
	Screen *new = malloc(sizeof(Screen));
	int screen_bpp;
	
	//be lazy for now
	subsystems = SDL_INIT_VIDEO | SDL_INIT_JOYSTICK | SDL_INIT_AUDIO;
	
	// initialize SDL video    
	if (SDL_Init(subsystems) < 0 )
    {
        fprintf(stderr, "Unable to init SDL: %s\n", SDL_GetError() );
        return NULL;
    }
    
	// make sure SDL cleans up before exit
    atexit(SDL_Quit);

	//enables OpenGL double buffering
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	switch(bpp)
	{
		case 1 ... 8:
		default:
			screen_bpp = 8;
			break;
		
		case 16:
			screen_bpp = 16;
			break;
		
		case 32:
			screen_bpp = 32;
			break;
	}
    
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, screen_bpp);
	
	new->bpp = bpp;
	new->height = height;
	new->width = width;
	new->angle = 0.25f;
	
	new->vram = malloc(height * width * (screen_bpp/8));	
	memset(new->vram, 0xFF, height * width * (screen_bpp/8));

	new->window = SDL_CreateWindow(name,
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		width, height,
		SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
	
	if(!new->window)
	{
        fprintf(stderr, "Unable to init SDL: %s\n", SDL_GetError());
        return NULL;
	}	

	if((new->context = SDL_GL_CreateContext(new->window)) == NULL)
   	{
        fprintf(stderr, "Unable to init SDL: %s\n", SDL_GetError());
        return NULL;
	}

	SDL_GL_SetSwapInterval(1);

	//OpenGL Setup
	glEnable(GL_TEXTURE_2D);

	glClearColor( 0.0f, 0.0f, 0.0f, 0.0f);
	glViewport(0, 0, width, height);

	glClear(GL_COLOR_BUFFER_BIT);
	glDisable(GL_DEPTH_TEST);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glOrtho(0.0f, width, height, 0.0f, -1.0f, 1.0f);
	
	glMatrixMode(GL_MODELVIEW);

	glGenTextures(1, &new->texture);

	// Bind the texture object
	glBindTexture(GL_TEXTURE_2D, new->texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    return new;
}

//int screen_draw_raw
int screen_draw(Screen *screen)
{
	glBindTexture(GL_TEXTURE_2D, screen->texture);
	glClear(GL_COLOR_BUFFER_BIT);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, screen->height, screen->width, 0, GL_RGBA, GL_UNSIGNED_BYTE, screen->vram);
			glBindTexture(GL_TEXTURE_2D, screen->texture);
			glBegin(GL_QUADS);
			//probably needs to be fixed for rotation
				glTexCoord2d(0,1); glVertex2i(0, 0);
				glTexCoord2d(0,0); glVertex2i(0, screen->width);
				glTexCoord2d(1,0); glVertex2i(screen->width,  screen->height);
				glTexCoord2d(1,1); glVertex2i(screen->height, 0);
			glEnd();
			SDL_GL_SwapBuffers();
			SDL_GL_SwapWindow(screen->window);
}


