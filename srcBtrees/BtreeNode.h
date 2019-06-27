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
    bool leaf; ///Se é folha ou não
    int n; ///Numero de chaves atual do no
    rating** keys;  ///Vetor de chaves

public:

    BtreeNode(int _t, bool _leaf);
    ~BtreeNode();

    void traverse(); ///Percorre todos os nos que tem esse no como raiz

    BtreeNode* search(rating* k, int& keyComparisons); ///Funcao que procura um no numa subarvore com raiz nesse no

    void insertNonFull(rating* k, int& keysComparisons); ///Funcao que insere a chave k na subarvore que tem raiz nesse no. Assume-se que o no não está cheio
    void splitChild(int i, BtreeNode* y); ///Funcao que splita o filho y desse no. O filho deve estar cheio

    friend class Btree;
};



#endif // BTREENODE_H_INCLUDED