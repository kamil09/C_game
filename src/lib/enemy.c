#include "enemy.h"

int setEnemy(){
	EnemyCrafts[0].sizeX=mainDisplayWidth/14;
	EnemyCrafts[0].sizeY=mainDisplayWidth/14;
	EnemyCrafts[0].speed=1/FPS*200*mainDisplayWidth/1500;
	EnemyCrafts[0].shootSpeed=1/FPS;
	EnemyCrafts[0].bulletSpeed=1/FPS*600*mainDisplayHeight/700;
	EnemyCrafts[0].damage=20;
	EnemyCrafts[0].life=100;
	EnemyCrafts[0].shootDelay=1;
	EnemyCrafts[0].weaponLevel=1;
	EnemyCrafts[0].bullSizeX=EnemyCrafts[0].sizeX/8;
	EnemyCrafts[0].bullSizeY=EnemyCrafts[0].bullSizeX*2;

	EnemyCrafts[1].sizeX=mainDisplayWidth/13;
	EnemyCrafts[1].sizeY=mainDisplayWidth/13;
	EnemyCrafts[1].speed=1/FPS*300*mainDisplayWidth/1500;
	EnemyCrafts[1].shootSpeed=1/FPS/2;
	EnemyCrafts[1].bulletSpeed=1/FPS*500*mainDisplayHeight/700;
	EnemyCrafts[1].damage=10;
	EnemyCrafts[1].life=100;
	EnemyCrafts[1].shootDelay=1;
	EnemyCrafts[1].weaponLevel=2;
	EnemyCrafts[1].bullSizeX=EnemyCrafts[1].sizeX/8;
	EnemyCrafts[1].bullSizeY=EnemyCrafts[1].bullSizeX*2;

	EnemyCrafts[2].sizeY=mainDisplayWidth/12;
	EnemyCrafts[2].sizeX=EnemyCrafts[2].sizeY*4/5;
	EnemyCrafts[2].speed=1/FPS*200*mainDisplayWidth/1500;
	EnemyCrafts[2].shootSpeed=1/FPS/3;
	EnemyCrafts[2].bulletSpeed=1/FPS*400*mainDisplayHeight/700;
	EnemyCrafts[2].damage=25;
	EnemyCrafts[2].life=150;
	EnemyCrafts[2].shootDelay=1;
	EnemyCrafts[2].weaponLevel=4;
	EnemyCrafts[2].bullSizeX=EnemyCrafts[2].sizeX/8;
	EnemyCrafts[2].bullSizeY=EnemyCrafts[2].bullSizeX*2;

	EnemyCrafts[3].sizeX=mainDisplayWidth/11;
	EnemyCrafts[3].sizeY=EnemyCrafts[3].sizeX*4/5;
	EnemyCrafts[3].speed=1/FPS*150*mainDisplayWidth/1500;
	EnemyCrafts[3].shootSpeed=1/FPS/4;
	EnemyCrafts[3].bulletSpeed=1/FPS*300*mainDisplayHeight/700;
	EnemyCrafts[3].damage=30;
	EnemyCrafts[3].life=200;
	EnemyCrafts[3].shootDelay=1;
	EnemyCrafts[3].weaponLevel=5;
	EnemyCrafts[3].bullSizeX=EnemyCrafts[3].sizeX/10;
	EnemyCrafts[3].bullSizeY=EnemyCrafts[3].bullSizeX*2;

	EnemyCrafts[4].sizeX=mainDisplayWidth/7;
	EnemyCrafts[4].sizeY=EnemyCrafts[4].sizeX*3/5;
	EnemyCrafts[4].speed=1/FPS*200*mainDisplayWidth/1500;
	EnemyCrafts[4].shootSpeed=1/FPS*2.5;
	EnemyCrafts[4].bulletSpeed=1/FPS*1000*mainDisplayHeight/700;
	EnemyCrafts[4].damage=30;
	EnemyCrafts[4].life=50000;
	EnemyCrafts[4].shootDelay=1;
	EnemyCrafts[4].weaponLevel=1;
	EnemyCrafts[4].bullSizeX=EnemyCrafts[4].sizeX/10;
	EnemyCrafts[4].bullSizeY=EnemyCrafts[4].bullSizeX*2;

	return 0;
}

