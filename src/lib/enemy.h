#pragma once
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <math.h>
#include <stdio.h>
#include "global.h"
#include "structs.h"
#include "craft.h"

//Ustawia wartości początkowe przeciwników
int setEnemy();

/** Wczytuje przeciwników i zwrac jego strukturę
 ** enemy - struktura przeciwnika
 ** number - numer rodzaju przeciwnikw <0;4>
 ** path - ściezka dostępu do grafiki prsecika
 ** bulletPath - ścieżka grafiki pociesku przeciwnika
*/
struct enemyCraftStruct loadEnemy(struct enemyCraftStruct enemy,int number, char *path, char *bulletPath);

/** dodaje orzeciwnika do listy przeciwników
 ** rodzaj - numer rodzaju orzecnika <0;4>
 ** posX - pozycja startowa przeciwnika
 ** posY - pozycja startowa przeciwnika
 ** toGoX - pozycja do której dąży przeciwnik
 ** toGoY - pozycja do której daży przeciwnik
*/
void addToEnemyList(int rodzaj,int posX,int posY,int toGoX,int toGoY);

//Dodaje przecinika (losuje wartości i wywołuje dodanie do listy)
void addEnemy();

/** Dodaje przecinika - boss'a
 ** posX - pozycja startowa przediniwka
 ** posY - pozycja startowa przecinika
 ** toGoX - pozycja do której dązy boss
 ** toGoY - pozycja do której daży boss
*/
void addBoss(int posX,int posY, int toGoX, int toGoY);

//Sprawdza czy przeciwnicy dotarli do swojego celu, jesli tak losuje kolejne miejsce
void enemyOnPlace();

//Rysuje przeciwników na ekranie
void drowEnemies();

/**Usuwa przeciników z listy przeciników
 ** tmp - wskaźnik na przecinika
*/
struct listOfEnemyStruct *removeEnemy(struct listOfEnemyStruct *tmp);

/** Usuwa przeciników gdy life<0
 ** Dokonuje modyfikacji niektorych zmiennych
 ** enemyOnScreen - ilość przeciwników na ekranie
 ** killedEnemy - ilość zabittych przeciniów
 ** newEnemyDelay - czas do pojawienia się kolejnego przecinika
 ** killToMoreEnemy - ilosć przeciników które nalezy zabić, aby pojawiło się więcej na ekranie
*/
void removeDead(int *enemyOnScreen, int *killedEnemy, float *newEnemyDelay,int *killToMoreEnemy);

//Odejmuje zycie trafionym przeciwnikom
void ifEnemyShoot();

//Regeneruje czas strzału przecinika
void enemyShootDelay();

//Odpowiada za strzał przecinika
void EnemyShoot();

//Porusza przecinikami
void moveEnemy();

/** Dodaje pocisk do drzewa pocisków
 ** root - wskaźnik na korzeń drzewa
 ** posX - pozycja X pocisku
 ** posY - pozycja Y pocisku
 ** numberOfEnemy - numer rodzaju przecinika
*/
struct treeBulletStruct *addToBulletTree(struct treeBulletStruct *root,int posX, int posY, int numberOfEnemy);

/**REKURENCYJNA funkcja dodająca przecinika do drzewa pocisków (BST)
 ** this - wskaźnik na element drzewa na którym obecnie jestśmy
 ** new - wskaxnik na nowy element
*/
void addToBulletTreeReq(struct treeBulletStruct *this, struct treeBulletStruct *new);

/** Niszczy drzewo pocisków
 ** this - wskaxnik na korzeń dzrzewa
*/
struct treeBulletStruct *freeBulletMemory(struct treeBulletStruct *this);

/** Usuwa dany element z dzrewa
 ** this - wskaźnik na usuwany element
*/
void usunZDrzewa(struct treeBulletStruct *this);

//LRP - LEWY / RODZIC / PRAWY
//Rysuje pociski, przesuwa je i usuwa te, które wyleciały poza obszar
//Sprawdza czy nasz statek został trafiony jakimś pociskiem
void drowEnemyBulletsReq(struct treeBulletStruct *this);

/** Sprawdza czy boss nie żyje
 ** Jeśli tak dokonuje modyfikacji kilku zmiennych
 ** bossTime - czy jest czas Bossa
 ** bossOnScreen - czy boss znajduje się na ekranie
 ** killedEnemy - ilość zabitych przecików
 ** numberOfEnemy - max ilość przeciników na ekranie
 ** killToMoreEnemy - ilość p. do zabicia do pojawienia się kolejnego na ekranie
*/
void checkBossLife(bool *bossTime, bool *bossOnScreen, int *killedEnemy, int *numberOfEnemy, int *killToMoreEnemy);

//Rysuje pasek życia bossa
void drowBossLife();