#include "FuncoesGerais.h"

///Classe timer para marcar o tempo de duração de alguma funcionalidade
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

///Le o arquivo ratings com o tamanho correspondente
void leArq(rating** elementos){
 
    int n = 1;
    int val;

    std::ifstream file;
    file.open(raiz_dir + "\\arquivosEntrada\\ratings.csv");

    std::string buffer;
    if(file.is_open()){

        ///pula primeira linha
        getline(file, buffer);
        int cont = 0;
        int cont2 = 0;

        int probLimit;
        
        probLimit = (numElementos/5);
        ///Pega linhas pulando aleatoriamente
        while(!file.eof() && cont < numElementos){

            /// Pega um valor aleatorio entre 1 e n
            val = rand()% n+1;

            ///Probabilidade do programa ler a linha (quanto maior o limite, maior a probabilidade).
            ///Se o numero de linhas que quiser pegar  for muito grande, aumentar a probabilidade (limite)
            ///porque, se nao, o arquivo acaba antes de pegar todas as linhas que quiser (para o de 26 milhoes talvez nao tenha esse problema).
            if(val < probLimit){
                
                rating* elemento = new rating();
                elementos[cont] = elemento;

                getline(file, buffer, ',');
                elementos[cont]->userId = stoi(buffer);

                getline(file, buffer, ',');
                elementos[cont]->movieId = stoi(buffer);

                getline(file, buffer, ',');
                elementos[cont]->rate = stof(buffer);

                getline(file, buffer, '\n');
                elementos[cont]->timestamp = buffer;
                
                
                elementos[cont]->keyValue = elementos[cont]->userId + elementos[cont]->movieId;

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

///Cria a arvore B com os elementos passados por parametro e anora as estatisticas nos arquivos de saida
///Correspondentes
Btree* criaBTree(rating** elementos, int numIter){

    std::string name = raiz_dir + "\\arquivosSaidaInsercao\\saidaInsercao" + std::to_string(numElementos) + "-" + std::to_string(numIter) + ".txt";
    std::ofstream file;
    file.open(name);

    float time;
    Timer* timer = new Timer(&time);

    ///Cria arvore com grau escolhido
    Btree* btree = new Btree(13);

    ///Numero de comparacoes e copias
    int numComparacoesChaves = 0;
    int numCopias = 0;

    ///Insere todos os elementos
    for(int i = 0; i < numElementos;i++)
        btree->insere(elementos[i], numComparacoesChaves, numCopias);


    delete timer;

    ///Anota as estatisticas
    file << "NUM ELEMENTOS = " << numElementos << std::endl;
    file << "D = " << btree->get_D() << std::endl;
    file << "NUMERO DE COPIAS DAS CHAVES NA INSERCAO DAS MESMAS = " << numCopias << std::endl;
    file << "NUMERO DE COMPARACOES ENTRE CHAVES PARA INSERCAO DAS MESMAS = " << numComparacoesChaves << std::endl;
    file << "TEMPO DE PROCESSAMENTO PARA A CRIACAO DA ARVORE = " << time << "segundos" << std::endl;

    return btree;
}

///Faz a busca de todos os elementos na arvore, um por um e anota as estatisticas nos arquivos de saida
///Correspondentes
void fazBuscas(Btree* btree, rating** elementos, int numIter){

    std::string name = raiz_dir + "\\arquivosSaidaBusca\\saidaBusca" + std::to_string(numElementos) + "-" + std::to_string(numIter) + ".txt";
    std::ofstream file;
    file.open(name);

    float time;
    Timer* timer = new Timer(&time);
    
    ///Numero de comparacoes e copias feitas
    int numComparacoesChaves = 0;
    int numCopias = 0;
    
    ///Busca todas as chaves uma por uma
    for(int i = 0; i < numElementos;i++){
        if(btree->busca(elementos[i], numComparacoesChaves, numCopias) == NULL)
            std::cout << "Nao encontrou avaliacao! " << std::endl;
    }

    delete timer;

    ///Anota as estatisticas
    file << "NUM ELEMENTOS = " << numElementos << std::endl;
    file << "D = " << btree->get_D() << std::endl;
    file << "NUMERO DE COPIAS DAS CHAVES NA BUSCA DAS MESMAS = " << numCopias << std::endl;
    file << "NUMERO DE COMPARACOES ENTRE CHAVES NA BUSCA DAS MESMAS = " << numComparacoesChaves << std::endl;
    file << "TEMPO DE PROCESSAMENTO PARA REALIZAR TODAS AS BUSCAS = " << time << " segundos" << std::endl;
    
}