struct enemyCraftStruct loadEnemy(struct enemyCraftStruct enemy,int number, char *path, char *bulletPath){
	enemy.enemyCraft=al_load_bitmap(path);
	enemy.enemyBulletImage=al_load_bitmap(bulletPath);
	if(!enemy.enemyCraft){
		puts("Błąd podczas wczytywania grafiki");
	}
	enemy.defaultSizeX=al_get_bitmap_width(enemy.enemyCraft);
	enemy.defaultSizeY=al_get_bitmap_height(enemy.enemyCraft);
	enemy.bullDefaultSizeX=al_get_bitmap_width(enemy.enemyBulletImage);
	enemy.bullDefaultSizeY=al_get_bitmap_height(enemy.enemyBulletImage);
	return enemy;
}

void addToEnemyList(int rodzaj,int posX,int posY,int toGoX,int toGoY){
	struct listOfEnemyStruct *new;
	new=malloc(1*sizeof(*new));
	new->posX=posX;
	new->posY=posY;
	new->goToX=toGoX;
	new->goToY=toGoY;
	new->shootDelay=1;
	new->numberOfEnemy=rodzaj;
	new->life=EnemyCrafts[rodzaj].life;
	new->prev=NULL;
	new->next=NULL;
	if(listOfEnemy==NULL) listOfEnemy=new;
	else{
		new->next=listOfEnemy;
		listOfEnemy->prev=new;
		listOfEnemy=new;
	}
}

//Dodawanie przeciwników mega losowe rozwiązanie ;)
void addEnemy(){
	int rodzaj;
	int posX;
	int posY;
	int toGoX;
	int toGoY;
	posY=-200;
	posX=rand()%(mainDisplayWidth-200);
	toGoY=rand()%(mainDisplayHeight/2);
	rodzaj=rand()%4;
	toGoX=rand()%(mainDisplayWidth-200);
	addToEnemyList(rodzaj,posX,posY,toGoX,toGoY);
}

void addBoss(int posX,int posY, int toGoX, int toGoY){
	addToEnemyList(4,posX,posY,toGoX,toGoY);
}

void enemyOnPlace(){
	struct listOfEnemyStruct *tmp;
	tmp=listOfEnemy;
	while(tmp){
		if( (tmp->posX==tmp->goToX) && (tmp->posY==tmp->goToY) ){
			if(tmp->numberOfEnemy!=4) tmp->goToY=rand()%(mainDisplayHeight/2);
			tmp->goToX=rand()%(mainDisplayWidth-200);
		}
		tmp=tmp->next;
	}
}

void drowEnemies(){
	struct listOfEnemyStruct *tmp;
	tmp=listOfEnemy;
	while(tmp){
		al_draw_scaled_bitmap(
			EnemyCrafts[tmp->numberOfEnemy].enemyCraft,
			0,
			0,
			EnemyCrafts[tmp->numberOfEnemy].defaultSizeX,
			EnemyCrafts[tmp->numberOfEnemy].defaultSizeY,
			tmp->posX,
			tmp->posY,
			EnemyCrafts[tmp->numberOfEnemy].sizeX,
			EnemyCrafts[tmp->numberOfEnemy].sizeY,
			0);
		tmp=tmp->next;
	}
}

