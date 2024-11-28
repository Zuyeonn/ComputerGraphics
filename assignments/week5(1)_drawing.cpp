// 20221365 ���ֿ�
// ��ǻ�ͱ׷��Ƚ� 5���� ����(1)

#include <glut.h>

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);  

    // ��
    glBegin(GL_LINE_LOOP);
    glColor3f(0.0f, 1.0f, 1.0f);  
    glVertex3f(-0.7f, 0.85f, 0.0f);  
    glVertex3f(-0.75f, 0.6f, 0.0f);  
    glVertex3f(-0.6f, 0.75f, 0.0f);  
    glVertex3f(-0.8f, 0.75f, 0.0f);
    glVertex3f(-0.65f, 0.6f, 0.0f);  
    glEnd();

    // �ﰢ��
    glBegin(GL_TRIANGLES);
    glColor3f(1.0f, 1.0f, 0.0f);  
    glVertex3f(0.7f, 0.9f, 0.0f);
    glVertex3f(0.6f, 0.7f, 0.0f);
    glVertex3f(0.8f, 0.7f, 0.0f);
    glEnd();

    // ������
    glBegin(GL_LINE_LOOP);
    glColor3f(1.0f, 0.0f, 1.0f);  
    glVertex3f(0.0f, 0.9f, 0.0f);
    glVertex3f(-0.1f, 0.8f, 0.0f);
    glVertex3f(-0.05f, 0.7f, 0.0f);
    glVertex3f(0.05f, 0.7f, 0.0f);
    glVertex3f(0.1f, 0.8f, 0.0f);
    glEnd();

    // '��'
    glColor3f(1.0f, 1.0f, 1.0f); 
    // '��' 
    glBegin(GL_LINE_STRIP);
    glVertex3f(-0.2f, 0.2f, 0.0f); 
    glVertex3f(-0.2f, 0.0f, 0.0f);
    glVertex3f(0.1f, 0.0f, 0.0f);
    glVertex3f(0.1f, 0.2f, 0.0f);
    glEnd();

    glBegin(GL_LINES);
    glVertex3f(-0.2f, 0.1f, 0.0f);
    glVertex3f(0.1f, 0.1f, 0.0f);



    // '��'
    glBegin(GL_LINES);
    glVertex3f(0.2f, 0.2f, 0.0f);
    glVertex3f(0.2f, 0.0f, 0.0f);

    glVertex3f(0.2f, 0.1f, 0.0f);
    glVertex3f(0.4f, 0.1f, 0.0f);
    glEnd();

    // '��'
    glBegin(GL_LINES);
    glVertex3f(-0.2f, -0.1f, 0.0f);
    glVertex3f(0.2f, -0.1f, 0.0f);

    glVertex3f(0.2f, -0.1f, 0.0f);
    glVertex3f(0.2f, -0.3f, 0.0f);
    glEnd();



    // �ؿ� ��
    glBegin(GL_LINES);
    glVertex3f(-0.6f, -0.6f, 0.0f);
    glVertex3f(-0.2f, -0.6f, 0.0f);

    glVertex3f(-0.6f, -0.8f, 0.0f);
    glVertex3f(-0.2f, -0.8f, 0.0f);
    glEnd();

    // ��2
    glBegin(GL_LINE_STRIP);
    glVertex3f(0.2f, -0.6f, 0.0f);
    glVertex3f(0.6f, -0.6f, 0.0f);
    glVertex3f(0.6f, -0.8f, 0.0f);
    glVertex3f(0.2f, -0.8f, 0.0f);
    glEnd();

    glFlush(); 
}

void init(void)
{
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);  
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0); 
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("drawing");

    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
