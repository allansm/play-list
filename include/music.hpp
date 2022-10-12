#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <string>

class Music{
	std::string file;

	public:
		Music(std::string file);
		void play();
};
