#include "menu.h"

void makeConfFile(){
	FILE *conf;
	conf=fopen(confFile,"w");
	fprintf(conf,"x-res:%d\n",mainDisplayWidth);
	fprintf(conf,"y-res:%d\n",mainDisplayHeight);
	fprintf(conf,"music:%d\n",music);
	fprintf(conf,"sound:%d\n",sound);
	fprintf(conf,"fps:%d\n",(int)FPS);
	fclose(conf);
}

void loadConfFile(FILE *conf){
	char buffer[20];
	char name[10];
	char value[10];
	int i=0;
	int j=0;
	while(!feof(conf)){
		for(i=0;i<10;i++){
			name[i]=0;
			value[i]=0;
		}
		fscanf(conf,"%s\n",buffer);
		for(i=0;i<20;i++){
			if(buffer[i]!=':') name[i]=buffer[i];
			else break;
		}
		i++;
		for(j=-1;i<20;i++){
			j++;
			if(buffer[i]!=0) value[j]=buffer[i];
			else break;
		}
		if(!strcmp(name,"x-res")) mainDisplayWidth=atoi(value);
		if(!strcmp(name,"y-res")) mainDisplayHeight=atoi(value);
		if(!strcmp(name,"music")) music=atoi(value);
		if(!strcmp(name,"sound")) sound=atoi(value);
		if(!strcmp(name,"fps"))	FPS=atoi(value);
	}
}

void writeOptions(ALLEGRO_EVENT ev){
	char buffer[30];
	al_draw_bitmap(menu2,0,0,0);
	al_draw_text(font3, al_map_rgb(204, 204, 204), 260, 30,ALLEGRO_ALIGN_CENTRE, "OPCJE");
	al_draw_text(font, al_map_rgb(204, 204, 204), 50, 150,ALLEGRO_ALIGN_LEFT, "Szerokosc okna:");
	sprintf(buffer,"%d",mainDisplayWidth);
	al_draw_text(font, al_map_rgb(204, 204, 204), 250, 150,ALLEGRO_ALIGN_LEFT, buffer);
	al_draw_text(font, al_map_rgb(204, 204, 204), 50, 180,ALLEGRO_ALIGN_LEFT, "Wysokosc okna:");
	sprintf(buffer,"%d",mainDisplayHeight);
	al_draw_text(font, al_map_rgb(204, 204, 204), 250, 180,ALLEGRO_ALIGN_LEFT, buffer);
	al_draw_text(font, al_map_rgb(204, 204, 204), 50, 210,ALLEGRO_ALIGN_LEFT, "Muzyka:");
	if (music==1) sprintf(buffer,"on");
	else sprintf(buffer,"off");
	al_draw_text(font, al_map_rgb(204, 204, 204), 250, 210,ALLEGRO_ALIGN_LEFT, buffer);
	al_draw_text(font, al_map_rgb(204, 204, 204), 50, 240,ALLEGRO_ALIGN_LEFT, "Odglosy:");
	if (sound==1) sprintf(buffer,"on");
	else sprintf(buffer,"off");
	al_draw_text(font, al_map_rgb(204, 204, 204), 250, 240,ALLEGRO_ALIGN_LEFT, buffer);
	al_draw_text(font, al_map_rgb(204, 204, 204), 50, 270,ALLEGRO_ALIGN_LEFT, "Ilosc klatek /s:");
	sprintf(buffer,"%d",(int)FPS);
	al_draw_text(font, al_map_rgb(204, 204, 204), 250, 270,ALLEGRO_ALIGN_LEFT, buffer);
	al_draw_text(font, al_map_rgb(204, 204, 204), 260, 320,ALLEGRO_ALIGN_CENTRE, "w celu zmiany ustawien");
	al_draw_text(font, al_map_rgb(204, 204, 204), 260, 345,ALLEGRO_ALIGN_CENTRE, "dokonaj modyfikacji pliku konfiguracyjnego");
	al_draw_text(font3, al_map_rgb(204, 204, 204), 260, 450,ALLEGRO_ALIGN_CENTRE, "POWROT");
	al_flip_display();
	while(1){
		al_wait_for_event(eventQueue, &ev);
  		if(ev.type == ALLEGRO_EVENT_TIMER){}
  		else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
     		break;
  		}
  		else if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){
  			if( (ev.mouse.x>145) && (ev.mouse.x<380) ){
	  			if( (ev.mouse.y>455) && (ev.mouse.y<480) )	break;
	  		}
  		}
  		else if(ev.type == ALLEGRO_EVENT_MOUSE_AXES){
  			al_set_system_mouse_cursor(mainDisplay,ALLEGRO_SYSTEM_MOUSE_CURSOR_DEFAULT);
  			if( (ev.mouse.x>145) && (ev.mouse.x<380) ){
	  			if( (ev.mouse.y>455) && (ev.mouse.y<480) )	al_set_system_mouse_cursor(mainDisplay,ALLEGRO_SYSTEM_MOUSE_CURSOR_LINK);
	  		}
  		}
	}

	drowMenu();
}

