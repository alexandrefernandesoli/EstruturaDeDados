#include "FilePatternSearch.hpp"


/*
    Abre o arquivo principal e lê cada uma de suas linhas.
    Salvando os nomes dos arquivos de verificação no vector 'files' e passando o vector para o método 'saveOnMap'.
    Passa o nome do arquivo de palavras para o método 'stringSplit'.
*/
void
FilePatternSearch::search(){
    ifstream myfile (entryFileName);
    string line;
    vector<string> files;
    int fileQuantity;

	if(myfile.is_open()){
		getline(myfile, line);
        fileQuantity = atoi(line.c_str());

        for(int i = 0; i < fileQuantity; i++){
            getline(myfile, line);
            files.push_back(line);
        }

        getline(myfile, line);
        stringSplit(line);
		myfile.close();
	}

    saveOnMap(files);
    createOutputFile();
}

/*
    Abre o arquivo wordsFile que contem uma linha com palavras, essa linha, sendo uma string, será
    dividida em várias strings conforme seus espaços, essas strings serão guardadas no vector "wordsVector".
*/
void
FilePatternSearch::stringSplit(string wordsFile){
    ifstream file (wordsFile);
    string line;
    string word;

    if(file.is_open()){
        getline(file, line);
        stringstream ss(line);

        while(getline(ss, word, ' ')) {
		    wordsVector.push_back(word);
	    }
    }
}

/*
    Tenta abrir cada um dos arquivos com seus respectivos nomes passados por parametro pelo vetor files,
    os arquivos que são abertos com sucesso, são salvados em um map, com a key do tipo int sendo um indice que aumenta
    conforme os arquivos são abertos com sucesso e seu value do tipo string sendo o nome do arquivo aberto com sucesso.
*/
void
FilePatternSearch::saveOnMap(vector<string> files){
    int i = 1;
    for(auto fileName: files){
        ifstream openFile (fileName);
        if(openFile.is_open()){
            filesMap.insert({i, fileName});
            i++;
        }
    }
}

/*  
    Cria o arquivo de saida conforme especificado: "nome do arquivo de entrada" + ".out".
*/
void
FilePatternSearch::createOutputFile(){
    ofstream outputFile (entryFileName+".out");

    if(outputFile.is_open()){
        searchWord(outputFile);
    }
}

/*

*/
void
FilePatternSearch::searchWord(ofstream& outputFile){
    vector<string> linesToWrite;

    for(auto word: wordsVector){
        string lineToWrite;
        int occurrences = 0;

        for_each(word.begin(), word.end(), [](char & c) {
            c = ::tolower(c);
        });
        lineToWrite = word;

        for(auto const& file: filesMap){
            ifstream openFile(file.second);
            string line;
            int line_count = 1;

            if(openFile.is_open()){
                while(getline(openFile, line)){
                    if(line != ""){
                        for_each(line.begin(), line.end(), [](char & c) {
                            c = ::tolower(c);
                        });
                        int aux[line.length()];
                        prefix(word, aux);
                        if(kmp(line, word, aux)){
                            lineToWrite = lineToWrite + ' ' +  to_string(file.first) + ',' + to_string(line_count);
                            occurrences++;
                        }
                    }
                    line_count++;
                }
            }
        }

        if(occurrences > 0)
            linesToWrite.push_back(lineToWrite);

    }

    for(int i = 0; i < linesToWrite.size(); i++){
        if(i < linesToWrite.size() - 1){
            outputFile << linesToWrite[i] << endl;
            cout << linesToWrite[i] << endl;
        }else{
            outputFile << linesToWrite[i];
            cout << linesToWrite[i] << endl;
        }
    }
}



void
FilePatternSearch::prefix(string pattern, int aux[]){
	aux[0] = 0;
	int j = 0;
    int i = 1;

	while(i < pattern.size()){
		if(pattern[i] == pattern[j]){
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
FilePatternSearch::kmp(string text, string pattern, int aux[]){
	int idxText = 0, idxPattern = 0;

	while(idxText < text.size()){
		if(pattern[idxPattern] == text[idxText]){
			idxPattern++;
			idxText++;
		}

		if(idxPattern == pattern.size()){
			idxPattern = aux[idxPattern - 1];
            return true;
		}

		if(idxText < text.size() && pattern[idxPattern] != text[idxText]){
			if(idxPattern)
				idxPattern = aux[idxPattern - 1];
			else
				idxText++;
		}
	}
    return false;
}


