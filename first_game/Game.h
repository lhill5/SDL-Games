#ifndef GAME
#define GAME

class Game {
	private:
		static shared_ptr<SDL_Window> window;
		static shared_ptr<SDL_Renderer> mainRend;

	public:
		Game();
		static SDL_Window* get_window() { return window.get(); }
		static SDL_Renderer* get_main_rend() { return mainRend.get(); }
};


#endif