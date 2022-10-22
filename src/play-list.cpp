#include <music.hpp>
#include <playlist.hpp>
#include <norepeat.hpp>

void play(char** argv){
	Playlist root((std::string) argv[1]);
	std::vector<Playlist> playlists;
	int total = 0;

	while(!root.end()){
		std::string next = root.next();

		Playlist playlist(next);
		
		std::cout << next << "\n" << playlist.getName() << "\n\n";
		
		total += playlist.size();
		
		playlists.push_back(playlist);
	}

	std::cout << "total music: " << total << "\n\n";
	
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
					std::cout << playlists[i].getName() << " " << playlists[i].current() << "/" << playlists[i].size() <<"\n\n";
					std::cout << "Listening: " << music.getTitle() << "\n\n";
					music.play();
					
					norepeat.add(music.getTitle());

					break;
				}else{
					std::cout << "skiping " << music.getTitle() << "\n\n";
				}
			}
		}
	}
	
	std::cout << "clearing cache...\n\n";

	norepeat.clear();
}

int main(int argc, char** argv){
	bool loop = false;
	
	if(argc == 1){
		std::cout << "Usage: play-list path/to/playlist [OPTIONS]\n";

		return 1;
	}

	if(argc == 3)
		if(((std::string) argv[2]) == "--loop") loop = true;
	
	if(loop) 
		std::cout << "Music will never end\n\n";
	
	do play(argv); while(loop);

	return 0;
}