void removeDead(int *enemyOnScreen, int *killedEnemy, float *newEnemyDelay,int *killToMoreEnemy){
	struct listOfEnemyStruct *tmp;
	tmp=listOfEnemy;
	while(tmp){
		if(tmp->life<=0){
			myCraft.points+=1000*(tmp->numberOfEnemy)+1000;
			tmp=removeEnemy(tmp);
			(*enemyOnScreen)--;
			(*killedEnemy)++;
			(*newEnemyDelay)=0;

			if((*killedEnemy)>0 && (*killedEnemy)>*killToMoreEnemy){
				(*killToMoreEnemy)*=2;
     			numberOfEnemy++;
     		}
     		if((*killedEnemy)>0 && (*killedEnemy)%4==0){
     			EnemyCrafts[0].life=EnemyCrafts[0].life+(EnemyCrafts[0].life/12);
     			EnemyCrafts[1].life=EnemyCrafts[1].life+(EnemyCrafts[1].life/12);
     			EnemyCrafts[2].life=EnemyCrafts[2].life+(EnemyCrafts[2].life/12);
     			EnemyCrafts[3].life=EnemyCrafts[3].life+(EnemyCrafts[3].life/12);
     			EnemyCrafts[0].shootSpeed+=EnemyCrafts[0].shootSpeed/15;
     			EnemyCrafts[1].shootSpeed+=EnemyCrafts[1].shootSpeed/15;
     			EnemyCrafts[2].shootSpeed+=EnemyCrafts[2].shootSpeed/15;
     			EnemyCrafts[3].shootSpeed+=EnemyCrafts[3].shootSpeed/15;
     			EnemyCrafts[0].bulletSpeed+=EnemyCrafts[0].bulletSpeed/15;
     			EnemyCrafts[1].bulletSpeed+=EnemyCrafts[1].bulletSpeed/15;
     			EnemyCrafts[2].bulletSpeed+=EnemyCrafts[2].bulletSpeed/15;
     			EnemyCrafts[3].bulletSpeed+=EnemyCrafts[3].bulletSpeed/15;
     		}
     		if (sound) al_play_sample(explosive, 1, 0.0,1.0,ALLEGRO_PLAYMODE_ONCE,NULL);

			return;
		}
		else tmp=tmp->next;
	}
}

struct listOfEnemyStruct *removeEnemy(struct listOfEnemyStruct *tmp){
	struct listOfEnemyStruct *tmp2;
	tmp2=tmp;
	tmp=tmp->next;
	if(tmp2->next) tmp2->next->prev = tmp2->prev;
	if(tmp2->prev) tmp2->prev->next = tmp2->next;
	else listOfEnemy=listOfEnemy->next;
	free(tmp2);
	tmp2=NULL;
	return tmp;
}

//Odejmuje życie trafionym przeciwnikom
void ifEnemyShoot(){
	struct listOfEnemyStruct *tmp;
	bulletStruct *tmpBull=NULL;
	tmp=listOfEnemy;
	tmpBull=myCraftBullets;
	while(tmpBull){
		tmp=listOfEnemy;
		while(tmp){
			if( (tmpBull->posX>tmp->posX+5) && (tmpBull->posX<tmp->posX+EnemyCrafts[tmp->numberOfEnemy].sizeX-5) && (tmpBull->posY>tmp->posY+5) && (tmpBull->posY<tmp->posY+EnemyCrafts[tmp->numberOfEnemy].sizeY-5) ){
				tmpBull->posX=0;
				tmpBull->posY=-20;
				tmp->life-=myCraft.damage;
				break;
			}
			tmp=tmp->next;
		}
		tmpBull=tmpBull->next;
	}
}

void enemyShootDelay(){
 		struct listOfEnemyStruct *tmp;	
 		tmp=listOfEnemy;
		while(tmp){
			if(tmp->shootDelay<1){
				tmp->shootDelay+=EnemyCrafts[tmp->numberOfEnemy].shootSpeed;
			}
			tmp=tmp->next;
		}
}

