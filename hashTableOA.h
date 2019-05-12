#ifndef HASHTABLEOA_H_INCLUDED
#define HASHTABLEOA_H_INCLUDED

///Estrutura para representar a chave nos tratamentos com enderecamento aberto
struct chave{

public:

    int userId, movieId;
    bool preenchido; ///para verificar se aquela posicao do vetor ja esta preenchida.

};

///Classe que contem o tamanho da tabela e o vetor de chaves que representa a tabela
///com os tratamentos de enderecamento aberto(sondagem linear, sondagem quadratica, reHash).
class hashTableOA{

private:

    int tableSize;///Tamanho da tabela
    chave* table; ///Estrutura para representar a tabela (vetor de chaves)

public:

    static long long unsigned int colisoes;
    static int numInsercoes;

    hashTableOA(int tam);
    ~hashTableOA();

    int hashFunction(chave k);
    int sondagemLinear(chave k, int pos); ///Trata as colisoes por sondagem Linear
    int sondagemQuadratica(chave k, int pos); ///Trata as colisoes por sondagem Quadratica
    int reHash(chave k, int pos); ///Trata as colisoes por reHash
    void insereChave(chave k, char tratamento);
    void imprimeTable();
    float memoriaUtilizada();


};

#endif // HASHTABLEOA_H_INCLUDED
