#include "../include/norepeat.hpp"

NoRepeat::NoRepeat(){
	const char* home = getenv("HOME");

	home = home ? home : getenv("USERPROFILE");
	
	chdir(home);
	
	struct stat info;
	
	if(stat("play-list", &info) != 0){
		#if defined _WIN32
			mkdir("play-list");
		#else
			mkdir("play-list", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
		#endif
	}

	chdir("play-list");

	std::ifstream temp(".norepeat");

	std::string line;

	while(getline(temp, line)){
		this->titles.push_back(line);
	}

	temp.close();
}

void NoRepeat::add(std::string title){
	this->titles.push_back(title);

	std::string text = "";
	for(auto n : this->titles){
		text+=n+"\n";
	}

	std::ofstream file(".norepeat");
	file << text.c_str();
	file.close();
}

bool NoRepeat::check(std::string x){
	return std::find(this->titles.begin(), this->titles.end(), x) != this->titles.end();
}

void NoRepeat::clear(){
	std::ofstream file(".norepeat");
	file << "";
	file.close();
}
