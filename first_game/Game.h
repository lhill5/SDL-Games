#ifndef GAME
#define GAME

class Game {
	private:
		static shared_ptr<SDL_Window> window;
		static shared_ptr<SDL_Renderer> mainRend;
		static float gravity;

	public:
		Game();
		static SDL_Window* get_window();
		static SDL_Renderer* get_main_rend();
		static float get_gravity();

};


#endif