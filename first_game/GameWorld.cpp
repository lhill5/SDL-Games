#include "defs.h"

GameWorld::GameWorld() {

	if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO) != 0) {
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		exit(1);
	} else {
		cout << "successfully initalized SDL" << endl;
	}

	this->window = nullptr;
	this->mainRend = nullptr;
};


GameWorld::~GameWorld() {
	this->destroyAll();
	SDL_Quit();
};


void GameWorld::create_window() {
	SDL_Window* window = SDL_CreateWindow("Game",
                      SDL_WINDOWPOS_UNDEFINED,
                      SDL_WINDOWPOS_UNDEFINED,
                      WINDOW_WIDTH, WINDOW_HEIGHT,
                      SDL_WINDOW_RESIZABLE);
	
	if (!window) {
		printf("error creating window: %s\n", SDL_GetError());
		this->destroyAll(true);
	} else {
		this->window = window;
	}
};


SDL_Window* GameWorld::get_window() {
	return this->window;
};


void GameWorld::create_main_renderer() {
	// create a renderer, which sets up the graphics hardware
    Uint32 render_flags = SDL_RENDERER_ACCELERATED;
    SDL_Renderer* mainRend = SDL_CreateRenderer(this->window, -1, render_flags);
    if (!mainRend)
    {
        printf("error creating renderer: %s\n", SDL_GetError());
        this->destroyAll(true);
    }
};


SDL_Renderer* GameWorld::get_main_renderer() {
	return this->mainRend;
};


SDL_Texture* create_texture_from_image(string img_path) {
	SDL_Surface* image = IMG_Load(img_path);
	if (!image) {
		cout << "error creating surface, couldn't find image" << endl;
		this->destroyAll(true);
	}
}



void GameWorld::destroyAll(bool quit) {
	cout << "destroying!!" << endl;

	// free objects in reverse order they were created
	if (this->mainRend) SDL_DestroyRenderer(this->mainRend);
	if (this->window) SDL_DestroyWindow(this->window);

	// if quit is true, then there was a error creating sdl object 
	// (window/renderer/surface/texture/etc.) so force program to exit
	if (quit) {
		SDL_Quit();
		exit(1);
	}
};