void drowMenu(){
  	al_draw_bitmap(menu,0,0,0);
  	al_set_system_mouse_cursor(mainDisplay,ALLEGRO_SYSTEM_MOUSE_CURSOR_DEFAULT);
  	al_draw_text(font3, al_map_rgb(204, 204, 204), 260, 150,ALLEGRO_ALIGN_CENTRE, "NOWA GRA");
  	al_draw_text(font3, al_map_rgb(204, 204, 204), 260, 210,ALLEGRO_ALIGN_CENTRE, "OPCJE");
  	al_draw_text(font3, al_map_rgb(204, 204, 204), 260, 280,ALLEGRO_ALIGN_CENTRE, "RANKING");
  	al_draw_text(font3, al_map_rgb(204, 204, 204), 260, 350,ALLEGRO_ALIGN_CENTRE, "WYJSCIE");
  	al_flip_display();
}

int gamePause(ALLEGRO_EVENT ev){
	key[KEY_ESC]=false;
	ALLEGRO_BITMAP *pauseBack=al_load_bitmap(carbonBackground);
	al_draw_tinted_scaled_bitmap(pauseBack,al_map_rgba_f(1,1,1,0.91),0,0,al_get_bitmap_width(pauseBack),al_get_bitmap_height(pauseBack),0,0,mainDisplayWidth,mainDisplayHeight,0);
	al_draw_text(font3, al_map_rgb(204, 204, 204), mainDisplayWidth/2, mainDisplayHeight/2-40,ALLEGRO_ALIGN_CENTRE, "KONTYNUUJ");
  	al_draw_text(font3, al_map_rgb(204, 204, 204), mainDisplayWidth/2, mainDisplayHeight/2+40,ALLEGRO_ALIGN_CENTRE, "WYJSCIE");
	al_set_system_mouse_cursor(mainDisplay,ALLEGRO_SYSTEM_MOUSE_CURSOR_DEFAULT);
	al_show_mouse_cursor(mainDisplay);
	al_flip_display();

	while(1){
		al_wait_for_event(eventQueue, &ev);
		if(ev.type == ALLEGRO_EVENT_TIMER){}
  		else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
     		break;
  		}
  		else if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){
  			if( (ev.mouse.x>mainDisplayWidth/2-90) && (ev.mouse.x<mainDisplayWidth/2+90) ){
	  			if( (ev.mouse.y>mainDisplayHeight/2-40) && (ev.mouse.y<mainDisplayHeight/2-10) ) return 0;
	  			if( (ev.mouse.y>mainDisplayHeight/2+40) && (ev.mouse.y<mainDisplayHeight/2+70) ) return -1;
	  		}
  		}
  		else if(ev.type == ALLEGRO_EVENT_MOUSE_AXES){
  			al_set_system_mouse_cursor(mainDisplay,ALLEGRO_SYSTEM_MOUSE_CURSOR_DEFAULT);
	  		if( (ev.mouse.x>mainDisplayWidth/2-90) && (ev.mouse.x<mainDisplayWidth/2+90) ){
	  			if( (ev.mouse.y>mainDisplayHeight/2-40) && (ev.mouse.y<mainDisplayHeight/2-10) )	al_set_system_mouse_cursor(mainDisplay,ALLEGRO_SYSTEM_MOUSE_CURSOR_LINK);
	  			if( (ev.mouse.y>mainDisplayHeight/2+40) && (ev.mouse.y<mainDisplayHeight/2+70) )	al_set_system_mouse_cursor(mainDisplay,ALLEGRO_SYSTEM_MOUSE_CURSOR_LINK);
	  		}
  		}
  		else if(ev.type == ALLEGRO_EVENT_KEY_DOWN) {
     		switch(ev.keyboard.keycode) {
    			case ALLEGRO_KEY_LEFT: 
       				return 0;
       			break;
       		}
       	}
	}
	return 0;
}

