#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>

#include <string>
#include <iostream>
#include <filesystem>

// namespace fs = std::filesystem;
using std::filesystem::directory_iterator;
using recursive_directory_iterator = std::filesystem::recursive_directory_iterator;


void cpp_17_method();
void recursive_c17_method();


int main (void)
{
  // DIR *dp;
  // int i = 0;
  // struct dirent *ep;     
  // dp = opendir ("./images/zombie_animations");

  // if (dp != NULL)
  // {
  //   while ((ep = readdir (dp))) {
  //     puts(ep->d_name);
  //     if (ep->d_type == DT_DIR) {
  //       printf("%s is a directory\n", ep->d_name);
  //     } else {
  //       printf("%s is not a directory\n", ep->d_name);
  //     }

  //     if (strncmp(ep->d_name, "folder", strlen("folder")) == 0) {
  //       i++;
  //     }
  //   }
  //   (void) closedir (dp);
  // }
  // else
  //   perror ("Couldn't open the directory");

  // printf("There's %d files in the current directory.\n", i);

  // cpp_17_method();
  recursive_c17_method();

  return 0;
}

/*
void recursive_dir_search(string path, DIR* dp) {
  struct dirent* dir_struct;

  if (dp != NULL) {
    dir_struct = readdir(dp);
    string folder_name = dir_struct->d_name;
    string sub_directory = path + '/' + folder_name;
    try {
      opendir(sub_directory);
    }

    }
  }
*/

void cpp_17_method() {
  std::string path = "./images";
  for (const auto & entry : directory_iterator(path)) {
      std::cout << entry.path() << std::endl;
  }
}

void recursive_c17_method() {
  std::string path = "./images";
  for (const auto& dirEntry : recursive_directory_iterator(path)) {
    // std::cout << typeid(dirEntry.path()).name() << std::endl;
    std::cout << dirEntry.path() << std::endl;
  }
}

