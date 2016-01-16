#include <time.h>
#include "glutSetup.h"
#include "glm.h"
#include <vector>
#include <math.h>
#include "tga.h"
#include "camera.h"
#include "userTank.h"
#include "enemyTankMovement.h"
#include <iostream>
using namespace std;



int screen_width = 800, screen_height = 500; //set the default variables for the size of the screen
float aspect = (float)screen_width/screen_height;
GLMmodel *model[2];

// file name for each model
char *ModelName[2] = {"objects/Tank_noGun.obj","objects/Tank_MainGun.obj"}; //gun must be a separate object from the rest of the tank since it moves individually
int ModelID = 0;
GLuint textureArray[10]; //support up to 10 textures

//initialize the first position of the user's tank
double tankPosX = 0; 
double tankPosY = 0;
double tankPosZ = 0;
double spin = 270;
double gunRotateX = 0, gunRotateY = 0;
double hitPoints = 3;
//initialize the first position of the windmillsails
double windmillSpin = 0;

//initialize the bird's eye view bool
bool birdseye = false;

//create our camera and keep track of where the user tank goes
CCamera Camera;
userTank playerTank;

//the enemyBulletClass keeps track of the enemies' bullets that they fire
class EnemyBulletClass{
public:
  GLfloat bulletPosX, bulletPosY, bulletPosZ;
  double localxDegree;
  double localyDegree;
  double zRatio;
  double xRatio;
  double yRatio;

  // constructor - where the round starts
  EnemyBulletClass(double enemySpin, double enemyGunRotateX, double enemyGunRotateY,  
  double enemyTankPosX, double enemyTankPosY, double enemyTankPosZ){

	localxDegree = enemySpin-enemyGunRotateX;
    localyDegree = enemyGunRotateY+90;
    bulletPosX = enemyTankPosX+cos((enemySpin*PI*2)/360)*1; 
	bulletPosY = enemyTankPosY; 
	bulletPosZ = enemyTankPosZ+sin((enemySpin*PI*2)/360)*1;
	
	if (localxDegree>=180 && localxDegree <=270){
		if (localxDegree-180 == 0)
			zRatio = 0;
		else
			zRatio = ((localxDegree-180)*1)/90;
		xRatio = -(1-zRatio);
		zRatio = -zRatio;
	}
	else if (localxDegree>270 && localxDegree<360){
		xRatio = ((localxDegree-270)*1)/90;
		zRatio = -(1-xRatio);
	}
	else if (localxDegree>=0 && localxDegree<=90){
		if(localxDegree-0 == 0)
			zRatio = 0;
		else
			zRatio = ((localxDegree-0)*1)/90;
		xRatio = 1-zRatio;
	}
	else if (localxDegree>90 && localxDegree<180){
		xRatio = ((localxDegree-90)*1)/90;
		zRatio = 1-xRatio;
		xRatio = -xRatio;
	}
	if (localyDegree > 90)
		yRatio = -(((localyDegree-90)*1)/90);
	else if (localyDegree == 90)
		yRatio = 0;
	else if (localyDegree < 90)
		yRatio = 1-(((localyDegree)*1)/90);
  }

  // draw the bullet
  void draw() {
	glColor3f(0,0,1);
    glPushMatrix();
    glTranslatef(bulletPosX, bulletPosY, bulletPosZ);
    glutSolidSphere(.25,300,20);
    glPopMatrix();
  }

  int hits() {
    // if we're within the hit box of the user's tank, call it a hit
    if (bulletPosX < tankPosX+0.4 &&  bulletPosX > tankPosX-0.4 &&
		bulletPosY < tankPosY+0.15 &&  bulletPosY > tankPosY-0.15 &&
		bulletPosZ < tankPosZ+0.65 &&  bulletPosZ > tankPosZ-0.65)
      return 1;
    else
      return 0;
  }

};

//the enemyTank class is in charge of creating the enemy tanks
class enemyTank {
public:
	int hitPoints;
	double enemyGunRotateY, enemyGunRotateX;
	double enemyTankPosX, enemyTankPosY, enemyTankPosZ;
	double enemyTankRotX, enemyTankRotY, enemyTankRotZ;
	double enemySpin;
	int enemyHitPoints;
	bool hitLastFrame;
	enemyTankMovement enemyTankInstance;
	vector <EnemyBulletClass> enemyBullets; //each enemy tank gets their own vector of bullet objects
	int randomButton;

	void randomValues() {
		enemyTankPosX = rand()%20;
		enemyTankPosY = rand()%20;
		enemyTankPosZ = rand()%20;
	}

  //constructor - called when the enemy tank is first created
	 enemyTank() {
		randomValues();
		enemyGunRotateY = 0;
		enemyGunRotateX = 0;
		enemySpin = 0;
		enemyHitPoints = 3;
		hitLastFrame = false;
	 }

	void enemyTankKeysAI(){
		switch(randomButton)
		{
			case 1:		
			if (enemySpin-5 < 0){
				enemySpin -= 5.0;
				enemySpin += 360;
			}
			else
				enemySpin -= 5.0;
			enemyTankInstance.RotateY(5.0);
			break;
		case 2:		
			if (enemySpin+5 > 360){
				enemySpin += 5.0;
				enemySpin -= 360;
			}
			else
				enemySpin += 5.0;
			enemyTankInstance.RotateY(-5.0);
			break;
		case 3:
			enemyTankInstance.MoveForwards( -0.3 ) ;
			break;
		case 4:	
			enemyTankInstance.MoveForwards( 0.3 ) ;
			break;
		}
	}

