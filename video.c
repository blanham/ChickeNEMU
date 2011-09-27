
#include <stdio.h>
#include "video.h"
#include <strings.h>
Screen *screen_init(char *name, int subsystems, int height, int width, int bpp, int scale)
{
	Screen *new = malloc(sizeof(Screen));
	int screen_bpp;
	//be lazy for now
	subsystems = SDL_INIT_VIDEO| SDL_INIT_JOYSTICK | SDL_INIT_AUDIO;
	// initialize SDL video
    if ( SDL_Init(subsystems) < 0 )
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
	/* only correct for 8 byte pixels at the moment */
	new->vram = malloc(height*width*4);	
	memset(new->vram, 0xFF, height*width);

	new->window = SDL_CreateWindow(name,
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		width, height,
		SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
	if(!new->window)
	{
        fprintf(stderr, "Unable to init SDL: %s\n", SDL_GetError() );
        return NULL;
	}	
//	SDL_Surface *screen = SDL_GetVideoSurface();
	/* Deprecated by SDL 1.3?*/
//	if((screen = SDL_SetVideoMode(height, width, screen_bpp, SDL_OPENGL| SDL_HWSURFACE)) == NULL)
	{
  //      fprintf(stderr,"Unable to set %ix%i video: %s\n", height, width, SDL_GetError());
 //       return NULL;
	}


	if((new->context = SDL_GL_CreateContext(new->window)) == NULL)
   	{
        fprintf(stderr, "Unable to init SDL: %s\n", SDL_GetError() );
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
/*glMatrixMode(GL_TEXTURE);
  glLoadIdentity();
  glTranslatef(0.5,0.5,0.0);
  glRotatef(new->angle,0.0,0.0,1.0);
  glTranslatef(-0.5,-0.5,0.0);
*/	glMatrixMode(GL_MODELVIEW);

	glGenTextures(1, &new->texture );

	// Bind the texture object
	glBindTexture( GL_TEXTURE_2D, new->texture );

 //	glTexImage2D(GL_TEXTURE_2D, 0, 4, 256, 240, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

    return new;
}


int screen_draw(Screen *screen)
{
	glBindTexture(GL_TEXTURE_2D, screen->texture);
	glClear(GL_COLOR_BUFFER_BIT);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, screen->height, screen->width, 0, GL_RGBA, GL_UNSIGNED_BYTE, screen->vram);
			glBindTexture(GL_TEXTURE_2D, screen->texture);
			glBegin(GL_QUADS);
				glTexCoord2d(0,1); glVertex2i(0, 0);
				glTexCoord2d(0,0); glVertex2i(0, screen->width);
				glTexCoord2d(1,0); glVertex2i(screen->width, screen->height);
				glTexCoord2d(1,1); glVertex2i(screen->height, 0);
			glEnd();
			SDL_GL_SwapBuffers();
			SDL_GL_SwapWindow(screen->window);
	free(screen->vram);
}
/*

int drawScreen()
{
	glBindTexture(GL_TEXTURE_2D, texture);
	glClear(GL_COLOR_BUFFER_BIT);
	unsigned char color;
	unsigned short fuck;
	int k = 0;
	int h = 0;



	
//	for(size_t i = 0; i < 224; ++i)
//	{
		for(size_t j = 0; j < 32 ; ++j)
		{
			fuck = (RAM[0x2400 + 32*scanline + j] );

			for(size_t k = 0; k < 8; ++k)
			{
				color = 0xFF * ((fuck >> k )&0x1);

				h = j*8+k;
				
				if(h > (223-32))	pixels[h][scanline][0] = color;
				else if(h>223-144){
					pixels[h][scanline][0] = color;
					pixels[h][scanline][1] = color;
					pixels[h][scanline][2] = color;
				}
				else if(h<64){
					pixels[h][scanline][0] = color;
					pixels[h][scanline][1] = color;
					pixels[h][scanline][2] = color;
				}
				else	pixels[h][scanline][1] = color;
				//		pixels[h][i][2] = color;
				//	pixels[j*8+k][i][1] = 0xFF * (((RAM[0x2400 + 32*i + j] >> k) &0x1));
				//	pixels[j*8+k][i][2] = 0xFF * (((RAM[0x2400 + 32*i + j] >> k) &0x1));
		
			}
		}
//	}
		if(scanline == 0)
		{
			interrupt |= 0x80;
	//doOP(0xD7);
	//		SP--;
	//			RAM[SP] = PC & 0xFF;
	//			SP--;
	//			RAM[SP] = (0xFF00 & PC) >> 8;
	//			//PC++;
	//			PC = 8;
	//			printf("I?\n");
	//		
		}
		else if(scanline > 223)
		{
			
			 scanline = 0;
		//	doOP(0xCF);
			interrupt |=0x40;
		if(interrupt)
		{	glClear(GL_COLOR_BUFFER_BIT);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 224, 256, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
			glBindTexture(GL_TEXTURE_2D, texture );
			glBegin(GL_QUADS);
				glTexCoord2d(0,1); glVertex2i(0, 0);
				glTexCoord2d(0,0); glVertex2i(0, 256);
				glTexCoord2d(1,0); glVertex2i(224, 256);
				glTexCoord2d(1,1); glVertex2i(224, 0);
			glEnd();
			SDL_GL_SwapBuffers();
			SDL_GL_SwapWindow(mainwindow);}
		}
		scanline++;
		


}
*/
