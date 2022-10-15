#include <music.hpp>
#include <playlist.hpp>

int main(int argc, char** argv){
	Playlist root((std::string) argv[1]);
	std::vector<Playlist> playlists;
	
	while(!root.end()){
		std::string next = root.next();

		Playlist playlist(next);
		
		std::cout << next << "\n" << playlist.getName() << "\n\n";

		playlists.push_back(playlist);
	}

	bool end = false;
	while(!end){
		unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
		std::default_random_engine e(seed);
		std::shuffle(playlists.begin(), playlists.end(), e);
		
		for(auto playlist : playlists){
			end = playlist.end();
			
			if(!end){
				std::string next = playlist.next();
				Music music(next);

				std::cout << playlist.getName() << "\n\n";
				std::cout << "Listening: " << music.getTitle() << "\n\n";
				
				music.play();

				break;
			}
		}
	}

	return 0;
}
