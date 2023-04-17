#include <music.hpp>
#include <playlist.hpp>
#include <norepeat.hpp>

#include <csignal>

void on_exit(int) {
	exit(0);
}

void notify(std::string title, std::string message){
	std::string command = "";

	#if defined (__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
		command = "notify-send \""+title+"\" \""+message+"\"";
		
		system(command.c_str());
	#endif
}

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
					
					notify("Listening:", music.getTitle());
					
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
	std::signal(SIGINT, on_exit);

	bool loop = false;
	
	if(argc == 1){
		std::cout << "Usage: play-list path/to/playlist [OPTIONS]\n";

		return 1;
	}

	if(argc == 3)
		if(((std::string) argv[2]) == "--loop") loop = true;
	
	if(loop){
		std::cout << "Music will never end\n\n";
		notify("play-list:", "Music will never end");
	}
	
	do play(argv); while(loop);

	return 0;
}
