#include <stdint.h>

#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>
#include <SDL/SDL_mixer.h>

#ifdef __APPLE__
#include <OpenGL/gl.h>
#else
#include <GL/gl.h>
#endif

/* audio.c */
typedef struct {
	Mix_Music *music;
	uint16_t audio_format;
	int audio_channels;
	int audio_buffers;
} Sound;



/* util.h */
int memory_dump(char *filename, uint8_t *pointer, size_t length, size_t offset);
size_t rom_load(char *filename, uint8_t *pointer, size_t size, size_t offset);
size_t rom_load_zip(char *filename, char *zipfile, uint8_t *pointer, size_t size, size_t offset);

/* video.h */
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
	uint8_t palette[256];

} Screen;

Screen *screen_init(char *name, int subsystems, int width, int height, int bpp, int scale);
int screen_draw(Screen *screen);
