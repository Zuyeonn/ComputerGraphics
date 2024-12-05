#include <iostream>
#include <glut.h> 
#include <gl/glu.h>
using namespace std;

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(0.0, 0.0, 0.0, 0.0, 0.0, 5.0, 0.0, 1.0, 0.0);

	glColor3f(1, 0, 0); // red
    glTranslatef(10, 5, 10);
	glutWireTeapot(3);

	glColor3f(0, 1, 0); // green
	glTranslatef(-10, -5, -5);
	glutWireTeapot(3);

	glColor3f(0, 0, 1); // blue
	glTranslatef(-10, -5, 15); 
	glutWireTeapot(3);
	glFlush();
}

void reshape(int w, int h)
{
	// Viewport 설정: 윈도우 왼쪽 위에 반쪽 크기 설정
	glViewport(0, h / 2, w / 2, h / 2);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//glOrtho(-20.0, 20.0, -20.0, 20.0, -20.0, 30.0);
	glFrustum(-20, 20, -20, 20, 5, 30);
	glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_SINGLE);
	glutInitWindowSize(600, 400); // 윈도우 크기
	glutInitWindowPosition(100, 200); // 윈도우 위치
	glutCreateWindow("Viewing Transformation");
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}