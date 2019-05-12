#include "FuncoesGerais.h"

using namespace std;

extern ofstream saida;
extern int tamanho;

///Acha o numero primo para usar como tamanho da tabela
int achaPrimo(int n)
{   
    //Código adaptado de https://www.geeksforgeeks.org/sieve-sundaram-print-primes-smaller-n/
    // No geral o Crivo de Sundaram, produz primos menores
    // que (2*x + 2) para um dado numero x.
    // Como nos queremos primos menores x reduzimos n pela metadade
    int nNew = (n-2)/2;

    // Esse vetor eh usado para separar numeros da forma i+j+2ij
    // dos outros onde  1 <= i <= j
    bool marked[nNew + 1];

    // Inicializa todos os elementos como nao marcados
    memset(marked, false, sizeof(marked));

    // Logica principal de Sundaram.  marca todos os numeros
    // na forma i + j + 2ij como verdadeiros onde 1 <= i <= j

    long long int ind;
    for (long long int i=1; i<=nNew; i++)
        for (long long int j=i; (ind = (i + j + 2*i*j)) <= nNew; j++)
            marked[ind] = true;



    // Printa outros primos. Primos restantes sao da forma
    // 2*i + 1 tais que  marked[i] eh  falso.
    for (long long int i=1; i<=nNew; i++)
        if (marked[i] == false && (2*i + 1) > n/2)
            return (2*i + 1);
}

///Recebe os vetores userId, movieId, rating, timestamp, e ratings(vetor de objetos).
///Le o arquivo e preenche esses vetores com as respectivas informacoes do arquivo.
///Embaralha os vetores
void leituraArqAvaliacoes(int* userId, int* movieId, float* rating, string* timestamp){

    int n = 1;
    int val;

    ifstream arquivo;
    arquivo.open("ratings.csv");

    string buffer;
    if(arquivo.is_open()){

        ///pula primeira linha
        getline(arquivo, buffer);
        int cont = 0;
        int cont2 = 0;
        ///Pega linhas pulando aleatoriamente
        while(!arquivo.eof() && cont < tamanho){

            /// Pega um valor aleatorio entre 1 e n
            val = rand()% n+1;

            int limiar;

            if(tamanho == 1000)
                limiar = 5;

            if(tamanho == 5000)
                limiar = 15;

            if(tamanho == 10000)
                limiar = 50;

            if(tamanho == 50000)
                limiar = 100;
            
            if(tamanho == 100000)
                limiar = 300;

            if(tamanho == 500000)
                limiar = 800;
            
            if(tamanho == 1000000)
                limiar = 1500;
            
            ///Probabilidade do programa ler a linha (quanto maior o limite, maior a probabilidade).
            ///Se o numero de linhas que quiser pegar  for muito grande, aumentar a probabilidade (limite)
            ///porque, se nao, o arquivo acaba antes de pegar todas as linhas que quiser (para o de 26 milhoes talvez nao tenha esse problema).
            if(val < 5000){

                getline(arquivo, buffer, ',');
                userId[cont] = stoi(buffer);

                getline(arquivo, buffer, ',');
                movieId[cont] = stoi(buffer);

                getline(arquivo, buffer, ',');
                rating[cont] = stof(buffer);

                getline(arquivo, buffer, '\n');
                timestamp[cont] = buffer;

                cont++;
                n++;
            }
            cont2++;
            getline(arquivo, buffer);
        }

        ///embaralha os vetores

        random_shuffle(&userId[0], &userId[tamanho]);
        random_shuffle(&movieId[0], &movieId[tamanho]);
        random_shuffle(&rating[0], &rating[tamanho]);
        random_shuffle(&timestamp[0], &timestamp[tamanho]);


        arquivo.close();
    }else
        cout << "Erro ao abrir o arquivo !" << endl;
}


///Recebe os vetores userId e movieId.
///Cria o vetor de chaves com os valores correspondentes de userId e movieId.
///Cria a tabela Hash e trata as colisoes pelo metodo de sondagem linear
void hash_sondagemLinear(int* userId, int* movieId){
    
    saida << "-----SONDAGEM LINEAR-----" << endl;

    chave* vetorChaves = new chave[tamanho];

    ///Utilizamos um fator de carga de 75%, para evitarmos um pouco das colisoes
    ///Pegamos o primeiro primo depois de ter achado o tamanho com fator de carga de 75%
    ///Por exemplo , se o numero de elementos for 1000, o tamanho da tabela sera 1337
    int tam = tamanho/0.75;
    tam = achaPrimo(tam*2);
    hashTableOA obj(tam);

    for(int i = 0; i < tamanho;i++){
        vetorChaves[i].userId = userId[i];
        vetorChaves[i].movieId = movieId[i];
        vetorChaves[i].preenchido = false;
        obj.insereChave(vetorChaves[i], 'L');

    }

    saida << "TAMANHO OCUPADO = " << obj.memoriaUtilizada() << " Mb !" << endl;
    saida << "COLISOES = " << obj.colisoes << endl;
    saida << "NUMERO DE INSERCOES = " << obj.numInsercoes << endl;

    hashTableOA::colisoes = 0;
    hashTableOA::numInsercoes= 0;

    delete [] vetorChaves;
}