void writeRanking(ALLEGRO_EVENT ev,struct rankList *ranking){
	char buffer[80];
	struct rankList *tmp=NULL;
	int i=0;
	al_draw_bitmap(menu2,0,0,0);
	al_draw_text(font3, al_map_rgb(204, 204, 204), 260, 30,ALLEGRO_ALIGN_CENTRE, "RANKING");
	tmp=ranking;
	while(tmp){
		sprintf(buffer,"%d",tmp->points);
		al_draw_text(font, al_map_rgb(204, 204, 204), 20, 100+(i*32),ALLEGRO_ALIGN_LEFT, tmp->name);
		al_draw_text(font, al_map_rgb(204, 204, 204), 370, 100+(i*32),ALLEGRO_ALIGN_LEFT, buffer);
		i++;
		if(i>=10) break;
		tmp=tmp->next;
	}
	al_draw_text(font3, al_map_rgb(204, 204, 204), 260, 450,ALLEGRO_ALIGN_CENTRE, "POWROT");
	al_flip_display();
	while(1){
		al_wait_for_event(eventQueue, &ev);
  		if(ev.type == ALLEGRO_EVENT_TIMER){}
  		else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
     		break;
  		}
  		else if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){
  			if( (ev.mouse.x>145) && (ev.mouse.x<380) ){
	  			if( (ev.mouse.y>455) && (ev.mouse.y<480) )	break;
	  		}
  		}
  		else if(ev.type == ALLEGRO_EVENT_MOUSE_AXES){
  			al_set_system_mouse_cursor(mainDisplay,ALLEGRO_SYSTEM_MOUSE_CURSOR_DEFAULT);
  			if( (ev.mouse.x>145) && (ev.mouse.x<380) ){
	  			if( (ev.mouse.y>455) && (ev.mouse.y<480) )	al_set_system_mouse_cursor(mainDisplay,ALLEGRO_SYSTEM_MOUSE_CURSOR_LINK);
	  		}
  		}
	}

	drowMenu();
}

struct rankList *rankDestroy(){
	struct rankList *tmp=NULL;
	while(ranking){
		tmp=ranking;
		ranking=ranking->next;
		free(tmp);
	}
	return NULL;
}

struct rankList *rankAdd(struct rankList *ranking,char name[],int points){
	struct rankList *nowy=NULL;
	struct rankList *tmp=NULL;
	nowy=malloc(sizeof(*nowy));
	strcpy(nowy->name,name);
	nowy->points=points;
	nowy->next=NULL;
	if (!ranking){
		ranking=nowy;
	}
	else{
		tmp=ranking;
		if(nowy->points>=ranking->points){
			nowy->next=ranking;
			ranking=nowy;
		}
		else{
			while(tmp->next){
				if(nowy->points>=tmp->next->points){
					nowy->next=tmp->next;
					tmp->next=nowy;
					break;
				}
				tmp=tmp->next;
			}
			tmp->next=nowy;
		}
	}
	return ranking;
}

void loadRanking(FILE *rankFile){
	char buffer[60];
	char name[40];
	char value[20];
	int i=0;
	int j=0;
	while(!feof(rankFile)){
		for(i=0;i<40;i++) name[i]=0;
		for(i=0;i<20;i++) value[i]=0;

		fscanf(rankFile,"%s\n",buffer);
		if(buffer[0]==0) break;
		for(i=0;i<40;i++){
			if(buffer[i]!=':') name[i]=buffer[i];
			else break;
		}
		i++;
		for(j=-1;j<20;i++){
			j++;
			if(buffer[i]!=0) value[j]=buffer[i];
			else break;
		}
		ranking=rankAdd(ranking,name,atoi(value));
	}
}



