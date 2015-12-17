#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include "lib/craft.h"
#include "lib/global.h"
#include "lib/structs.h"
#include "lib/menu.h"
#include "lib/other.h"
#include "lib/enemy.h"

int main(int argc, char **argv)
{
	bool redrow=false;
	FILE *conf;
	FILE *rankFile;
	ALLEGRO_EVENT ev;
	int enemyOnScreen=0;
	int killedEnemy=0;
	float newEnemyDelay=1;
	int killToNextLevelWeapon=8;
	int killToMoreEnemy=2;
	bool ifBreak=false;
	bool bossTime=false;
	bool bossOnScreen=false;
	srand(time(NULL));


	//*********************WCZYTYWANIE / TWORZENIE PLIKU KONFIGURACYJNEGO*******************
	conf=fopen(confFile,"r");
	if(!conf){
		makeConfFile();
		fclose(conf);
	}
	else{
		loadConfFile(conf);
		fclose(conf);
	}
	//*********************WCZYTYWANIE PLIKU RANKINGOWEGO***********************************
	rankFile=fopen(rankFileSrc,"r");
	if(rankFile) {
		loadRanking(rankFile);	
		fclose(rankFile);
	}

	//**************INSTALACJA ELEMNETÓW Z BIBLIOTEKI ALLEGRO*******************************
	//Inicjacja biblioteki allegro
	if(!al_init()) {
		fprintf(stderr, "Wystąpił błąd podczas wczytywania biblioteki allegro\n");
  		return -1;
	}
	if(!al_init_image_addon()) {
  		fprintf(stderr,"Wystąpił błąd!!!\n");	
		return -1;
   	}
	//Instalacja klawiatury
	if(!al_install_keyboard()) {
  		fprintf(stderr, "Wystąpił błąd podczas próby inicjacji klawiatury!\n");
  		return -1;
   	}
	//Instalacja myszy
	if(!al_install_mouse()) {
  		fprintf(stderr, "Wystąpił błąd podczas inicjacji myszy\n");
  		return -1;
   	}
   	//Instalacja czcionek
   	al_init_font_addon();
   	al_init_ttf_addon();
	//Inicjacja timera
	timer = al_create_timer(1.0 / FPS);
	if(!timer){
		fprintf(stderr,"Wystąpił błąd podczas inicjacji zegara\n");
		return -1;
	}
	//Tworzenie kolejki eventów
	eventQueue = al_create_event_queue();
   	if(!eventQueue) {
  		fprintf(stderr, "Błąd podczas tworzenia kolejki eventów\n");
  		return -1;
   	}
   	//Wczytanie czcionki
   	font = al_load_ttf_font(fontSrc1,16,0 );
   	if(!font){
   		fprintf(stderr,"Wystąpił błąd podczas wczytywania czcionki\n");
   		return -1;
   	}
   	font2 = al_load_ttf_font(fontSrc1,32,0 );
   	if(!font2){
   		fprintf(stderr,"Wystąpił błąd podczas wczytywania czcionki\n");
   		return -1;
   	}
   	font3 = al_load_ttf_font(fontSrc2,32,0 );
   	if(!font2){
   		fprintf(stderr,"Wystąpił błąd podczas wczytywania czcionki\n");
   		return -1;
   	}
   	//Tworzenie ekranu głównego
   	mainDisplay = al_create_display(520, 520);
	if(!mainDisplay) {
  		fprintf(stderr, "Wystąpił bląd podczas próby utworzenia okna\n");
  		return -1;
   	}
   	if(!al_install_audio()){
      fprintf(stderr, "failed to initialize audio!\n");
      return -1;
    }
 
    if(!al_init_acodec_addon()){
      fprintf(stderr, "failed to initialize audio codecs!\n");
      return -1;
    }
 
    if (!al_reserve_samples(1)){
      fprintf(stderr, "failed to reserve samples!\n");
      return -1;
    }


	//Rejestracja ekranu w kolejce eventów
	al_register_event_source(eventQueue, al_get_display_event_source(mainDisplay));
	//Rejestracja timera w kolejce
	al_register_event_source(eventQueue, al_get_timer_event_source(timer));
	//Rejestracja klawiatury
	al_register_event_source(eventQueue, al_get_keyboard_event_source());
	//Rejestracja myszy
	al_register_event_source(eventQueue, al_get_mouse_event_source());
	//Włączenie timera
	al_start_timer(timer);
	//Zaczernienie ekranu
	al_clear_to_color(al_map_rgb(0,0,0));
	al_draw_text(font, al_map_rgb(204, 204, 204), 260, 240,ALLEGRO_ALIGN_CENTRE, "LOADING ...");
 	//Wyświetlanie buffora ekranu
  	al_flip_display();

  	//*****************************USTAWIANIE POCZĄTKOWYCH WARTOŚCI***************************************************
  	setBackground(&mainBackgroundBitmap,backgroundPath,1);		//Ustawienie tła
	setBackground(&secondBackgroundBitmap,backgroundPath2,1.6);	//Ustawienie tła
	setBackground(&thirdBackgroundBitmap,backgroundPath3,2.5);	//Ustawienie tła
	setCraft();			//Ustawianie statku
	setBullet(&myBullet,1,myCraft.damage,(int)myCraft.bulletSpeed);
	loadCraft();
	loadLifeBitmap();
	//******************************WCZYTYWANIE NIEKTÓRYCH BITMAP*****************************************************
	menu=al_load_bitmap(menuBackground);										//TŁO MENU 1
  	menu2=al_load_bitmap(menuBackground2);										//TLO MENU 2
  	mainBackground=loadBackground(&mainBackgroundBitmap,mainBackground);		//Wczytywanie tła
   	secondBackground=loadBackground(&secondBackgroundBitmap,secondBackground);	//Wczytywanie 2 tła
   	thirdBackground=loadBackground(&thirdBackgroundBitmap,thirdBackground);		//Wczytywanie 2 tła
   	craftBullet=loadBullet(craftBullet,&myBullet,craftBulletImage);
   	//****************************WCZYTYWANIE BITMAP PRZECIWNIKOW*******************************************************
   	EnemyCrafts[0]=loadEnemy(EnemyCrafts[0],0,enemyImage1,enemyBulletImage);
   	EnemyCrafts[1]=loadEnemy(EnemyCrafts[1],1,enemyImage2,enemyBulletImage);
   	EnemyCrafts[2]=loadEnemy(EnemyCrafts[2],2,enemyImage3,enemyBulletImage);
   	EnemyCrafts[3]=loadEnemy(EnemyCrafts[3],3,enemyImage4,enemyBulletImage);
   	EnemyCrafts[4]=loadEnemy(EnemyCrafts[4],4,bossImage,bossBulletImage);
   	menuMusic=al_load_sample(menuMusicPath);
   	gameMusic=al_load_sample(gameMusicPath);
   	gameMusicInstance=al_create_sample_instance(gameMusic);
   	al_set_sample_instance_playmode(gameMusicInstance,ALLEGRO_PLAYMODE_LOOP);
   	al_attach_sample_instance_to_mixer(gameMusicInstance,al_get_default_mixer());
   	al_set_sample_instance_gain(gameMusicInstance,0.7);
   	explosive=al_load_sample(explosivePath);



//Pętla w której toczy się cała gra - menu - rozgrywka - menu - rozgrywka itd
while(1){
  	//********************************PĘTLA MENU***********************************************************************
   	if (music) al_play_sample(menuMusic, 0.5, 0.0,1.0,ALLEGRO_PLAYMODE_LOOP,NULL);
   	al_resize_display(mainDisplay,520,520);
   	al_clear_to_color(al_map_rgb(0,0,0));
	al_draw_text(font, al_map_rgb(204, 204, 204), 260, 240,ALLEGRO_ALIGN_CENTRE, "LOADING ...");
   	al_flip_display();
  	al_show_mouse_cursor(mainDisplay);
  	al_rest(0.5);
  	drowMenu();
  	while(1){
  		al_wait_for_event(eventQueue, &ev);
  		if(ev.type == ALLEGRO_EVENT_TIMER){
  		}
  		else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
     		return 0;
  		}
  		else if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){
  			if( (ev.mouse.x>145) && (ev.mouse.x<380) ){
	  			if( (ev.mouse.y>135) && (ev.mouse.y<182) )	break;
	  			if( (ev.mouse.y>200) && (ev.mouse.y<250) )	writeOptions(ev);
	  			if( (ev.mouse.y>272) && (ev.mouse.y<322) )	writeRanking(ev,ranking);
	  			if( (ev.mouse.y>343) && (ev.mouse.y<392) )	{
	  				destroyAllegroData();
	  				return 0;
	  			}
	  		}
  		}
  		else if(ev.type == ALLEGRO_EVENT_MOUSE_AXES){
  			al_set_system_mouse_cursor(mainDisplay,ALLEGRO_SYSTEM_MOUSE_CURSOR_DEFAULT);
  			if( (ev.mouse.x>145) && (ev.mouse.x<380) ){
	  			if( (ev.mouse.y>135) && (ev.mouse.y<182) )	al_set_system_mouse_cursor(mainDisplay,ALLEGRO_SYSTEM_MOUSE_CURSOR_LINK);
	  			if( (ev.mouse.y>200) && (ev.mouse.y<250) )	al_set_system_mouse_cursor(mainDisplay,ALLEGRO_SYSTEM_MOUSE_CURSOR_LINK);
	  			if( (ev.mouse.y>272) && (ev.mouse.y<322) )	al_set_system_mouse_cursor(mainDisplay,ALLEGRO_SYSTEM_MOUSE_CURSOR_LINK);
	  			if( (ev.mouse.y>343) && (ev.mouse.y<392) )	al_set_system_mouse_cursor(mainDisplay,ALLEGRO_SYSTEM_MOUSE_CURSOR_LINK);
	  		}
  		}
  	}
  	al_hide_mouse_cursor(mainDisplay);
  	al_resize_display(mainDisplay,mainDisplayWidth,mainDisplayHeight);
  	//*****************************************************************************************************

	//*************************************GŁÓWNA PĘTLA GRY********************************
	if(music){
		al_stop_samples();
		al_play_sample_instance(gameMusicInstance);
	}
	setEnemy();
	ifBreak=false;
	bossTime=false;

	while(1){
		if( ifBreak==true ) break;
      	al_wait_for_event(eventQueue, &ev);
      	//****************************Timer event**********************************************************
      	switch (ev.type){
      		case ALLEGRO_EVENT_TIMER:
      			if(key[KEY_ESC]) {
					if(gamePause(ev)==-1) if(writeEnd(2,ev,rankFile)==-1) ifBreak=true;
				}
				if(key[KEY_LEFT]) moveCraft(-1);
	     		if(key[KEY_RIGHT]) moveCraft(1);
	     		if(key[KEY_CTRL]) craftShoot();
      			craftShootDelay();
      			moveBullets(1);
	     		removeBullets(1);
	     		shieldReg();
	     		enemyShootDelay();
	      		EnemyShoot();
	      		enemyOnPlace();
	     		moveEnemy();
	     		ifEnemyShoot();
	     		if (bossTime==false){	
		     		if (enemyOnScreen<numberOfEnemy && newEnemyDelay>=1){
		     			addEnemy();
		     			enemyOnScreen++;
		     			newEnemyDelay=0.5;
		     		}
		     		else{
		     			if(newEnemyDelay<1) newEnemyDelay+=1/FPS;
		     		}
		     		if(killedEnemy>killToNextLevelWeapon){
		     			killToNextLevelWeapon*=2;
		     			myCraft.bulletSpeed+=1/FPS*160*mainDisplayHeight/700;
		     			myCraft.shootSpeed+=1.6/FPS;
		     			if(myCraft.weaponLevel<5) myCraft.weaponLevel+=1;
		     		}
		     	}
	     		al_clear_to_color(al_map_rgb(0, 0, 0));
				rysujTlo(&mainBackgroundBitmap,mainBackground);
				rysujTlo(&secondBackgroundBitmap,secondBackground);
				rysujTlo(&thirdBackgroundBitmap,thirdBackground);
				drowLife();
				drowCraft();
				drowEnemies();
				drowBullets();
				drowEnemyBulletsReq(TreeBullet);
				drowPoints();
				removeDead(&enemyOnScreen,&killedEnemy,&newEnemyDelay,&killToMoreEnemy);
				if (killedEnemy>100) bossTime=true;
				if (bossTime && !bossOnScreen && enemyOnScreen==0){
					bossOnScreen=true;
				 	addBoss(50,-200,mainDisplayWidth-EnemyCrafts[4].sizeX-10,30);
				}
				if(bossTime && bossOnScreen){
					checkBossLife(&bossTime,&bossOnScreen,&killedEnemy,&numberOfEnemy,&killToMoreEnemy);
					drowBossLife();
					
				}
				if(checkLife(ev,rankFile)==-1) ifBreak=true;
				redrow=true;
      		break;
      		
      	    case ALLEGRO_EVENT_DISPLAY_CLOSE:
      			break;
      		break;
      		case ALLEGRO_EVENT_KEY_DOWN:
  				switch(ev.keyboard.keycode) {
	    			case ALLEGRO_KEY_LEFT: 
	       				key[KEY_LEFT] = true;
	       			break;

	    			case ALLEGRO_KEY_RIGHT:
	       				key[KEY_RIGHT] = true;
	       			break;

	       			case ALLEGRO_KEY_SPACE:
	       				key[KEY_CTRL] = true;
	       			break;

	       			case ALLEGRO_KEY_ESCAPE:
	       				key[KEY_ESC] = true;
	       			break;
 				}
      		break;
      		case ALLEGRO_EVENT_KEY_UP:
	         	switch(ev.keyboard.keycode) {
	            	case ALLEGRO_KEY_LEFT: 
	               		key[KEY_LEFT] = false;
	               	break;
	 
	            	case ALLEGRO_KEY_RIGHT:
	               		key[KEY_RIGHT] = false;
	               	break;

	                case ALLEGRO_KEY_SPACE:
	       			 	key[KEY_CTRL] = false;
	       			break;

	       			case ALLEGRO_KEY_ESCAPE:
	       				key[KEY_ESC] = false;
	       			break;
	       		}
         	break;
      	}
      	if(redrow && al_is_event_queue_empty(eventQueue)) {
			al_flip_display();
			redrow=false;
      	}
	}
	//*****************ZWALNIANIE ZBEDNYCH ZASOBÓW TYPU PRZECIWNICY POCISKI ITP***************************
	destroyALLData();
	resetGame(
		&enemyOnScreen,
		&killedEnemy,
		&killToNextLevelWeapon,
		&killToMoreEnemy,
		&bossTime,
		&bossOnScreen
	);
	al_stop_samples();
	al_stop_sample_instance(gameMusicInstance);
	puts("ZWOLNIONO ZBĘDNE ZASOBY");
	//****************************************************************************************************

}
	//************************************ZWALNIANIE RESZTY ZASOBÓW (ekran itp)************************
	destroyAllegroData();
   	//*****************************************************************************************************

    return 0;
}


