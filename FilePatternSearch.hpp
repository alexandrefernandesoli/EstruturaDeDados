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
		string entryFileName; /** Guarda o nome do arquivo principal de entrada */
		vector<string> wordsVector; /** Guarda as palavras a serem testadas */
		map<int, string> filesMap; /** Guarda os arquivos que serão testados */

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