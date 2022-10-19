#include <vector>
#include <string>
#include <algorithm>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <fstream>

class NoRepeat{
	std::vector<std::string> titles;
	
	public:
		NoRepeat();

		void add(std::string title);
		bool check(std::string title);
		void clear();
};
