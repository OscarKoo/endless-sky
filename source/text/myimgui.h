//# include "imgui.h"
//# include "imgui_impl_sdl2.h"
//# include "imgui_impl_opengl3.h"
# include <stdio.h>
# include <SDL2/SDL.h>

void myimgui_init ( SDL_Window * window , SDL_GLContext gl_context , const char * glsl_version ) ;

void myimgui_event ( SDL_Event * sdlEvent ) ;

void myimgui_render ( ) ;

void myimgui_draw ( ) ;

void myimgui_framestart ( ) ;

