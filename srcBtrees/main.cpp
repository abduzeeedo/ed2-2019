#include "FuncoesGerais.h"

int numElementos;

int main(int argc, char const *argv[])
{   

    for(int numIter = 0; numIter < 1; numIter++){

        unsigned int seed = time(NULL);
        srand(seed);

        std::ifstream file;
        file.open("C:\\Users\\thiag\\Desktop\\Btrees\\arquivosEntrada\\entradaTamanhos.txt");

        std::string buffer;

        if(file.is_open()){
        
            while(!file.eof()){

                getline(file, buffer);
                numElementos = stoi(buffer);

                rating** elements = new rating*[numElementos];

                std::cout << "LENDO O ARQUIVO RATINGS... " << std::endl;
                readFile(elements);
                
                std::cout << "MONTANDO ARVORES PARA " << numElementos << " ELEMENTOS..."  << std::endl; 
                Btree* btree = createBTree(elements, seed, numIter+1);

                std::cout << "ELEMENTOS " << std::endl; 
                for(int i = 0; i < numElementos;i++)
                    std::cout << elements[i]->userId << " " << elements[i]->movieId << std::endl;

                btree->printTree();

                std::cout << "FAZENDO AS BUSCAS NA ARVORE..." << std::endl;
                makeSearches(btree, elements, seed, numIter+1);

                std::cout << "TERMINADO COM SUCESSO ! RESULTADOS COLOCADOS NOS ARQUIVOS DE SAIDA :) " << std::endl; 

                delete [] elements;
                delete btree;
            }

        }else
            std::cout << "Erro ao abrir o arquivo !" << std::endl;
    }

    return 0;
}
