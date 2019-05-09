#include "ordenacoes.h"
using namespace std;

//Construtor
Ordenacoes::Ordenacoes()
{
	numTrocas = 0;
	numCompar = 0;
	tempoGasto = 0.0;
}

//Destrutor
Ordenacoes::~Ordenacoes()
{
}

//Retorna o numero de trocas feitas
int Ordenacoes::getNumTrocas()
{
	return numTrocas;
}

//Retorna o numero de comparacoes feitas
int Ordenacoes::getNumComparacoes()
{
	return numCompar;
}

//Retorna o tempo gasto pela ordenacao
double Ordenacoes::getTempoGasto()
{
	return tempoGasto;
}

//Funcao usada zerar os atributos a fim de preparar para outra ordenacao
void Ordenacoes::limpaDados()
{
	numCompar = 0;
	numTrocas = 0;
	tempoGasto = 0;
}

//Algoritmo InsertionSort
//ENTRADA: Vetor de objetos do tipo Rating, a posicao inicial e final do intervalo a ser ordenado
//SAIDA: Tal vetor ordenado via InsertionSort
void Ordenacoes::insertionsort(Rating* vet[], int inicio, int fim)
{
	clock_t relogio;
	relogio = clock();//Instancia um novo contador de tempo

	int i, j;
	Rating* chave; //chave auxiliar

	for (i = inicio + 1; i < fim; i++) //comeca da posicao inicio e termina na posicao fim
	{
		chave = vet[i]; //salva o valor atual do vet[i] na chave auxiliar
		j = i - 1;

		/* Desloca os elementos anteriores a chave que sao maiores que ela 1 posicao a frente da sua posicao atual*/
		while (j >= 0 && (vet[j]->getUserID() > chave->getUserID()) && ++numCompar)
		{
			vet[j + 1] = vet[j];
			numTrocas++;
			j--;
		}
		vet[j + 1] = chave; //coloca o valor salvo da chave na posicao que "sobrou" antes dos valores maiores que a chave
		numTrocas++;
	}

	tempoGasto += (clock() - relogio) / (double)CLOCKS_PER_SEC;
}

//Algoritmo InsertionSort aplicado a um vetor de inteiros
//ENTRADA: Vetor de inteiros (userIDs), a posicao inicial e final do intervalo a ser ordenado
//SAIDA: Tal vetor ordenado via InsertionSort
void Ordenacoes::insertionsortInt(int vet[], int inicio, int fim)
{
	clock_t relogio;
	relogio = clock();//Instancia um novo contador de tempo

	int i, j;
	int chave; //chave auxiliar

	for (i = inicio + 1; i < fim; i++) //comeca da posicao inicio e termina na posicao fim
	{
		chave = vet[i]; //salva o valor atual do vet[i] na chave auxiliar
		j = i - 1;

		/* Desloca os elementos anteriores a chave que sao maiores que ela 1 posicao a frente da sua posicao atual*/
		while (j >= 0 && (vet[j] > chave) && ++numCompar)
		{
			vet[j + 1] = vet[j];
			numTrocas++;
			j--;
		}
		vet[j + 1] = chave; //coloca o valor salvo da chave na posicao que "sobrou" antes dos valores maiores que a chave
		numTrocas++;
	}

	tempoGasto += (clock() - relogio) / (double)CLOCKS_PER_SEC;
}

//Funcao que realiza a troca de posicao entre dois objetos do tipo Rating
//ENTRADA: 2 Objetos do tipo Rating a serem trocados de posicao entre si
//SAIDA: A troca de posicao entre os dois objetos
void Ordenacoes::troca(Rating* &r1, Rating* &r2)
{
	if (r1 != r2) //Nao troca se r1 e r2 sao iguais, ja que nao precisa
	{
		Rating* aux = r1;
		r1 = r2;
		r2 = aux;
		numTrocas++;
	}
}