	void EnemyTankMouseClickAI(){
		//if the enemy tank left clicks, shoot a bullet
		EnemyBulletClass enBul(enemySpin, enemyGunRotateX, enemyGunRotateY, enemyTankPosX, enemyTankPosY, enemyTankPosZ);
		//add the bullet to our enemy bullet object vector
		enemyBullets.push_back(enBul);
	}

	void enemyTankMouseMoveAI(int x, int y){
		//passes in a random x,y mouse coordinate
		enemyGunRotateX = 70+(-((75*x)/(screen_width/2)));
		enemyGunRotateY = -90+((45*y)/(screen_height/3));
	}

  // draw the target
	void drawEnemyTank()
	{
		if(rand()%5 == 1){
			 randomButton = rand()%4+1;
			 
			 enemyTankMouseMoveAI(rand()%screen_width+1,rand()%screen_height+1);

			 int fireOrNot = rand()%4+1;
			 if (fireOrNot == 3)
				 EnemyTankMouseClickAI();
		}

		 enemyTankKeysAI();
		 enemyTankRotX = enemyTankInstance.Render(0);
		 enemyTankRotY = enemyTankInstance.Render(1);
		 enemyTankRotZ = enemyTankInstance.Render(2);
		 enemyTankPosX = enemyTankInstance.Render(3);
		 enemyTankPosY = enemyTankInstance.Render(4);
		 enemyTankPosZ = enemyTankInstance.Render(5);

		 glPushMatrix();
		 glTranslatef(0,0,0);
		 glTranslatef(enemyTankPosX, enemyTankPosY, enemyTankPosZ);
		 glRotatef(enemyTankRotX , 1.0, 0.0, 0.0);
		 glRotatef(enemyTankRotY , 0.0, 1.0, 0.0);
		 glRotatef(enemyTankRotZ , 0.0, 0.0, 1.0);
		 glRotatef(180,0,1,0);
		 createEnemyTank();
		 glPopMatrix();
	}

	void createEnemyTankGun(){
		 if(enemyGunRotateX > 45)
			 enemyGunRotateX = 45;
		 if(enemyGunRotateX < -45)
			 enemyGunRotateX = -45;
		 glPushMatrix();
		 glTranslatef(0,-2,0);
		 glRotatef(enemyGunRotateX,0,1,0);
		 glTranslatef(0,2.25,0.9);
		 glmDraw( model[1], GLM_SMOOTH | GLM_MATERIAL );
		 glPopMatrix();
	}

	void createEnemyTank(){
		 if (hitLastFrame){
			 glColor3f(0.5,0.1,0.1);
			 hitLastFrame = false;
		 }
		 else
			glColor3f(0.1,0.5,0.1);
		 glPushMatrix();
		 glTranslatef(0,0.15,0);
		 glmDraw( model[0], GLM_SMOOTH | GLM_MATERIAL );
		 glPopMatrix();

		 glPushMatrix();
		 glRotatef(enemyGunRotateY,1,0,0);
		 glTranslatef(0,-0.15,0);
		 createEnemyTankGun();
		 glPopMatrix();
	}
};

//bullet class
class bullet{
public:
  GLfloat bulletPosX, bulletPosY, bulletPosZ;
  double localxDegree;
  double localyDegree;
  double zRatio;
  double xRatio;
  double yRatio;

  // constructor of the bullet class
  bullet() 
  {
	localxDegree = spin-gunRotateX;
    localyDegree = gunRotateY+90;

    bulletPosX = tankPosX+cos((spin*PI*2)/360)*1; 
	bulletPosY = tankPosY; 
	bulletPosZ = tankPosZ+sin((spin*PI*2)/360)*1;
	
	if (localxDegree>=180 && localxDegree <=270){
		if (localxDegree-180 == 0)
			zRatio = 0;
		else
			zRatio = ((localxDegree-180)*1)/90;
		xRatio = -(1-zRatio);
		zRatio = -zRatio;
	}
	else if (localxDegree>270 && localxDegree<360){
		xRatio = ((localxDegree-270)*1)/90;
		zRatio = -(1-xRatio);
	}
	else if (localxDegree>=0 && localxDegree<=90){
		if(localxDegree-0 == 0)
			zRatio = 0;
		else
			zRatio = ((localxDegree-0)*1)/90;
		xRatio = 1-zRatio;
	}
	else if (localxDegree>90 && localxDegree<180){
		xRatio = ((localxDegree-90)*1)/90;
		zRatio = 1-xRatio;
		xRatio = -xRatio;
	}
	if (localyDegree > 90)
		yRatio = -(((localyDegree-90)*1)/90);
	else if (localyDegree == 90)
		yRatio = 0;
	else if (localyDegree < 90)
		yRatio = 1-(((localyDegree)*1)/90);
  }

