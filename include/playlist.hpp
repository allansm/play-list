#include <unistd.h>
#include <dirent.h>
#include <vector>
#include <sys/stat.h>
#include <iostream>
#include <stdlib.h>

#include <algorithm>
#include <random>
#include <chrono>

class Playlist{
	std::string path;
	std::vector<std::string> playlist;
	
	int index = 0;
	bool playlist_end = false;

	public:
		Playlist(std::string path);
		std::string next();
		bool end();
};
