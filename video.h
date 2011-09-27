#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>
#ifdef __APPLE__
#include <OpenGL/gl.h>
#else
#include <GL/gl.h>
#endif

typedef struct {
	SDL_Surface *screen;
	SDL_GLContext context;
	SDL_Window 	*window;
	
	SDL_Event event;
	
	GLuint texture;

	int height;
	int width;
	int bpp;
	int scale;
	GLfloat angle;
	uint8_t *vram;

} Screen;

Screen *screen_init(char *name, int subsystems, int width, int height, int bpp, int scale);