  	int hits(enemyTank &t) {
    // if we're within the hit box, call it a hit
    if (bulletPosX < t.enemyTankPosX+0.4 &&  bulletPosX > t.enemyTankPosX-0.4 &&
		bulletPosY < t.enemyTankPosY+0.15 &&  bulletPosY > t.enemyTankPosY-0.15 &&
		bulletPosZ < t.enemyTankPosZ+0.65 &&  bulletPosZ > t.enemyTankPosZ-0.65)
      return 1;
    else
      return 0;
  }

  // draw the round
  void draw() {
	glColor3f(0,0,1);
    glPushMatrix();
    glTranslatef(bulletPosX, bulletPosY, bulletPosZ);
    glutSolidSphere(.2,100,20);
    glPopMatrix();
  }

};


vector <bullet> bullets;
vector <enemyTank> enemyTanks;

// create enemy tanks
void initEnemyTanks() {
  srand(time(NULL));
  for(int i=0;i<5;i++) {
    enemyTank t;
    enemyTanks.push_back(t);
  }
}


void createSky()
{
	 GLfloat color[] = {0.2, 0.2, 0.2};
	 glBindTexture(GL_TEXTURE_2D, textureArray[2]);
	 glColor3f(1,1,1);
	 glBegin(GL_QUADS);
	 glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, color);
	 glTexCoord2f(0, 0); glVertex3f(-20, 20, 20);
	 glTexCoord2f(0, 1.0); glVertex3f(-20, 20, -20);
	 glTexCoord2f(1.0, 1.0); glVertex3f(20, 20, -20);
	 glTexCoord2f(1.0, 0); glVertex3f(20, 20, 20);
	 glEnd();

	 glBegin(GL_QUADS);
	 glTexCoord2f(0, 0); glVertex3f(-20, 20, 20);
	 glTexCoord2f(0, 1.0); glVertex3f(-20, -.27, 20);
	 glTexCoord2f(1.0, 1.0); glVertex3f(20, -.27, 20);
	 glTexCoord2f(1.0, 0); glVertex3f(20, 20, 20);
	 glEnd();

	 glBegin(GL_QUADS);
	 glTexCoord2f(0, 0); glVertex3f(-20, 20, -20);
	 glTexCoord2f(0, 1.0); glVertex3f(-20, -.27, -20);
	 glTexCoord2f(1.0, 1.0); glVertex3f(20, -.27, -20);
	 glTexCoord2f(1.0, 0); glVertex3f(20, 20, -20);
	 glEnd();

	 glBegin(GL_QUADS);
	 glTexCoord2f(0, 0); glVertex3f(-20, 20, -20);
	 glTexCoord2f(0, 1.0); glVertex3f(-20, -.27, -20);
	 glTexCoord2f(1.0, 1.0); glVertex3f(-20, -.27, 20);
	 glTexCoord2f(1.0, 0); glVertex3f(-20, 20, 20);
	 glEnd();

	 glBegin(GL_QUADS);
	 glTexCoord2f(0, 0); glVertex3f(20, 20, -20);
	 glTexCoord2f(0, 1.0); glVertex3f(20, -.27, -20);
	 glTexCoord2f(1.0, 1.0); glVertex3f(20, -.27, 20);
	 glTexCoord2f(1.0, 0); glVertex3f(20, 20, 20);
	 glEnd();
}


void createGrass()
{

	 glBindTexture(GL_TEXTURE_2D, textureArray[3]);
	 glColor3f(1,1,1);
	 glBegin(GL_QUADS);
	 glTexCoord2f(0, 0); glVertex3f(-0.425, 0.270, 0.425);
	 glTexCoord2f(0, 1.0); glVertex3f(-0.425, 0.270, -0.425);
	 glTexCoord2f(1.0, 1.0); glVertex3f(0.425, 0.270, -0.425);
	 glTexCoord2f(1.0, 0); glVertex3f(0.425, 0.270, 0.425);
	 glEnd();

}

void createBell()
{
	//sphere for the top of the bell
	 glPushMatrix();
	 glColor3f(0.65,0.75,0.70); //color it
	 glutSolidSphere(.5, 200, 50);
	 glPopMatrix();
	 //cone for the bottom of the bell
	 glPushMatrix();
	 glTranslatef(0.0, -0.5, 0.0); //move it
	 glRotatef(-90, 1.0, 0.0, 0.0); //rotate it
	 glutSolidCone(.65, 1, 75, 4);
	 glPopMatrix();
	//sphere for the ball at the bottom of the bell
	 glPushMatrix();
	 glColor3f(0.65,0.75,0.70); //color it
	 glTranslatef(0.15, -0.60, 0.0); //move it
	 glutSolidSphere(.13, 100, 30);
	 glPopMatrix();
	 //the part at the top of the bell that connects it to the columns
	 glPushMatrix();
	 glColor3f(1,0.3,0.45); //color it
	 glTranslatef(0.0, 0.70, 0.0); //move it
	 glScalef(0.70,2,0.70); //scale it
	 glutSolidCube(.25); 
	 glPopMatrix();
}

