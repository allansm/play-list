#include <SDL.h>
#include <SDL_mixer.h>
#include <string>

class Music{
	std::string file;
	std::string title;

	public:
		Music(std::string file);
		
		void play();
		std::string getTitle();
};