//Algoritmo de particionamento do vetor
//ENTRADA: Vetor de objetos do tipo Rating, posicao inicial e final deste vetor e indice da posicao onde o pivo sera posicionado
//SAIDA: Vetor Particionado
int Ordenacoes::particiona(Rating* vet[], int inicio, int fim, int pos)
{
	int pospiv;
	/*
	Posicao do vetor, a formula para calcular a posiçao é (inicio + ((posicao)%(fim-inicio+1))). No caso, posicao = (inicio + fim) / 2), metade do vetor
	Exemplo, caso queira passar a posicao 3 do vetor como pivo int pospiv = inicio + (3 % (fim - inicio + 1));
	*/
	if (pos == -1) { //Pos com Codigo -1: Usa a posicao central do vetor como pivo
		pospiv = inicio + (((inicio + fim) / 2) % (fim - inicio + 1));
	}
	else { //Caso Contratio, utiliza a posicao passada por parametro
		pospiv = inicio + (pos % (fim - inicio + 1));
	}

	long long int pivo = vet[pospiv]->getUserID(); //Pega o userID da posicao que foi pedida e coloca ela como pivo
	troca(vet[pospiv], vet[fim]); // Coloca o pivo como o ultimo elemento do vetor
	pospiv = fim; //Volta a posicao do pivo como sendo o fim do vetor que vai ser particionado

	//Variaveis para percorrer no vetor particionado
	int i = inicio - 1; //Comeca antes do inicio pq na primeira troca ele ja vai virar o inicio
	int j = inicio; //Anda do comeco ate o fim-1 do vetor

	while (j <= fim - 1) //Ele nao vai ate o fim do vetor pois o ultimo elemento eh o pivo que foi jogado para o final no comeco da execucao
	{
		if ((vet[j]->getUserID() <= pivo) && ++numCompar)
		{
			i++;
			troca(vet[i], vet[j]);
		}
		j++;
	}

	troca(vet[i + 1], vet[pospiv]); //Coloca o elemento ja ordenado na ultima posicao do vetor particionado
	return i + 1;
}

//Algoritmo do quicksort recursivo
//ENTRADA: Vetor de objetos do tipo Rating, posicao inicial e final deste vetor e codigo "tipo" que indica o tipo de quicksort a ser realizado
//SAIDA: Vetor ordenado via QuickSort
//Tipo r: QuickSort Recursivo com Pivo Central
//Tipo m: QuickSort Recursivo com Pivo sendo a Mediana entre 3 valores aleatorios do vetor
//Tipo M: QuickSort Recursivo com Pivo sendo a Mediana entre 5 valores aleatorios do vetor
//Tipo i: QuickSort Recursivo utilizando InsertionSort para particoes de tamanho menor ou igual a 10
//Tipo I: QuickSort Recursivo utilizando InsertionSort para particoes de tamanho menor ou igual a 100
void Ordenacoes::quicksort(Rating* vet[], int ini, int fim, char tipo)
{
	clock_t relogio;
	relogio = clock();
	if (tipo == 'r') { //QuickSort Recursivo Padrao
		if (ini < fim)
		{
			int part = particiona(vet, ini, fim, -1); //Codigo -1 em pos: Particao usando posicao central do vetor como pivo
			quicksort(vet, ini, part - 1, 'r');
			quicksort(vet, part + 1, fim, 'r');
		}
	}
	if (tipo == 'm') { //QuickSort Recursivo com Mediana de 3 valores
		if (ini < fim)
		{
			int posMediana = mediana(vet, 3, ini, fim); //posMediana recebe a posicao calculada na funcao Mediana com 3 valores
			int part = particiona(vet, ini, fim, posMediana);
			quicksort(vet, ini, part - 1, 'm');
			quicksort(vet, part + 1, fim, 'm');
		}
	}

	if (tipo == 'M') { //QuickSort Recursivo com Mediana de 5 valores
		if (ini < fim)
		{
			int posMediana = mediana(vet, 5, ini, fim); //posMediana recebe a posicao calculada na funcao Mediana com 5 valores
			int part = particiona(vet, ini, fim, posMediana);
			quicksort(vet, ini, part - 1, 'm');
			quicksort(vet, part + 1, fim, 'm');
		}
	}

	if (tipo == 'i') { //QuickSort Recursivo Hibrido (com Insertion para particoes de tamanho menor ou igual a 10)
		if (ini < fim)
		{
			if (fim - ini <= 10) {//Se a subparticao possuir tamanho menor ou igual a 10, ordena via InsertionSort
				Ordenacoes ordena;
				ordena.insertionsort(vet, ini, fim + 1);
				numCompar = numCompar + ordena.getNumComparacoes();
				numTrocas = numTrocas + ordena.getNumTrocas();
			}
			else {
				int part = particiona(vet, ini, fim, -1); //Codigo -1 em pos: Particao usando posicao central do vetor como pivo
				quicksort(vet, ini, part - 1, 'i');
				quicksort(vet, part + 1, fim, 'i');
			}
		}
	}

	if (tipo == 'I') { //QuickSort Recursivo Hibrido (com Insertion para particoes de tamanho menor ou igual a 100)
		if (ini < fim)
		{
			if (fim - ini <= 100) {//Se a subparticao possuir tamanho menor ou igual a 100, ordena via InsertionSort
				Ordenacoes ordena;
				ordena.insertionsort(vet, ini, fim + 1);
				numCompar = numCompar + ordena.getNumComparacoes();
				numTrocas = numTrocas + ordena.getNumTrocas();
			}
			else {
				int part = particiona(vet, ini, fim, -1); //Codigo -1 em pos: Particao usando posicao central do vetor como pivo
				quicksort(vet, ini, part - 1, 'I');
				quicksort(vet, part + 1, fim, 'I');
			}
		}
	}

	tempoGasto += (clock() - relogio) / (double)CLOCKS_PER_SEC;
}


