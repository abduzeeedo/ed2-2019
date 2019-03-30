/*---------------------------------------
TRABALHO DE ESTRUTURA DE DADOS 2
GRUPO:
Bruno 
Diogo
Fernanda
Thiago
--------------------------------------*/
#ifndef RATING_H
#define RATING_H

#include <string>
#include <stdlib.h>
#include <iostream>

using namespace std;

class Rating
{
private:
	int userID;//ID do usuario
	int movieID;//ID do filme
	double rating; //valor do rating
	string timeStamp; //data e hora da pergunta
public:
	Rating();//Construtor Sobrecarregado
	Rating(int uid, int mid, double ra, string ts);//Construtor Padrao, com todas as variaveis
	void addRating(int uid, int mid, double ra, string ts);//Funcao que atribui dados a um objeto
	int getUserID();//Retorna o ID do usuario de um objeto
	int getMovieID();//Retorna o ID do filme de um objeto
	double getRating(); //Retorna o Rating de um objeto
	string getTimeStamp();//Retorna a Data e Hora do timeStamp de um objeto
	void setUserID(int uid);//Atribui um ID de usuario a um objeto
	void setMovieID(int mid);//Atribui um ID de filme a um objeto
	void setRating(double ra); //Atribui um Rating a um objeto
	void setTimeStamp(string ts);//Atribui a Data e Hora a um objeto
	void printRating();//Imprime os dados de um rating na tela
	~Rating();//Destrutor
};

#endif // TWEETS_H
