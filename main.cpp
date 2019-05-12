#include "FuncoesGerais.h"
#include <ctime>
#include <cmath>

using namespace std;

ofstream saida;///Stream na qual eh impressa os resultados
int tamanho;///Quantidade de elementos que ira ler do arquivo


///Tem-se um laco com os 7 tamanhos usados que rodam 5 vezes para cada tamanho com seeds diferentes
///e imprimem no arquivo de saida os resultados.
int main()
{   

    //saida.open("saida.txt");

    //srand(time(NULL));

    int tamanhos[7] = {1000, 5000, 10000, 50000, 100000, 500000, 1000000};

    for(int i = 0; i < 7;i++){

        tamanho = tamanhos[i];

        for(int j = 0; j < 5;j++){
            
            int* userId = new int[tamanhos[i]];
            int* movieId = new int[tamanhos[i]];
            float* rating = new float[tamanhos[i]];
            string* timestamp = new string[tamanhos[i]];


            string nomeArq = "saida";
            nomeArq = nomeArq + to_string(tamanhos[i]) + "-" + to_string(j) + ".txt";
            saida.open(nomeArq);

            saida << "-----SAIDAS PARA OS TRATAMENTOS DE COLISAO COM " << tamanhos[i] << " ELEMENTOS !-----" << endl;

            int seed = rand()% RAND_MAX;
            srand(seed);

            leituraArqAvaliacoes(userId, movieId, rating, timestamp);

            clock_t inicio, fim;

            ///SONDAGEM LINEAR
            inicio = clock();

            hash_sondagemLinear(userId, movieId);

            fim = clock();
            saida << "TEMPO = " << (float)(fim - inicio)/CLOCKS_PER_SEC << " segundos" << std::endl;

            ///SONDAGEM QUADRATICA
            inicio = clock();

            hash_sondagemQuadratica(userId, movieId);

            fim = clock();
            saida  << "TEMPO = " << (float)(fim - inicio)/CLOCKS_PER_SEC << " segundos" << std::endl;


            ///REHASH
            inicio = clock();

            hash_reHash(userId, movieId);

            fim = clock();
            saida  << "TEMPO = " << (float)(fim - inicio)/CLOCKS_PER_SEC << " segundos" << std::endl;


            ///ENCADEAMENTO EXTERNO
            inicio = clock();

            hash_encadeamentoExterno(userId, movieId);

            fim = clock();
            saida  << "TEMPO = " << (float)(fim - inicio)/CLOCKS_PER_SEC << " segundos" << std::endl;
            
            ///ENCADEAMENTO COALESCIDO
            inicio = clock();

            hash_encadeamentoCoalescido(userId, movieId);

            fim = clock();
            saida << "TEMPO = " << (float)(fim - inicio)/CLOCKS_PER_SEC << " segundos" << std::endl;

            saida.close();

            delete [] userId; 
            delete [] movieId;
            delete [] rating;
            delete [] timestamp;

        }
    }

    system("pause");

    return 0;
 }
