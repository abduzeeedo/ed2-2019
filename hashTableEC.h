#ifndef HASHTABLEEC_H_INCLUDED
#define HASHTABLEEC_H_INCLUDED

///Estrutura para representar a chave no tratamento com encadeamento coalescido sem porao
struct chaveC{

    int userId, movieId;
    chaveC* prox;
    int status; ///Auxiliar na hora de percorrer o vetor quando colidir

};

///Classe que contem o tamanho da tabela e o vetor de chaves que representa a tabela
///com o tratamento por encadeamento coalescido.
class hashTableEC{

private:

    int tableSize; ///Tamanho da tabela
    chaveC** table; ///Estrutura que representa a tabela(vetor de ponteiros de chaves)

public:
    static long long unsigned int colisoes;
    static int numInsercoes;

    hashTableEC(int tam);
    ~hashTableEC();

    int hashFunction(chaveC k);
    void insereChave(chaveC k);
    float memoriaUtilizada();
    void imprimeTable();

};

#endif // HASHTABLEC_H_INCLUDED
