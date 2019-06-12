#include <string>
#include <iostream>
#include <fstream>
using namespace std;

class KMP{
	public:
		void prefix(string, int[]);
		bool kmp(string, string, int[]);
};