#pragma once

#include <stdio.h>
#include "structs.h"
#include "global.h"

//Tworzy plik konfiguracyjny - weśli taki nie istnieje
void makeConfFile();

/**Wczytuje dane z pliku konfiguracyjnego
 **FILE *conf - wskaźnik na plik w trybue do odczytu
*/
void loadConfFile(FILE *conf);

/**Wypisuje Menu opcji
 **ev - event 
*/
void writeOptions(ALLEGRO_EVENT ev);

/**Wypisuje listę rankingową
 **ev - event
*/ 
void writeRanking(ALLEGRO_EVENT ev,struct rankList *ranking);

//Rysuje Menu
void drowMenu();

/**Pauzuje gre, wyświetla mozliwosć wyjścia/ kontyvuacji
 ** ev - event
*/
int gamePause(ALLEGRO_EVENT ev);

/**Wczytuje listę rankingową z pliku
 **Parametr rankFile - wskaźnik na wczytany plik
*/
void loadRanking(FILE *rankFile);

/**Dodaje wpis do listy rankingowej
 **ranking - wskaźnik na 1 element listy
 **name - imię gracza w rankingu
 **points - punkty
*/
struct rankList *rankAdd(struct rankList *ranking,char name[],int points);

/**Rysuje ekran końcowy 
 ** Prosi o podanie iemia, zapisuje wynik do listy rankingowe oraz do pliku
 ** tryb - rodzaj zakończenia:
 		0- przegrana
 		1- wybrana
 		2- poddano się
*/
int writeEnd(int tryb,ALLEGRO_EVENT ev,FILE *rankFile);

/**Zwalnia pamięć z listy rankingowej
*/
struct rankList *rankDestroy();

