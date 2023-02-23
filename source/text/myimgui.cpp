
# include "imgui.h"
# include "imgui_impl_sdl2.h"
# include "imgui_impl_opengl3.h"
# include "imgui_internal.h"
# include <stdio.h>
# include <SDL2/SDL.h>

void myimgui_init ( SDL_Window * window , SDL_GLContext gl_context , const char * glsl_version ) {
	ImGui :: CreateContext ( ) ;
	ImGuiIO & io = ImGui :: GetIO ( ) ;
	( void ) io ;
	ImGui :: StyleColorsDark ( ) ;
	// Setup Platform/Renderer backends
	ImGui_ImplSDL2_InitForOpenGL ( window , gl_context ) ;
	ImGui_ImplOpenGL3_Init ( glsl_version ) ;
	ImFontConfig config ;
	config . MergeMode = true ;
	io . Fonts -> AddFontFromFileTTF ( "/usr/share/fonts/freefontsCJK/SourceCodePro-Medium.otf" , 16.0f ) ;
	io . Fonts -> AddFontFromFileTTF ( "/usr/share/fonts/freefontsCJK/荆南麦圆体.ttf" , 16.0f , & config ,
		io . Fonts -> GetGlyphRangesChineseFull ( ) ) ;
	//ImGui_ImplOpenGL3_NewFrame ( ) ;
}

void myimgui_event ( SDL_Event * sdlEvent ) {
	ImGui_ImplSDL2_ProcessEvent ( sdlEvent ) ;
}
void myimgui_render ( ) {
	ImGui_ImplOpenGL3_RenderDrawData ( ImGui :: GetDrawData ( ) ) ;
}
void myimgui_framestart ( ) {
	ImGui_ImplOpenGL3_NewFrame ( ) ;
	ImGui_ImplSDL2_NewFrame ( ) ;
	ImGui :: NewFrame ( ) ;
}
static bool show_demo_window = false ;
static bool show_another_window = false ;
static ImVec4 clear_color = ImVec4 ( 0.45f , 0.55f , 0.60f , 1.00f ) ;
void myimgui_draw ( ) {
	// 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
	if ( show_demo_window )
	ImGui :: ShowDemoWindow ( & show_demo_window ) ;

	// 2. Show a simple window that we create ourselves. We use a Begin/End pair to create a named window.
	{
		static float f = 0.0f ;
		static int counter = 0 ;

		ImGui :: Begin ( "ES汉化" ) ; // Create a window called "Hello, world!" and append into it.
		//ImGui :: Text ( "ES汉化" ) ; // Display some text (you can use a format strings too)
		ImGui :: Checkbox ( "Demo Window" , & show_demo_window ) ; // Edit bools storing our window open/close state
		ImGui :: Checkbox ( "Another Window" , & show_another_window ) ;
		{
			//ImGuiWindow * window = ImGui :: GetCurrentWindow ( ) ;
			//printf ( "[d] %f %f %f\n" ,
			//	window -> DC . CursorPos . x ,
			//	window -> DC . CursorPos . y ,
			//	window -> DC . CurrLineTextBaseOffset ) ;
		}
		ImGui :: SliderFloat ( "float" , & f , 0.0f , 1.0f ) ; // Edit 1 float using a slider from 0.0f to 1.0f
		ImGui :: ColorEdit3 ( "clear color" , ( float * ) & clear_color ) ; // Edit 3 floats representing a color
		if ( ImGui :: Button ( "Button" ) ) // Buttons return true when clicked (most widgets return true when edited/activated)
		counter ++ ;
		ImGui :: SameLine ( ) ;
		ImGui :: Text ( "counter = %d" , counter ) ;

		ImGui :: Text ( "Application average %.3f ms/frame (%.1f FPS)" , 1000.0f / ImGui :: GetIO ( ) . Framerate , ImGui :: GetIO ( ) . Framerate ) ;
		ImGui :: End ( ) ;
	}
	ImGui :: Render ( ) ;
}

