#include "craft.h"


void loadCraft(){
	craft = al_load_bitmap(myCraft.path);
	myCraft.defaultSizeX=al_get_bitmap_width(craft);
	myCraft.defaultSizeY=al_get_bitmap_height(craft);
	craftShieldImg = al_load_bitmap(craftShieldPath);
	craftLifeImg = 	al_load_bitmap(craftLifePath);
}
void moveCraft(int tryb){
	if( (tryb==-1) && (myCraft.posX>myCraft.sizeX/2) ) myCraft.posX-=myCraft.speed;
	if( (tryb==1) && (myCraft.posX<(mainDisplayWidth-(myCraft.sizeX*3/2))) ) myCraft.posX+=myCraft.speed;
}
void drowCraft(){
	al_draw_scaled_bitmap(craft,0,0,myCraft.defaultSizeY,myCraft.defaultSizeY,myCraft.posX,myCraft.posY,myCraft.sizeX,myCraft.sizeY,0);
}
void setCraft(){
	myCraft.defaultSizeX=0;
	myCraft.defaultSizeY=0;
	myCraft.sizeX=mainDisplayWidth/15;
	myCraft.sizeY=myCraft.sizeX;
	myCraft.posX=mainDisplayWidth/2-(myCraft.sizeX/2);
	myCraft.posY=mainDisplayHeight-myCraft.sizeY-10;
	myCraft.speed=1/FPS*600*mainDisplayWidth/1500;
	sprintf(myCraft.path,"%s",craftImage);
	myCraft.shootSpeed=1/FPS*2;
	myCraft.bulletSpeed=1/FPS*900*mainDisplayHeight/700;
	myCraft.shield=100;
	myCraft.life=100;
	myCraft.weaponLevel=1;
	myCraft.shootDelay=1;
	myCraft.shieldReg=true;
	myCraft.points=0;
	myCraft.damage=50;
}

void shieldReg(){
	if(myCraft.shield<100){
		if( myCraft.shield==0 ) myCraft.shieldReg=false;
		if(myCraft.shieldReg) myCraft.shield+=1/FPS*4;
		if(myCraft.shield>100) myCraft.shield=100;
	}
}

void setBullet(struct bulletStruct *bullet,int sizeMulti,int damage, int speed){
	bullet->sizeX=myCraft.sizeX/9*sizeMulti;
	bullet->sizeY=bullet->sizeX*sizeMulti;
	bullet->damage=damage;
	bullet->speed=speed;
}

void craftShootDelay(){
	if(myCraft.shootDelay<1) myCraft.shootDelay+=myCraft.shootSpeed;
}

void drowLife(){
	int lineWidth=(int)mainDisplayWidth/8;
	int lineHeight=(int)mainDisplayHeight/80;

	al_set_target_bitmap(lifeBitmap);
	al_clear_to_color(al_map_rgb(204, 204, 204));
	al_set_target_bitmap(al_get_backbuffer(mainDisplay));
	al_draw_bitmap(lifeBitmap, 20, mainDisplayHeight-60, 0);

	al_set_target_bitmap(lifeBitmap);
	al_clear_to_color(al_map_rgb(204, 204, 204));
	al_set_target_bitmap(al_get_backbuffer(mainDisplay));
	al_draw_bitmap(lifeBitmap, 20, mainDisplayHeight-30, 0);

	al_set_target_bitmap(lifeBitmap);
	al_clear_to_color(al_map_rgb(250, 0, 0));
	al_set_target_bitmap(al_get_backbuffer(mainDisplay));
	al_draw_scaled_bitmap(lifeBitmap,0,0,lineWidth, lineHeight,20,mainDisplayHeight-60,lineWidth*myCraft.life/100, lineHeight, 0);

	al_set_target_bitmap(lifeBitmap);
	al_clear_to_color(al_map_rgb(0, 0, 204));
	al_set_target_bitmap(al_get_backbuffer(mainDisplay));
	al_draw_scaled_bitmap(lifeBitmap,0,0,lineWidth, lineHeight,20,mainDisplayHeight-30,lineWidth*myCraft.shield/100, lineHeight, 0);

	al_set_target_bitmap(al_get_backbuffer(mainDisplay));
	al_draw_text(font, al_map_rgb(204, 204, 204), lineWidth/2+20, mainDisplayHeight-63,ALLEGRO_ALIGN_CENTRE, "LIFE");
	al_draw_text(font, al_map_rgb(204, 204, 204), lineWidth/2+20, mainDisplayHeight-33,ALLEGRO_ALIGN_CENTRE, "SHIELD");
}

