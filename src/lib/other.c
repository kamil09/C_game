#include "other.h"

//Ustawia tło : wartości początkowe, ścieżkę do pliku prędkość
void setBackground(struct mainBackgroundStruct * bitmap, char sciezkaTla[], float moreSpeed){				
	bitmap->defaultSizeX=0;
	bitmap->defaultSizeY=0;
	bitmap->sizeX=0;
	bitmap->sizeY=0;
	bitmap->posX=0;
	bitmap->posY=0;
	sprintf(bitmap->path,"%s",sciezkaTla);
	bitmap->speed=1/FPS*180*moreSpeed*mainDisplayHeight/700;
}
ALLEGRO_BITMAP *loadBackground(struct mainBackgroundStruct * bitmap, ALLEGRO_BITMAP *allegroBitmap){
	allegroBitmap = al_load_bitmap(bitmap->path);
    if (!allegroBitmap ){
    	fprintf(stderr, "Błąd podczas wczytywania grafiki\n");
        return 0;
    }
	bitmap->defaultSizeX=al_get_bitmap_width(allegroBitmap);
	bitmap->defaultSizeY=al_get_bitmap_height(allegroBitmap);
	bitmap->sizeX=mainDisplayWidth;
	bitmap->sizeY=mainDisplayHeight*4.5;
	bitmap->posY=mainDisplayHeight*(-3.5);
	return allegroBitmap;
}
void rysujTlo(struct mainBackgroundStruct * bitmap, ALLEGRO_BITMAP *allegroBitmap){
	bitmap->posY+=(int)bitmap->speed;
	if (bitmap->posY>=0) 
      	al_draw_scaled_bitmap(allegroBitmap,0,0,bitmap->defaultSizeX,bitmap->defaultSizeY,bitmap->posX,(-bitmap->sizeY)+bitmap->posY,bitmap->sizeX,bitmap->sizeY,0);
    if (bitmap->posY>=mainDisplayHeight) {
		bitmap->posY=mainDisplayHeight*(-3.5)+(bitmap->posY-mainDisplayHeight)+1;
	}
	al_draw_scaled_bitmap(allegroBitmap,0,0,bitmap->defaultSizeX,bitmap->defaultSizeY,bitmap->posX,bitmap->posY,bitmap->sizeX,bitmap->sizeY,0);
}

/**
**	Usuwa/zwalnia pamięć:
**	---	Listę naszych pocisków
**	---	Listę przeciwników
**	---	Drzewko pocisków przeciwników
*/
void destroyALLData(){
	while(TreeBullet) usunZDrzewa(TreeBullet);
	while(listOfEnemy) listOfEnemy=removeEnemy(listOfEnemy); 
	removeBullets(-1);
}

/**
 ** RESETUJE USTAWIENIA GRY TAKIE JAK PUNKTY ITP
*/
 void resetGame(
 	int *enemyOnScreen,
	int *killedEnemy,
	int *killToNextLevelWeapon,
	int *killToMoreEnemy,
	bool *bossTime,
	bool *bossOnScreen
	){
	*enemyOnScreen=0;
	*killedEnemy=0;
	*killToNextLevelWeapon=8;
	*killToMoreEnemy=2;
	*bossTime=false;
	*bossOnScreen=false;
	myCraft.points=0;
	myCraft.shield=100;
	myCraft.life=100;
	myCraft.posX=mainDisplayWidth/2;
	myCraft.weaponLevel=1;
	myCraft.shootSpeed=1/FPS*2;
	myCraft.bulletSpeed=1/FPS*900*mainDisplayHeight/700;
	key[0]=false;
	key[1]=false;
	key[2]=false;
	key[3]=false;
	key[4]=false;
	numberOfEnemy=1;
 }

 void destroyAllegroData(){
 	int i=0;
 	ranking=rankDestroy();
 	if (gameMusicInstance) al_destroy_sample_instance(gameMusicInstance);
 	if (gameMusic) al_destroy_sample(gameMusic);
 	if (menuMusic) al_destroy_sample(menuMusic);
 	if (explosive) al_destroy_sample(explosive);
	if (font) al_destroy_font(font);
	if (font2) al_destroy_font(font2);
	if (font3) al_destroy_font(font3);
   	if (menu) al_destroy_bitmap(menu);
	if (menu2) al_destroy_bitmap(menu2);
	if (mainBackground) al_destroy_bitmap(mainBackground);
	if (secondBackground) al_destroy_bitmap(secondBackground);
	if (thirdBackground) al_destroy_bitmap(thirdBackground);
	if (lifeBitmap) al_destroy_bitmap(lifeBitmap);
	if (craft) al_destroy_bitmap(craft);
	if (craftBullet) al_destroy_bitmap(craftBullet);
	if (craftShieldImg) al_destroy_bitmap(craftShieldImg);
	if (craftLifeImg) al_destroy_bitmap(craftLifeImg);
	for (i=0;i<5;i++){
		if(EnemyCrafts[i].enemyCraft) al_destroy_bitmap(EnemyCrafts[i].enemyCraft);
		if(EnemyCrafts[i].enemyBulletImage) al_destroy_bitmap(EnemyCrafts[i].enemyBulletImage);
	}
   	if (timer) al_destroy_timer(timer);
   	if (eventQueue) al_destroy_event_queue(eventQueue);
   	if (mainDisplay) al_destroy_display(mainDisplay);
 	puts("ZWOLNIONO ZASOBY ALLEGRO");
 }