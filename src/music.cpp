#include <music.hpp>

Music::Music(std::string file){
	this->file = file;

	this->title = file.substr(file.find_last_of("/\\") + 1);
	this->title = this->title.substr(0, this->title.find_last_of("."));
}

void Music::play(){
	Mix_OpenAudio(22050, AUDIO_S16SYS, 2, 640);
	Mix_Music *music = Mix_LoadMUS(this->file.c_str());
	Mix_PlayMusic(music, 1);

	while (Mix_PlayingMusic()) {
		SDL_Delay(250);
	}

	Mix_FreeMusic(music);
	Mix_CloseAudio();
}

std::string Music::getTitle(){
	return this->title;
}
