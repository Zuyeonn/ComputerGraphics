// ��ǻ�ͱ׷��Ƚ� �߰�����
// 20221365 ���ֿ�
#include<iostream>
#include<glut.h>
#include <math.h> 
using namespace std;

#define PI 3.141592
float scaleX = 1.0f, scaleY = 1.0f, scaleZ = 1.0f;
float translateX = 0.0f, translateY = 0.0f, translateZ = 0.0f;
float translatex = 0.0f, translatey = 0.0f, translatez = 0.0f;

float shoulder = 0, elbow = 0;
float legSwing = 0; bool legSwingDirection = true;   // �ٸ��� ������ ����, ���� (true: ������, false: �ڷ�)
float moveX = 0.0f, moveY = 0.0f; // ĳ������ ��ġ
bool armAnim = false, legAnim = false; // ��, �ٸ� �ִϸ��̼� Ȱ��ȭ ����
string armDirection = "clockwise", legDirection = "clockwise"; // ��, �ٸ� ȸ�� ����

float textScale = 1.0f; // "��" ������ ������ ũ��
bool scaleAnim = false; // ���� ũ�� ���� �ִϸ��̼� Ȱ��ȭ ����
bool textScaleDirection = true; // ���� ũ�� ����/���� ���� (true: ����, false: ����)

bool giScaleAnim = false;    // '��' ������ Ȯ��/��� �ִϸ��̼� Ȱ��ȭ ����
bool giScaleDirection = true; // '��' ���� Ȯ�� ���� (true: Ȯ��, false: ���)
float giScale = 1.0f;        // '��' ������ ���� ������ ũ��

float rotateBa = 0.0f, rotateGi = 0.0f; // '��' , '��' ������ ȸ�� ����
bool rotateBaAnim = false, rotateGiAnim = false; // '��' , '��' ������ ȸ�� �ִϸ��̼� Ȱ��ȭ
float shakeGi = 0.0f; // '��' ����
bool shakeGiAnim = false;


float beeX = 0.0f, beeY = 0.0f; float speedX = 0.0003f, speedY = 0.0003f; // ���� ��ġ�� �ӵ�
float beeRotation = 0.0f; // ���� ȸ�� ����

float scaleFactor = 1.0f;  // ȭ�� Ȯ��/��� ����
bool isScalingUp = true;   // Ȯ�� ���� ����
int repeatCount = 0;       // �ݺ� Ƚ��

float characterRotation = 0.0f; // ĳ���� ȸ�� ����
bool characterRotateAnim = false; // ĳ���� ȸ�� �ִϸ��̼� Ȱ��ȭ ����

// ������ "��" ������ �ִϸ��̼��� ���� ���� �߰�
bool jumpAnim = false;
float jumpHeight = 0.0f;
bool isJumpingUp = true;

bool giMoveAnim = false;
float giMoveOffset = 0.0f;
bool giMovingRightUp = true;

// �ٸ� �Ĵ��Ĵ� �ִϸ��̼��� ���� ����
float legFlapAngle = 0.0f;
bool legFlapAnim = false;
bool legFlapDirection = true; // true�� ��������, false�� ���̴� ����

void drawBox() {
	// �ո� 
	glColor3f(1.0, 0.0, 0.0); // ������
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.5, 0.0, -0.5);
	glVertex3f(0.5, 0.0, -0.5);
	glVertex3f(0.5, 2.0, -0.5);
	glVertex3f(-0.5, 2.0, -0.5);
	glEnd();

	// �޸�
	glColor3f(0.0, 1.0, 0.0); // �ʷϻ�
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.5, 0.0, 0.5);
	glVertex3f(0.5, 0.0, 0.5);
	glVertex3f(0.5, 2.0, 0.5);
	glVertex3f(-0.5, 2.0, 0.5);
	glEnd();

	// ���� 
	glColor3f(0.0, 1.0, 1.0); // �ϴû�
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.5, 2.0, -0.5);
	glVertex3f(0.5, 2.0, -0.5);
	glVertex3f(0.5, 2.0, 0.5);
	glVertex3f(-0.5, 2.0, 0.5);
	glEnd();

	// �Ʒ��� 
	glColor3f(0.0, 0.0, 1.0); // ����
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.5, 0.0, -0.5);
	glVertex3f(0.5, 0.0, -0.5);
	glVertex3f(0.5, 0.0, 0.5);
	glVertex3f(-0.5, 0.0, 0.5);
	glEnd();
}

