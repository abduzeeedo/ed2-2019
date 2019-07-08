#ifndef BTREENODE_H_INCLUDED
#define BTREENODE_H_INCLUDED

struct rating{

    int userId;
    int movieId;
    float rate;
    std::string timestamp;

    int keyValue;
};

class BtreeNode{

private:

    int d;      ///Ordem
    BtreeNode** C; ///Vetor de ponteiros para os filhos
    bool ehFolha; ///Se é folha ou não
    int n; ///Numero de chaves atual do no
    rating** chaves;  ///Vetor de chaves

public:

    BtreeNode(int _d, bool _ehFolha);
    ~BtreeNode();

    void percorre(); ///Percorre todos os nos que tem esse no como raiz

    BtreeNode* busca(rating* k, int& numComparacoesChaves, int& numCopias); ///Funcao que procura um no numa subarvore com raiz nesse no

    void insereNaoCheio(rating* k, int& numComparacoesChaves, int& numCopias); ///Funcao que insere a chave k na subarvore que tem raiz nesse no. Assume-se que o no não está cheio
    void splitFilho(int i, BtreeNode* w, int& numCopias); ///Funcao que splita o filho y desse no. O filho deve estar cheio

    friend class Btree;
};



#endif // BTREENODE_H_INCLUDED