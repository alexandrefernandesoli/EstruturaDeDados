#include "FilePatternSearch.hpp"

int main(int argc, char *argv[]){
	FilePatternSearch *test = new FilePatternSearch(argv[1]);

	test->search();

    return 0;
}