///Recebe os vetores userId e movieId.
///Cria o vetor de chaves com os valores correspondentes de userId e movieId.
///Cria a tabela Hash e trata as colisoes pelo metodo de sondagem quadratica
void hash_sondagemQuadratica(int* userId, int* movieId){

    saida << "-----SONDAGEM QUADRATICA-----" << endl;

    chave* vetorChaves = new chave[tamanho];


    int tam = tamanho/0.75;
    tam = achaPrimo(tam*2);
    hashTableOA obj(tam);

    ///Utilizamos um fator de carga de 75%, para evitarmos um pouco das colisoes
    ///Pegamos o primeiro primo depois de ter achado o tamanho com fator de carga de 75%
    ///Por exemplo , se o numero de elementos for 1000, o tamanho da tabela sera 1337
    for(int i = 0; i < tamanho;i++){
        vetorChaves[i].userId = userId[i];
        vetorChaves[i].movieId = movieId[i];
        vetorChaves[i].preenchido = false;
        obj.insereChave(vetorChaves[i], 'Q');
        
    }

    saida << "TAMANHO OCUPADO = " << obj.memoriaUtilizada() << " mb !" << endl;
    saida << "COLISOES = " << obj.colisoes << endl;
    saida << "NUMERO DE INSERCOES = " << obj.numInsercoes << endl;

    hashTableOA::colisoes = 0;
    hashTableOA::numInsercoes= 0;

    delete [] vetorChaves;
}

///Recebe os vetores userId e movieId.
///Cria o vetor de chaves com os valores correspondentes de userId e movieId.
///Cria a tabela Hash e trata as colisoes pelo metodo de reHash
void hash_reHash(int* userId, int* movieId){

    saida << "-----REHASH-----" << endl;

    chave* vetorChaves = new chave[tamanho];

    int tam = tamanho/0.75;
    tam = achaPrimo(tam*2);
    hashTableOA obj(tam);

    ///Utilizamos um fator de carga de 75%, para evitarmos um pouco das colisoes
    ///Pegamos o primeiro primo depois de ter achado o tamanho com fator de carga de 75%
    ///Por exemplo , se o numero de elementos for 1000, o tamanho da tabela sera 1337
    for(int i = 0; i < tamanho;i++){
        vetorChaves[i].userId = userId[i];
        vetorChaves[i].movieId = movieId[i];
        obj.insereChave(vetorChaves[i], 'R');
    }

    saida << "TAMANHO OCUPADO = " << obj.memoriaUtilizada() << " mb !" << endl;
    saida << "COLISOES = " << obj.colisoes << endl;
    saida << "NUMERO DE INSERCOES = " << obj.numInsercoes << endl;

    hashTableOA::colisoes = 0;
    hashTableOA::numInsercoes= 0;

    delete [] vetorChaves;

}

///Recebe os vetores userId e movieId.
///Cria o vetor de chaves com os valores correspondentes de userId e movieId.
///Cria a tabela Hash e trata as colisoes pelo metodo de encadeamento Externo
void hash_encadeamentoExterno(int* userId, int* movieId){

    saida << "-----ENCADEAMENTO EXTERNO----" << endl;

    chaveL* vetorChaves = new chaveL[tamanho];

    int tam = tamanho/0.75;
    tam = achaPrimo(tam*2);
    hashTableEE obj(tam);

    for(int i = 0; i < tamanho; i++){
        vetorChaves[i].userId = userId[i];
        vetorChaves[i].movieId = movieId[i];
        obj.insereChave(vetorChaves[i]);
    }

    saida << "TAMANHO OCUPADO = " << obj.memoriaUtilizada() << " mb !" << endl;
    saida << "COLISOES = " << obj.colisoes << endl;
    saida << "NUMERO DE INSERCOES = " << obj.numInsercoes << endl;

    hashTableEE::colisoes = 0;
    hashTableEE::numInsercoes = 0;

    delete [] vetorChaves;
}

///Recebe os vetores userId e movieId.
///Cria o vetor de chaves com os valores correspondentes de userId e movieId.
///Cria a tabela Hash e trata as colisoes pelo metodo de encadeamento Coalescido
void hash_encadeamentoCoalescido(int* userId, int* movieId){


    saida << "-----ENCADEAMENTO COALESCIDO-----" << endl;

    chaveC* vetorChaves = new chaveC[tamanho];

    int tam = tamanho/0.75;
    tam = achaPrimo(tam*2);
    hashTableEC obj(tam);

    for(int i = 0; i < tamanho;i++){
        vetorChaves[i].userId = userId[i];
        vetorChaves[i].movieId = movieId[i];
        obj.insereChave(vetorChaves[i]);
       
    }

    saida << "TAMANHO OCUPADO = " << obj.memoriaUtilizada() << " mb !" << endl;
    saida << "COLISOES = " << obj.colisoes << endl;
    saida << "NUMERO DE INSERCOES = " << obj.numInsercoes << endl;

    hashTableEC::colisoes = 0;
    hashTableEC::numInsercoes= 0;

}