//Funcao que calcula a mediana entre 3 e 5 valores aleatorios
//ENTRADA: Vetor de objetos do tipo Rating, numero de valores a serem tomados para o calculo da mediana, posicao inicial e final do vetor passado por parametro
//SAIDA: Retorna um inteiro que indica a posicao do vetor de Rating`s referente a mediana calculada, para ser usado como pivo do quicksort recursivo.
int Ordenacoes::mediana(Rating* vet[], int numVal, int inicio, int fim) {

	int posMediana;//posicao a ser calculada e retornada da funcao
	int posRand;//Posicao Calculada Randomicamente
	if (numVal == 3) { //para k=3
		Rating* vetor[3];
		for (int i = 0; i < 3; i++) {
			srand(i);
			posRand = rand() % (fim - inicio); //Atribui a posicao randomica do vetor original
			vetor[i] = new Rating(posRand, vet[posRand]->getMovieID(), 0 , ""); //Atribui a MovieID a posicao em si, e em UserID o valor do UserID contido nesta posicao
		}
		Ordenacoes ordena;
		ordena.insertionsort(vetor, 0, 3);//utiliza o insertionSort para ordenar o UserID do vetor de 3 posicoes
		posMediana = vet[1]->getMovieID();//pega o valor central do vetor (mediana) e atribui o movieID, que é a posicao original do vetor de Ratings
		return posMediana;
	}

	if (numVal == 5) {//para k=5
		Rating* vetor[5];
		for (int i = 0; i < 5; i++) {
			srand(i);
			posRand = rand() % (fim - inicio); //Atribui a posicao randomica do vetor original
			vetor[i] = new Rating(posRand, vet[posRand]->getMovieID(), 0, ""); //Atribui a MovieID a posicao em si, e em UserID o valor do UserID contido nesta posicao
		}
		Ordenacoes ordena;
		ordena.insertionsort(vetor, 0, 3);//utiliza o insertionSort para ordenar o UserID do vetor de 3 posicoes
		posMediana = vet[2]->getMovieID();//pega o valor central do vetor (mediana) e atribui o MovieID, que é a posicao original do vetor de Ratings
		return posMediana;
	}
	return inicio; //caso nao entre em nenhuma condicao, passa a posicao inicial como valor

}

void Ordenacoes::QuickSortInt(int* userId, int inicio, int fim){

    clock_t relogio;
	relogio = clock();

    int esquerda, direita, pivo, meio, aux;

    //limites da esquerda e da direita da região analisada
    esquerda = inicio;
    direita = fim;

    //ajustando auxiliares do centro
    meio = (int)((esquerda + direita)/2);
    pivo = userId[meio];

    while(direita > esquerda) {

      while(userId[esquerda] < pivo) {
        esquerda = esquerda +1;
        numCompar++;
        }
        while(userId[direita] > pivo) {
            numCompar++;
            direita = direita - 1;
        }

        if(esquerda <= direita){
            numCompar++;
            //realiza a troca
            aux = userId[esquerda];
            userId[esquerda] = userId[direita];
            userId[direita] = aux;
            numTrocas++;

            //Faz o limites laterais andarem para o centro
            esquerda = esquerda + 1;
            direita = direita - 1;

        }

    }

    //recursão para continuar comparando
    if(inicio < direita) {
        QuickSortInt(userId, inicio, direita);
    }

    if(esquerda < fim) {
        QuickSortInt(userId, esquerda, fim);
    }
    tempoGasto = (clock() - relogio) / (double)CLOCKS_PER_SEC;
}
//Procedimento que controi um vetor de objetos Heap
//ENTRADA: Vetor de objetos do tipo Rating, tamanho do vetor e o indice raiz
void Ordenacoes::constroiHeap(int vetor[], int tam, int indice_raiz)
{
	int ramificacao;
	int valor;
	valor = vetor[indice_raiz];

	while (indice_raiz < tam / 2) {
		ramificacao = 2 * indice_raiz + 1;

		if (ramificacao < tam - 1 && vetor[ramificacao] < vetor[ramificacao + 1]) {
			ramificacao++;

		}
		if (valor >= vetor[ramificacao]) {//Identifica o max-heap
			numTrocas++;
			break;
		}

		vetor[indice_raiz] = vetor[ramificacao];
		indice_raiz = ramificacao;
		++numCompar;
	}
	vetor[indice_raiz] = valor;
}




