#include "defs.h"


shared_ptr<SDL_Window> create_window() {
	SDL_Window* temp_window;
	temp_window = SDL_CreateWindow("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
									WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_RESIZABLE);

	if (!temp_window) {
		cout << "error creating window" << endl;
		exit_program();
	}

	shared_ptr<SDL_Window> window(temp_window, SDL_DestroyWindow);
	return window;
}


shared_ptr<SDL_Renderer> create_main_renderer(SDL_Window* window) {
	Uint32 render_flags = SDL_RENDERER_ACCELERATED;
    SDL_Renderer* mainRend = SDL_CreateRenderer(window, -1, render_flags);

    if (!mainRend) {
      cout << "error creating renderer: " << SDL_GetError() << endl;
      exit_program();
    }

    shared_ptr<SDL_Renderer> main_renderer(mainRend, SDL_DestroyRenderer);
    return main_renderer;
}


shared_ptr<SDL_Texture> create_texture_from_image(SDL_Renderer* mainRend, string img_path) {
	// necessary for IMG_Load function which takes in a const char* parameter
	const char* img_path_cstr = img_path.c_str();
	// cout << img_path << endl;
	// try {
		SDL_Surface* image_surface = IMG_Load(img_path_cstr);
	// }
	// catch (...) { }
	
	if (!image_surface) {
		cout << "error loading background image" << endl;
		exit_program();
	}
	SDL_Texture* image_texture = SDL_CreateTextureFromSurface(mainRend, image_surface);
	SDL_FreeSurface(image_surface);

	if (!image_texture) {
		cout << "error creating texture from image" << endl;
		exit_program();
	}

	shared_ptr<SDL_Texture> sp_image_texture(image_texture, free_texture);

	return sp_image_texture;
}


void exit_program() {
	SDL_Quit();
	exit(1);
}


void free_texture(SDL_Texture* txt) {
	static int i = 0;
	if (i == 0) {
		cout << "deleting texture" << endl;
		i++;
	}
	SDL_DestroyTexture(txt);
}


void here() {
	cout << "here" << endl;	
}




