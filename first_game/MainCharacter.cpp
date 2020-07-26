#include "defs.h"


MainCharacter::MainCharacter(SDL_Renderer* mainRend) {
	// creates reference to main renderer used to draw images to canvas
	this->mainRend = mainRend;
	// loads in sprites to MainCharacter instance
	this->_load_in_images("images/zombie_images");

};


void MainCharacter::_load_in_images(string folder_name) {
	string dir_path = "./" + folder_name;
	cout << dir_path << endl;

	for (const auto& dirEntry : directory_iterator(dir_path)) {
		// std::cout << typeid(dirEntry.path()).name() << std::endl;
		auto subdir_path = dirEntry.path().string();
		int found = subdir_path.find_last_of("/");
		string subfolder_name = subdir_path.substr(found+1);

		// cout << subfolder_name << endl;

		vector<pair<shared_ptr<SDL_Texture>, SDL_Rect>> subdir_images;
		// cout << "sub: " << subdir_path << "\t" << subfolder_name << endl;
		// if this path is a directory
		if (subfolder_name.find(".") == string::npos) {
			vector<string> image_paths;
			cout << subdir_path << endl;
			// get all image_paths from folder and sort based off image name
			for (const auto& subdir : directory_iterator(subdir_path)) {
				auto image_path = subdir.path().string();
				image_paths.push_back(image_path);
				// cout << image_path << endl;
			}
			sort(image_paths.begin(), image_paths.end());

			for (string image_path : image_paths) {
				cout << image_path << endl;
				shared_ptr<SDL_Texture> text = create_texture_from_image(this->mainRend, image_path);

				SDL_Rect sprite;
				SDL_QueryTexture(text.get(), NULL, NULL, &sprite.w, &sprite.h);

				pair<shared_ptr<SDL_Texture>, SDL_Rect> sprite_pair(text, sprite);
				subdir_images.push_back(sprite_pair);
			}
			this->animation_commands.push_back(subfolder_name);
			this->character_animations[subfolder_name] = subdir_images;
		}
	}
};


int get_num_files_in_folder(string folder_name) {
	DIR *dp;
	int count = 0;
	struct dirent *ep; 

	string folder_path = "./images/" + folder_name;
	const char* folder_path_c = folder_path.c_str();

	dp = opendir(folder_path_c);

	if (dp != NULL) {
		while ((ep = readdir(dp))) {
			// puts(ep->d_name);
			count++;
		}
		(void) closedir (dp);
	}
	else {
		perror ("Couldn't open the directory");
	}

	// printf("There's %d files in the current directory.\n", i-2);
	count -= 2; // remove . .. as files, so remove 2 from total count
	return count;
};


void MainCharacter::_draw_animation(string command, bool increment) {
	// check if command (key) exists in character's animations (map)
	static int sprite_count = 1;
	if (this->character_animations.count(command)) {

		vector<pair<shared_ptr<SDL_Texture>, SDL_Rect>> sprites = this->character_animations[command];
		pair<shared_ptr<SDL_Texture>, SDL_Rect> sprite = sprites[sprite_count];	

		SDL_Texture* text = sprite.first.get();
		SDL_Rect dest = sprite.second;

		SDL_RenderCopy(this->mainRend, text, NULL, &dest);
		if (increment) {
			sprite_count++;
			if (sprite_count >= sprites.size()) {
				sprite_count = 1;
			}
		}
	} else {
		cout << "couldn't draw sprite to screen" << endl;
	}
}


void MainCharacter::walk(int left, int right, int up, int down) {
	if ((left and right) or (up and down)) {
		return;
	}

	if (left) {
		_draw_animation("walk_left");
	}
	else if (right) {
		_draw_animation("walk_right");
	}
	else if (up) {
		_draw_animation("walk_front");
	}
	else if (down) {
		_draw_animation("walk_back");
	}
}

