// 20221365 박주연
// 컴퓨터그래픽스 2주차 과제2
#include <iostream>
#include <glut.h> 
#include <math.h> 
using namespace std;

#define PI 3.141592


float scaleX = 1.0f, scaleY = 1.0f, scaleZ = 1.0f; 
float translateX = 0.0f, translateY = 0.0f, translateZ = 0.0f; 

void drawBox()
{
	// Red rectangle
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_LINE_LOOP);
	glVertex3f(-1.0, -1.0, -1.0);
	glVertex3f(1.0, -1.0, -1.0);
	glVertex3f(1.0, 1.0, -1.0);
	glVertex3f(-1.0, 1.0, -1.0);
	glEnd();

	// Green rectangle
	glColor3f(0.0, 1.0, 0.0);
	glBegin(GL_LINE_LOOP);
	glVertex3f(-1.0, -1.0, 1.0);
	glVertex3f(1.0, -1.0, 1.0);
	glVertex3f(1.0, 1.0, 1.0);
	glVertex3f(-1.0, 1.0, 1.0);
	glEnd();

	// Blue lines
	glColor3f(0.0, 0.0, 1.0);
	glBegin(GL_LINES);
	glVertex3f(-1.0, -1.0, -1.0);
	glVertex3f(-1.0, -1.0, 1.0);
	glVertex3f(1.0, -1.0, -1.0);
	glVertex3f(1.0, -1.0, 1.0);
	glVertex3f(1.0, 1.0, -1.0);
	glVertex3f(1.0, 1.0, 1.0);
	glVertex3f(-1.0, 1.0, -1.0);
	glVertex3f(-1.0, 1.0, 1.0);
	glEnd();
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//glLoadIdentity();
	glPushMatrix();		 

	glTranslatef(translateX, translateY, translateZ);
	glScalef(scaleX, scaleY, scaleZ);

	glRotatef(45.0, 1.0, 1.0, 1.0);
	glScalef(0.1, 0.2, 0.1);
	drawBox();
	glPopMatrix();
	glFlush();
}

void xyzRotate(char mode)
{
	switch (mode) {
	case 'x': glRotatef(PI, 1, 0, 0); break;
	case 'y': glRotatef(PI, 0, 1, 0); break;
	case 'z': glRotatef(PI, 0, 0, 1); break;
	default: break;
	}
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'x': xyzRotate('x'); glutPostRedisplay(); break;
	case 'y': xyzRotate('y'); glutPostRedisplay(); break;
	case 'z': xyzRotate('z'); glutPostRedisplay(); break;

	case 's':
		scaleX += 0.1f;
		scaleY += 0.1f;
		scaleZ += 0.1f;
		glutPostRedisplay();
		break;

	case 'a':
		scaleX -= 0.1f;
		scaleY -= 0.1f;
		scaleZ -= 0.1f;
		glutPostRedisplay();
		break;

	case 't':
		translateX += 0.1f;
		glutPostRedisplay();
		break;

	case 'r':
		translateX -= 0.1f;
		glutPostRedisplay();
		break;

	default: break;
	}
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_SINGLE);
	glutCreateWindow("Transformation");

	glClearColor(1.0, 1.0, 1.0, 0.0);
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutMainLoop();

	return 0;
}