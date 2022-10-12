#include <music.hpp>
#include <playlist.hpp>

int main(int argc, char** argv){
	Playlist root((std::string) argv[1]);
	std::vector<Playlist> playlists;
	
	while(!root.end()){
		playlists.push_back(Playlist(root.next()));
	}

	bool end = false;
	while(!end){
		for(auto playlist: playlists){
			end = playlist.end();

			if(!end){
				std::string next = playlist.next();
				std::cout << next << "\n";

				Music(next).play();
			}
		}
	}

	return 0;
}