void drawBox2() {
	// �ո� 
	glColor3f(0.0, 0.0, 0.0); // ������
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.5, 0.0, -0.5);
	glVertex3f(0.5, 0.0, -0.5);
	glVertex3f(0.5, 2.0, -0.5);
	glVertex3f(-0.5, 2.0, -0.5);
	glEnd();

	// �޸� 
	glColor3f(0.6, 0.3, 0.0); // ����
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.5, 0.0, 0.5);
	glVertex3f(0.5, 0.0, 0.5);
	glVertex3f(0.5, 2.0, 0.5);
	glVertex3f(-0.5, 2.0, 0.5);
	glEnd();

	// ���� 
	glColor3f(0.5, 0.0, 0.5); // �����
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.5, 2.0, -0.5);
	glVertex3f(0.5, 2.0, -0.5);
	glVertex3f(0.5, 2.0, 0.5);
	glVertex3f(-0.5, 2.0, 0.5);
	glEnd();

	// �Ʒ��� 
	glColor3f(0.0, 0.39, 0.0); // ���� �ʷϻ�
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.5, 0.0, -0.5);
	glVertex3f(0.5, 0.0, -0.5);
	glVertex3f(0.5, 0.0, 0.5);
	glVertex3f(-0.5, 0.0, 0.5);
	glEnd();
}