void drowPoints(){
	char string[20];
	myCraft.points+=1/FPS*6;
	sprintf(string,"%d",(int)myCraft.points);
	al_draw_text(font2, al_map_rgb(204, 204, 204), mainDisplayWidth-100, 10, ALLEGRO_ALIGN_CENTRE, string);

}

int loadLifeBitmap(){
	lifeBitmap = al_create_bitmap((int)mainDisplayWidth/8,(int)mainDisplayHeight/80);
	if(!lifeBitmap){
		fprintf(stderr, "Błąd podczas tworzenia bitmapy pasków zycia!\n");
		return -1;
	}
	return 1;
}

ALLEGRO_BITMAP *loadBullet(ALLEGRO_BITMAP *allegroBitmap, struct bulletStruct *bullet,char path[]){
	allegroBitmap = al_load_bitmap(path);
	 if (!allegroBitmap ){
    	fprintf(stderr, "Błąd podczas wczytywania grafiki\n");
        return 0;
    }
    bullet->defaultSizeX=al_get_bitmap_width(allegroBitmap);
	bullet->defaultSizeY=al_get_bitmap_height(allegroBitmap);
	return allegroBitmap;
}

void drowBullets(){
	bulletStruct *tmp=NULL;
	tmp=myCraftBullets;
	while(tmp){
		al_draw_scaled_bitmap(craftBullet,0,0,myBullet.defaultSizeY,myBullet.defaultSizeY,tmp->posX,tmp->posY,myBullet.sizeX,myBullet.sizeY,0);
		tmp=tmp->next;
	}
}

bulletStruct *addToBulletList(bulletStruct *listaRoot, int posX, int posY){
	bulletStruct *nowy=NULL;
	nowy=malloc(1*sizeof(nowy));
	nowy->posX=posX;
	nowy->posY=posY;
	if(listaRoot==NULL){
		listaRoot=nowy;
		listaRoot->next=NULL;
	}
	else{
		nowy->next=listaRoot;
		listaRoot=nowy;
	}
	return listaRoot;
}
void moveBullets(int tryb){
	bulletStruct *tmp=NULL;
	if(tryb==1){
		tmp=myCraftBullets;
		while(tmp){
			tmp->posY-=myBullet.speed;
			tmp=tmp->next;
		}
	}
	if(tryb==-1){
	}
}
void removeBullets(int tryb){
	bulletStruct *tmp=NULL;
	bulletStruct *tmp2=NULL;
	if(tryb==1){
		tmp=myCraftBullets;
		while(tmp){
			if(tmp->posY<0){
				myCraftBullets=myCraftBullets->next;
				free(tmp);
				tmp=myCraftBullets;
			}
			else break;
		}
		if(tmp){
			while(tmp->next){
		 		if(tmp->next->posY<0){
		 			tmp2=tmp->next;
		 			tmp->next=tmp2->next;
		 			free(tmp2);
		 		}
		 		if(tmp->next) tmp=tmp->next;
			}
		}
	}
	if(tryb==-1){
		tmp=myCraftBullets;
		while(tmp){
			myCraftBullets=myCraftBullets->next;
			free(tmp);
			tmp=myCraftBullets;
	
		}
		if(tmp){
			while(tmp->next){
		 		tmp2=tmp->next;
		 		tmp->next=tmp2->next;
		 		free(tmp2);
		 		if(tmp->next) tmp=tmp->next;
			}
		}
	}
}

