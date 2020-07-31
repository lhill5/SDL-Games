#include "defs.h"

typedef struct PlayerDirection {
	int left;
	int right;
	int up;
	int down;
} PlayerDirection;


int main(void) {

	shared_ptr<SDL_Window> window = create_window();
	shared_ptr<SDL_Renderer> mainRend_guard = create_main_renderer(window.get());
	SDL_Renderer* mainRend = mainRend_guard.get();

	const char* bg_path = "images/tileset/BG/BG.png";
	shared_ptr<SDL_Texture> background_guard = create_texture_from_image(mainRend, bg_path);
	SDL_Texture* background = background_guard.get();

	// load_in_folder_sprites("zombie_images/");
	// load_in_folder_sprites("zombie_animations/");

	MainCharacter hero(mainRend);
	// for (string command : hero.animation_commands) {
	// 	cout << command << endl;
	// }
	// hero.load_in_images("images/zombie_images");

	float fps = 10;
	int up = 0, down = 0, left = 0, right = 0;

	int x_pos = hero.get_xpos();
	int y_pos = hero.get_ypos();
	int x_vel, y_vel;

	// animation loop
	bool game_loop = true;
	while (game_loop) {
		// event loop
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
				case SDL_QUIT:
					game_loop = false;
					break;
				case SDL_KEYDOWN:
					// cout << "keydown" << endl;
					switch(event.key.keysym.scancode) {
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
							up = 1;
							left = right = down = 0;
							break;
						case SDL_SCANCODE_S:
						case SDL_SCANCODE_DOWN:
							down = 1;
							left = right = up = 0;
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

		int error = SDL_RenderCopy(mainRend, background, NULL, NULL);
		hero.walk(left, right, up, down);

		SDL_RenderPresent(mainRend);


		SDL_Delay(1000/fps); // wait 1/60 second (parameter in milliseconds)

	}
    return 0;
}



