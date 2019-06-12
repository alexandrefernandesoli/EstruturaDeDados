#include "KMP.hpp"

int main(int argc, char *argv[]){
    ifstream myfile (argv[1]);
	string line;
	KMP *kmp = new KMP();
	string palavra = "Testando";
	int aux[palavra.size()];
	
	if(myfile.is_open()){
		while( getline(myfile, line)){
			cout << line << '\n';
			kmp->prefix(palavra, aux);
			kmp->kmp(line, palavra, aux);
		}
		myfile.close();
	}else{
		cout << "Não foi possivel abrir este arquivo";
	}

    return 0;
}