int writeEnd(int tryb,ALLEGRO_EVENT ev,FILE *rankFile){
	char name[30];
	int i=0;
	ALLEGRO_BITMAP *pauseBack=al_load_bitmap(carbonBackground);
	al_draw_scaled_bitmap(pauseBack,0,0,al_get_bitmap_width(pauseBack),al_get_bitmap_height(pauseBack),0,0,mainDisplayWidth,mainDisplayHeight,0);
	
	for(i=0;i<30;i++) name[i]=0;
	i=0;

	if(tryb==0)
		al_draw_text(font3, al_map_rgb(204, 204, 204), mainDisplayWidth/2, mainDisplayHeight/2-40,ALLEGRO_ALIGN_CENTRE, "NIESTETY... POLEGLES :(");
  	if(tryb==1)
  		al_draw_text(font3, al_map_rgb(204, 204, 204), mainDisplayWidth/2, mainDisplayHeight/2-40,ALLEGRO_ALIGN_CENTRE, "GRATULACJE, WYGRALES!!!");
  	if(tryb==2)
  		 al_draw_text(font3, al_map_rgb(204, 204, 204), mainDisplayWidth/2, mainDisplayHeight/2-40,ALLEGRO_ALIGN_CENTRE, "PODDAŁEŚ SIĘ, KONIEC GRY!!!");

  	al_draw_text(font2, al_map_rgb(204, 204, 204), mainDisplayWidth/2, mainDisplayHeight/2+40,ALLEGRO_ALIGN_CENTRE, "Wpisz swoje imie, aby kontynuować");
	al_draw_text(font3, al_map_rgb(204, 204, 204), mainDisplayWidth/2, mainDisplayHeight/2+250,ALLEGRO_ALIGN_CENTRE, "ZAPISZ MOJ WYNIK");
	al_set_system_mouse_cursor(mainDisplay,ALLEGRO_SYSTEM_MOUSE_CURSOR_DEFAULT);
	al_show_mouse_cursor(mainDisplay);
	al_flip_display();
	while(1){
		al_wait_for_event(eventQueue, &ev);
		if(ev.type == ALLEGRO_EVENT_TIMER){}
  		else if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){
  			if( (ev.mouse.x>mainDisplayWidth/2-150) && (ev.mouse.x<mainDisplayWidth/2+150) ){
	  			if( (ev.mouse.y>mainDisplayHeight/2+250) && (ev.mouse.y<mainDisplayHeight/2+290) ) {
	  				ranking=rankAdd(ranking,name,(int)myCraft.points);	
	  				rankFile=fopen(rankFileSrc,"a+");
	  				if(rankFile){
	  					fprintf(rankFile, "%s:%d\n",name,(int)myCraft.points);
	  					fclose(rankFile);
	  				}
	  				return -1;
	  			}
	  		}
  		}
  		else if(ev.type == ALLEGRO_EVENT_MOUSE_AXES){
  			al_set_system_mouse_cursor(mainDisplay,ALLEGRO_SYSTEM_MOUSE_CURSOR_DEFAULT);
	  		if( (ev.mouse.x>mainDisplayWidth/2-150) && (ev.mouse.x<mainDisplayWidth/2+150) ){
	  			if( (ev.mouse.y>mainDisplayHeight/2+250) && (ev.mouse.y<mainDisplayHeight/2+290) )	al_set_system_mouse_cursor(mainDisplay,ALLEGRO_SYSTEM_MOUSE_CURSOR_LINK);
	  		}
  		}
  		else if(ev.type == ALLEGRO_EVENT_KEY_CHAR){
  			char unichar = (char)ev.keyboard.unichar;
  			if((int)unichar>32 && i<30){
  				name[i]=(char)unichar;
  				i++;
  			}
  			if( (unichar==8) && (i>=1) ){
  				i--;
  				name[i]=0;
  			}
  			al_draw_scaled_bitmap(pauseBack,0,0,al_get_bitmap_width(pauseBack),al_get_bitmap_height(pauseBack),0,0,mainDisplayWidth,mainDisplayHeight,0);
  			if(tryb==0)
				al_draw_text(font3, al_map_rgb(204, 204, 204), mainDisplayWidth/2, mainDisplayHeight/2-40,ALLEGRO_ALIGN_CENTRE, "NIESTETY... POLEGLES :(");
  			if(tryb==1)
  				al_draw_text(font3, al_map_rgb(204, 204, 204), mainDisplayWidth/2, mainDisplayHeight/2-40,ALLEGRO_ALIGN_CENTRE, "GRATULACJE, WYGRALES!!!");
  			if(tryb==2)
  		 		al_draw_text(font3, al_map_rgb(204, 204, 204), mainDisplayWidth/2, mainDisplayHeight/2-40,ALLEGRO_ALIGN_CENTRE, "PODDAŁEŚ SIĘ, KONIEC GRY!!!");
			
			al_draw_text(font2, al_map_rgb(204, 204, 204), mainDisplayWidth/2, mainDisplayHeight/2+40,ALLEGRO_ALIGN_CENTRE, "Wpisz swoje imie, aby kontynuować");
			al_draw_text(font3, al_map_rgb(204, 204, 204), mainDisplayWidth/2, mainDisplayHeight/2+250,ALLEGRO_ALIGN_CENTRE, "ZAPISZ MOJ WYNIK");
  			al_draw_text(font3, al_map_rgb(204, 204, 204), mainDisplayWidth/2, mainDisplayHeight/2+100,ALLEGRO_ALIGN_CENTRE, name);
  			al_flip_display();
  		}
	}
	return 0;
}