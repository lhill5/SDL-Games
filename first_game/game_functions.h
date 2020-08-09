#ifndef GAME_FUNCTIONS
#define GAME_FUNCTIONS

// #include "defs.h"
using std::string;

// function declarations
shared_ptr<SDL_Window> create_window();
shared_ptr<SDL_Renderer> create_main_renderer(SDL_Window* window);

void exit_program();
void free_texture(SDL_Texture* txt);
void here();

shared_ptr<SDL_Texture> create_texture_from_image(SDL_Renderer* mainRend, string img_path);
pair<SDL_Texture, SDL_Rect> get_sprite_from_texture(SDL_Texture);
map<string, pair<shared_ptr<SDL_Texture>, SDL_Rect>> load_in_tiles(string folder_name);
pair<int,int> get_xy_coords(int grid_x, int grid_y);

#endif