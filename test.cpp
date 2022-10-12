#include <music.hpp>
#include <playlist.hpp>

int main(int argc, char** argv){
	Playlist playlist((std::string) argv[1]);
	
	while(!playlist.end()){
		std::string current = playlist.next();
		std::cout << current << "\n";

		Music(current).play();
	}

	return 0;
}
