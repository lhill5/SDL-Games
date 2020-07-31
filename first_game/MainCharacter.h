#ifndef MAINCHARACTER
#define MAINCHARACTER

class MainCharacter {
	protected:
		int x_pos = 0, y_pos = 0;
		int x_vel, y_vel;
		int width = 64, height = 64;
		string prev_direction = "walk_front";

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
		void _draw_animation(string command, bool pause=false);
		void walk(int left, int right, int up, int down);
		
		void set_xpos(int x_pos);
		int get_xpos();
		void set_ypos(int y_pos);
		int get_ypos();


};

#endif