void createBase()
{
	 glColor3f(1,0.5,0.5);
	 glBindTexture(GL_TEXTURE_2D, textureArray[1]);

	 glBegin(GL_QUADS);
	 glTexCoord2f(1, 1); glVertex3f(-.5, .25, 0.5);
	 glTexCoord2f(0, 1); glVertex3f(-.5, .25, -0.5);
	 glTexCoord2f(0, 0); glVertex3f(-.5, -.25, -0.5);
	 glTexCoord2f(1, 0); glVertex3f(-.5, -.25, 0.5);
	 glEnd();

	 glBegin(GL_QUADS);
	 glTexCoord2f(1, 1); glVertex3f(.5, .25, 0.5);
	 glTexCoord2f(0, 1); glVertex3f(.5, .25, -0.5);
	 glTexCoord2f(0, 0); glVertex3f(.5, -.25, -0.5);
	 glTexCoord2f(1, 0); glVertex3f(.5, -.25, 0.5);
	 glEnd();

	 glBegin(GL_QUADS);
	 glTexCoord2f(1, 1); glVertex3f(.5, .25, 0.5);
	 glTexCoord2f(1, 0); glVertex3f(.5, -.25, 0.5);
	 glTexCoord2f(0, 0); glVertex3f(-.5, -.25, 0.5);
	 glTexCoord2f(0, 1); glVertex3f(-.5, .25, 0.5);
	 glEnd();

	 glBegin(GL_QUADS);
	 glTexCoord2f(1, 1); glVertex3f(.5, .25, -0.5);
	 glTexCoord2f(1, 0); glVertex3f(.5, -.25, -0.5);
	 glTexCoord2f(0, 0); glVertex3f(-.5, -.25, -0.5);
	 glTexCoord2f(0, 1); glVertex3f(-.5, .25, -0.5);
	 glEnd();
}

void createTankGun(){
	 if(gunRotateX > 45)
		 gunRotateX = 45;
	 if(gunRotateX < -45)
		 gunRotateX = -45;
	 glPushMatrix();
	 glTranslatef(0,-2,0);
	 glRotatef(gunRotateX,0,1,0);
	 glTranslatef(0,2.25,0.9);
	 glmDraw( model[1], GLM_SMOOTH | GLM_MATERIAL );
	 glPopMatrix();
}

void createTank(){

	 glColor3f(0.0,0.3,0.1);
	 glPushMatrix();
	 glTranslatef(0,0.15,0);
	 glmDraw( model[0], GLM_SMOOTH | GLM_MATERIAL );
	 glPopMatrix();

	 glPushMatrix();
	 glRotatef(gunRotateY,1,0,0);
	 glTranslatef(0,-0.15,0);
	 createTankGun();
	 glPopMatrix();
}



void drawHitBox(){ //used for drawing a box around a tank to confirm the hit box ranges
	//right side
	glBegin(GL_QUADS);
	glVertex3f(0.4, 0, -1.3); // The bottom left corner  
	glVertex3f(0.4, 0.3, -1.3); // The top left corner  
	glVertex3f(0.4, 0.3, -2.6); // The top right corner  
	glVertex3f(0.4, 0, -2.6); // The bottom right corner  
	glEnd();
	//left side
	glBegin(GL_QUADS);
	glVertex3f(-0.4, 0, -1.3); // The bottom left corner  
	glVertex3f(-0.4, 0.3, -1.3); // The top left corner  
	glVertex3f(-0.4, 0.3, -2.6); // The top right corner  
	glVertex3f(-0.4, 0, -2.6); // The bottom right corner  
	glEnd();
	//back
	glBegin(GL_QUADS);
	glVertex3f(-0.4, 0, -1.3); // The bottom left corner  
	glVertex3f(-0.4, 0.3, -1.3); // The top left corner  
	glVertex3f(0.4, 0.3, -1.3); // The top right corner  
	glVertex3f(0.4, 0, -1.3); // The bottom right corner  
	glEnd();
	//front
	glBegin(GL_QUADS);
	glVertex3f(-0.4, 0, -2.6); // The bottom left corner  
	glVertex3f(-0.4, 0.3, -2.6); // The top left corner  
	glVertex3f(0.4, 0.3, -2.6); // The top right corner  
	glVertex3f(0.4, 0, -2.6); // The bottom right corner  
	glEnd();
	//top
	glBegin(GL_QUADS);
	glVertex3f(-0.4, 0.3, -1.3); // The bottom left corner  
	glVertex3f(-0.4, 0.3, -2.6); // The top left corner  
	glVertex3f(0.4, 0.3, -2.6); // The top right corner  
	glVertex3f(0.4, 0.3, -1.3); // The bottom right corner  
	glEnd();

}


void createWindmillSail(){
	 glBindTexture(GL_TEXTURE_2D, textureArray[6]);
	 glBegin(GL_QUADS);
	 glColor4f(1.0, 1.0, 1.0, 0.73);
	 glTexCoord2f(0, 0); glVertex3f(-0.51, 2.95, 1.425);
	 glTexCoord2f(0, 1.0); glVertex3f(-0.51, 0, 1.425);
	 glTexCoord2f(1.0, 1.0); glVertex3f(0.51, 0, 1.425);
	 glTexCoord2f(1.0, 0); glVertex3f(0.51, 2.95, 1.425);
	 glEnd();
}

