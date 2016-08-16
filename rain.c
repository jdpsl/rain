// rain.c

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>

char* wipe=" ";
char* characters[16]={"0","1","2","3","4","5","6","7","8","9","A","B","C","D","E","F"};

char* allchars[72]={"a","b","c","d","e","f","g","h","i","j","k","l","m","n","o","p","q","r","s","t","u","v","w","x","y","z","A","B","C","D","E","F","G","H","I","J","K","L","M","N","O","P","Q","R","S","T","U","V","W","X","Y","Z","0","1","2","3","4","5","6","7","8","9","!","@","#","$","%","^","&","*","(",")"};

char* splay[100][200];

int glyph_x[200];
int glyph_y[200];
int glyph_life[200];
int glyph_alive[200];
char* glyph_chars[200];
int glyph_life[200];
int glyph_erase[200];

int w=80,h=20;


// Game Code

void RandGlyphs(){
  int i;
  for (i=0;i<200;i++){
    if (glyph_erase[i]){
      glyph_chars[i]=" ";
    }else{
      glyph_chars[i]=allchars[rand()%72];
    }
  }
}

void NewGlyph(){
  int i;
  for (i=0;i<200;i++){
    if (!glyph_alive[i]){
      glyph_erase[i]=0;
      glyph_x[i]=rand()%w;
      if (rand()%9){
        glyph_y[i]=rand()%h;
      }else{
        glyph_y[i]=0;
      }
      if (!(rand()%3)){
        glyph_erase[i]=1;
      }
      glyph_life[i]=(rand()%12)+6;
      glyph_alive[i]=1;
      break;
    }
  }
}

void StepGlyphs(){
  int i;
  for (i=0;i<200;i++){
    if (glyph_alive[i]){
      glyph_y[i]++;
      glyph_life[i]--;
      if (glyph_y[i] > h || glyph_life[i] <= 0){
        glyph_alive[i]=0;
      }
    }
  }
}

void InitGame(){
  int y,x,i;
  RandGlyphs();

  for (i=0;i<200;i++){
    glyph_alive[i]=0;
  }

  for (y=0;y<h;y++){
    for (x=0;x<w;x++){
      splay[y][x]=" ";
    }
  }
}

void DrawGlyphs(){
  int i;
  for (i=0;i<200;i++){
    if (glyph_alive[i]){
      splay[glyph_y[i]][glyph_x[i]]=glyph_chars[i];
    }
  }
}

void GameTick(){
  DrawGlyphs();
  RandGlyphs();
  StepGlyphs();
}

void GameSleep(){
}

// Splay Code

void SplayClear(){
  int x,y;
  for (y=0;y<h;y++){
    for (x=0;x<w;x++){
      splay[y][x]=" ";
    }
  }
}

void RenderTick(){
  int y,x;
  printf("\n");

  for (y=0;y<h;y++){
    for (x=0;x<w;x++){
      printf("%s",splay[y][x]);
    }
  printf("\n");
  }
}


int main(int argc, char** argv){
  int tick=0;

  if (argc != 3){
    w=80;
    h=23;
  }else{
    w=atoi(argv[1]);
    h=atoi(argv[2]);
  }

  printf("%s",argv[1]);

  char buf [33];
  int x,y,i,c,a=1;
  InitGame();

  while (a){
    clock_t endwait;
    endwait=clock()+(CLOCKS_PER_SEC)*0.1;
    
    while (clock() < endwait){
      GameSleep();
    }
    tick++;
    if (!(tick%3)){
      for (i=0;i<13;i++){
        NewGlyph();
      }
    }
    if (!(tick%1000)){
      tick=1;
    }
    GameTick();
    RenderTick();     
  }
}