//Algoritmo HeapSort
//ENTRADA: Vetor de objetos do tipo Rating, e o tamanho do vetor
//SAIDA: Tal vetor ordenado via HeapSort
void Ordenacoes::heapsort(int vetor[], int tam)
{
	clock_t relogio;
	relogio = clock();

	int indice;
	int troca;
	for (indice = tam / 2; indice >= 0; indice--)
		constroiHeap(vetor, tam, indice);

	while (tam > 0)
	{
		troca = vetor[0];
		vetor[0] = vetor[tam - 1];
		vetor[tam - 1] = troca;
		numTrocas++;
		constroiHeap(vetor, --tam, 0);
	}

	tempoGasto = (clock() - relogio) / (double)CLOCKS_PER_SEC;
}

void Ordenacoes::MergeSort(int* vetor, int indiceEsquerdo, int indiceDireito)
{
    if(indiceEsquerdo < indiceDireito){
        //define o meio
        int meio = indiceEsquerdo + (indiceDireito - indiceEsquerdo)/2;

        //chama passando a primeira metada
        MergeSort(vetor, indiceEsquerdo, meio);

        //chama passando a segunda metade
        MergeSort(vetor, meio+1, indiceDireito);


        //une os dois sub arrays que foram criados
        Merge(vetor, indiceEsquerdo, meio, indiceDireito);
    }

}

//Junta os dois sub arrays criados com o vetor principal
void Ordenacoes::Merge(int* vetor, int indiceEsquerdo, int meio, int indiceDireito)
{
    int i,j,k; //contadores

    int n = meio - indiceEsquerdo + 1; //tamanho do primeiro vetor auxiliar
    int n2 = indiceDireito - meio;   //tamanho do segundo vetor auxiliar

    int* vetorEsquerdo;
    int* vetorDireito; //vetores temporarios

    //Passa os elementos da primeira metada para o vetor auxiliar
    for( i = 0; i < n; i++){
        vetorEsquerdo[i] = vetor[indiceEsquerdo+1];
    }
    //Passa os elementos da segunda metada para o vetor auxiliar
    for( j = 0; j<n2; j++){
        vetorDireito[j] = vetor[meio + 1 + j];
    }

    //reseta variaveis
    i = 0;
    j = 0;
    k = indiceEsquerdo;

    while(i < n && j < n2){

        //caso o valor na esquerda seja menor, passa o valor para o vetor principal
        if(vetorEsquerdo[i] < vetorDireito[j]){
            vetor[k] = vetorEsquerdo[i];
            //incrementa para passar para a proxima posi��o
            i++;
        } else {
            vetor[k] = vetorDireito[j];
            //incrementa para passar para a proxima posi��o
            j++;
        }
        k++;
    }

    //se faltarem elementos, passar para o vetor principal
    while( i < n) {
        vetor[k] = vetorEsquerdo[i];
        i++;
        k++;
    }

     //se faltarem elementos, passar para o vetor principal
    while( j < n2) {
        vetor[k] = vetorDireito[j];
        j++;
        k++;
    }

}

