#include "FuncoesGerais.h"

class Timer{

    clock_t inicio, fim;
    float* time;

public:
    Timer(float* _time){
        
        time = _time;
        inicio = clock();
    }

    ~Timer(){
        fim = clock();
        *time = (float)(fim - inicio)/CLOCKS_PER_SEC;
    }
};


void readFile(rating** elements){

    int n = 1;
    int val;

    std::ifstream file;
    file.open("C:\\Users\\thiag\\Desktop\\Btrees\\arquivosEntrada\\ratings.csv");

    std::string buffer;
    if(file.is_open()){

        ///pula primeira linha
        getline(file, buffer);
        int cont = 0;
        int cont2 = 0;

        int probLimit;
        
        probLimit = numElementos/5;
        ///Pega linhas pulando aleatoriamente
        while(!file.eof() && cont < numElementos){

            /// Pega um valor aleatorio entre 1 e n
            val = rand()% n+1;

            ///Probabilidade do programa ler a linha (quanto maior o limite, maior a probabilidade).
            ///Se o numero de linhas que quiser pegar  for muito grande, aumentar a probabilidade (limite)
            ///porque, se nao, o arquivo acaba antes de pegar todas as linhas que quiser (para o de 26 milhoes talvez nao tenha esse problema).
            if(val < probLimit){
                
                rating* element = new rating();
                elements[cont] = element;

                getline(file, buffer, ',');
                elements[cont]->userId = stoi(buffer);

                getline(file, buffer, ',');
                elements[cont]->movieId = stoi(buffer);

                getline(file, buffer, ',');
                elements[cont]->rate = stof(buffer);

                getline(file, buffer, '\n');
                elements[cont]->timestamp = buffer;
                
                
                elements[cont]->keyValue = elements[cont]->userId + elements[cont]->movieId;

                cont++;
                n++;
            }

            cont2++;
            getline(file, buffer);
        }

        if(cont != numElementos)
            std::cout << "Nao foram lidos todos as avaliacoes requeridas, aumentar o limite para a probabilidade de pegar uma linha ! " << std::endl;

        file.close();

    }else
        std::cout << "Erro ao abrir o arquivo ratings.csv ! " << std::endl;

}


Btree* createBTree(rating** elements, unsigned int seed, int numIter){

    std::string name = "C:\\Users\\thiag\\Desktop\\Btrees\\arquivosSaidaInsercao\\saidaInsercao" + std::to_string(numElementos) + "-" + std::to_string(numIter) + ".txt";
    std::ofstream file;
    file.open(name);

    float time;
    Timer* timer = new Timer(&time);

    Btree* btree = new Btree(2);

    int keysComparisons = 0;

    for(int i = 0; i < numElementos;i++)
        btree->insert(elements[i], keysComparisons);


    delete timer;
    file << "NUM ELEMENTOS = " << numElementos << std::endl;
    file << "D = " << btree->get_D() << std::endl;
    file << "NUMERO DE COMPARACOES ENTRE CHAVES PARA INSERCAO DAS MESMAS = " << keysComparisons << std::endl;
    file << "TEMPO DE PROCESSAMENTO PARA A CRIACAO DA ARVORE = " << time << "segundos" << std::endl;
    file << "SEED = " << seed << std::endl;

    return btree;
}

void makeSearches(Btree* btree, rating** elements, unsigned int seed, int numIter){

    std::string name = "C:\\Users\\thiag\\Desktop\\Btrees\\arquivosSaidaBusca\\saidaBusca" + std::to_string(numElementos) + "-" + std::to_string(numIter) + ".txt";
    std::ofstream file;
    file.open(name);

    float time;
    Timer* timer = new Timer(&time);
    
    int keysComparisons = 0;

    int cont = 0;
    
    for(int i = 0; i < numElementos;i++){
        if(btree->search(elements[i], keysComparisons) == NULL)
            std::cout << "Nao encontrou avaliacao! " << std::endl;
    }

    delete timer;
    file << "NUM ELEMENTOS = " << numElementos << std::endl;
    file << "D = " << btree->get_D() << std::endl;
    file << "NUMERO DE COMPARACOES ENTRE CHAVES NA BUSCA DAS MESMAS = " << keysComparisons << std::endl;
    file << "TEMPO DE PROCESSAMENTO PARA REALIZAR TODAS AS BUSCAS = " << time << " segundos" << std::endl;
    file << "SEED = " << seed << std::endl;
}