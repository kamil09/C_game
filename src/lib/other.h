#pragma once
#include <stdio.h>
#include "global.h"
#include "structs.h"
#include "craft.h"
#include "enemy.h"

/**Ustawia wartoiści początkowe tła
 ** bitmap - struktura tła
 ** sciezkaTla - sciezkja dostępu do tła 
 ** moreSpeed - mnoznik czy tło ma się poruszać szybciej
*/
void setBackground(struct mainBackgroundStruct * bitmap, char sciezkaTla[], float moreSpeed);

/** Wczytywanie bitmapy rła
 ** bitmap - struktura tła
 ** allegroBitmap - wskaźnil na bitmapę allegro
*/
ALLEGRO_BITMAP *loadBackground(struct mainBackgroundStruct * bitmap, ALLEGRO_BITMAP *allegroBitmap);

/** Rysuje tło
 ** bitmap - struktura tła
 ** allegroBitmap - wskaźnik na bitmapę allegro
*/
void rysujTlo(struct mainBackgroundStruct * bitmap, ALLEGRO_BITMAP *allegroBitmap);

/**
**	Usuwa/zwalnia pamięć:
**	---	Listę naszych pocisków
**	---	Listę przeciwników
**	---	Drzewko pocisków przeciwników
*/
void destroyALLData();

//Resetje ustawienia gry
void resetGame(
 	int *enemyOnScreen,
	int *killedEnemy,
	int *killToNextLevelWeapon,
	int *killToMoreEnemy,
	bool *bossTime,
	bool *bossOnScreen
	);

//Zwalnia pamięć z danych ALLEGRO
void destroyAllegroData();