void display(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPushMatrix();
	glScalef(scaleFactor, scaleFactor, scaleFactor); // ��ü ��� Ȯ�� ����

	// '��' ���� ȸ��
	glPushMatrix();
	if (rotateBaAnim) {
		rotateBa += 0.05f;
		if (rotateBa >= 360.0f) rotateBa -= 360.0f;
	}
	glTranslatef(0.0f, 0.0f, 0.0f);
	glRotatef(rotateBa, 0.0f, 1.0f, 0.0f); // y�� ȸ��

	// '��' ���� �׸��� �� ������ �����ϸ�
	glPushMatrix();
	glTranslatef(-0.75, -0.5, 0.0); // ���������� �̵�
	glScalef(textScale, textScale, textScale); // ũ�� ����
	glTranslatef(0.75, 0.5, 0.0);  // ���� ��ġ�� ����

	// '��'�� ���� '��'
	glPushMatrix();
	glTranslatef(-0.8, 0.0, 0.0);
	glTranslatef(translateX, translateY, translateZ);
	glScalef(scaleX, scaleY, scaleZ);
	glRotatef(20.0, 1.0, 1.0, 0.0);
	glScalef(0.1, 0.2, 0.1);
	drawBox();
	glPopMatrix();
	// '��'�� ������ '��'
	glPushMatrix();
	glTranslatef(-0.6, 0.0, 0.0);
	glTranslatef(translateX, translateY, translateZ);
	glScalef(scaleX, scaleY, scaleZ);
	glRotatef(20.0, 1.0, 1.0, 0.0);
	glScalef(0.1, 0.2, 0.1);
	drawBox();
	glPopMatrix();
	// '��'�� �߰� '��'
	glPushMatrix();
	glTranslatef(-0.7, 0.18, 0.0);
	glTranslatef(translateX, translateY, translateZ);
	glScalef(scaleX, scaleY, scaleZ);
	glScalef(0.1, 0.05, 0.1);
	glRotatef(20.0, 1.0, 1.0, 0.0);
	drawBox();
	glPopMatrix();
	// '��'�� �� �� '��'
	glPushMatrix();
	glTranslatef(-0.7, 0.0, 0.0);
	glTranslatef(translateX, translateY, translateZ);
	glScalef(scaleX, scaleY, scaleZ);
	glScalef(0.1, 0.05, 0.1);
	glRotatef(20.0, 1.0, 1.0, 0.0);
	drawBox();
	glPopMatrix();

	// '��'�� '��'
	glPushMatrix();
	glTranslatef(-0.4, 0.0, 0.0);
	glTranslatef(translateX, translateY, translateZ);
	glScalef(scaleX, scaleY, scaleZ);
	glRotatef(20.0, 1.0, 1.0, 0.0);
	glScalef(0.1, 0.2, 0.1);
	drawBox2();
	glPopMatrix();
	// '��'�� '��' (�� ���� ���)
	glPushMatrix();
	glTranslatef(-0.28, 0.2, 0.0);
	glTranslatef(translateX, translateY, translateZ);
	glScalef(scaleX, scaleY, scaleZ);
	glColor3f(1.0, 0.71, 0.76);
	glutWireSphere(0.07, 20, 20);
	glPopMatrix();

	glPopMatrix(); // '��' ȸ�� ��ȯ ��


	// '��' ����
	glPushMatrix();
	if (rotateGiAnim) {
		rotateGi += 0.02f;
		if (rotateGi >= 360.0f) rotateGi -= 360.0f;
	}
	if (shakeGiAnim) {
		shakeGi += 0.1f;
		glTranslatef(0.0f, sin(shakeGi * 10) * 0.02f, 0.0f); // ���� ȿ��
	}
	if (giMoveAnim) {
		glTranslatef(giMoveOffset, giMoveOffset, 0.0f); // �缱 ���� �̵�
	}

	glTranslatef(0.0f, 0.0f, 0.0f);
	glRotatef(rotateGi, 1.0f, 0.0f, 0.0f); // x�� ȸ��
	glScalef(giScale, giScale, giScale); // '��' ���� Ȯ��/��� ����
	// '��' �� '��' �κ�
	glPushMatrix();
	glTranslatef(-0.6, -0.3, 0.0);
	glTranslatef(translateX, translateY, translateZ);
	glScalef(scaleX, scaleY, scaleZ);
	glRotatef(20.0, 1.0, 1.0, 0.0);
	glScalef(0.4, 0.05, 0.1);
	drawBox2();
	glPopMatrix();
	// '��'�� '��' �κ� (���� ���� ���)
	glPushMatrix();
	glTranslatef(-0.47, -0.3, 0.0);
	glTranslatef(translateX, translateY, translateZ);
	glScalef(scaleX, scaleY, scaleZ);
	glRotatef(80.0, 1.0, 0.0, 0.0);
	glColor3f(0.5, 0.5, 0.5);
	glutWireCone(0.07, 0.4, 40, 40);
	glPopMatrix();

	glPopMatrix();
	glPopMatrix();

	// �� ����
	glPushMatrix();
	glTranslatef(beeX, beeY, 0.0f); // ���� ��ġ ����
	glRotatef(beeRotation, 1.0f, 1.0f, 1.0f); // ȸ�� �߰�
	// ����
	glColor3f(1.0, 0.85, 0.0);
	glTranslatef(0.0, 0.0, 0.0);
	glPushMatrix();
	glScalef(0.06, 0.05, 0.08);
	glutSolidCube(1.0);
	glPopMatrix();
	// ���� ���� 
	glPushMatrix();
	glColor3f(0.53, 0.81, 0.98);
	glTranslatef(-0.03, 0.03, 0.0);
	glutSolidSphere(0.02, 15, 15);
	glPopMatrix();
	// ������ ����
	glPushMatrix();
	glColor3f(0.53, 0.81, 0.98);
	glTranslatef(0.03, 0.03, 0.0);
	glutSolidSphere(0.02, 15, 15);
	glPopMatrix();

	glPopMatrix();

	// ĳ���� ����
	glPushMatrix(); // ��ü ĳ���� ��ȯ ����
	// ĳ���� ���� �ִϸ��̼� ����
	if (jumpAnim) {
		glTranslatef(0.0f, jumpHeight, 0.0f);
	}
	// ĳ���� ȸ�� �ִϸ��̼� ����
	if (characterRotateAnim) {
		glRotatef(characterRotation, 0.0f, 1.0f, 0.0f); // y�� ���� ȸ��
	}
	glTranslatef(translatex, translatey, translatez); // ĳ���� ��ü ��ġ �̵�

	glPushMatrix();
	// Body
	glTranslatef(0.3, 0.3, 0);
	glPushMatrix();
	glScalef(0.4, 0.4, 0.2);
	glColor3f(0.68, 0.85, 0.9);
	glutSolidCube(1.0);
	glColor3f(0.0, 0.0, 0.0);
	glutWireCube(1.0);
	glPopMatrix();

	// Head
	glPushMatrix();
	glTranslatef(0.0, 0.35, 0);
	glColor3f(1.0, 0.85, 0.7);
	glutSolidSphere(0.15, 30, 30);
	glPopMatrix();

	// �� (����)
	glPushMatrix();
	glTranslatef(-0.05, 0.4, -0.15);
	glColor3f(0.0, 0.0, 0.0);
	glutSolidSphere(0.02, 10, 10);
	glPopMatrix();
	// �� (������)
	glPushMatrix();
	glTranslatef(0.05, 0.4, -0.15);
	glColor3f(0.0, 0.0, 0.0);
	glutSolidSphere(0.02, 10, 10);
	glPopMatrix();

	// ������ �� Upper Arm
	glPushMatrix();
	glTranslatef(0.1, 0.15, 0.0);
	glRotatef((GLfloat)shoulder, 0.0, 0.0, 1.0);
	if (armAnim) glRotatef((GLfloat)shoulder, 0.0, 0.0, 1.0); // ��� ȸ��
	glTranslatef(0.2, 0.0, 0.0);
	glPushMatrix();
	glScalef(0.2, 0.1, 0.1);
	glColor3f(0.68, 0.85, 0.9);
	glutSolidCube(1.0);
	glColor3f(0.0, 0.0, 0.0);
	glutWireCube(1.0);
	glPopMatrix();
	// ������ �� Lower Arm
	glTranslatef(0.1, 0.0, 0.0);
	glRotatef((GLfloat)elbow, 0.0, 0.0, 1.0);
	glTranslatef(0.1, 0.0, 0.0);
	glPushMatrix();
	glScalef(0.2, 0.1, 0.1);
	glColor3f(1.0, 0.85, 0.7);
	glutSolidCube(1.0);
	glColor3f(0.0, 0.0, 0.0);
	glutWireCube(1.0);
	glPopMatrix();
	glPopMatrix();

	// ���� �� Upper Arm
	glPushMatrix();
	glTranslatef(-0.1, 0.15, 0.0);
	glRotatef(-(GLfloat)shoulder, 0.0, 0.0, 1.0);
	if (armAnim) glRotatef(-(GLfloat)shoulder, 0.0, 0.0, 1.0);
	glTranslatef(-0.2, 0.0, 0.0);
	glPushMatrix();
	glScalef(0.2, 0.1, 0.1);
	glColor3f(0.68, 0.85, 0.9);
	glutSolidCube(1.0);
	glColor3f(0.0, 0.0, 0.0);
	glutWireCube(1.0);
	glPopMatrix();
	// ���� �� Lower Arm
	glTranslatef(-0.2, 0.0, 0.0);
	glRotatef(-(GLfloat)elbow, 0.0, 0.0, 1.0);
	glPushMatrix();
	glScalef(0.2, 0.1, 0.1);
	glColor3f(1.0, 0.85, 0.7);
	glutSolidCube(1.0);
	glColor3f(0.0, 0.0, 0.0);
	glutWireCube(1.0);
	glPopMatrix();
	glPopMatrix();

	// ������ �ٸ� Upper Leg
	glPushMatrix();
	glTranslatef(0.1, -0.32, 0.0);
	if (legAnim) glRotatef((GLfloat)legSwing, 1.0, 0.0, 0.0);  // �ٸ� �յڷ� ������
	if (legFlapAnim) glRotatef(legFlapAngle, 0.0, 0.0, 1.0); // �ٸ� �Ĵ��Ĵ� �ִϸ��̼�
	glPushMatrix();
	glScalef(0.15, 0.25, 0.1);
	glColor3f(0.55, 0.27, 0.07);
	glutSolidCube(1.0);
	glColor3f(0.0, 0.0, 0.0);
	glutWireCube(1.0);
	glPopMatrix();
	// ������ �ٸ� Lower Leg
	glTranslatef(0.0, -0.25, 0.0);
	glPushMatrix();
	glScalef(0.15, 0.25, 0.1);
	glColor3f(1.0, 0.85, 0.7);
	glutSolidCube(1.0);
	glColor3f(0.0, 0.0, 0.0);
	glutWireCube(1.0);
	glPopMatrix();
	glPopMatrix();

	// ���� �ٸ� Upper Leg
	glPushMatrix();
	glTranslatef(-0.1, -0.32, 0.0);
	if (legAnim) glRotatef(-(GLfloat)legSwing, 1.0, 0.0, 0.0);  // �ݴ� �������� ������
	if (legFlapAnim) glRotatef(-legFlapAngle, 0.0, 0.0, 1.0); // �ݴ� �������� �Ĵ��Ĵ�
	glPushMatrix();
	glScalef(0.15, 0.25, 0.1);
	glColor3f(0.55, 0.27, 0.07);
	glutSolidCube(1.0);
	glColor3f(0.0, 0.0, 0.0);
	glutWireCube(1.0);
	glPopMatrix();
	// ���� �ٸ� Lower Leg
	glTranslatef(0.0, -0.25, 0.0);
	glPushMatrix();
	glScalef(0.15, 0.25, 0.1);
	glColor3f(1.0, 0.85, 0.7);
	glutSolidCube(1.0);
	glColor3f(0.0, 0.0, 0.0);
	glutWireCube(1.0);
	glPopMatrix();
	glPopMatrix();

	glPopMatrix();
	glPopMatrix();
	glPopMatrix(); // ��ü ��� Ȯ�� ��ȯ ��
	glFlush();
}

