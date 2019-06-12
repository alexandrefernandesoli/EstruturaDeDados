#include "KMP.hpp"

void
KMP::prefix(string padrao, int aux[]){
	aux[0] = 0;
	int j = 0, i = 1;

	while(i < padrao.size()){
		if(padrao[i] == padrao[j]){
			j++;
			aux[i] = j;
			i++;
		}else{
			if(j)
				j = aux[j - 1];
			else{
				aux[i] = 0;
				i++;
			}
		}
	}
}

bool
KMP::kmp(string texto, string padrao, int aux[]){
	int idx_texto = 0, idx_padrao = 0;

	while(idx_texto < texto.size()){
		if(padrao[idx_padrao] == texto[idx_texto]){
			idx_padrao++;
			idx_texto++;
		}

		if(idx_padrao == padrao.size()){
			cout << "Padrao encontrado na posicao: " << (idx_texto - idx_padrao) << endl;
			idx_padrao = aux[idx_padrao - 1];
            return true;
		}

		if(idx_texto < texto.size() && padrao[idx_padrao] != texto[idx_texto]){
			if(idx_padrao)
				idx_padrao = aux[idx_padrao - 1];
			else
				idx_texto++;
		}
	}
    cout << "Padrão nao encontrado";
    return false;
}
