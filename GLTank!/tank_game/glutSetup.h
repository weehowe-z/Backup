/********************************************
** glut_template.h                         **
** ---------------                         **
**                                         **
** Header file for the morphing program    **
**                                         **
** Chris Wyman (9/28/2000)                 **
********************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <GL/glut.h>

/* GL callback functions */
void display ( void );
void reshape( int w, int h );
void idle ( void );
void motion(int x, int y);
void button(int b, int st, int x, int y);
void menu( int value );
void keys(unsigned char key, int x, int y);