//Algoritmo de particionamento do vetor
//ENTRADA: Vetor de objetos do tipo Rating, posicao inicial e final deste vetor e indice da posicao onde o pivo sera posicionado
//SAIDA: Vetor Particionado
int Ordenacoes::particionaInt(int vet[], int inicio, int fim, int pos)
{
	int pospiv;
	int aux;
	/*
	Posicao do vetor, a formula para calcular a posiçao é (inicio + ((posicao)%(fim-inicio+1))). No caso, posicao = (inicio + fim) / 2), metade do vetor
	Exemplo, caso queira passar a posicao 3 do vetor como pivo int pospiv = inicio + (3 % (fim - inicio + 1));
	*/
	if (pos == -1) { //Pos com Codigo -1: Usa a posicao central do vetor como pivo
		pospiv = inicio + (((inicio + fim) / 2) % (fim - inicio + 1));
	}
	else { //Caso Contratio, utiliza a posicao passada por parametro
		pospiv = inicio + (pos % (fim - inicio + 1));
	}

	int pivo = vet[pospiv]; //Pega o userID da posicao que foi pedida e coloca ela como pivo
	aux = vet[pospiv];
	vet[pospiv] = vet[fim];
	vet[fim] = aux;
	pospiv = fim; //Volta a posicao do pivo como sendo o fim do vetor que vai ser particionado

	//Variaveis para percorrer no vetor particionado
	int i = inicio - 1; //Comeca antes do inicio pq na primeira troca ele ja vai virar o inicio
	int j = inicio; //Anda do comeco ate o fim-1 do vetor

	while (j <= fim - 1) //Ele nao vai ate o fim do vetor pois o ultimo elemento eh o pivo que foi jogado para o final no comeco da execucao
	{
		if ((vet[j] <= pivo) && ++numCompar)
		{
			i++;
			//troca(vet[i], vet[j]);
			aux = vet[i];
            vet[i] = vet[j];
            vet[j] = aux;
		}
		j++;
	}

	//troca(vet[i + 1], vet[pospiv]); //Coloca o elemento ja ordenado na ultima posicao do vetor particionado
	aux = vet[i + 1];
    vet[i + 1] = vet[pospiv];
    vet[pospiv] = aux;

	return i + 1;
}

//Algoritmo do quicksort recursivo
//ENTRADA: Vetor de objetos do tipo Rating, posicao inicial e final deste vetor e codigo "tipo" que indica o tipo de quicksort a ser realizado
//SAIDA: Vetor ordenado via QuickSort
//Tipo r: QuickSort Recursivo com Pivo Central
//Tipo m: QuickSort Recursivo com Pivo sendo a Mediana entre 3 valores aleatorios do vetor
//Tipo M: QuickSort Recursivo com Pivo sendo a Mediana entre 5 valores aleatorios do vetor
//Tipo i: QuickSort Recursivo utilizando InsertionSort para particoes de tamanho menor ou igual a 10
//Tipo I: QuickSort Recursivo utilizando InsertionSort para particoes de tamanho menor ou igual a 100
void Ordenacoes::quicksortInteiros(int vet[], int ini, int fim, char tipo)
{
	clock_t relogio;
	relogio = clock();
	if (tipo == 'r') { //QuickSort Recursivo Padrao
		if (ini < fim)
		{
			int part = particionaInt(vet, ini, fim, -1); //Codigo -1 em pos: Particao usando posicao central do vetor como pivo
			quicksortInteiros(vet, ini, part - 1, 'r');
			quicksortInteiros(vet, part + 1, fim, 'r');
		}
	}
	if (tipo == 'm') { //QuickSort Recursivo com Mediana de 3 valores
		if (ini < fim)
		{
			int posMediana = medianaInt(vet, 3, ini, fim); //posMediana recebe a posicao calculada na funcao Mediana com 3 valores
			int part = particionaInt(vet, ini, fim, posMediana);
			quicksortInteiros(vet, ini, part - 1, 'm');
			quicksortInteiros(vet, part + 1, fim, 'm');
		}
	}

	if (tipo == 'M') { //QuickSort Recursivo com Mediana de 5 valores
		if (ini < fim)
		{
			int posMediana = medianaInt(vet, 5, ini, fim); //posMediana recebe a posicao calculada na funcao Mediana com 5 valores
			int part = particionaInt(vet, ini, fim, posMediana);
			quicksortInteiros(vet, ini, part - 1, 'm');
			quicksortInteiros(vet, part + 1, fim, 'm');
		}
	}

	if (tipo == 'i') { //QuickSort Recursivo Hibrido (com Insertion para particoes de tamanho menor ou igual a 10)
		if (ini < fim)
		{
			if (fim - ini <= 10) {//Se a subparticao possuir tamanho menor ou igual a 10, ordena via InsertionSort
				Ordenacoes ordena;
				ordena.insertionsortInt(vet, ini, fim + 1);
				numCompar = numCompar + ordena.getNumComparacoes();
				numTrocas = numTrocas + ordena.getNumTrocas();
			}
			else {
				int part = particionaInt(vet, ini, fim, -1); //Codigo -1 em pos: Particao usando posicao central do vetor como pivo
				quicksortInteiros(vet, ini, part - 1, 'i');
				quicksortInteiros(vet, part + 1, fim, 'i');
			}
		}
	}

	if (tipo == 'I') { //QuickSort Recursivo Hibrido (com Insertion para particoes de tamanho menor ou igual a 100)
		if (ini < fim)
		{
			if (fim - ini <= 100) {//Se a subparticao possuir tamanho menor ou igual a 100, ordena via InsertionSort
				Ordenacoes ordena;
				ordena.insertionsortInt(vet, ini, fim + 1);
				numCompar = numCompar + ordena.getNumComparacoes();
				numTrocas = numTrocas + ordena.getNumTrocas();
			}
			else {
				int part = particionaInt(vet, ini, fim, -1); //Codigo -1 em pos: Particao usando posicao central do vetor como pivo
				quicksortInteiros(vet, ini, part - 1, 'I');
				quicksortInteiros(vet, part + 1, fim, 'I');
			}
		}
	}

	tempoGasto += (clock() - relogio) / (double)CLOCKS_PER_SEC;
}


