#pragma once
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

//PLIK ZAWIEFA DEKLARACJE WSZYSTKICH STRUKTUR WYKORZYSTYWANYCH W GRZE

//Struktura tła
struct mainBackgroundStruct{
	int defaultSizeX;			//Szerokość wczytanego obrazu
	int defaultSizeY;			//Wysokość wczytanego obrazu
	int sizeX;					//Szerokość tła (okna)
	int sizeY;					//Wysokość tła (okna)
	int posX;					//Pozycja X tła
	int posY;					//Pozycja Y tła
	char path[100];				//Ścieżka dostępu do grafiki tła
	float speed;				//prędkowśc poruszznia sie tla
};
extern struct mainBackgroundStruct mainBackgroundBitmap;	//Deklaracja zmiennej tła
extern struct mainBackgroundStruct secondBackgroundBitmap;	//Deklaracja zmiennej 2 tła
extern struct mainBackgroundStruct thirdBackgroundBitmap;	//Deklaracja zmiennej 3 tła

//Struktura naszego statku
struct myCraftStruct{
	int defaultSizeX;	//Szerokość Bitmapy
	int defaultSizeY;	//Wysokość Bitmapy
	int sizeX;			//Szerokość Statku
	int sizeY;			//Wysokość Statku
	int posX;			//Pozycja X statku
	int posY;			//Pozycja Y statku
	int speed;			//Prędkość statku
	float shootSpeed;	//prędkość strzelania
	int bulletSpeed;	//Prędkość lotu pocisku
	char path[100];		//Ścieżka do grafiki statku
	int damage;			//Siła ognia
	float shield;			//Punkty tarcz
	bool shieldReg;		//Regeneracja tarczy - gdy 0 tarcze się nie odnawiają.
	int life;			//Punkty życia
	float shootDelay;	//Gdy < 1 nie można wykonać strzału, po strzale jest zerowane
	int weaponLevel;	//Rodzaj broni od 1-5 zależy od tego ilość pocisków w jednym strzale
	float points;			//Ilość punktow zdobytych podczas rozgrywki
};
extern struct myCraftStruct myCraft;	//Deklaracja zmiennej z naszym statkiem

struct enemyCraftStruct{
	int defaultSizeX;	//Szerokosc Bitmapy
	int defaultSizeY;	//Wysokosc bitmapy
	int sizeX;			//Szerokosc statku
	int sizeY;			//Wysokosc Statku
	int speed;			//Prędkosc statku
	float shootSpeed;	//prędkość strzelania
	int bulletSpeed;	//Prędkość lotu pocisku
	char *path;		//Ścieżka do grafiki statku
	int damage;			//Siła ognia
	int life;			//Punkty życia
	float shootDelay;	//Gdy < 1 nie można wykonać strzału, po strzale jest zerowane
	int weaponLevel;	//Rodzaj broni od 1-5 zależy od tego ilość pocisków w jednym strzale
	ALLEGRO_BITMAP *enemyCraft;			//Bitmapa statku przecoiwnika
	ALLEGRO_BITMAP *enemyBulletImage;	//Bitmapa pocisku przeciwnika
	int bullDefaultSizeX;				//Rozmiar bitmapy pocisku przecinika
	int bullDefaultSizeY;
	int bullSizeX;						//Rozmiar pocisku przeciwnika
	int bullSizeY;			
};
extern struct enemyCraftStruct EnemyCrafts[5];	//Deklaracja tablicy przeciwników nr 5 - BOSS!!!!!!!!!!!!!!!!!!!!!

//Struktura listy przeciników
struct listOfEnemyStruct{
	int posX;						//pozycja x przecinika				
	int posY;						//pozcycja Y przecika
	int goToX;						//Cel X przecikia
	int goToY;						// Cell Y przeciwnika
	int numberOfEnemy;				//numer rodzaju przeciwnika
	float shootDelay;				//Czy można strzalić
	int life;						//Życie przecinika
	struct listOfEnemyStruct *next;	//Wskaxnik na następny element
	struct listOfEnemyStruct *prev; //Wskaxnik na poprzedni elemnt
};
extern struct listOfEnemyStruct *listOfEnemy;	//Deklaracja wskaxnika na 1 elemnt listy

//Struktura pocisku pozucje pocisków przecowywane są w liście pocisków
struct bulletStruct{
	int damage;			//Obrażenia
	int speed;			//Prędkość pocisku
	int sizeX;			//Szerokość pocisku				
	int sizeY;			//Wysokość pocisku
	int defaultSizeX; 	//Szerokosc bitmapy
	int defaultSizeY; 	//Wysokosc bitmapy
};
extern struct bulletStruct myBullet;	

//Lista pocisków naszego statku
typedef struct bulletListStruct{
	int posX;						//Pozycja X pocieku
	int posY;						//Pozycja Y pocisku
	struct bulletListStruct *next;	//wskaxnik na następny element pocisku

} bulletStruct;
extern bulletStruct *myCraftBullets;	//Deklaracja wskaxnika na 1 element listy pocisów

//Lista rankingowa
struct rankList{
	char name[40];			//Nazwa gracza		
	int points;				//Punkty gracza
	struct rankList *next;	//Wskaxnik ana następny element listy
};
extern struct rankList *ranking; 

//Drzewko pocisków przeciników
struct treeBulletStruct{
	int *numberOfEnemy;				//Rodzaj przecinika
	int *posX;						//Pozycja X pocisku
	int *posY;						//pozycja Y pocisku
	float *alfa;					//kąt strzału (wykorzystywany tylko przy bossie)
	struct treeBulletStruct *left;	//Wskaxnik na lewe dziecko
	struct treeBulletStruct *right; //Wskaxnik na prawe dziecko
	struct treeBulletStruct *parent;//Wskaxnik na rodzica
};
extern struct treeBulletStruct *TreeBullet;
