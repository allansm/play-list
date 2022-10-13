#include <SDL.h>
#include <SDL_mixer.h>
#include <string>

class Music{
	std::string file;

	public:
		Music(std::string file);
		void play();
};