//Funcao que calcula a mediana entre 3 e 5 valores aleatorios
//ENTRADA: Vetor de objetos do tipo Rating, numero de valores a serem tomados para o calculo da mediana, posicao inicial e final do vetor passado por parametro
//SAIDA: Retorna um inteiro que indica a posicao do vetor de Rating`s referente a mediana calculada, para ser usado como pivo do quicksort recursivo.
int Ordenacoes::medianaInt(int vet[], int numVal, int inicio, int fim) {

	int posMediana;//posicao a ser calculada e retornada da funcao
	int posRand;//Posicao Calculada Randomicamente
	if (numVal == 3) { //para k=3
		Rating** vetor = new Rating*[3];
		for (int i = 0; i < 3; i++) {
			srand(i);
			posRand = rand() % (fim - inicio); //Atribui a posicao randomica do vetor original
			vetor[i] = new Rating(vet[posRand], posRand, 0 , ""); //Atribui a MovieID a posicao em si, e em UserID o valor do UserID contido nesta posicao
		}
		Ordenacoes ordena;
		ordena.insertionsort(vetor, 0, 3);//utiliza o insertionSort para ordenar o UserID do vetor de 3 posicoes
		posMediana = vetor[1]->getMovieID();//pega o valor central do vetor (mediana) e atribui o movieID, que é a posicao original do vetor de Ratings
		return posMediana;
	}

	if (numVal == 5) { //para k=3
		Rating** vetor = new Rating*[5];
		for (int i = 0; i < 5; i++) {
			srand(i);
			posRand = rand() % (fim - inicio); //Atribui a posicao randomica do vetor original
			vetor[i] = new Rating(vet[posRand], posRand, 0 , ""); //Atribui a MovieID a posicao em si, e em UserID o valor do UserID contido nesta posicao
		}
		Ordenacoes ordena;
		ordena.insertionsort(vetor, 0, 5);//utiliza o insertionSort para ordenar o UserID do vetor de 3 posicoes
		posMediana = vetor[1]->getMovieID();//pega o valor central do vetor (mediana) e atribui o movieID, que é a posicao original do vetor de Ratings
		return posMediana;
	}
	return inicio; //caso nao entre em nenhuma condicao, passa a posicao inicial como valor

}
void Ordenacoes::shell_sort(int vetor[], int tam) {
  int i, j, atual;
  int h = 1;

  //de quanto em quanto sera o pulo entre analises
  while(h < tam){
    h = 3*h +1;
  }

  while(h > 1) {
    //reduz a distância entre as analises
    h = h/3;

    for(int i = h; i < tam; i++){
        atual = vetor[i];

        j = i - h;

        while((j>=0) && (atual < vetor[j])){
            vetor[j+h] = vetor[j];

            j = j - h;
        }

        vetor[j+h] = atual;
    }
  }
}
