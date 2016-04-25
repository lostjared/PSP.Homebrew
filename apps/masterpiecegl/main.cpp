/***************************************************************************
                          main.cpp  -  description
                             -------------------
    begin                : Sun Aug 10 19:31:53 EDT 2003
    written by           :  jared bruni
    email                :  jared@lostsidedead.com
    to compile           :  g++ main.cpp -B /usr/X11R6/lib -o mp3d -lX11 -lXi -lXmu -lglut -lGL -lGLU -ljpeg -lm -lpthread
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/


#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include"platform.h"
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<GL/gl.h>
#include<GL/glu.h>
#include<GL/glut.h>
#ifdef FOR_PSP
#include<pspctrl.h>
#endif

void initgl(int width, int height);
void resize(int width, int height);
void render();
void keydown(unsigned char key, int x, int y);
void specialkey(int key, int x, int y);
void releaseblock();
void moveleft();
void moveright();
void movedown();
void shiftup();
void shiftdown();
void procblocks();
void checkformovedown();
void clearboard();

enum COLOR { BLACK = 0, WHITE, RED, GREEN, BLUE, GRAY };


struct block {

  float r,g,b;
  COLOR color;

  block()    
  {
    color = BLACK;
    r = 0.0f;
    g = 0.0f;
    b = 0.0f;
  }
  
  inline void copyblock(struct block *g_block )
  {
    color = g_block->color;
    r = g_block->r;
    g = g_block->g;
    b = g_block->b;
  }

  inline void clear()
  {
    color = BLACK;
    r = 0.0f;
    g = 0.0f;
    b = 0.0f;
  }

};

struct gameblock : block {

  int x,y;

  gameblock()
  {
    color = BLACK;
    r = 0.0f;
    g = 0.0f;
    b = 0.0f;
    x = 0;
    y = 0;
  }
  
  inline void randcolor()
  {
    switch(rand()%5)
    {
      case 0:
      r = 1.0f;
      g = 0.0f;
      b = 0.0f;
      color = RED;
      break;
      case 1:
      r = 0.0f;
      g = 1.0f;
      b = 0.0f;
      color = GREEN;
      break;      
      case 2:
      r = 0.0f;
      g = 0.0f;
      b = 1.0f;
      color = BLUE;
      break;
      case 3:
      r = 1.0f;
      g = 1.0f;
      b = 1.0f;
      color = WHITE;
      break;
      case 4:
      case 5:
      r = .5f;
      g = .5f;
      b = .5f;
      color = GRAY;
      break;
    }
  }

};

struct block tiles[17][8];
struct gameblock gblock[3];

float rquad = 0.0f, r_quad = 0.0f;
int wnd = 0, i = 0,z = 0, p = 0,score = 0;
#ifdef FOR_PSP
SceCtrlData pad;
#endif

	
int main(int argc, char * argv[])
{
    srand(time(0));
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_ALPHA | GLUT_DEPTH);
    glutInitWindowSize(480, 272);
    glutInitWindowPosition(0, 0);
    wnd = glutCreateWindow("MasterPiece 3D");
    glutDisplayFunc(&render);
    //glutFullScreen();
    glutIdleFunc(&render);
    glutReshapeFunc(&resize);
    glutKeyboardFunc(&keydown);
    glutSpecialFunc(&specialkey);
    initgl(640, 480);
    releaseblock();
#ifdef FOR_PSP
   	sceCtrlSetSamplingCycle(0);
	sceCtrlSetSamplingMode(PSP_CTRL_MODE_ANALOG);	
#endif
    glutMainLoop();
    return (0);
}

void initgl(int width, int height)
{
  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
  glClearDepth(1.0);
  glDepthFunc(GL_LESS);
  glEnable(GL_DEPTH_TEST);
  glShadeModel(GL_SMOOTH);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(45.0f,(float)width/(float)height,0.1f,100.0f);
  glMatrixMode(GL_MODELVIEW);
}

void resize(int width, int height)
{
    if (height==0)
    height=1;
  glViewport(0, 0, width, height);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  gluPerspective(45.0f,(float)width/(float)height,0.1f,100.0f);
  glMatrixMode(GL_MODELVIEW);
}

void proc_ctrl() {
     #ifdef FOR_PSP
     static int counter = 0;
     
     if(++counter % 4 == 0) {
         sceCtrlReadBufferPositive(&pad, 1); 
         if(pad.Buttons & PSP_CTRL_CROSS) {
              shiftdown();               
         }
         if(pad.Buttons & PSP_CTRL_SQUARE) 
              shiftup();
        
        if(pad.Buttons & PSP_CTRL_LEFT)
        moveleft();
        if(pad.Buttons & PSP_CTRL_RIGHT)
        moveright();
        if(pad.Buttons & PSP_CTRL_DOWN)
        movedown();
        if(pad.Buttons & PSP_CTRL_LTRIGGER)
        rquad -= 0.5f;
        if(pad.Buttons & PSP_CTRL_RTRIGGER)
        rquad += 0.5f;
        if(pad.Buttons & PSP_CTRL_CIRCLE)
        r_quad += 0.5f;
        if(pad.Buttons & PSP_CTRL_TRIANGLE)
        r_quad -= 0.5f;
        
     }     
     #endif
}

void render()
{
     #ifdef FOR_PSP
     proc_ctrl();
     #endif
    checkformovedown();
    procblocks();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();

    glTranslatef(-10.0f,15.0f,-45.0f);

    glRotatef(rquad,1.0f,0.0f,0.0f);
    glRotatef(r_quad,0.0f,1.0f,0.0f);

    //draw the board
    for(i = 0; i < 17; i++)
    {

      for(z = 0; z < 8; z++)
      {
        for(p = 0; p < 3; p++)
        {

        // draw the current game block 
        if(gblock[p].x == z && gblock[p].y == i)
        {
            glBegin(GL_QUADS);

            glColor3f(gblock[p].r + .3f, gblock[p].g + .3f, gblock[p].b + .3f);
            glVertex3f( 1.0f, 1.0f,-1.0f);
            glVertex3f(-1.0f, 1.0f,-1.0f);
            glVertex3f(-1.0f, 1.0f, 1.0f);
            glVertex3f( 1.0f, 1.0f, 1.0f);

            glColor3f(gblock[p].r + .3f, gblock[p].g + .3f, gblock[p].b + .3f);
            glVertex3f( 1.0f,-0.5f, 1.0f);
            glVertex3f(-1.0f,-0.5f, 1.0f);
            glVertex3f(-1.0f,-0.5f,-1.0f);
            glVertex3f( 1.0f,-0.5f,-1.0f);

            glColor3f(gblock[p].r,gblock[p].g,gblock[p].b);
            glVertex3f( 1.0f, 1.0f, 1.0f);
            glVertex3f(-1.0f, 1.0f, 1.0f);
            glVertex3f(-1.0f,-.5f, 1.0f);
            glVertex3f( 1.0f,-.5f, 1.0f);

            glColor3f(gblock[p].r + .2f,gblock[p].g + .2f,gblock[p].b + .2f);
            glVertex3f( 1.0f,-.5f,-1.0f);
            glVertex3f(-1.0f,-.5f,-1.0f);
            glVertex3f(-1.0f, 1.0f,-1.0f);
            glVertex3f( 1.0f, 1.0f,-1.0f);

            glColor3f(gblock[p].r + .1f, gblock[p].g + .1f,gblock[p].b + .1f);
            glVertex3f(-1.0f, 1.0f,1.0f);
            glVertex3f(-1.0f, 1.0f,-1.0f);
            glVertex3f(-1.0f, -0.5f,-1.0f);
            glVertex3f(-1.0f, -0.5f, 1.0f);

            glVertex3f(1.0f,1.0f,1.0f);
            glVertex3f(1.0f,1.0f,-1.0f);
            glVertex3f(1.0f,-0.5f,-1.0f);
            glVertex3f(1.0f,-0.5f,1.0f);

            glEnd();
        }

      }
      
        // draw the rest of the blocks
        if(tiles[i][z].color != BLACK)
        {
            glBegin(GL_QUADS);

            glColor3f(tiles[i][z].r + .3f, tiles[i][z].g + .3f, tiles[i][z].b + .3f);
            glVertex3f( 1.0f, 1.0f,-1.0f);
            glVertex3f(-1.0f, 1.0f,-1.0f);
            glVertex3f(-1.0f, 1.0f, 1.0f);
            glVertex3f( 1.0f, 1.0f, 1.0f);

            glColor3f(tiles[i][z].r + .3f, tiles[i][z].g + .3f, tiles[i][z].b + .3f);
            glVertex3f( 1.0f,-0.5f, 1.0f);
            glVertex3f(-1.0f,-0.5f, 1.0f);
            glVertex3f(-1.0f,-0.5f,-1.0f);
            glVertex3f( 1.0f,-0.5f,-1.0f);

            glColor3f(tiles[i][z].r,tiles[i][z].g,tiles[i][z].b);
            glVertex3f( 1.0f, 1.0f, 1.0f);
            glVertex3f(-1.0f, 1.0f, 1.0f);
            glVertex3f(-1.0f,-.5f, 1.0f);
            glVertex3f( 1.0f,-.5f, 1.0f);

            glColor3f(tiles[i][z].r + .2f,tiles[i][z].g + .2f,tiles[i][z].b + .2f);
            glVertex3f( 1.0f,-.5f,-1.0f);
            glVertex3f(-1.0f,-.5f,-1.0f);
            glVertex3f(-1.0f, 1.0f,-1.0f);
            glVertex3f( 1.0f, 1.0f,-1.0f);

            glColor3f(tiles[i][z].r + .1f, tiles[i][z].g + .1f,tiles[i][z].b + .1f);
            glVertex3f(-1.0f, 1.0f,1.0f);
            glVertex3f(-1.0f, 1.0f,-1.0f);
            glVertex3f(-1.0f, -0.5f,-1.0f);
            glVertex3f(-1.0f, -0.5f, 1.0f);

            glVertex3f(1.0f,1.0f,1.0f);
            glVertex3f(1.0f,1.0f,-1.0f);
            glVertex3f(1.0f,-0.5f,-1.0f);
            glVertex3f(1.0f,-0.5f,1.0f);

            glEnd();

          }
          glTranslatef(3.0f,0.0f,0.0f);
       }

      glTranslatef(-24.0,-2.0,0.0f);

    }

    glutSwapBuffers();
  
}



void keydown(unsigned char key, int x, int y)
 {
     #ifndef FOR_PSP
     switch(key)
     {
     case 27:
     {
// 	    glutDestroyWindow(wnd);
 	    exit(0);
 	   }
     break;
     case 'x':
     case 'A':
     shiftup();
     break;
     case 'S':
     case 'd':
     shiftdown();
     break;
      case 'l':
	   {
	       rquad += 0.5;
	   }
	   break;
     case 'r':
	   {

	       rquad -= 0.5;
	   }
	   break;
     case 'o':
	   {
	       r_quad -= 0.5f;
     }
	   break;
     case 's':
	   {
	       r_quad += 0.5f;
	   }
	   break;
     }
     #endif
 }
 
 void keyup(unsigned char key, int x, int y) {
 }

void specialkey(int key, int x, int y)
{
#ifndef FOR_PSP
     switch(key)
     {
    
     case GLUT_KEY_UP:
     {
       releaseblock();
     }
     break;
     case GLUT_KEY_DOWN:
     {
       movedown();
     }
     break;
     case GLUT_KEY_LEFT:
     {
       moveleft();
     }
     break;
     case GLUT_KEY_RIGHT:
     {
       moveright();
     }
     break;
     }
#endif
     
}

void releaseblock()
{
do
{
  gblock[0].randcolor();
  gblock[1].randcolor();
  gblock[2].randcolor();
}
while(gblock[0].color == gblock[1].color && gblock[0].color == gblock[2].color);

  gblock[0].x = 3;
  gblock[0].y = 0;
  gblock[1].x = 3;
  gblock[1].y = 1;
  gblock[2].x = 3;
  gblock[2].y = 2;
  
}

void moveleft()
{
  if(gblock[0].x > 0 && tiles[gblock[0].y][gblock[0].x-1].color == BLACK && tiles[gblock[1].y][gblock[1].x-1].color == BLACK && tiles[gblock[2].y][gblock[2].x-1].color == BLACK)
  {
     gblock[0].x--;
     gblock[1].x--;
     gblock[2].x--;
  }
}

void moveright()
{
  if(gblock[0].x < 7 && tiles[gblock[0].y][gblock[0].x+1].color == BLACK && tiles[gblock[1].y][gblock[1].x+1].color == BLACK && tiles[gblock[2].y][gblock[2].x+1].color == BLACK)
  {
    gblock[0].x++;
    gblock[1].x++;
    gblock[2].x++;
  }
}

void movedown()
{
  if(gblock[2].y < 16)
  {
    if(tiles[gblock[2].y+1][gblock[2].x].color != BLACK)
    {
      tiles[gblock[2].y][gblock[2].x].copyblock(&gblock[2]);
      tiles[gblock[1].y][gblock[1].x].copyblock(&gblock[1]);
      tiles[gblock[0].y][gblock[0].x].copyblock(&gblock[0]);
      if(gblock[2].y < 3)
      {
        clearboard();
        printf("game over\nyour score: %i\n", score);
      }
      else
      releaseblock();
      
    }  
    else
    {
      gblock[0].y++;
      gblock[1].y++;
      gblock[2].y++;
    }
  }
  else
  {
    tiles[gblock[2].y][gblock[2].x].copyblock(&gblock[2]);
    tiles[gblock[1].y][gblock[1].x].copyblock(&gblock[1]);
    tiles[gblock[0].y][gblock[0].x].copyblock(&gblock[0]);
    releaseblock();
  }
}

void shiftup()
{
  struct gameblock g_block;
  g_block = gblock[0];
  gblock[0].copyblock(&gblock[1]);
  gblock[1].copyblock(&gblock[2]);
  gblock[2].copyblock(&g_block);
}

void shiftdown()
{
  struct gameblock g_block;
  g_block = gblock[0];
  gblock[0].copyblock(&gblock[2]);
  gblock[2].copyblock(&gblock[1]);
  gblock[1].copyblock(&g_block);
}

void procblocks()
{

  for(i = 0; i < 17; i++)
  {
    for(z = 0; z < 8; z++)
    {
      COLOR cur_color = tiles[i][z].color;

      if(cur_color != BLACK)
      {
        if(z+2 < 8)
        {
          if(tiles[i][z+1].color == cur_color && tiles[i][z+2].color == cur_color)
          {
            tiles[i][z].clear();
            tiles[i][z+1].clear();
            tiles[i][z+2].clear();
            score += 5;
            return;
          }
        }

        if(z+3 < 8)
        {
          if(tiles[i][z+1].color == cur_color && tiles[i][z+2].color == cur_color && tiles[i][z+3].color == cur_color)
          {
            tiles[i][z].clear();
            tiles[i][z+1].clear();
            tiles[i][z+2].clear();
            tiles[i][z+3].clear();
            score += 7;
            return;
          }
       }

        if(i+2 < 17)
        {
          if(tiles[i+1][z].color == cur_color && tiles[i+2][z].color == cur_color)
          {
            tiles[i][z].clear();
            tiles[i+1][z].clear();
            tiles[i+2][z].clear();
            score += 5;
            return;
          }
        }
        
        if(i+3 < 17)
        {
          if(tiles[i+1][z].color == cur_color && tiles[i+2][z].color == cur_color)
          {
            tiles[i][z].clear();
            tiles[i+1][z].clear();
            tiles[i+2][z].clear();
            tiles[i+3][z].clear();
            score += 7;
            return;
          }
        }
      }
      
    }
  }

  for(z = 0; z < 8; z++)
  {
    for(i = 0; i < 17; i++)
    {
      COLOR cur_color = tiles[i][z].color;
      if(cur_color != BLACK)
      {
        if(i+2 < 17 && z+2 < 8)
        {
          
          if(tiles[i+1][z+1].color == cur_color && tiles[i+2][z+2].color == cur_color)
          {
            tiles[i][z].clear();
            tiles[i+1][z+1].clear();
            tiles[i+2][z+2].clear();
            score += 10;
            return;
          }

        }
        if(i-2 >= 0 && z-2 >= 0)
        {
          if(tiles[i-1][z-1].color == cur_color && tiles[i-2][z-2].color == cur_color)
          {
            tiles[i][z].clear();
            tiles[i-1][z-1].clear();
            tiles[i-2][z-2].clear();
            score += 10;
            return;
          }
        }

        if(i-2 >= 0)
        {
          if(tiles[i-1][z+1].color == cur_color && tiles[i-2][z+2].color == cur_color)
          {
            tiles[i][z].clear();
            tiles[i-1][z+1].clear();
            tiles[i-2][z+2].clear();
            score += 10;
            return;
          }
        }

        if(z-2 >= 0)
        {
          if(tiles[i+1][z-1].color == cur_color && tiles[i+2][z-2].color == cur_color)
          {
            tiles[i][z].clear();
            tiles[i+1][z-1].clear();
            tiles[i+2][z-2].clear();
            score += 10;
            return;            
          }
        }
            
      }
    }
  }
  
  for(z = 0; z < 8; z++)
  {
    for(i = 0; i < 16; i++)
    {
      if(tiles[i][z].color != BLACK && tiles[i+1][z].color == BLACK)
      {
        tiles[i+1][z] = tiles[i][z];
        tiles[i][z].clear();
      }
    }
  }
  
   
}

void checkformovedown()
{
  time_t t = time(0);
  static time_t st_t = time(0);
  if(t > st_t)
  {
    movedown();
    st_t = t;
  }
}

void clearboard()
{
  for(i = 0; i < 17; i++)
  {
    for(z = 0; z < 8; z++)
    {
      tiles[i][z].clear();
    }
  }
}



