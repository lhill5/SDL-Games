#ifndef MAINCHARACTER
#define MAINCHARACTER

class MainCharacter {
	protected:
		SDL_Renderer* mainRend;
		vector<string> animation_folder_names;
		map<string, vector<pair<shared_ptr<SDL_Texture>, SDL_Rect>>> character_animations;
		vector<string> animation_commands;

		// map<string, vector<shared_ptr<SDL_Texture>>> character_images;
		int image_count;

		// vector<int> end_row_num;
		// vector<const char*> row_name;
	public:
		MainCharacter(SDL_Renderer* mainRend);
		void _load_in_images(string folder_name);
		int get_num_files_in_folder(string folder_name);
		void _draw_animation(string command, bool increment=true);
		void walk(int left, int right, int up, int down);


};

#endif

