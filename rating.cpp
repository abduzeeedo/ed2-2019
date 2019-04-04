/*---------------------------------------
TRABALHO DE ESTRUTURA DE DADOS 2
GRUPO:
Bruno
Diogo
Fernanda
Thiago
--------------------------------------*/
#include "rating.h"



// Construtor sobrecarregado para poder utilizar dois tipos de inicializa��o
Rating::Rating()
{
}
//Construtor Padrao
Rating::Rating(int uid, int mid, float ra, string ts)
{
	userID = uid;
	movieID = mid;
	rating = ra;
	timeStamp = ts;
}
//Funcao que adiciona um rating
void Rating::addRating(int uid, int mid, float ra, string ts)
{
	userID = uid;
	movieID = mid;
	rating = ra;
	timeStamp = ts;
}
//Retorna o UserID de um objeto
int Rating::getUserID()
{
	return userID;
}
//Atribui um UserID a um objeto
void Rating::setUserID(int uid) {
	userID = uid;
}
//Retorna o ID de filme de um objeto
int Rating::getMovieID()
{
	return movieID;
}
//Atribui um ID de filme a um objeto
void Rating::setMovieID(int mid) {
	movieID = mid;
}
//Retorna o Rating do filme de um objeto
float Rating::getRating()
{
	return rating;
}
//Atribui um Rating do filme a um objeto
void Rating::setRating(float ra) {
	rating = ra;
}
//Retorna o timeStamp de um objeto
string Rating::getTimeStamp()
{
	return timeStamp;
}
//Atribui um timeStamp a um objeto
void Rating::setTimeStamp(string ts) {
	timeStamp = ts;
}
//Imprime Rating em tela
void Rating::printRating() {
	cout << "UserID:" << userID << " MovieID:" << movieID << " Rating:" << rating << " TimeStamp:" << timeStamp << endl << "\n";
}
//Destrutor
Rating::~Rating() {}
