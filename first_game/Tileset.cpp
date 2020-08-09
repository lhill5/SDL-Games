#include "defs.h"


map<string, pair<shared_ptr<SDL_Texture>, SDL_Rect>> Tileset::tileset = load_in_tiles("images/tileset/Ground");
vector<string> Tileset::tileset_names = {};
vector<pair<int,int>> Tileset::tileset_coords = {};
int Tileset::width = 64;
int Tileset::height = 64;
int Tileset::num_drawn_tiles = 0;


Tileset::Tileset() {
	cout << "loaded in tileset" << endl;
};


map<string, pair<shared_ptr<SDL_Texture>, SDL_Rect>> Tileset::load_in_tiles(string folder_name) {

	SDL_Renderer* mainRend = Game::get_main_rend();

	string dir_path = "./" + folder_name;
	// cout << dir_path << endl;

	map<string, pair<shared_ptr<SDL_Texture>, SDL_Rect>> tileset;

	for (const auto& dirEntry : directory_iterator(dir_path)) {
		// std::cout << typeid(dirEntry.path()).name() << std::endl;
		auto file_path = dirEntry.path().string();

		if (file_path.find(".DS_Store") != string::npos) {
			continue;
		}

		int found = file_path.find_last_of("/");
		int found_png = file_path.find(".png");
		string file_name = file_path.substr(found+1);
		file_name.erase(file_name.size() - 4); // removes .png from file_name
		
		// cout << file_path << "\t" << file_name << endl;

		shared_ptr<SDL_Texture> text = create_texture_from_image(mainRend, file_path);
		
		SDL_Rect tile;
		SDL_QueryTexture(text.get(), NULL, NULL, &tile.w, &tile.h);

		pair<shared_ptr<SDL_Texture>, SDL_Rect> tile_pair(text, tile);



		tileset[file_name] = tile_pair;
		tileset_names.push_back(file_name);
		// cout << file_name << endl;
	}

	return tileset;
};


void Tileset::draw_tile_background() {

	static bool first_call = true;

	int tile_size = width;
	int cols = WINDOW_WIDTH / tile_size;
 
	vector<vector<string>> bg = { 
		{"middle_left", "middle_center", "middle_right"},
		{"top_left", "top_center", "top_right"}
	};

	// cout << cols << endl;
	// vector<string> tile_bg;

	pair<int,int> coords;

	int r, c;
	for (r = 0; r < bg.size(); r++) {
		int tile_num = 0;
		coords.second = r;
		for (c = 0; c < cols; c++) {
			coords.first = c;
			if (c == 0) {
				draw_tile(bg[r][0], c, r);
				tile_num++;
			}
			else if (c != cols-1) {
				draw_tile(bg[r][1], c, r);
			}
			else {
				tile_num++;
				draw_tile(bg[r][2], c, r);
			}
			if (first_call) {
				tileset_coords.push_back(coords);
				num_drawn_tiles++;
			}
		}
	}

	if (first_call) first_call = false;
	// if (c == 4 or c == 5 or c == 10 or c == 11) draw_tile("water", c, 0);
	// else if (c == 0) draw_tile("middle_left", c, 0);
	// else if (c == cols-1) draw_tile("middle_right", c, 0);
	// else draw_tile("middle_center", c, 0);
}


void Tileset::draw_tile(string type, int grid_x, int grid_y) {
	
	if (tileset.count(type)) {
		pair<shared_ptr<SDL_Texture>, SDL_Rect> tile = tileset[type];

		SDL_Texture* tile_txt = tile.first.get();
		SDL_Rect tile_rect = tile.second;

		// cout << tile_rect.w << " " << tile_rect.h << endl;

		tile_rect.w /= 2;
		tile_rect.h /= 2;

		pair<int,int> coords = get_xy_coords(grid_x, grid_y);
		
		tile_rect.x = coords.first;
		tile_rect.y = coords.second;

		SDL_Renderer* mainRend = Game::get_main_rend();
		SDL_RenderCopy(mainRend, tile_txt, NULL, &tile_rect);
	}
	else {
		// cout << "couldn't draw tile to screen" << endl;
	}
}


void Tileset::print_tiles() {
	map<string, pair<shared_ptr<SDL_Texture>, SDL_Rect>>::iterator tileset_itr;
	tileset_itr = tileset.begin();
	while (tileset_itr != tileset.end()) {
		// cout << tileset_itr->first << endl;
		tileset_itr++;
	}
}


void Tileset::print_bg_coords() {
	// cout << "function called " << tileset_coords.size() << " " << num_drawn_tiles << endl;
	for (pair<int,int> p : tileset_coords) {
		cout << p.first << ", " << p.second << endl;
	}
}

