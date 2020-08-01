#ifndef TILESET
#define TILESET


class Tileset {
	protected:
		float fps;
		int x_pos = 0, y_pos = 0;
		int width = 64, height = 64;

		static vector<string> tileset_names;
		static map<string, pair<shared_ptr<SDL_Texture>, SDL_Rect>> tileset;

	public:
		Tileset();
		static map<string, pair<shared_ptr<SDL_Texture>, SDL_Rect>> load_in_tiles(string folder_name);
		static void draw_tile(string type, int grid_x, int grid_y);
		static void draw_tile_background();
		static void print_tiles();
};


#endif