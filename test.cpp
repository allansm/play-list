#include <allansm/simple/sdl2/audio.hpp>
#include <allansm/path.hpp>

main(int argc, char** argv){
	chdir(argv[1]);

	for(auto n : ls(".")){
		if(n != "." && n != ".."){
			std::cout << n << "\n";
			
			listen(n.c_str());
		}
	}
}