void createWindmillBase(){
	 glColor4f(1.0, 1.0, 1.0, 1.0);
	 glBindTexture(GL_TEXTURE_2D, textureArray[5]);
	 glBegin(GL_QUADS);
	 glTexCoord2f(0, 0); glVertex3f(-0.985, 2.26, 1.13);
	 glTexCoord2f(0, 1.0); glVertex3f(-0.985, 2.26, -1.13);
	 glTexCoord2f(1.0, 1.0); glVertex3f(0.985, 2.26, -1.13);
	 glTexCoord2f(1.0, 0); glVertex3f(0.985, 2.26, 1.13);
	 glEnd();

	 glBegin(GL_QUADS);
	 glTexCoord2f(0, 0); glVertex3f(-0.985, 2.26, 1.13);
	 glTexCoord2f(0, 1.0); glVertex3f(-0.985, 0, 1.13);
	 glTexCoord2f(1.0, 1.0); glVertex3f(0.985, 0, 1.13);
	 glTexCoord2f(1.0, 0); glVertex3f(0.985, 2.26, 1.13);
	 glEnd();

	 glBegin(GL_QUADS);
	 glTexCoord2f(0, 0); glVertex3f(-0.985, 2.26, -1.13);
	 glTexCoord2f(0, 1.0); glVertex3f(-0.985, 0, -1.13);
	 glTexCoord2f(1.0, 1.0); glVertex3f(0.985, 0, -1.13);
	 glTexCoord2f(1.0, 0); glVertex3f(0.985, 2.26, -1.13);
	 glEnd();

	 glBegin(GL_QUADS);
	 glTexCoord2f(0, 0); glVertex3f(-0.985, 2.26, -1.13);
	 glTexCoord2f(0, 1.0); glVertex3f(-0.985, 0, -1.13);
	 glTexCoord2f(1.0, 1.0); glVertex3f(-0.985, 0, 1.13);
	 glTexCoord2f(1.0, 0); glVertex3f(-0.985, 2.26, 1.13);
	 glEnd();

	 glBegin(GL_QUADS);
	 glTexCoord2f(0, 0); glVertex3f(0.985, 2.26, -1.13);
	 glTexCoord2f(0, 1.0); glVertex3f(0.985, 0, -1.13);
	 glTexCoord2f(1.0, 1.0); glVertex3f(0.985, 0, 1.13);
	 glTexCoord2f(1.0, 0); glVertex3f(0.985, 2.26, 1.13);
	 glEnd();

}

void createWindmillSailsTogether(){
	 double spinRate = 1.2;
	 double x = windmillSpin*spinRate;

	 double rotation =  ((x)*360) / (PI*2);
	 double cosspin = cos(windmillSpin*spinRate)*0.7;
	 double sinspin = sin(windmillSpin*spinRate)*0.7;

	 glPushMatrix();
	 glScalef(0.35,0.35,0.35);
	 
	 glTranslatef(-cosspin, -sinspin, 0);
	 glTranslatef(-3, 4, 7);
	 glRotatef(rotation, 0, 0, 1);
	 createWindmillSail();
	 glPopMatrix();

	 glPushMatrix();
	 glScalef(0.35,0.35,0.35);
	 glTranslatef(-3, 4, 7);
	 glRotatef(90,0,0,1);
	 glTranslatef(-cosspin, -sinspin, 0);
	 glRotatef(rotation, 0, 0, 1);
	 createWindmillSail();
	 glPopMatrix();

	 glPushMatrix();
	 glScalef(0.35,0.35,0.35);
	 glTranslatef(-3, 4, 7);
	 glRotatef(270,0,0,1);
	 glTranslatef(-cosspin, -sinspin, 0);
	 glRotatef(rotation, 0, 0, 1);
	 createWindmillSail();
	 glPopMatrix();

	 glPushMatrix();
	 glScalef(0.35,0.35,0.35);
	 glTranslatef(-3, 4, 7);
	 glRotatef(180,0,0,1);
	 glTranslatef(-cosspin, -sinspin, 0);
	 glRotatef(rotation, 0, 0, 1);
	 createWindmillSail();
	 glPopMatrix();
}

void createWindmill(){
	
	 glPushMatrix();
	 glScalef(0.35,0.35,0.35);
	 glTranslatef(-3, 0, 7);
	 glRotatef(180,0,1,0);
	 createWindmillBase();
	 glPopMatrix();
	
	 glPushMatrix();
	 glScalef(0.35,0.35,0.35);
	 glTranslatef(-3, 2.26, 7);
	 createWindmillBase();
	 glPopMatrix();

	 glPushMatrix();
	 createWindmillSailsTogether();
	 glPopMatrix();
}

