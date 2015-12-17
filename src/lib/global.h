#pragma once

#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

//PLIK ZAWIERA DEKLARACJĘ WSZYSTKICH ZMIENNYCH GLOBALNYCH

//USTAWIENIA - MOŻNA JE ZMIENIĆ W OKNIE USTAWIEN, ZNAJDUJĄ SIĘ W PLIKU KONFIGURACYJNYM.
//Podane tu wartości są defaultowe - pierwsze uruchomienie lub brak pliku konfiguracyjnego
extern float FPS;					//Ilosc klatek na sekunde
extern int mainDisplayWidth;		//Szerokość okna
extern int mainDisplayHeight;		//Wysokość oknach
extern int sound;					//Czy włączyć dźwięki (wystrzał, zniszczenie statku)
extern int music;					//Czy włączyć muzykę 
extern char confFile[30];			//Sciezka pliku konfiguracyjnegi
extern char rankFileSrc[30];		//ściezka do pliku z rankingiuem			
extern char backgroundPath[30];		//Ścieżki do obrazów tła
extern char backgroundPath2[30];
extern char backgroundPath3[30];
extern char craftImage[30];			//Ścieżka obrazu statku
extern char craftBulletImage[30];	//ścieżki obrazów pocisków
extern char enemyBulletImage[30];
extern char fontSrc1[30];				//Ścieżka do czcionki
extern char fontSrc2[30];
extern char menuBackground[30];		//Ścieżka do tła menu
extern char menuBackground2[30];		//Ścieżka do tła menu
extern char carbonBackground[30];	//Ściezka do tła (pauzowanie gry)
extern int numberOfEnemy;			//Liczba przeciwników na mapie
extern char enemyImage1[30];		//Ścieżki dostepu do obrazów przeciwników
extern char enemyImage2[30];
extern char enemyImage3[30];
extern char enemyImage4[30];
extern char craftShieldPath[30];	//Ścieżka do obrazu tarczy statku
extern char craftLifePath[30];		//Sciezka do obrazu, który pojawia się gdy zosaniemy trafieni a tarcze<=0
extern char bossImage[30];			//Obraz bossa
extern char bossBulletImage[30];	//Obraz pociskóœ bossa
extern char menuMusicPath[30];		//Ściezka do Muzyki menu
extern char gameMusicPath[30];		//Ścieżka do muzyki gry
extern char explosivePath[30];		//Ściezka do odgłosu eksplozji

enum KEYS{							
	KEY_LEFT, KEY_RIGHT, KEY_CTRL, KEY_ESC, KEY_SPACE
};
extern enum KEYS key[5];			//Przechowuje informację o naciśniętym klawiszu

//ZMIENNE ALLEGRO:
extern ALLEGRO_SAMPLE *menuMusic;			//Muzyka menu
extern ALLEGRO_SAMPLE *gameMusic;			//Muzyka gry
extern ALLEGRO_SAMPLE_INSTANCE *gameMusicInstance;	//Muzyka gry
extern ALLEGRO_SAMPLE *explosive;			//Odgłos eksplozji
extern ALLEGRO_DISPLAY *mainDisplay;		//Główny ekran
extern ALLEGRO_FONT *font;					//Czcionka
extern ALLEGRO_FONT *font2;	
extern ALLEGRO_FONT *font3;
extern ALLEGRO_TIMER *timer;				//timer
extern ALLEGRO_EVENT_QUEUE *eventQueue;		//Kolejka eventów
extern ALLEGRO_BITMAP *menu;				//Tło menu
extern ALLEGRO_BITMAP *menu2;	
extern ALLEGRO_BITMAP *mainBackground;		//Główne tło
extern ALLEGRO_BITMAP *secondBackground;	//2 Tło
extern ALLEGRO_BITMAP *thirdBackground;
extern ALLEGRO_BITMAP *lifeBitmap;			//Bitmapa pasków życia, tarcz
extern ALLEGRO_BITMAP *craft;				//Obraz naszego statku
extern ALLEGRO_BITMAP *craftBullet;			//Obrazy pocisków
extern ALLEGRO_BITMAP *craftShieldImg;		//Obrazki wyswietlające się, gdy nasz statek zostanie trafiony
extern ALLEGRO_BITMAP *craftLifeImg;		