void EnemyShoot(){
	struct listOfEnemyStruct *tmp;
	int shootPoint=0;
	tmp=listOfEnemy;
	while(tmp){
		if(tmp->shootDelay>=1){
			shootPoint=tmp->posX+(EnemyCrafts[tmp->numberOfEnemy].sizeX/2);
			int shootBulletSize=EnemyCrafts[tmp->numberOfEnemy].bullSizeX;
			int shootBulletSizeY=EnemyCrafts[tmp->numberOfEnemy].bullSizeY;
			if( ((shootPoint>myCraft.posX) && (shootPoint<myCraft.posX+myCraft.sizeX) && (tmp->posY>0)) || (tmp->numberOfEnemy==4 && (tmp->posY>0)) ){
				tmp->shootDelay=0;
				switch(EnemyCrafts[tmp->numberOfEnemy].weaponLevel){
					case 1:
						TreeBullet=addToBulletTree(TreeBullet, shootPoint-(shootBulletSize/2),tmp->posY+shootBulletSizeY,		tmp->numberOfEnemy);
					break;
					case 2:
						TreeBullet=addToBulletTree(TreeBullet, shootPoint-(shootBulletSize*2),tmp->posY+shootBulletSizeY,		tmp->numberOfEnemy );
						TreeBullet=addToBulletTree(TreeBullet, shootPoint+(shootBulletSize*1),tmp->posY+shootBulletSizeY,		tmp->numberOfEnemy );
					break;
					case 3:
						TreeBullet=addToBulletTree(TreeBullet, shootPoint-(shootBulletSize*2),tmp->posY+shootBulletSizeY,	tmp->numberOfEnemy );
						TreeBullet=addToBulletTree(TreeBullet, shootPoint-(shootBulletSize/2),tmp->posY+(shootBulletSizeY*2),		tmp->numberOfEnemy );
						TreeBullet=addToBulletTree(TreeBullet, shootPoint+(shootBulletSize*1),tmp->posY+shootBulletSizeY,	tmp->numberOfEnemy );
					break;
					case 4:
						TreeBullet=addToBulletTree(TreeBullet, shootPoint-(shootBulletSize*4),tmp->posY+shootBulletSizeY,	tmp->numberOfEnemy );
						TreeBullet=addToBulletTree(TreeBullet, shootPoint-(shootBulletSize*2),tmp->posY+(shootBulletSizeY*2),		tmp->numberOfEnemy );
						TreeBullet=addToBulletTree(TreeBullet, shootPoint+(shootBulletSize*1),tmp->posY+(shootBulletSizeY*2),		tmp->numberOfEnemy );
						TreeBullet=addToBulletTree(TreeBullet, shootPoint+(shootBulletSize*3),tmp->posY+shootBulletSizeY,	tmp->numberOfEnemy);
					break;
					case 5:
						TreeBullet=addToBulletTree(TreeBullet, shootPoint-(shootBulletSize*4),tmp->posY+shootBulletSizeY,tmp->numberOfEnemy );
						TreeBullet=addToBulletTree(TreeBullet, shootPoint-(shootBulletSize*2),tmp->posY+(shootBulletSizeY*2),tmp->numberOfEnemy );
						TreeBullet=addToBulletTree(TreeBullet, shootPoint-(shootBulletSize/2),tmp->posY+(shootBulletSizeY*3),tmp->numberOfEnemy );
						TreeBullet=addToBulletTree(TreeBullet, shootPoint+(shootBulletSize*1),tmp->posY+(shootBulletSizeY*2),tmp->numberOfEnemy );
						TreeBullet=addToBulletTree(TreeBullet, shootPoint+(shootBulletSize*3),tmp->posY+shootBulletSizeY,tmp->numberOfEnemy );
					break;
				}
			}
		}
		tmp=tmp->next;
	}
}

void moveEnemy(){
	float tg;
	int Xlength;
	int Ylength;
	struct listOfEnemyStruct *tmp;
	tmp=listOfEnemy;

	while(tmp){
		Xlength=(tmp->goToX)-(tmp->posX);
		Ylength=(tmp->goToY)-(tmp->posY);
		//printf("%d %d %d\n",tmp->posY,tmp->posX,EnemyCrafts[tmp->numberOfEnemy].speed);
		if(Xlength<0) Xlength*=-1;
		if(Ylength<0) Ylength*=-1;
		
		if(Xlength==0){
			if(tmp->posY>tmp->goToY) tmp->posY-=EnemyCrafts[tmp->numberOfEnemy].speed;
			else tmp->posY+=EnemyCrafts[tmp->numberOfEnemy].speed;
		}
		else {
			if(Ylength==0){
				if(tmp->posX>tmp->goToX) tmp->posX-=EnemyCrafts[tmp->numberOfEnemy].speed;
				else tmp->posX+=EnemyCrafts[tmp->numberOfEnemy].speed;
			}
			else{
				tg=Xlength/Ylength;
				tg=atan(tg);

				if(tmp->posY>tmp->goToY) tmp->posY-=(int)(EnemyCrafts[tmp->numberOfEnemy].speed*cos(tg));
				else tmp->posY+=(int)(EnemyCrafts[tmp->numberOfEnemy].speed*cos(tg));	
		
				if(tmp->posX>tmp->goToX) tmp->posX-=(int)(EnemyCrafts[tmp->numberOfEnemy].speed*sin(tg));
				else tmp->posX+=(int)(EnemyCrafts[tmp->numberOfEnemy].speed*sin(tg));
			
			}
		}

		Xlength=(tmp->goToX)-(tmp->posX);
		Ylength=(tmp->goToY)-(tmp->posY);
		
		if(Xlength<0) Xlength*=-1;
		if(Ylength<0) Ylength*=-1;
		if(Xlength<EnemyCrafts[tmp->numberOfEnemy].speed) tmp->posX=tmp->goToX;
		if(Ylength<EnemyCrafts[tmp->numberOfEnemy].speed) tmp->posY=tmp->goToY;

		
		tmp=tmp->next;
	}
}

