#include <music.hpp>
#include <allansm/path.hpp>

int main(int argc, char** argv){
	chdir(argv[1]);

	for(auto n : ls(".")){
		if(n != "." && n != ".."){
			std::cout << n << "\n";
			
			Music(n.c_str()).play();
		}
	}

	return 0;
}
