#pragma once
#include <stdio.h>
#include "global.h"
#include "structs.h"
#include "menu.h"
#include "enemy.h"
//Znajdują się tu wszystkie funkcje skojarzone z statkiem gracza.

//Wczytyuje bitmapę statku
void loadCraft();

/**Poruszanie statku 
 * tryb =-1 - ruch w lewo
 * tryb = 1 - ruch w prawo
*/
void moveCraft(int tryb);

//Rysowanie statku
void drowCraft();

//Ustawianie początkowych wartości struktury statku
void setCraft();

//Regeneracja tarcz
void shieldReg();

//Ustawienie pocisków
/**
 * buttel - wskażnik do struktóry posicku
 * sizeMulti - przy ustawianiu wielkości pocisku wartość domyśla jest mnożona prze sizeMulti
 * speed - ustawienie prędkości pocisku 
*/
void setBullet(struct bulletStruct *bullet,int sizeMulti,int damage, int speed);

//Ustawianie opóźnenia strzału
void craftShootDelay();

//Rysuje na ekranie paski zycia i tarcz
void drowLife();

//Wczytyje bitmapę pocisku
/**
 * *allegroBitmap - wskaźnik za bitmapę
 * *bullet - wskaźnik na stróktórę odpowiadającą naszemu pociskowi
 * path[] - ścieżka dostępu do grafiki pocisku
 */
ALLEGRO_BITMAP *loadBullet(ALLEGRO_BITMAP *allegroBitmap, struct bulletStruct *bullet,char path[]);

//Wypisuje na ekran ilosć punktów zdobywanych podczas rozgrywki
void drowPoints();

//Tworzy bitmapę z paskami życia
int loadLifeBitmap();

//Rysuje na ekran pociski naszego statku
void drowBullets();

//Dodaje pocisk po wystrzale do listy
bulletStruct *addToBulletList(bulletStruct *listaRoot, int posX, int posY);

//Przesuwa pociski znajdujące się na liście
void moveBullets(int tryb);

//Usuwa pociski z  listy, jezliw wyleciały poza ekran
void removeBullets(int tryb);

//Odpowiada za strzał statku
void craftShoot();

/** Sprawdza ilość życia naszego statku
 ** żcie < 0 wyświetla ekran końcowy,
 ** wywołuje funkcję writeEnd z pliku menu.h
 ** ev - event
 ** rankfFile - wskaxnik na plik rankingowy
*/
int checkLife(ALLEGRO_EVENT ev,FILE *rankFile);

/**Sprawdza czy nasz statek został trafiony jakimś pociskiem
 ** this- wskaźnik na korzeń drzewa pocisów
*/
void destroyMyCraft(struct treeBulletStruct *this);