struct treeBulletStruct *addToBulletTree(struct treeBulletStruct *root,int posX, int posY, int numberOfEnemy){
	struct treeBulletStruct *nowy;
	float alfa=0;
	float tmp=0;
	nowy=malloc(1*sizeof(*nowy));
	nowy->posX=malloc(sizeof(int));
	nowy->posY=malloc(sizeof(int));
	nowy->numberOfEnemy=malloc(sizeof(int));
	nowy->parent=NULL;
	nowy->left=NULL;
	nowy->right=NULL;
	*nowy->posX=posX;
	*nowy->posY=posY;
	*nowy->numberOfEnemy=numberOfEnemy;
	if(numberOfEnemy==4) {
		nowy->alfa=malloc(sizeof(float));
		alfa=myCraft.posX+(myCraft.sizeX/2)-posX;
		tmp=posY-myCraft.posY-10;
		alfa=alfa/tmp;
		if(alfa<0) alfa*=-1;
		alfa=atan(alfa);
		if(posX<myCraft.posX+(myCraft.sizeX/2)) alfa*=-1;
		*nowy->alfa=alfa;
		//printf("%f\n",alfa);
	}

	//printf("%d - %d - %d\n",*nowy->posX,*nowy->posY,*nowy->numberOfEnemy);
	if(root==NULL){
		root=nowy;
	}
	else{
		addToBulletTreeReq(root,nowy);
	}
	return root;
}


//Rekurencyjna funkcja dodająca do Drzewka pociski
void addToBulletTreeReq(struct treeBulletStruct *this, struct treeBulletStruct *new){
	if(*new->posX<*this->posX){
		if(this->left!=NULL){
			addToBulletTreeReq(this->left,new);
		}
		else{
			this->left=new;
			new->parent=this;
		}			
	}
	else{
		if(this->right!=NULL){
			addToBulletTreeReq(this->right,new);
		}
		else{
			this->right=new;
		 	new->parent=this;
		}
	}
}

struct treeBulletStruct *freeBulletMemory(struct treeBulletStruct *this){
	free(this->posX);
	free(this->posY);
	if(*this->numberOfEnemy==4) free(this->alfa);
	free(this->numberOfEnemy);
	free(this);
	return NULL;
}

//Usuwa dany pocisk z drzewa
void usunZDrzewa(struct treeBulletStruct *this){
	struct treeBulletStruct *tmp;
	//BRAK DZIECI
	if( (!this->left) && (!this->right) ){
		if(this->parent){
			if (*this->posX<*this->parent->posX) this->parent->left=NULL;
			else this->parent->right=NULL;
			this=freeBulletMemory(this);
		}
		else{
			TreeBullet=freeBulletMemory(this);
		}
		return;
	}
	//2 Dzieci
	if( (this->left) && (this->right) ){

		tmp=this->right;
 		while(tmp->left) tmp=tmp->left;

 		//Przepisywanie danych
 		*this->posX=*tmp->posX;
 		*this->posY=*tmp->posY;
 		*this->numberOfEnemy=*tmp->numberOfEnemy;

		if(tmp->parent!=this) {
			if (tmp->right!=NULL){
				tmp->parent->left=tmp->right;
				tmp->right->parent=tmp->parent;
			}
			else tmp->parent->left=NULL;
		}
		else {
			if(this->right->right!=NULL){
				tmp->parent->right=tmp->right;
				tmp->right->parent=tmp->parent;
			}
		else this->right=NULL;
		}
				
 		tmp=freeBulletMemory(tmp);
		return;
	}	
	//Gdy 1 dziecko
	if((this->left!=NULL) && (this->right==NULL)){
		if (this->parent){
			if((*this->posX)<(*this->parent->posX)) {

				this->parent->left=this->left;
				this->left->parent=this->parent;
			}
			else {

				this->parent->right=this->left;	
				this->left->parent=this->parent;
			}
		}
		else {
			TreeBullet=this->left;
			TreeBullet->parent=NULL;
		}
		this=freeBulletMemory(this);
		return;
	}
	if((this->left==NULL) && (this->right!=NULL)){
		if (this->parent!=NULL){
			if((*this->posX)<(*this->parent->posX)) {
				this->parent->left=this->right;
				this->right->parent=this->parent;							

			}
			else {

				this->parent->right=this->right;
				this->right->parent=this->parent;
			}
		}
		else {
			TreeBullet=this->right;
			TreeBullet->parent=NULL;
			}
		this=freeBulletMemory(this);
		return;
	}		

}