void xyzRotate(char mode) {
	switch (mode) {
	case 'x': glRotatef(PI, 1, 0, 0); break;
	case 'y': glRotatef(PI, 0, 1, 0); break;
	case 'z': glRotatef(PI, 0, 0, 1); break;
	default: break;
	}
}

void idle() {
	// 1. ��ü Ȯ��, ��� 3ȸ �ݺ� �ִϸ��̼�
	if (repeatCount < 3) {
		if (isScalingUp) {
			scaleFactor += 0.0008f;  // Ȯ��
			if (scaleFactor >= 1.65f) { isScalingUp = false; }
		}
		else {
			scaleFactor -= 0.0008f;  // ���
			if (scaleFactor <= 1.0f) { isScalingUp = true; repeatCount++; } // �ݺ� Ƚ�� ����
		}
	}
	// 2. �� ������ �ִϸ��̼�
	beeX += speedX; beeY += speedY;
	beeRotation += 0.05f;  // ���� ȸ�� �ӵ�
	if (beeRotation >= 360.0f) beeRotation -= 360.0f;
	// ȭ�� �����ڸ��� ��������� �ݴ� �������� ��ȯ�ϸ� ������ �ӵ� ����
	if (beeX > 0.9f) {
		beeX = 0.9f; // ȭ�� ������ ������ �ʵ��� ����
		speedX = -0.0002f * (rand() % 5 + 1); // ���� �������� ��ȯ
	}
	else if (beeX < -0.9f) {
		beeX = -0.9f;
		speedX = 0.0002f * (rand() % 5 + 1); // ������ �������� ��ȯ
	}
	if (beeY > 0.9f) {
		beeY = 0.9f;
		speedY = -0.0002f * (rand() % 5 + 1); // �Ʒ��� �������� ��ȯ
	}
	else if (beeY < -0.9f) {
		beeY = -0.9f;
		speedY = 0.0002f * (rand() % 5 + 1); // ���� �������� ��ȯ
	}
	// 3. '��' ���� ũ�� �ִϸ��̼� (FPS)
	if (scaleAnim) {
		if (textScaleDirection) textScale += 0.0004;
		else textScale -= 0.0004;
		if (textScale >= 1.5) textScaleDirection = false; // ũ�� ���ҷ� ��ȯ
		else if (textScale <= 1.0) textScaleDirection = true; // ũ�� ������ ��ȯ
	}
	// 4. �� �� �Ʒ��� �����̴� �ִϸ��̼�
	if (armAnim) {
		if (armDirection == "clockwise") shoulder += 0.05;
		else shoulder -= 0.05;
		if (shoulder >= 40) armDirection = "anticlockwise";
		else if (shoulder <= -30) armDirection = "clockwise";
	}
	// 5. �ٸ� �ϵڷ� �����̴� �ִϸ��̼�
	if (legAnim) {
		if (legDirection == "clockwise") legSwing += 0.1;
		else legSwing -= 0.1;
		if (legSwing >= 45) legDirection = "anticlockwise";
		else if (legSwing <= -45) legDirection = "clockwise";
	}
	// 6. ĳ���� ���ڸ� ȸ�� �ִϸ��̼�
	if (characterRotateAnim) {
		characterRotation += 0.08f; // ȸ�� �ӵ� ����
		if (characterRotation >= 360.0f) characterRotation -= 360.0f; // ���� ����
	}
	// 7. '��' ���� Ȯ��/��� �ִϸ��̼�
	if (giScaleAnim) {
		if (giScaleDirection) {
			giScale += 0.0015f;
			if (giScale >= 1.5f) giScaleDirection = false; // ��ҷ� ��ȯ
		}
		else {
			giScale -= 0.0015f;
			if (giScale <= 1.0f) giScaleDirection = true; // Ȯ��� ��ȯ
		}
	}
	// 8. ĳ���� ���� �ִϸ��̼�
	if (jumpAnim) {
		if (isJumpingUp) {
			jumpHeight += 0.0005f;
			if (jumpHeight >= 0.2f) { isJumpingUp = false; }
		}
		else {
			jumpHeight -= 0.0005f;
			if (jumpHeight <= 0.0f) { isJumpingUp = true; }
		}
	}
	// 9. '��' ���� �缱 �̵� �ִϸ��̼�
	if (giMoveAnim) {
		if (giMovingRightUp) {
			giMoveOffset += 0.0007f;
			if (giMoveOffset >= 0.2f) { giMovingRightUp = false; }
		}
		else {
			giMoveOffset -= 0.0007f;
			if (giMoveOffset <= -0.2f) { giMovingRightUp = true; }
		}
	}
	// 10. ĳ���� �ٸ� �Ĵ��Ĵ� �ִϸ��̼�
	if (legFlapAnim) {
		if (legFlapDirection) {
			legFlapAngle += 0.1f;
			if (legFlapAngle >= 20.0f) { legFlapDirection = false; } // �ٸ��� �������� �ִ밢��
		}
		else {
			legFlapAngle -= 0.1f;
			if (legFlapAngle <= 0.0f) { legFlapDirection = true; } // �ٸ��� ���̴� �ִ밢��
		}
	}
		glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y) {
	switch (key) {
	// '��' ������ ���� Ű����
	case 'x': xyzRotate('x'); glutPostRedisplay(); break; // 'x, y, z' ���� ȸ��
	case 'y': xyzRotate('y'); glutPostRedisplay(); break;
	case 'z': xyzRotate('z'); glutPostRedisplay(); break;
	case 's': scaleX += 0.1f; scaleY += 0.1f; scaleZ += 0.1f; glutPostRedisplay(); break; // 's' ���� Ȯ��
	case 'a': scaleX -= 0.1f; scaleY -= 0.1f; scaleZ -= 0.1f; glutPostRedisplay(); break; // 'a' ���� ���
	case 't': translateX += 0.1f; glutPostRedisplay(); break; // 't' ���� ���������� �̵�
	case 'r': translateX -= 0.1f; glutPostRedisplay(); break; // 'r' ���� �������� �̵�
	case 'd': rotateBaAnim = !rotateBaAnim; rotateGiAnim = !rotateGiAnim;glutPostRedisplay();break; // 'd' '��','��' ȸ��
	case 'q': shakeGiAnim = !shakeGiAnim; break; // 'q' '��' ���� ����

	// ĳ���Ϳ� ���� Ű����
	case 'e': elbow += 5; glutPostRedisplay(); break; // 'e' �� �ø� (�ð� �������� ȸ��)
	case 'w': elbow -= 5; glutPostRedisplay(); break; // 'w' �� ���� (�ݽð� �������� ȸ��)
	case 'h': shoulder += 5; glutPostRedisplay(); break; // 'h' ��� �ø� (�ð� �������� ȸ��)
	case 'g': shoulder -= 5; glutPostRedisplay(); break; // 'g' ��� ���� (�ݽð� �������� ȸ��)
	case 'l': translatex += 0.1f; glutPostRedisplay(); break; // 'l' ���� ���������� �̵�
	case 'j': translatex -= 0.1f; glutPostRedisplay(); break; // 'j' ���� �������� �̵�
	case 'i': translatey += 0.1f; glutPostRedisplay(); break; // 'i' ���� ���� �̵�
	case 'k': translatey -= 0.1f; glutPostRedisplay(); break; // 'k' ���� �Ʒ��� �̵�

	// �ִϸ��̼� - Ű����
	case 'p': armAnim = !armAnim; scaleAnim = !scaleAnim; break; // 'p' �� �ִϸ��̼� + FPS ����/����
	case 'c': characterRotateAnim = !characterRotateAnim; legAnim = !legAnim; break; // 'c' ĳ���� ȸ�� ����/����
	case 'f': repeatCount = 0; scaleFactor = 1.0f; isScalingUp = true; glutIdleFunc(idle); // 'f' ��ü Ȯ��, ��� 3ȸ �ݺ�
	case 'u': giScaleAnim = !giScaleAnim; break; // 'u' '��' ���� Ȯ��/��� �ִϸ��̼�
	case 'v': jumpAnim = !jumpAnim; giMoveAnim = !giMoveAnim; legFlapAnim = !legFlapAnim; break; // 'v' ĳ���� ����, ĳ���� �ٸ� �Ĵ��Ĵ�, '��' �缱���� �̵�

	default: break;
	}
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_SINGLE);
	glutInitWindowSize(600, 600);
	glutCreateWindow("OpenGL");

	glClearColor(1.0, 1.0, 1.0, 0.0);
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutIdleFunc(idle);
	glutMainLoop();

	return 0;
}