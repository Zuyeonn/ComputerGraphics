// 20221365 박주연
// 컴퓨터그래픽스 6주차 과제1
#include<glut.h>


GLfloat blueAngle = 0.0f;

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glLoadIdentity();

	glColor3f(1.0f, 0.0f, 0.0f);   // red
	glutSolidSphere(0.1f, 100, 100);

	glPushMatrix();
	glRotatef(blueAngle, 0.0f, 0.0f, 1.0f);
	glTranslatef(0.6f, 0.0f, 0.0f);
	glColor3f(0.0f, 0.0f, 1.0f);   // blue
	glutSolidSphere(0.05f, 100, 100);


	glPushMatrix();
	glRotatef(-2*blueAngle, 0.0f, 0.0f, 1.0f);
	glTranslatef(0.15f, 0.0f, 0.0f);
	glColor3f(0.0f, 0.0f, 0.0f);   //  black
	glutSolidSphere(0.03f, 100, 100);
	glPopMatrix();




	glPushMatrix();
	glRotatef(blueAngle, 0.0f, 0.0f, 1.0f);
	glTranslatef(0.3f, 0.0f, 0.0f);
	glColor3f(0.0f, 1.0f, 0.0f);   // green
	glutSolidSphere(0.05f, 100, 100);

	glPushMatrix();
	glRotatef(blueAngle, 0.0f, 0.0f, 1.0f);
	glTranslatef(0.15f, 0.0f, 0.0f);
	glColor3f(0.53f, 0.81f, 0.98f);   // sky blue
	glutSolidSphere(0.02f, 100, 100);
	glPopMatrix();




	glPopMatrix();
	glRotatef(1 - blueAngle, 0.0f, 0.0f, 1.0f);
	glTranslatef(0.3f, 0.0f, 0.0f);
	glColor3f(1.0f, 1.0f, 0.0f);   // yellow
	glutSolidSphere(0.05f, 100, 100);

	glPushMatrix();
	glRotatef(1 - blueAngle, 0.0f, 0.0f, 1.0f);
	glTranslatef(0.15f, 0.0f, 0.0f);
	glColor3f(1.0f, 0.75f, 0.8f);   // pink
	glutSolidSphere(0.03f, 100, 100);
	glPopMatrix();


	blueAngle += 0.5f;
	if (blueAngle == 360) blueAngle = 0;
	glFlush();
}



int main(int argc, char** argv)
{
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_SINGLE);
	glutCreateWindow("Transformation");

	glutDisplayFunc(display);
	glutIdleFunc(display);

	glutMainLoop();

	return 0;
}
