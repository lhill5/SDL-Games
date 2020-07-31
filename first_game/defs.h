#ifndef DEFSH
#define DEFSH

// #define WINDOW_WIDTH 640
// #define WINDOW_HEIGHT 480
#define WINDOW_WIDTH 1000
#define WINDOW_HEIGHT 750
#define PLAYER_SPEED 50

#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm> 

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <unistd.h>
#include <memory>
#include <stdbool.h>
#include <typeinfo>

// for reading in file names in directory
#include <sys/types.h>
#include <dirent.h>
#include <filesystem>

#include <stdio.h>
#include <string.h>

using std::filesystem::directory_iterator;
using std::filesystem::recursive_directory_iterator;

using std::cout;
using std::endl;
using std::shared_ptr;
using std::unique_ptr;
using std::string;
using std::vector;
using std::map;
using std::pair;
using std::sort;

// #include "GameWorld.h"
#include "game_functions.h"
#include "MainCharacter.h"

#endif

