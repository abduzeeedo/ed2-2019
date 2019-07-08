#include <iostream>
#include "BtreeNode.h"

using namespace std;

///Construtor
BtreeNode::BtreeNode(int _d, bool _ehFolha){

    d = _d; 
    ehFolha = _ehFolha; 
   
    chaves = new rating*[2*d-1]; 
    C = new BtreeNode*[2*d]; 
  
    n = 0;

}

///Destrutor
BtreeNode::~BtreeNode(){

    delete [] chaves;

    for(int i = 0; i < 2*d+1; i++)
        delete C[i];
    delete [] C;
}

///Percorre a arvore toda, em ordem crescente
void BtreeNode::percorre(){
    
    int i;

    for (i = 0; i < n; i++) 
    {   
        ///Se nao for folha vai para o filho
        if (ehFolha == false)
            C[i]->percorre();
        
        ///Quando for folha, imprime as n chaves e vai voltar a funcao recursiva pra quem chamou
        ///imprimir o no de quem chamou e ir para o proximo filho e voltar novamente,
        ///até ter percorrido todos
        cout << " (" << chaves[i]->userId << ", " << chaves[i]->movieId << ")"; 
    } 
    
    ///Teste para conseguir percorrer o ultimo filho do no se nao for folha
    if (ehFolha == false)
        C[i]->percorre(); 
}

///Busca uma avaliacao passada por parametro
BtreeNode* BtreeNode::busca(rating* k, int& numComparacoesChaves, int& numCopias){

    int i = 0; 
    ///Acha a primeira chave com userId maior ou igual a do k 
    while (i < n && ++numComparacoesChaves &&  k->userId > chaves[i]->userId) 
        i++;

    ///Se for igual, acha a primeira chave com movieId maior ou igual a do k
    while(i < n && ++(++numComparacoesChaves) &&  k->userId == chaves[i]->userId && k->movieId > chaves[i]->movieId)
        i++; 
    

    ///Teste para verificar se o i saiu com o valor de n para nao crashar
    if(i != n){

        ///Se a chave encontrada tiver o mesmo userId e o mesmo movieId,ahou
        if (++(++numComparacoesChaves) && chaves[i]->userId == k->userId && chaves[i]->movieId == k->movieId){
            //cout << " ACHOU " << chaves[i]->userId << ", " << chaves[i]->movieId << endl;
            return this; 
        }

    }else{

        if (++(++numComparacoesChaves) && chaves[i-1]->userId == k->userId && chaves[i-1]->movieId == k->movieId){
            //cout << " ACHOU " << chaves[i-1]->userId << ", " << chaves[i-1]->movieId << endl;
            return this; 
        }
    }
    
  
    /// Se a chave nao foi encontrada ate aqui e esse no eh um no folha, nao achou
    if (ehFolha == true) 
        return NULL; 
  
    
    ///Se a chave nao foi encontrada ate aqui e nao eh um no folha, entao vai para o filho certo
    ///definido pelo i
    return C[i]->busca(k, numComparacoesChaves, numCopias);

}

///Metodo que insere na arvore presupondo que esse no nao esteja cheio
void BtreeNode::insereNaoCheio(rating* k, int& numComparacoesChaves, int& numCopias){

    /// Começa o i como sendo o elemento mais a direita no no 
    int i = n-1; 
   
    if (ehFolha == true) 
    { 

        ///Acha qual a posicao a nova chave sera inserida e move as chaves que sao maiores
        ///um lugar para frente
        while (i >= 0 && ++numComparacoesChaves && chaves[i]->userId > k->userId) 
        { 
            chaves[i+1] = chaves[i]; 
            i--;
            numCopias++;
        }

        ///Mesma coisa do de cima , mas considerando em qual lugar entre as chaves com userId igual
        ///a nova sera inserida baseada no movieId  e move as chaves maiores uma posicao para frente
        while(i >= 0 && ++(++numComparacoesChaves) && (chaves[i]->userId == k->userId) &&  (chaves[i]->movieId > k->movieId)){
            chaves[i+1] = chaves[i]; 
            i--;
            numCopias++;
        }

        ///Insere a chave na posicao encontrada i 
        chaves[i+1] = k; 
        n = n+1; ///Soma um no numero de chaves
        numCopias++;
    } 
    else
    { 
        ///Acha em qual filho a nova chave sera colocada, se esse no nao for folha
        while (i >= 0 && ++numComparacoesChaves && chaves[i]->userId > k->userId) 
            i--;

        while(i >= 0 && ++(++numComparacoesChaves) && (chaves[i]->userId == k->userId) &&  (chaves[i]->movieId > k->movieId)) 
            i--;
        

        ///Se o filho encontrado estiver cheio 
        if (C[i+1]->n == 2*d-1) 
        {  
            splitFilho(i+1, C[i+1], numCopias); 

            ///Depois de splitar, a chave do meio do filho vai para o no de cima
            ///e eh divido em dois e verifica qual dos dois novos nos tera
            ///a nova chave
            if (++(++(++numComparacoesChaves)) && chaves[i+1]->userId < k->userId || (chaves[i+1]->userId == k->userId && chaves[i+1]->movieId < k->movieId)) 
                i++;
        } 
        
        ///Insere a chave
        C[i+1]->insereNaoCheio(k, numComparacoesChaves, numCopias); 
        //std::cout << "INSERIU NO FILHO " << i+1 << std::endl;
    } 
} 

///Metodo que splita o filho w desse no
void BtreeNode::splitFilho(int i, BtreeNode *w, int& numCopias) 
{   
    
    ///O novo no z tera d-1 chaves (o minimo)
    BtreeNode *z = new BtreeNode(w->d, w->ehFolha); 
    z->n = d-1;  

    ///Passa as primeiras chaves do filho para o novo no z
    for (int j = 0; j < d-1; j++){
        z->chaves[j] = w->chaves[j+d]; 
        numCopias++;
    }
  
    ///Copia os d+1 filhos do filho w para z 
    if (w->ehFolha == false) 
    { 
        for (int j = 0; j < d; j++){
            z->C[j] = w->C[j+d]; 
            numCopias++;
        }
    } 
  
    ///Atualiza o numero de chaves de w 
    w->n = d-1; 
  
    ///Cria um espaco para um filho em nesse no(s)
    for (int j = n; j >= i+1; j--) 
        C[j+1] = C[j]; 
  
    /// Linka o no que criamos em s 
    C[i+1] = z; 
  
    ///Acha o lugar que a chave sera inserida nesse no (s) baseado no i passado por parametro
    ///E move todas as chaves maiores um lugar pra frente
    for (int j = n-1; j >= i; j--) {
        chaves[j+1] = chaves[j]; 
        numCopias++;
    }
  
    ///A chave do meio de w sera copiada para esse no (s) na posicao i 
    chaves[i] = w->chaves[d-1]; 
    numCopias++;
  
    ///Atualiza o numero de chaves desse no (s)
    n = n + 1; 
}