/***************************************************
**               display function                 **
***************************************************/
void display ( void )
{

	/* display stuff... */
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
	glLoadIdentity(); 
	float light_position[] = {0.0, 0.0, 1.0, 0.0};
	glMatrixMode(GL_MODELVIEW);
	Camera.Render(); //update the camera position
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);	//set up our light in the right position

	
	createSky();
	glColor3f(1,1,1);
	glBindTexture(GL_TEXTURE_2D, textureArray[3]);
	glBegin(GL_QUADS);
		glTexCoord2f(-7.0, -7.0); glVertex3f(-20, -.27, 20);
		glTexCoord2f(-7.0, 1.0); glVertex3f(-20, -.27, -20);
		glTexCoord2f(1.0, 1.0); glVertex3f(20, -.27, -20);
		glTexCoord2f(1.0, -7.0); glVertex3f(20, -.27, 20);
	glEnd();

	 //base one
	 glPushMatrix();
	 glTranslatef(0, 0, -2); //move it
	 createBase();
	 glPopMatrix();

	 //base one grass
	 glPushMatrix();
	 glColor3f(0.0,1,0.0); //color it
	 glScalef(0.85,0.60,0.85); //scale it
	 glTranslatef(0, 0.10, -2.35); //move it
	 glutSolidCube(1); 
	 glPopMatrix();
	 
	 //base two
	 glPushMatrix();
	 glTranslatef(-2, 0, 2); //move it
	 createBase();
	 glPopMatrix();

	 //base two grass
	 glPushMatrix();
	 glColor3f(0,1,0); //color it
	 glScalef(0.85,0.60,0.85); //scale it
	 glTranslatef(-2.35, 0.10, 2.35); //move it
	 glutSolidCube(1); 
	 glPopMatrix();

	 //base three
	 glPushMatrix();
	 glTranslatef(4, 0, 0); //move it
	 createBase();
	 glPopMatrix();

	 //base three grass
	 glPushMatrix();
	 glColor3f(0,1,0); //color it
	 glScalef(0.85,0.60,0.85); //scale it
	 glTranslatef(4.75, 0.10, 0.0); //move it
	 glutSolidCube(1); 
	 glPopMatrix();

	 //tallest column
	 glPushMatrix();
	 glColor3f(1,0.3,0.45); //color it
	 glTranslatef(1.85, 3.75, 0); //move it
	 glRotatef(32, 0.0, 0.0, 1.0); //rotate it
	 glScalef(0.4,9.25,0.4); //scale it
	 glutSolidCube(1); 
	 glPopMatrix();

	 //2nd tallest column
	 glPushMatrix();
	 glColor3f(1,0.3,0.45); //color it
	 glTranslatef(0, 3.25, -0.95); //move it
	 glRotatef(16, 1.0, 0.0, 0.0); //rotate it
	 glScalef(0.4,7,0.4); //scale it
	 glutSolidCube(1); 
	 glPopMatrix();

	 //shortest column
	 glPushMatrix();
	 glColor3f(1,0.3,0.45); //color it
	 glTranslatef(-1, 2.25, 0.75); //move it
	 glRotatef(-30, 1.0, 0.0, 0.0); //rotate it
	 glRotatef(-20, 0.0, 0.0, 1.0); //rotate it
	 glScalef(0.4,5.75,0.4); //scale it
	 glutSolidCube(1); 
	 glPopMatrix();

	 //first bell
	 glPushMatrix();
	 glScalef(0.85,0.85,0.85); //scale it
	 glTranslatef(0.65, 5.60, 0); //move it
	 createBell();
	 glPopMatrix();

	 //second bell
	 glPushMatrix();
	 glScalef(0.70,0.70,0.70); //scale it
	 glTranslatef(2, 5, 0); //move it
	 createBell();
	 glPopMatrix();

	 //third bell
	 glPushMatrix();
	 glScalef(0.60,0.60,0.60); //scale it
	 glTranslatef(3.65, 3.90, 0); //move it
	 createBell();
	 glPopMatrix();

	 //fourth bell
	 glPushMatrix();
	 glScalef(0.45,0.45,0.45); //scale it
	 glTranslatef(6.25, 3.20, 0); //move it
	 createBell();
	 glPopMatrix();

	 //fifth bell
	 glPushMatrix();
	 glTranslatef(-0.50, 2.30, 0); //move it
	 createBell();
	 glPopMatrix();

	 //createSky();

	 //create two windmills
	 glPushMatrix();
	 glTranslatef(-5, 0, 0);
	 glScalef(1.5,1.5,1.5);
	 createWindmill();
	 glPopMatrix();

	 glPushMatrix();
	 glTranslatef(15.4, 0, 5);
	 glScalef(1.5,1.5,1.5);
	 glRotatef(-90,0,1,0);
	 createWindmill();
	 glPopMatrix();

	 windmillSpin = windmillSpin + 0.009;
    if (windmillSpin > 360.0)
      windmillSpin = windmillSpin - 360.0;
	 
	 //create our player tank in the right position
	 double tankRotX = playerTank.Render(0);
	 double tankRotY = playerTank.Render(1);
	 double tankRotZ = playerTank.Render(2);
	 tankPosX = playerTank.Render(3);
	 tankPosY = playerTank.Render(4);
	 tankPosZ = playerTank.Render(5);

	 tankPosX = tankPosX+cos((spin*PI*2)/360)*2.5;
	 tankPosZ = tankPosZ+sin((spin*PI*2)/360)*2.5;

	 glPushMatrix();
	 glTranslatef(0,0,0);
	 glTranslatef(tankPosX, tankPosY, tankPosZ);
	 glRotatef(tankRotX , 1.0, 0.0, 0.0);
	 glRotatef(tankRotY , 0.0, 1.0, 0.0);
	 glRotatef(tankRotZ , 0.0, 0.0, 1.0);
	 glRotatef(180,0,1,0);
	 createTank();
	 glPopMatrix();

	 //drawHitBox();

	 // grass textures
	 glPushMatrix();
	 glTranslatef(0, 0.10, -2); //move it
	 createGrass();
	 glPopMatrix();

	 glPushMatrix();
	 glTranslatef(-2, 0.10, 2);
	 createGrass();
	 glPopMatrix();

	 glPushMatrix();
	 glTranslatef(4., 0.10, 0.0); //move it
	 createGrass();
	 glPopMatrix();

	 for(int i=0;i<enemyTanks.size();i++) {
		enemyTanks.at(i).drawEnemyTank(); //draw the enemy tank in the new position

		for(int j=0;j<enemyTanks.at(i).enemyBullets.size();j++) {
			//update enemy bullet positions and then draw the bullet
			enemyTanks.at(i).enemyBullets.at(j).bulletPosX += enemyTanks.at(i).enemyBullets.at(j).xRatio;
			enemyTanks.at(i).enemyBullets.at(j).bulletPosY += enemyTanks.at(i).enemyBullets.at(j).yRatio;
			enemyTanks.at(i).enemyBullets.at(j).bulletPosZ += enemyTanks.at(i).enemyBullets.at(j).zRatio;
			enemyTanks.at(i).enemyBullets.at(j).draw();

			// if the bullet has gone too far away, then kill it.
			if (enemyTanks.at(i).enemyBullets.at(j).bulletPosX < -30 ||enemyTanks.at(i).enemyBullets.at(j).bulletPosY > 30 || enemyTanks.at(i).enemyBullets.at(j).bulletPosY < -30 || 
			enemyTanks.at(i).enemyBullets.at(j).bulletPosX > 30 ||enemyTanks.at(i).enemyBullets.at(j).bulletPosZ > 30 ||enemyTanks.at(i).enemyBullets.at(j).bulletPosZ < -30) {
			  enemyTanks.at(i).enemyBullets.erase(enemyTanks.at(i).enemyBullets.begin()+j);
			  j--;
			  continue;
			}

			//if the bullet hits the user tank's hit box, lower the user's hit points
			if (enemyTanks.at(i).enemyBullets.at(j).hits()){ 
				hitPoints--;
				printf("Your tank was hit, %d hit points left \n", hitPoints);
				if(hitPoints == 0){
					printf("Your tank has been destroyed \n");
				}
			}

		}
	}

	//update user's bullets' positions and then draw the bullet
	for(int i=0;i<bullets.size();i++) {
		bullets.at(i).bulletPosX += bullets.at(i).xRatio;
		bullets.at(i).bulletPosY += bullets.at(i).yRatio;
		bullets.at(i).bulletPosZ += bullets.at(i).zRatio;
		bullets.at(i).draw();

		// if the bullet has gone too far away, then kill it.
		if (bullets.at(i).bulletPosX < -50 || bullets.at(i).bulletPosY > 50 || bullets.at(i).bulletPosY < -50 || 
		bullets.at(i).bulletPosX > 50 || bullets.at(i).bulletPosZ > 50 || bullets.at(i).bulletPosZ < -50) {
		  bullets.erase(bullets.begin()+i);
		  i--;
		  continue;
		}

		//if the bullet hits a hit box of an enemy tank, lower the hit points of that tank
		for(int j=0;j<enemyTanks.size();j++) {
			if (bullets.at(i).hits(enemyTanks.at(j))){
				enemyTanks.at(j).enemyHitPoints--;
				printf("Enemy tank hit, %d hit points left \n", enemyTanks.at(j).enemyHitPoints);
				enemyTanks.at(j).hitLastFrame = true;
				//if the enemy tank has no hit points left after the hit, destroy the tank
				if(enemyTanks.at(j).enemyHitPoints == 0){
					printf("Enemy tank destroyed \n");
					enemyTanks.erase(enemyTanks.begin()+j);
					j--;
				}
			}
		}
	}

	/* flush GL commands & swap buffers */
	glFlush();
	glutSwapBuffers();
}

