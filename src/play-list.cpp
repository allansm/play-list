#include <music.hpp>
#include <playlist.hpp>
#include <norepeat.hpp>

int main(int argc, char** argv){
	Playlist root((std::string) argv[1]);
	std::vector<Playlist> playlists;
	
	while(!root.end()){
		std::string next = root.next();

		Playlist playlist(next);
		
		std::cout << next << "\n" << playlist.getName() << "\n\n";

		playlists.push_back(playlist);
	}

	NoRepeat norepeat;

	bool end = false;
	while(!end){
		unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
		std::default_random_engine e(seed);
		std::shuffle(playlists.begin(), playlists.end(), e);
		
		for(int i = 0;i<playlists.size();i++){
			end = playlists[i].end();
			
			if(!end){
				std::string next = playlists[i].next();
				Music music(next);

				if(!norepeat.check(music.getTitle())){
					std::cout << playlists[i].getName() << "\n\n";
					std::cout << "Listening: " << music.getTitle() << "\n\n";
					music.play();
					
					norepeat.add(music.getTitle());

					break;
				}else{
					std::cout << "skiping " << music.getTitle() << "\n";
				}
			}
		}
	}

	norepeat.clear();

	return 0;
}
