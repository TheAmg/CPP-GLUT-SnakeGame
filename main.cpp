#include <ctime>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <iostream>
#include <stdlib.h>

#define snakeMaxLength 60

int FPSCAP=10;
bool isGameOver=false;
int gridX,gridY;
float gridSize=50;
int UP=1,DOWN=-1,LEFT=-2,RIGHT=2;
int snakePosX[snakeMaxLength]={gridSize/2,gridSize/2,gridSize/2,gridSize/2,gridSize/2};
int snakePosY[snakeMaxLength]={gridSize/2,gridSize/2-1,gridSize/2-2,gridSize/2-3,gridSize/2-4};
int snakeDir=2;
bool spawnFood=true;
int targetX,targetY;
int snakelength=5;
int points=0;


void drawGrid();
void updateGame();
void screenReshape(int,int);
void timerFunction(int);
void playerInput(int,int,int);
void drawSnake();
void drawTarget();

void initGrid(int x,int y)
{
    gridX=x;
    gridY=y;
}
void Cinit()
{
    glClearColor(1.0,1.0,1.0,1.0);
    initGrid(gridSize,gridSize);
}

int main(int argc,char**argv)
{
glutInit(&argc,argv);
glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
glutInitWindowPosition(100,100);
glutInitWindowSize(500,500);
glutCreateWindow("Snake game");

glutDisplayFunc(updateGame);
glutReshapeFunc(screenReshape);
glutSpecialFunc(playerInput);
glutTimerFunc(0,timerFunction,0);

Cinit();
glutMainLoop();
return 0;
}

void updateGame()
{
    glClear(GL_COLOR_BUFFER_BIT);

    drawGrid();
    drawSnake();
    drawTarget();
    glutSwapBuffers();
    if(isGameOver)
    {
      char scr[10];
      itoa(points,scr,10);
      char msg[25]="you scored: ";
      strcat(msg,scr);
      MessageBox(NULL,msg,"Game Over",0);
    exit(0);
    }
}
void screenReshape(int w, int h)
{
glViewport(0,0,(GLsizei)w,(GLsizei)h);
glMatrixMode(GL_PROJECTION);
glLoadIdentity();

glOrtho(0.0,gridSize,0.0,gridSize,-1.0,1.0);

glMatrixMode(GL_MODELVIEW);

}
void drawUnitSquare(int x, int y)
{
        if(x==0||x==gridSize-1||y==0||y==gridSize-1){
            glLineWidth(2.0f);
            glColor3f(1.0,0.0,0.0);
        }else{
            glLineWidth(1.0f);
            glColor3f(0.0,0.0,0.0);
        }


    glBegin(GL_LINE_LOOP);
    glVertex2i(x,y);
    glVertex2i(x+1,y);
    glVertex2i(x+1,y+1);
    glVertex2i(x,y+1);
    glEnd();
}
void drawGrid()
{
for(int i=0;i<gridSize;i++){
    for(int j=0;j<gridSize;j++){
        drawUnitSquare(i,j);
    }
}
}
void timerFunction(int)
{
    glutPostRedisplay();
    glutTimerFunc(1000/FPSCAP,timerFunction,0);
}
void changeSnakeDirection(int dir)
{
    if(snakeDir!=(-1*dir)){
        snakeDir=dir;
    }else{

    }

}
void playerInput(int key,int,int)
{
    switch(key)
    {
    case GLUT_KEY_DOWN:
        changeSnakeDirection(-1);
        break;
    case GLUT_KEY_UP:
        changeSnakeDirection(1);
        break;
    case GLUT_KEY_LEFT:
        changeSnakeDirection(-2);
        break;
    case GLUT_KEY_RIGHT:
        changeSnakeDirection(2);
        break;
    }

}
void drawSnake()
{
    for(int i=snakelength-1;i>0;i--)
    {
        snakePosX[i]=snakePosX[i-1];
        snakePosY[i]=snakePosY[i-1];
    }

    if(snakeDir==UP)
    {
        snakePosY[0]++;
    }else if(snakeDir==DOWN)
    {
        snakePosY[0]--;
    }else if(snakeDir==LEFT)
    {
        snakePosX[0]--;
    }else
    {
        snakePosX[0]++;
    }

    for(int i=0;i<snakelength;i++){
            if(i==0){
                glColor3f(0.2,0.2,0.2);
            }else
            {
                glColor3f(0.0,0.8,0.4);
            }

        glRectd(snakePosX[i],snakePosY[i],snakePosX[i]+1,snakePosY[i]+1);
    }

 if(snakePosX[0]==targetX && snakePosY[0]==targetY)
{
  //std::cout<<"+1"<<"\n";
  points++;
  if(snakelength<snakeMaxLength)
  {
    snakelength++;
  }else
  {
  }
  spawnFood=true;
}
 if(snakePosX[0]==0||snakePosX[0]==gridSize-1||snakePosY[0]==0||snakePosY[0]==gridSize-1)
{
  isGameOver=true;
}
for(int i=1;i<snakelength;i++){
    if(snakePosX[0]==snakePosX[i] && snakePosY[0]==snakePosY[i])
    {
        isGameOver=true;
    }
}

}
int generateRandomNumber()
{
   int ret=1;
   srand(time(NULL));
   int modV=gridSize-2-1;
   ret = 1 + rand()% modV;
   return ret;

}
void drawTarget()
{
   if(spawnFood)
   {
      targetX=generateRandomNumber();
      targetY=generateRandomNumber();
      spawnFood=false;
     // std::cout<<"new position: "<<targetX<<targetY<<"\n";
   }

      glColor3f(1.0,0.0,0.0);
      glRectd(targetX,targetY,targetX+1,targetY+1);

}
