#ifndef HASHTABLEEE_H_INCLUDED
#define HASHTABLEEE_H_INCLUDED

///Estrutura para representar a chave no tratamento com encadeamento externo
struct chaveL{

    int userId, movieId;
    bool preenchido; ///para verificar se aquela posicao do vetor ja esta preenchida.
    chaveL* prox;
    
};

///Classe que contem o tamanho da tabela e o vetor de chaves que representa a tabela
///com o tratamento por encadeamento externo.
class hashTableEE{

private:

    int tableSize; ///Tamanho da tabela
    chaveL** table;   ///Estrutura que representa a tabela(vetor de ponteiros de chaves)

public:

    static long long unsigned int colisoes;
    static int numInsercoes;

    hashTableEE(int tam);
    ~hashTableEE();

    int hashFunction(chaveL k);

    void insereChave(chaveL k);
    void imprimeTable();
    float memoriaUtilizada();
};

#endif // HASHTABLEEE_H_INCLUDED