//LRP - LEWY / RODZIC / PRAWY
//Rysuje pociski, przesuwa je i usuwa te, które wyleciały poza obszar
//Sprawdza czy nasz statek został trafiony jakimś pociskiem
void drowEnemyBulletsReq(struct treeBulletStruct *this){
	float tmp=0;
	if(this){
		drowEnemyBulletsReq(this->left);
		if(*this->numberOfEnemy<4 ) *this->posY+=EnemyCrafts[*this->numberOfEnemy].bulletSpeed;
		if (*this->numberOfEnemy==4){
			if(*this->alfa<0) {
				*this->posX+=sin((*this->alfa*-1))*EnemyCrafts[*this->numberOfEnemy].bulletSpeed;
				tmp=6.28+*this->alfa;
			}
			else {
				*this->posX-=sin(*this->alfa)*EnemyCrafts[*this->numberOfEnemy].bulletSpeed;
				tmp=*this->alfa;
			}
			*this->posY+=cos(*this->alfa)*EnemyCrafts[*this->numberOfEnemy].bulletSpeed;
		}

		al_draw_scaled_rotated_bitmap(
			EnemyCrafts[*this->numberOfEnemy].enemyBulletImage,
			0,
			0,
			*this->posX,
			*this->posY,
			(float)EnemyCrafts[*this->numberOfEnemy].bullSizeX/EnemyCrafts[*this->numberOfEnemy].bullDefaultSizeX,
			(float)EnemyCrafts[*this->numberOfEnemy].bullSizeY/EnemyCrafts[*this->numberOfEnemy].bullDefaultSizeY,
			tmp,
			0);
		if(*this->posY>mainDisplayHeight){
			usunZDrzewa(this);
		}
		destroyMyCraft(this);
		drowEnemyBulletsReq(this->right);
	}
}

void checkBossLife(bool *bossTime, bool *bossOnScreen, int *killedEnemy, int *numberOfEnemy, int *killToMoreEnemy){
	if(!listOfEnemy){
		*bossTime=false;
		*bossOnScreen=false;
		*killedEnemy=0;
		*numberOfEnemy=2;
		*killToMoreEnemy=2;
		EnemyCrafts[4].life*=2;
		myCraft.points+=EnemyCrafts[4].life;
	}
}

void drowBossLife(){
	if(listOfEnemy){
		int lineWidth=(int)mainDisplayWidth/2;
		int lineHeight=(int)mainDisplayHeight/70;

		al_set_target_bitmap(lifeBitmap);
		al_clear_to_color(al_map_rgb(204, 204, 204));
		al_set_target_bitmap(al_get_backbuffer(mainDisplay));
		al_draw_scaled_bitmap(lifeBitmap,0,0,al_get_bitmap_width(lifeBitmap),al_get_bitmap_height(lifeBitmap),mainDisplayWidth/4,30,lineWidth,lineHeight,0);

		al_set_target_bitmap(lifeBitmap);
		al_clear_to_color(al_map_rgb(250, 0, 0));
		al_set_target_bitmap(al_get_backbuffer(mainDisplay));
		al_draw_scaled_bitmap(lifeBitmap,0,0,al_get_bitmap_width(lifeBitmap),al_get_bitmap_height(lifeBitmap),mainDisplayWidth/4,30,lineWidth*listOfEnemy->life/EnemyCrafts[4].life, lineHeight, 0);

		al_set_target_bitmap(al_get_backbuffer(mainDisplay));
		al_draw_text(font, al_map_rgb(204, 204, 204), (lineWidth/2)+(mainDisplayWidth/4), 27,ALLEGRO_ALIGN_CENTRE, "****  BOSS LIFE  ****");
	}
}