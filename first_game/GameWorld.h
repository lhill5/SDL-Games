#ifndef GAMEWORLD
#define GAMEWORLD 

class GameWorld {
	protected:
		SDL_Window* window;
		SDL_Renderer* mainRend;
	public:
		GameWorld();
		~GameWorld();

		void create_window(); // setter
		SDL_Window* get_window(); // getter

		void create_main_renderer();
		SDL_Renderer* get_main_renderer();

		SDL_Texture* create_texture_from_image(string img_path);
		
		void destroyAll(bool quit=false);
};

#endif

