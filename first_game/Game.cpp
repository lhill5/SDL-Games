#include "defs.h"


shared_ptr<SDL_Window> Game::window = create_window();
shared_ptr<SDL_Renderer> Game::mainRend = create_main_renderer(window.get());


Game::Game() {
	get_window();
	get_main_rend();
}

