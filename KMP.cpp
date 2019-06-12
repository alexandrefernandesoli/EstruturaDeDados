#include "KMP.hpp"

void
KMP::principal(string arquivo){
    ifstream myfile (arquivo);
    string line;
    arquivoEntrada = arquivo;
    vector<string> arquivos;

	if(myfile.is_open()){
		getline(myfile, line);
        numeroDeArquivos = atoi(line.c_str());
        for(int i = 0; i < numeroDeArquivos; i++){
            getline(myfile, line);
            arquivos.push_back(line);
        }
        getline(myfile, line);
        stringSplit(line);
		myfile.close();
	}
    salvaNoMap(arquivos);
    verificar();
}

void
KMP::verificar(){
    ofstream arquivoSaida (arquivoEntrada+".out");

    if(arquivoSaida.is_open()){
        verificaPalavra(arquivoSaida);
    }
}


void
KMP::verificaPalavra(ofstream& arquivoSaida){
    vector<string> linhasParaEscrever;
    for(auto palavra: palavras){
        string linhaParaEscrever;
        int encontrados = 0;
        for_each(palavra.begin(), palavra.end(), [](char & c) {
            c = ::tolower(c);
        });
        linhaParaEscrever = palavra;
        for(auto const& arquivo: arquivosMap){
            ifstream openFile(arquivo.second);
            string line;
            int lineCount = 1;

            if(openFile.is_open()){
                while(getline(openFile, line)){
                    if(line != ""){
                        for_each(line.begin(), line.end(), [](char & c) {
                            c = ::tolower(c);
                        });
                        int aux[line.length()];
                        cout << line.length() << ' ' << line << endl;
                        prefix(palavra, aux);
                        if(kmp(line, palavra, aux)){
                            linhaParaEscrever = linhaParaEscrever + ' ' +  to_string(arquivo.first) + ',' + to_string(lineCount);
                            encontrados++;
                        }
                    }
                    lineCount++;
                }
            }
        }
        if(encontrados > 0)
            linhasParaEscrever.push_back(linhaParaEscrever);
    }
    for(int i = 0; i < linhasParaEscrever.size(); i++){
        if(i < linhasParaEscrever.size() - 1){
            arquivoSaida << linhasParaEscrever[i] << endl;
        }else{
            arquivoSaida << linhasParaEscrever[i];
        }
    }
}

void
KMP::salvaNoMap(vector<string> arquivos){
    int i = 1;
    for(auto nomeArquivo: arquivos){
        ifstream abreArquivo (nomeArquivo);
        if(abreArquivo.is_open()){
            arquivosMap.insert({i, nomeArquivo});
            i++;
        }
    }
    for (auto itr = arquivosMap.begin(); itr != arquivosMap.end(); itr++) { 
        cout << itr->first 
             << '\t' << itr->second << '\n'; 
    } 
}

void
KMP::prefix(string padrao, int aux[]){
	aux[0] = 0;
	int j = 0;
    int i = 1;

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
    return false;
}

void
KMP::stringSplit(string arquivoDePalavras){
    ifstream arquivo (arquivoDePalavras);
    string linha;
    string palavra;

    if(arquivo.is_open()){
        getline(arquivo, linha);
        stringstream ss(linha);

        while(std::getline(ss, palavra, ' ')) {
		    palavras.push_back(palavra);
		    std::cout << palavra << '\n';
	    }
    }
}
