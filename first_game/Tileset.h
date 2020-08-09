#ifndef TILESET
#define TILESET

class Tileset {
	protected:
		float fps;
		int x_pos, y_pos;
		// int start_x = 0, start_y = 0;

		static int num_drawn_tiles;
		static int width, height;
		static vector<string> tileset_names;
		static vector<pair<int,int>> tileset_coords;
		static map<string, pair<shared_ptr<SDL_Texture>, SDL_Rect>> tileset;

	public:
		Tileset();
		static map<string, pair<shared_ptr<SDL_Texture>, SDL_Rect>> load_in_tiles(string folder_name);
		static void draw_tile(string type, int grid_x, int grid_y);
		static void draw_tile_background();
		static void print_tiles();
		static void print_bg_coords();
		static int get_width() { return width; }
		static int get_height() { return height; }
};


#endif