
#include "defs.h"


MainCharacter::MainCharacter(SDL_Renderer* mainRend, float fps) {
	this->fps = fps;
	// creates reference to main renderer used to draw images to canvas
	this->mainRend = mainRend;
	// loads in sprites to MainCharacter instance
	this->_load_in_images("images/character_images");

};


void MainCharacter::set_xpos(int x_pos) {
	if (x_pos >= 0 and x_pos <= WINDOW_WIDTH - this->width) {
		this->x_pos = x_pos;
	}
};


int MainCharacter::get_xpos() {
	return this->x_pos;
};


void MainCharacter::set_ypos(int y_pos) {
	if (y_pos >= 0 and y_pos <= WINDOW_HEIGHT - this->height) {
		this->y_pos = y_pos;
	}
};


int MainCharacter::get_ypos() {
	return this->y_pos;
};


void MainCharacter::_load_in_images(string folder_name) {
	string dir_path = "./" + folder_name;
	// cout << dir_path << endl;

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
			// cout << subdir_path << endl;
			// get all image_paths from folder and sort based off image name
			for (const auto& subdir : directory_iterator(subdir_path)) {
				auto image_path = subdir.path().string();
				image_paths.push_back(image_path);
				// cout << image_path << endl;
			}
			sort(image_paths.begin(), image_paths.end());

			for (string image_path : image_paths) {
				// cout << image_path << endl;
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


void MainCharacter::_draw_animation(string command, bool pause) {
	// check if command (key) exists in character's animations (map)
	int repeat = 8;
	static int sprite_count = 1*repeat;

	// cout << command << endl;
	if (this->character_animations.count(command)) {

		int repeat_sprite_count = sprite_count / repeat;

		// cout << repeat_sprite_count << "\t" << sprite_count << endl;
		vector<pair<shared_ptr<SDL_Texture>, SDL_Rect>> sprites = this->character_animations[command];
		pair<shared_ptr<SDL_Texture>, SDL_Rect> sprite = sprites[repeat_sprite_count];	

		SDL_Texture* text = sprite.first.get();
		SDL_Rect dest = sprite.second;
		dest.x = this->x_pos;
		dest.y = this->y_pos;

		SDL_RenderCopy(this->mainRend, text, NULL, &dest);
		if (!pause) {
			sprite_count++;
			// cout << sprites.size() << "\t" << repeat_sprite_count << "\t" << sprite_count << endl;
			if (sprite_count >= sprites.size() * repeat) {
				sprite_count = 1*repeat;
			}
		}
	} else {
		cout << "couldn't draw sprite to screen" << endl;
	}
}


void MainCharacter::walk(int left, int right, int up, int down) {

	// if no direction keys are pressed, then show last animation, no need to change x_pos or y_pos
	if (left == 0 and right == 0 and up == 0 and down == 0) {
		bool pause_animation = true;
		// cout << this->prev_direction << endl;
		_draw_animation(this->prev_direction, pause_animation);
	}
	else {
		string command;
		if (left) {
			command = "walk_left";
		} else if (right) {
			command = "walk_right";
		} else if (up) {
			command = "walk_back";
		} else if (down) {
			command = "walk_front";
		}
		// reset velocity before changing x/p_pos, otherwise character moves diagonally when moving left/right
		this->x_vel = this->y_vel = 0;

		if (left and !right) this->x_vel = -PLAYER_SPEED;
		if (right and !left) this->x_vel = PLAYER_SPEED;
		if (up and !down) this->y_vel = -PLAYER_SPEED;
		if (down and !up) this->y_vel = PLAYER_SPEED;

		this->x_pos += x_vel/(this->fps);
		this->y_pos += y_vel/(this->fps);

		// boundary detection
		if (this->x_pos <= 0) this->x_pos = 0;
		if (this->y_pos <= 0) this->y_pos = 0;
		if (this->x_pos >= WINDOW_WIDTH - this->width) this->x_pos = WINDOW_WIDTH - this->width;
		if (this->y_pos >= WINDOW_HEIGHT - this->height) this->y_pos = WINDOW_HEIGHT - this->height;

		_draw_animation(command);
		this->prev_direction = command;
	}
}

