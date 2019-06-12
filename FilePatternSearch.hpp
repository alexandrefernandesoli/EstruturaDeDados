#include <string>
#include <sstream>
#include <vector>
#include <iostream>
#include <fstream>
#include <map>
#include <algorithm>
using namespace std;

class FilePatternSearch{
	private:
		string entryFileName;
		vector<string> wordsVector;
		map<int, string> filesMap;

		void createOutputFile();
		void saveOnMap(vector<string>);
		void stringSplit(string);
		void searchWord(ofstream&);

		void prefix(string, int[]);
		bool kmp(string, string, int[]);
	public:
		FilePatternSearch(string entryFileName){
			this->entryFileName = entryFileName;
		}
	
		void search();
		
};