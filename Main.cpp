#include <iostream>


using namespace std;

int main(int argc, char *argv[]){
    
	char* texto[argc];
	for(int i = 1; i < argc; i++){
		texto[i] = argv[i];

		cout << texto[i] << "\n";
	}

    return 0;
}