/***************************************************
**               idle function                    **
***************************************************/
void idle ( void )
{

	glutPostRedisplay();
}

/***************************************************
**          manage window resizing                **
***************************************************/
void reshape( int w, int h )
{
	/* width & height don't change */
	glViewport(0,0,screen_width,screen_height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90.0, aspect, 1.0, 100.0);
	glMatrixMode(GL_MODELVIEW);

}


/***************************************************
**             manage mouse clicks                **
***************************************************/
void button(int b, int st, int x, int y)
{
	switch ( b )
	{
	default:
		break;

	case GLUT_LEFT_BUTTON:
		{
			switch( st ) 
			{
			case GLUT_DOWN:
           // when there is a left click, fire a bullet.
				bullet bul;
				bullets.push_back(bul);
				break;
			}
		}
		break;
	}


}

/***************************************************
**             manage key strokes                 **
***************************************************/

void keysPressed(unsigned char key, int x, int y)
{
	switch ( key )
	{
	default:
		break;
	case 27:	//ESC
		exit(0);
		break;
	case 'a':
		if(!birdseye){
			Camera.RotateY(5.0);
			if (spin-5 < 0){
				spin -= 5.0;
				spin += 360;
			}
			else
				spin -= 5.0;
			playerTank.RotateY(5.0);
		}
		break;
	case 'd':
		if(!birdseye){
			Camera.RotateY(-5.0);
			if (spin+5 > 360){
				spin += 5.0;
				spin -= 360;
			}
			else
				spin += 5.0;
			playerTank.RotateY(-5.0);
		}
		break;
	case 'w':
		if (!birdseye){
			Camera.MoveForwards( -0.3 ) ;
			playerTank.MoveForwards( -0.3 ) ;
		}
		break;
	case 's':	
		if (!birdseye){
		Camera.MoveForwards( 0.3 ) ;
		playerTank.MoveForwards( 0.3 ) ;
		}
		break;
	case 'b':
		if (birdseye){
			Camera.Position.x = Camera.lastPosition.x;
			Camera.Position.y = Camera.lastPosition.y;
			Camera.Position.z = Camera.lastPosition.z;
			Camera.ViewDir.x = Camera.lastViewDir.x;
			Camera.ViewDir.y = Camera.lastViewDir.y;
			Camera.ViewDir.z = Camera.lastViewDir.z;
			Camera.RotatedY = Camera.lastRotatedY;
			
			birdseye = false;
		}
		else if (!birdseye){
			Camera.lastPosition.x = Camera.Position.x;
			Camera.lastPosition.y = Camera.Position.y;
			Camera.lastPosition.z = Camera.Position.z;
			Camera.lastViewDir.x = Camera.ViewDir.x;
			Camera.lastViewDir.y = Camera.ViewDir.y;
			Camera.lastViewDir.z = Camera.ViewDir.z;
			Camera.lastRotatedY = Camera.RotatedY;

			Camera.Position.x = 0;
			Camera.Position.y = 15;
			Camera.Position.z = 20;
			Camera.RotatedY = 0;
			birdseye = true;
		}
	}

}

