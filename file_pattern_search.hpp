#include <string>
#include <sstream>
#include <vector>
#include <iostream>
#include <fstream>
#include <map>
#include <algorithm>
using namespace std;

class file_pattern_search{
	private:
		string entry_file_name;
		vector<string> words_vector;
		map<int, string> map_files;

		void create_output_file();
		void save_on_map(vector<string>);
		void string_split(string);
		void search_word(ofstream&);

		void prefix(string, int[]);
		bool kmp(string, string, int[]);
	public:
		file_pattern_search(string entry_file_name){
			this->entry_file_name = entry_file_name;
		}
	
		void search();
		
};