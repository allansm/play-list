#include <playlist.hpp>

Playlist::Playlist(std::string path){
	this->name = path.substr(path.find_last_of("/\\") + 1);
	
	char current[255];
	getcwd(current,255);
	
	chdir(path.c_str());

	std::vector<std::string> playlist;
	DIR *dir;
	struct dirent *ent;
	if((dir = opendir(".")) != NULL){
		while ((ent = readdir (dir)) != NULL) {
			if((std::string)ent->d_name != "." && (std::string)ent->d_name != ".."){
				std::string p = path;
				
				if(p.back() != '/' && p.back() != '\\') p+="/";
				
				p+=ent->d_name;

				playlist.push_back(p);
			}
		}

		closedir (dir);
	}else{
		perror ("");	
	}
	
	chdir(current);

	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::default_random_engine e(seed);
	std::shuffle(playlist.begin(), playlist.end(), e);
	
	this->playlist = playlist;
}

std::string Playlist::next(){
	std::string current = this->playlist[this->index];
	
	if(this->index+1 >= this->playlist.size()){
		this->playlist_end = true;
	}

	if(!this->playlist_end) this->index+=1;

	return current;
}

std::string Playlist::getName(){
	return this->name;
}

bool Playlist::end(){
	return this->playlist_end;
}