/***************************************************
**                initializations                 **
***************************************************/
void init(void)
{

	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClearDepth(1.0);


	// looad all models

	for(int i=0; i<2; i++)
	{
		model[i] = glmReadOBJ( ModelName[i] );
		glmUnitize( model[i] );
		glmFacetNormals( model[i] );
		glmVertexNormals( model[i], 90.0 );
	}

	//set up the light source parameters
	float light_ambient[] = {0.2, 0.2, 0.2, 1.0}; 
	float light_diffuse[] = {1.0, 1.0, 1.0, 1.0};
	float light_specular[] = {1.0, 1.0, 1.0, 1.0};
	float light_position[] = {0.0, 0.0, 1.0, 0.0};

	//glClearColor (1.0, 1.0, 1.0, 1.0); 	// clear background into black
	//set GL_LIGHT0 to those specifications
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);

	//enable lighting and depth, etc.
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE); /* Normalize normals */
	glEnable(GL_COLOR_MATERIAL);

	//setup all textures
	glEnable(GL_TEXTURE_2D);	
    CreateTexture(textureArray,"textures/concrete2.tga",0);
	CreateTexture(textureArray,"textures/bricks.tga",1);
	CreateTexture(textureArray,"textures/sky.tga",2);
	CreateTexture(textureArray,"textures/grass.tga",3);
	CreateTexture(textureArray, "textures/mountain.tga",4);
	CreateTexture(textureArray, "textures/windmillbase.tga",5);
	CreateTexture(textureArray, "textures/windmillsail.tga",6);
	CreateTexture(textureArray, "textures/mountainlower.tga",7);

	//enable and set up blending
	glEnable (GL_BLEND); 
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glShadeModel (GL_FLAT);

	//enable and set up fog
    glEnable(GL_FOG);
    GLfloat fogColor[4] = {0.8, 0.8, 0.8, 1.0};

	static GLint fogMode;
    fogMode = GL_EXP2;
    glFogi (GL_FOG_MODE, fogMode);
    glFogfv (GL_FOG_COLOR, fogColor);
    glFogf (GL_FOG_DENSITY, 0.04);
    glHint (GL_FOG_HINT, GL_DONT_CARE);
    glFogf (GL_FOG_START, 0.0);
    glFogf (GL_FOG_END, 1.0);

    //initialize the enemy tanks
	initEnemyTanks();

	glShadeModel(GL_SMOOTH);

}



void mouseMovement(int x, int y) {
		gunRotateX = 70+(-((75*x)/(screen_width/2)));
		gunRotateY = -90+((45*y)/(screen_height/3));
}


/***************************************************
**               main entry point                 **
***************************************************/

int main(int argc, char** argv){

	/* initializations */
	glutInit(&argc, argv);
	glutInitDisplayMode( GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH );
	glutInitWindowSize( screen_width, screen_height );
	glutInitWindowPosition( 100, 100 );
	glutCreateWindow("Tank Game");
	init();

	/* set the callback functions */
	glutDisplayFunc( display );
	glutReshapeFunc( reshape );
	glutIdleFunc( idle );
	glutMouseFunc( button );
	glutPassiveMotionFunc(mouseMovement); 
	glutKeyboardFunc( keysPressed ); 
	
	/* start */
	glutMainLoop();
	return 0;
}

