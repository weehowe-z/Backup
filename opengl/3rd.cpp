#include "stdlib.h"
#include "math.h"
#include <glut.h>

float angle = 0.0;
float z = 0.0;
float x = 0.0;
float speed = 1.0;
double g_dAngle = 0.0f;

void reshape(int w, int h)
{
	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	float R = (float)w / h;
	gluPerspective(45., R, 0.1, 1000.);
	glEnable(GL_DEPTH_TEST);

}

void disp()
{
	float angle_C = (angle + 90) * 3.14159 / 180.;
	glClear(GL_COLOR_BUFFER_BIT);
	glClear(GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	
	gluLookAt(x, 1, z,
		x - 10.*cos(angle_C), 0, z - 10.*sin(angle_C),
		0, 1, 0
		);
	for (float i = 0.; i<2 * 3.1415; i += 0.5236)
	{
		glPushMatrix();
		glColor3f(102.0/255, 204.0/255, 1);
		glTranslatef(10.*cos(i), 0, 10.*sin(i));
		glRotatef(g_dAngle, 0.0f, 1.0f, 0.0f);
		glutWireTeapot(1);
		glPopMatrix();
	}

	glutSwapBuffers();
}

void OnTimer(int iTimerIndex)
{
	g_dAngle += 2.0f;
	if (g_dAngle > 360.0f)
	{
		g_dAngle -= 360.0f;
	}
	glutPostRedisplay();
	glutTimerFunc(50, OnTimer, 0);
}

void KeyProcess(unsigned char key, int x, int y)
{
	if (key == 27) { //ESC
		exit(0);
	}
}

void SpecialKey(int key, int xx, int yy)
{
	float angle_C = (angle - 90.) * 3.14159 / 180.;
	switch (key)
	{
	case GLUT_KEY_LEFT:
		angle -= 1.0;
		break;
	case GLUT_KEY_RIGHT:
		angle += 1.0;
		break;
	case GLUT_KEY_UP:
		x += speed*cos(angle_C);
		z += speed*sin(angle_C);
		break;
	case GLUT_KEY_DOWN:
		x -= speed*cos(angle_C);
		z -= speed*sin(angle_C);
		break;
	}
	disp();
}


void main()
{
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(200, 200);
	glutInitWindowSize(600, 600);
	glutCreateWindow("3rd Practice");
	glutFullScreen();

	glutReshapeFunc(reshape);

	glutTimerFunc(50, OnTimer, 0);
	glutKeyboardFunc(KeyProcess);
	glutSpecialFunc(SpecialKey);
	glutDisplayFunc(disp);
	glutMainLoop();

}

