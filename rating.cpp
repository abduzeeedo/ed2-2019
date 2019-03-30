/*---------------------------------------
TRABALHO DE ESTRUTURA DE DADOS 2
GRUPO:
Bruno
Diogo
Fernanda
Thiago
--------------------------------------*/
#include "rating.h"


// Construtor sobrecarregado para poder utilizar dois tipos de inicialização
Rating::Rating()
{
}
//Construtor Padrao
Rating::Rating(int uid, int mid, double ra, string ts)
{
	userID = uid;
	movieID = mid;
	rating = ra;
	timeStamp = ts;
}
//Funcao que adiciona um tweet
void Rating::addRating(int uid, int mid, double ra, string ts)
{
	userID = uid;
	movieID = mid;
	rating = ra;
	timeStamp = ts;
}
//Retorna o User de um objeto
int Rating::getUserID()
{
	return userID;
}
//Atribui um UserID a um objeto
void Rating::setUserID(int uid) {
	userID = uid;
}
//Retorna o TweetID de um objeto
int Rating::getMovieID()
{
	return movieID;
}
//Atribui um TweetID a um objeto
void Rating::setMovieID(int mid) {
	movieID = mid;
}
//Retorna o Texto do Tweet de um objeto
double Rating::getRating()
{
	return rating;
}
//Atribui um Texto do Tweet a um objeto
void Rating::setRating(double ra) {
	rating = ra;
}
//Retorna a data do tweet de um objeto
string Rating::getTimeStamp()
{
	return timeStamp;
}
//Atribui uma data do tweet a um objeto
void Rating::setTimeStamp(string ts) {
	timeStamp = ts;
}
//Imprime Tweet em tela
void Rating::printRating() {
	cout << userID << " " << movieID << " " << rating << " " << timeStamp << endl << "\n";
}
//Destrutor
Rating::~Rating() {}
