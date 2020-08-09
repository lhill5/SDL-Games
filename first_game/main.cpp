#include "defs.h"

typedef struct PlayerDirection {
	int left;
	int right;
	int up;
	int down;
} PlayerDirection;


int main(void) {

	// shared_ptr<SDL_Window> window = create_window();
	// shared_ptr<SDL_Renderer> mainRend_guard = create_main_renderer(window.get());

	Game game;
	SDL_Window* window = game.get_window();
	SDL_Renderer* mainRend = game.get_main_rend();

	const char* bg_path = "images/tileset/BG/BG.png";
	shared_ptr<SDL_Texture> background_guard = create_texture_from_image(mainRend, bg_path);
	SDL_Texture* background = background_guard.get();

	// load_in_folder_sprites("zombie_images/");
	// load_in_folder_sprites("zombie_animations/");

	float fps = 60;
	MainCharacter hero(mainRend, fps);
	Tileset tiles;
	// for (string command : hero.animation_commands) {
	// 	cout << command << endl;
	// }
	// hero.load_in_images("images/zombie_images");

	int up = 0, down = 0, left = 0, right = 0;
	bool jump = false;

	// animation loop
	int i = 0;

	bool game_loop = true;
	while (game_loop) {
		// event loop
		SDL_Event event;
		while (game_loop && SDL_PollEvent(&event)) {
			switch (event.type) {
				// cout << event.type << endl;
				case SDL_QUIT:
					game_loop = false;
					break;
				case SDL_KEYDOWN:
					// cout << "keydown" << endl;
					switch(event.key.keysym.scancode) {
						case SDL_SCANCODE_Q:
							game_loop = false;
							break;
						case SDL_SCANCODE_A:
						case SDL_SCANCODE_LEFT:
							left = 1;
							right = up = down = 0; // limits player to only move in one direction
							break;
						case SDL_SCANCODE_D:
						case SDL_SCANCODE_RIGHT:
							right = 1;
							left = up = down = 0;
							break;
						case SDL_SCANCODE_W:
						case SDL_SCANCODE_UP:
							break; // for now disable ability to walk up/down
							up = 1;
							left = right = down = 0;
							break;
						case SDL_SCANCODE_S:
						case SDL_SCANCODE_DOWN:
							break;
							down = 1;
							left = right = up = 0;
							break;
						case SDL_SCANCODE_SPACE:
							jump = true;
							break;
						default:
							break;
					}
					break;
				case SDL_KEYUP:
					// cout << "keyup" << endl;
					switch(event.key.keysym.scancode) {
						case SDL_SCANCODE_A:
						case SDL_SCANCODE_LEFT:
							left = 0;
							break;
						case SDL_SCANCODE_D:
						case SDL_SCANCODE_RIGHT:
							right = 0;
							break;
						case SDL_SCANCODE_W:
						case SDL_SCANCODE_UP:
							up = 0;
							break;
						case SDL_SCANCODE_S:
						case SDL_SCANCODE_DOWN:
							down = 0;
							break;
						default:
							break;
					}
					break;
			}
		}

		// cout << left << " " << right << " " << up << " " << down << endl;

		SDL_RenderClear(mainRend);

		// draw background
		SDL_RenderCopy(mainRend, background, NULL, NULL);
		// draw tiles
		tiles.draw_tile_background();
		// draw character
		hero.walk(left, right, up, down, jump);
		
		SDL_RenderPresent(mainRend);


		SDL_Delay(1000/fps); // wait 1/60 second (parameter in milliseconds)

	}

	tiles.print_bg_coords();

    return 0;
}



