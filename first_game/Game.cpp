#include "defs.h"


shared_ptr<SDL_Window> Game::window = create_window();
shared_ptr<SDL_Renderer> Game::mainRend = create_main_renderer(window.get());
float Game::gravity = 0.5;


Game::Game() {
	get_window();
	get_main_rend();
}

SDL_Window* Game::get_window() {
	return window.get(); 
}

SDL_Renderer* Game::get_main_rend() {
	return mainRend.get(); 
}

float Game::get_gravity() {
	return gravity;
}

