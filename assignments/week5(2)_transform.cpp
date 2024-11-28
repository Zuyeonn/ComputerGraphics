//20221365 박주연
//컴퓨터그래픽스 5주차 과제(2)
#include <glut.h>


void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // Red Cube 
    glColor3f(1.0, 0.0, 0.0);  
    glutSolidCube(0.3);

    // Green Cube 
    glPushMatrix();
    glColor3f(0.0, 1.0, 0.0); 
    glTranslatef(0.45, 0.45, 0.0);  // Translation 
    glRotatef(45.0, 0.0, 0.0, 1.0);  // Rotation
    glutSolidCube(0.3);
    glPopMatrix();

    // Blue Cube 
    glPushMatrix();
    glColor3f(0.0, 0.0, 1.0);  
    glTranslatef(0.6, 0.0, 0.0);  // Translation 
    glRotatef(45.0, 0.0, 0.0, 1.0);  // Rotation
    glutSolidCube(0.3);
    glPopMatrix();

    // Magenta Cube
    glPushMatrix();
    glColor3f(1.0, 0.0, 1.0); 
    glTranslatef(-0.45, -0.45, 0.0);  // Translation
    glRotatef(45.0, 0.0, 0.0, 1.0);  // Rotation
    glutSolidCube(0.3);
    glPopMatrix();

    // Yellow Cube 
    glPushMatrix();
    glColor3f(1.0, 1.0, 0.0);  
    glTranslatef(0.45, -0.45, 0.0);  // Translation 
    glRotatef(45.0, 0.0, 0.0, 1.0);  // Rotation
    glutSolidCube(0.3);
    glPopMatrix();

    // Gray Cube 
    glPushMatrix();
    glColor3f(0.5, 0.5, 0.5);  
    glTranslatef(-0.45, 0.45, 0.0);  // Translation 
    glRotatef(45.0, 0.0, 0.0, 1.0);  // Rotation
    glutSolidCube(0.3);
    glPopMatrix();

    // Cyan Cube (Bottom right corner)
    glPushMatrix();
    glColor3f(0.0, 1.0, 1.0);  
    glTranslatef(0.85, -0.85, 0.0); 
    glutSolidCube(0.3);
    glPopMatrix();

    glFlush();
}



int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("transform");

    glClearColor(1.0, 1.0, 1.0, 1.0);
    glEnable(GL_DEPTH_TEST); 

    glutDisplayFunc(display);


    glutMainLoop();
    return 0;
}
