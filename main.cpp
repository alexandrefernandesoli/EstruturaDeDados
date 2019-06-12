#include "file_pattern_search.hpp"

int main(int argc, char *argv[]){
	file_pattern_search *test = new file_pattern_search(argv[1]);

	test->search();

    return 0;
}