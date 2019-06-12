#include "file_pattern_search.hpp"


/*
    Abre o arquivo principal e lê cada uma de suas linhas.
    Salvando os nomes dos arquivos de verificação no vector 'files' e passando o vector para o método 'save_on_map'.
    Passa o nome do arquivo de palavras para o método 'string_split'.
*/
void
file_pattern_search::search(){
    ifstream myfile (entry_file_name);
    string line;
    vector<string> files;
    int file_quantity;

	if(myfile.is_open()){
		getline(myfile, line);
        file_quantity = atoi(line.c_str());

        for(int i = 0; i < file_quantity; i++){
            getline(myfile, line);
            files.push_back(line);
        }

        getline(myfile, line);
        string_split(line);
		myfile.close();
	}

    save_on_map(files);
    create_output_file();
}

/*
    Abre o arquivo words_file que contem uma linha com palavras, essa linha, sendo uma string, será
    dividida em várias strings conforme seus espaços, essas strings serão guardadas no vector "words_vector".
*/
void
file_pattern_search::string_split(string words_file){
    ifstream file (words_file);
    string line;
    string word;

    if(file.is_open()){
        getline(file, line);
        stringstream ss(line);

        while(getline(ss, word, ' ')) {
		    words_vector.push_back(word);
	    }
    }
}

/*
    Tenta abrir cada um dos arquivos com seus respectivos nomes passados por parametro pelo vetor files,
    os arquivos que são abertos com sucesso, são salvados em um map, com a key do tipo int sendo um indice que aumenta
    conforme os arquivos são abertos com sucesso e seu value do tipo string sendo o nome do arquivo aberto com sucesso.
*/
void
file_pattern_search::save_on_map(vector<string> files){
    int i = 1;
    for(auto file_name: files){
        ifstream open_file (file_name);
        if(open_file.is_open()){
            map_files.insert({i, file_name});
            i++;
        }
    }
}

/*  
    Cria o arquivo de saida conforme especificado: "nome do arquivo de entrada" + ".out".
*/
void
file_pattern_search::create_output_file(){
    ofstream output_file (entry_file_name+".out");

    if(output_file.is_open()){
        search_word(output_file);
    }
}

/*

*/
void
file_pattern_search::search_word(ofstream& output_file){
    vector<string> lines_to_write;

    for(auto word: words_vector){
        string line_to_write;
        int occurrences = 0;

        for_each(word.begin(), word.end(), [](char & c) {
            c = ::tolower(c);
        });
        line_to_write = word;

        for(auto const& file: map_files){
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
                            line_to_write = line_to_write + ' ' +  to_string(file.first) + ',' + to_string(line_count);
                            occurrences++;
                        }
                    }
                    line_count++;
                }
            }
        }

        if(occurrences > 0)
            lines_to_write.push_back(line_to_write);

    }

    for(int i = 0; i < lines_to_write.size(); i++){
        if(i < lines_to_write.size() - 1){
            output_file << lines_to_write[i] << endl;
            cout << lines_to_write[i] << endl;
        }else{
            output_file << lines_to_write[i];
            cout << lines_to_write[i] << endl;
        }
    }
}



void
file_pattern_search::prefix(string pattern, int aux[]){
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
file_pattern_search::kmp(string text, string pattern, int aux[]){
	int idx_text = 0, idx_pattern = 0;

	while(idx_text < text.size()){
		if(pattern[idx_pattern] == text[idx_text]){
			idx_pattern++;
			idx_text++;
		}

		if(idx_pattern == pattern.size()){
			idx_pattern = aux[idx_pattern - 1];
            return true;
		}

		if(idx_text < text.size() && pattern[idx_pattern] != text[idx_text]){
			if(idx_pattern)
				idx_pattern = aux[idx_pattern - 1];
			else
				idx_text++;
		}
	}
    return false;
}