void craftShoot(){
	if(myCraft.shootDelay>=1){
		myCraft.shootDelay=0;
		switch(myCraft.weaponLevel){
			case 1:
				myCraftBullets=addToBulletList(myCraftBullets, myCraft.posX+(myCraft.sizeX/2)-(myBullet.sizeX/2),myCraft.posY+myBullet.sizeY );
			break;
			case 2:
				myCraftBullets=addToBulletList(myCraftBullets, myCraft.posX+(myCraft.sizeX/2)-(myBullet.sizeX*2),myCraft.posY+myBullet.sizeY );
				myCraftBullets=addToBulletList(myCraftBullets, myCraft.posX+(myCraft.sizeX/2)+(myBullet.sizeX*1),myCraft.posY+myBullet.sizeY );
			break;
			case 3:
				myCraftBullets=addToBulletList(myCraftBullets, myCraft.posX+(myCraft.sizeX/2)-(myBullet.sizeX*2),myCraft.posY+(myBullet.sizeY*2) );
				myCraftBullets=addToBulletList(myCraftBullets, myCraft.posX+(myCraft.sizeX/2)-(myBullet.sizeX/2),myCraft.posY+myBullet.sizeY );
				myCraftBullets=addToBulletList(myCraftBullets, myCraft.posX+(myCraft.sizeX/2)+(myBullet.sizeX*1),myCraft.posY+(myBullet.sizeY*2) );
			break;
			case 4:
				myCraftBullets=addToBulletList(myCraftBullets, myCraft.posX+(myCraft.sizeX/2)-(myBullet.sizeX*4),myCraft.posY+(myBullet.sizeY*2) );
				myCraftBullets=addToBulletList(myCraftBullets, myCraft.posX+(myCraft.sizeX/2)-(myBullet.sizeX*2),myCraft.posY+myBullet.sizeY );
				myCraftBullets=addToBulletList(myCraftBullets, myCraft.posX+(myCraft.sizeX/2)+(myBullet.sizeX*1),myCraft.posY+myBullet.sizeY );
				myCraftBullets=addToBulletList(myCraftBullets, myCraft.posX+(myCraft.sizeX/2)+(myBullet.sizeX*3),myCraft.posY+(myBullet.sizeY*2) );
			break;
			case 5:
				myCraftBullets=addToBulletList(myCraftBullets, myCraft.posX+(myCraft.sizeX/2)-(myBullet.sizeX*4),myCraft.posY+(myBullet.sizeY*3) );
				myCraftBullets=addToBulletList(myCraftBullets, myCraft.posX+(myCraft.sizeX/2)-(myBullet.sizeX*2),myCraft.posY+(myBullet.sizeY*2) );
				myCraftBullets=addToBulletList(myCraftBullets, myCraft.posX+(myCraft.sizeX/2)-(myBullet.sizeX/2),myCraft.posY+myBullet.sizeY );
				myCraftBullets=addToBulletList(myCraftBullets, myCraft.posX+(myCraft.sizeX/2)+(myBullet.sizeX*1),myCraft.posY+(myBullet.sizeY*2) );
				myCraftBullets=addToBulletList(myCraftBullets, myCraft.posX+(myCraft.sizeX/2)+(myBullet.sizeX*3),myCraft.posY+(myBullet.sizeY*3) );
			break;
		}
		
	}
}

int checkLife(ALLEGRO_EVENT ev,FILE *rankFile){
	if(myCraft.life<=0){
		writeEnd(0,ev,rankFile);
		return -1;
	}
	return 0;
}
void destroyMyCraft(struct treeBulletStruct *this){
	if( (*this->posX>myCraft.posX+8) && (*this->posX<myCraft.posX+myCraft.sizeX-18) && (*this->posY>myCraft.posY+15) && (*this->posY<mainDisplayHeight-15) ){
		if(myCraft.shield>0){
			myCraft.shield-=EnemyCrafts[*this->numberOfEnemy].damage;
			if(myCraft.shield<0) myCraft.shield=0;
			al_draw_scaled_bitmap(craftShieldImg,0,0,myCraft.defaultSizeY,myCraft.defaultSizeY,myCraft.posX,myCraft.posY,myCraft.sizeX,myCraft.sizeY,0);

		}
		else {
			myCraft.life-=EnemyCrafts[*this->numberOfEnemy].damage;
			al_draw_scaled_bitmap(craftLifeImg,0,0,myCraft.defaultSizeY,myCraft.defaultSizeY,myCraft.posX,myCraft.posY,myCraft.sizeX,myCraft.sizeY,0);
		}
		usunZDrzewa(this);
	}
}

