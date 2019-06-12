#include <string>
#include <sstream>
#include <vector>
#include <iostream>
#include <fstream>
#include <map>
#include <algorithm>
using namespace std;

class KMP{
	private:
		int numeroDeArquivos;
		string arquivoEntrada;
		vector<string> palavras;
		map<int, string> arquivosMap;

		void verificar();
		void salvaNoMap(vector<string>);
		void stringSplit(string);
		void prefix(string, int[]);
		void verificaPalavra(ofstream&);
		bool kmp(string, string, int[]);
	public:
		void principal(string);
		
};