#include "KMP.hpp"

int main(int argc, char *argv[]){
	KMP *kmp = new KMP();
	string teste = argv[1];
	kmp->principal(teste);

    return 0;
}