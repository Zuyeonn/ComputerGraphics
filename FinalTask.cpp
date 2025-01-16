// 컴퓨터그래픽스 기말 대체 과제
// 20221365 박주연

#include <windows.h>
#include <iostream>
#include <gl/gl.h>
#include <gl/glu.h>
#include <math.h> 
#include <glut.h>
#include <cmath>
using namespace std;

#define WIDTH 600
#define HEIGHT 600
#define PI 3.141592

#define NUM_SNOWFLAKES 100 // 눈송이 개수
float snowX[NUM_SNOWFLAKES]; // 눈송이의 X 위치
float snowY[NUM_SNOWFLAKES]; // 눈송이의 Y 위치
float snowZ[NUM_SNOWFLAKES]; // 눈송이의 Z 위치
float snowSpeed[NUM_SNOWFLAKES]; // 눈송이가 떨어지는 속도

//camera position
GLfloat cameraPositionX = 5.0f;
GLfloat cameraPositionY = 5.0f;
GLfloat cameraPositionZ = 2.0f;

GLfloat lookAtX = 0.0f;
GLfloat lookAtY = 0.0f;
GLfloat lookAtZ = 0.0f;

GLfloat upX = 0.0f;
GLfloat upY = 1.0f;
GLfloat upZ = 0.0f;

bool isUpView = false;
bool isCameraLeft = false;

GLfloat vibrationAmount = 0.0;

// light
GLfloat ambient[] = { 0.1, 0.1, 0.1, 1.0 };
GLfloat diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat position[] = { 0, 0, 1, 1 };
GLfloat currentLightPosition[] = { 0, 0, 1, 1 };

// torus + sphere 장식품 material
GLfloat mat_a[] = { 0.1, 0.1, 0.1, 1.0 };
GLfloat mat_d[] = { 0.3, 0.6, 0.2, 1.0 };
GLfloat mat_s[] = { 0, 1, 0, 1.0 };
GLfloat low_sh[] = { 50.0 };
GLfloat material_emission[] = { 0.3,0.3,0,1 };

// material
// blue sphere
GLfloat ambient1[] = { 0.7, 0.7, 0.7, 0.1 };
GLfloat diffuse1[] = { 0.0, 0.0, 0.5, 1.0 };
GLfloat specular1[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat shininess1[] = { 5.0 };
GLfloat emission1[] = { 0, 0, 0.1, 1.0 };

// white sphere + 눈사람 몸통
GLfloat ambient2[] = { 0.2, 0.2, 0.2, 0.1 };
GLfloat diffuse2[] = { 0.5, 0.5, 1.0, 1.0 };
GLfloat specular2[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat shininess2[] = { 5.0 };
GLfloat emission2[] = { 0.2, 0.2, 0, 1 };

// yellow sphere
GLfloat ambient3[] = { 0.7, 0.7, 0.7, 0.1 };
GLfloat diffuse3[] = { 0.3, 0.2, 0.0, 1.0 };
GLfloat specular3[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat shininess3[] = { 50.0 };
GLfloat emission3[] = { 0.1,0.1,0,1 };

// red sphere
GLfloat ambient4[] = { 0.1, 0.1, 0.1, 1.0 };
GLfloat diffuse4[] = { 0.1, 0.0, 0.0, 1.0 };
GLfloat specular4[] = { 0.7, 1.0, 1.0, 1.0 };
GLfloat shininess4[] = { 50.0 };
GLfloat emission4[] = { 0.3, 0, 0, 1 };

// black 눈사람 눈
GLfloat ambient5[] = { 0.2, 0.2, 0.2, 1.0 }; 
GLfloat diffuse5[] = { 0.2, 0.2, 0.2, 1.0 }; 
GLfloat specular5[] = { 1.0, 1.0, 1.0, 1.0 }; 
GLfloat shininess5[] = { 40.0 };            
GLfloat emission5[] = { 0.0, 0.0, 0.0, 1.0 };



GLuint texID1, texID2, texID3, texID4, texID5; // texture ID

float rotationAngle = 0.0;
float rotationSpeed = 0.01f;

bool dir = true;

int ltype = 1;
float spotlightAngle = 10.0; // spotlight angle
float spotlightAttenuation = 1.0; // spotlight attenuation

float spin = 0;

bool rotationEnabled = false;


void initSnow() {  
	for (int i = 0; i < NUM_SNOWFLAKES; i++) {
		snowX[i] = (float(rand()) / RAND_MAX) * 3.0f - 2.0f; // X 위치 
		snowY[i] = (float(rand()) / RAND_MAX) * 4.0f;         // Y 위치 
		snowZ[i] = -0.8f;                                     // Z 위치 
		snowSpeed[i] = (float(rand()) / RAND_MAX) * 0.003f + 0.001f; // 속도 
	}
}

void updateSnow() {  // 눈 업데이트 함수
	for (int i = 0; i < NUM_SNOWFLAKES; i++) {
		snowY[i] -= snowSpeed[i]; // 눈송이를 아래로 이동
		if (snowY[i] < -1.0f) {  // 화면 아래로 떨어지면
			snowY[i] = 3.0f;      // 위로 다시 리셋
			snowX[i] = (float(rand()) / RAND_MAX) * 2.0f - 1.0f; 
		}
	}
}

void drawSnow() {  
	glDisable(GL_LIGHTING); 
	glDisable(GL_TEXTURE_2D); 
	glColor3f(1.0f, 1.0f, 1.0f); 

	for (int i = 0; i < NUM_SNOWFLAKES; i++) {
		glPushMatrix();
		glTranslatef(snowX[i], snowY[i], snowZ[i]); 
		glutSolidSphere(0.01, 10, 10); 
		glPopMatrix();
	}
	glEnable(GL_LIGHTING); 
	glEnable(GL_TEXTURE_2D);
}


void drawBox() {
	// 앞면 
	glColor3f(1.0, 1.0, 1.0); // 흰색
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.5, 0.0, -0.5);
	glVertex3f(0.5, 0.0, -0.5);
	glVertex3f(0.5, 2.0, -0.5);
	glVertex3f(-0.5, 2.0, -0.5);
	glEnd();

	// 뒷면 
	glColor3f(1.0, 1.0, 0.0); // 노란색
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.5, 0.0, 0.5);
	glVertex3f(0.5, 0.0, 0.5);
	glVertex3f(0.5, 2.0, 0.5);
	glVertex3f(-0.5, 2.0, 0.5);
	glEnd();

	// 윗면 
	glColor3f(0.5, 0.8, 1.0); // 하늘색
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.5, 2.0, -0.5);
	glVertex3f(0.5, 2.0, -0.5);
	glVertex3f(0.5, 2.0, 0.5);
	glVertex3f(-0.5, 2.0, 0.5);
	glEnd();

	// 아랫면 
	glColor3f(0.5, 0.8, 1.0); // 하늘색
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.5, 0.0, -0.5);
	glVertex3f(0.5, 0.0, -0.5);
	glVertex3f(0.5, 0.0, 0.5);
	glVertex3f(-0.5, 0.0, 0.5);
	glEnd();
}

void drawBox2() {
	// 앞면 
	glColor3f(1.0, 0.0, 0.0); // 빨간색
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.5, 0.0, -0.5);
	glVertex3f(0.5, 0.0, -0.5);
	glVertex3f(0.5, 2.0, -0.5);
	glVertex3f(-0.5, 2.0, -0.5);
	glEnd();

	// 뒷면
	glColor3f(0.0, 1.0, 0.0); // 초록색
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.5, 0.0, 0.5);
	glVertex3f(0.5, 0.0, 0.5);
	glVertex3f(0.5, 2.0, 0.5);
	glVertex3f(-0.5, 2.0, 0.5);
	glEnd();

	// 윗면 
	glColor3f(0.0, 1.0, 1.0); // 하늘색
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.5, 2.0, -0.5);
	glVertex3f(0.5, 2.0, -0.5);
	glVertex3f(0.5, 2.0, 0.5);
	glVertex3f(-0.5, 2.0, 0.5);
	glEnd();

	// 아랫면 
	glColor3f(0.0, 0.0, 1.0); // 남색
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.5, 0.0, -0.5);
	glVertex3f(0.5, 0.0, -0.5);
	glVertex3f(0.5, 0.0, 0.5);
	glVertex3f(-0.5, 0.0, 0.5);
	glEnd();
}

void drawSphere(float x, float y, float z, float radius, GLfloat ambient[], GLfloat diffuse[], GLfloat specular[], GLfloat shininess[], GLfloat emission[])
{
	glPushMatrix();
	glTranslatef(x, y, z);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emission);

	glutSolidSphere(radius, 40, 40);

	glPopMatrix();
}

void toggleRotation()
{
	rotationEnabled = !rotationEnabled;
}

void resetLightPosition()
{
	for (int i = 0; i < 4; ++i)
		currentLightPosition[i] = position[i];
}

void reshape(int w, int h) {
	glViewport(0, 0, w, h);
}

void updateCamera() {
	GLfloat t = 0.003f; // 카메라 이동 속도 조절
	cameraPositionX = (1.0f - t) * cameraPositionX + t * 0.0f;
	cameraPositionY = (1.0f - t) * cameraPositionY + t * 0.0f;
	cameraPositionZ = (1.0f - t) * cameraPositionZ + t * 2.0f;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(35.0, 1.0, 1.0, 30.0);

	gluLookAt(cameraPositionX, cameraPositionY, cameraPositionZ, lookAtX, lookAtY, lookAtZ, upX, upY, upZ);
}

void animateCamera() {
	GLfloat t = 0.005f;

	//lookAtX는 카메라가 바라보는 X축의 목표 위치
	lookAtX = (1.0f - t) * lookAtX + t * -5.0f; //카메라의 현재 시점 lookAtX를 목표위치 -5.0f로 점진적으로 이동시킴
	
	//cameraPositionY는 카메라의 Y축 위치
	cameraPositionY = (1.0f - t) * cameraPositionY + t * 5.0f; //카메라의 현재 위치를 목표 위치 5.0f로 점진적으로 이동시킴
	
	//카메라의 업 벡터 변경
	upX = (1.0f - t) * upX + t * 5.0f; //애니메이션 효과를 위해 카메라의 상단방향을 X축으로 기울이도록 조정

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(35.0, 1.0, 1.0, 30.0);

	gluLookAt(cameraPositionX, cameraPositionY, cameraPositionZ, lookAtX, lookAtY, lookAtZ, upX, upY, upZ);
}


void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1, 1, -1, 1, 1, 30);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	updateCamera();

	drawSnow();

	cameraPositionY += 0.0f;

	// Light
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);

	glPushMatrix();

	if (rotationEnabled)
	{
		glRotatef(spin, 0.0, 1.0, 0.0);
		spin += 0.3; // 회전 속도 조절

		// position[0]이 일정 값 이상이 되면 반대 방향으로 이동
		if (position[0] >= 5.0 || position[0] <= -5.0)
		{
			position[0] = (position[0] >= 5.0) ? 5.0 : -5.0;
			dir = !dir; // 방향전환
		}

		if (dir) position[0] += 0.005;
		else position[0] -= 0.005;
	}
	else
	{
		resetLightPosition();
	}
	glPopMatrix();

	switch (ltype) {
	case 1: // Point Light
		position[3] = 1;
		glLightfv(GL_LIGHT0, GL_POSITION, position);
		glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 90);
		glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 0.0);
		break;
	case 2: // Directional Light
		position[3] = 0;
		glLightfv(GL_LIGHT0, GL_POSITION, position);
		break;
	case 3: // Spotlight
		position[3] = 1;
		glLightfv(GL_LIGHT0, GL_POSITION, position);
		GLfloat sd[] = { 0.3, 0.0, -1.0 };
		glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, sd);
		glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, spotlightAngle);
		glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 0);
		glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 1.0);
		glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.0);
		glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, spotlightAttenuation);
		break;
	}

	float offset = 0.0;

	glDisable(GL_TEXTURE_2D);
	drawSphere(offset, offset - 0.05, -0.9, 0.07, ambient1, diffuse1, specular1, shininess1, emission1); // blue sphere
	drawSphere(0.25 + offset, -0.4 + offset, -0.9, 0.05, ambient2, diffuse2, specular2, shininess2, emission2); // white sphere
	drawSphere(-0.09 + offset, offset + 0.13, -0.9, 0.05, ambient3, diffuse3, specular3, shininess3, emission3); // yellow sphere
	drawSphere(-0.07 + offset, -0.28 + offset, -0.9, 0.04, ambient4, diffuse4, specular4, shininess4, emission4); // red sphere

	// 눈사람
	drawSphere(-0.6 + offset, -0.6 + offset, -0.7, 0.23, ambient2, diffuse2, specular2, shininess2, emission2); // 아래 몸통
	drawSphere(-0.6 + offset, -0.3 + offset, -0.7, 0.16, ambient2, diffuse2, specular2, shininess2, emission2); // 위 몸통
	drawSphere(-0.65 + offset, -0.25 + offset, -0.5, 0.02, ambient5, diffuse5, specular5, shininess5, emission5); // 눈(왼쪽)
	drawSphere(-0.55 + offset, -0.25 + offset, -0.5, 0.02, ambient5, diffuse5, specular5, shininess5, emission5); // 눈(오른쪽)

	glEnable(GL_TEXTURE_2D);

	// 눈사람 코 
	glDisable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);
	glPushMatrix();
	glTranslatef(-0.6 + offset, -0.3 + offset, -0.55); 
	glRotatef(35, 1.0, 0.0, 0.0); 
	glColor3f(1.0, 0.5, 0.0);
	glutSolidCone(0.02, 0.06, 20, 20);
	glPopMatrix();
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_LIGHTING);

	// Teapot 1 - 트리에 있는 주전자. 계속 Rotation 하는 중. 텍스처 매핑
	glBindTexture(GL_TEXTURE_2D, texID2);
	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_T);
	glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
	glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
	glPushMatrix();
	glTranslatef(-0.2, -0.5, -0.8);
	glRotatef(rotationAngle, 1.0f, 0.0f, 0.0f);
	glRotatef(rotationAngle, 0.0f, 1.0f, 0.0f);
	glRotatef(rotationAngle, 0.0f, 0.0f, 1.0f);
	glutSolidTeapot(0.07);
	glPopMatrix();
	glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_TEXTURE_GEN_T);

	// Teapot 2 - 바닥에 있는 주전자. 텍스처 매핑
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, texID4);
	glTranslatef(-1.3, -0.5, 0);
	glutSolidTeapot(0.25);
	glPopMatrix();

	//cube - 트리에 있는 큐브. 텍스처 매핑
	glBindTexture(GL_TEXTURE_2D, texID5);
	glTexGeni(GL_S, GL_TEXTURE_GEN_MODE,
		GL_OBJECT_LINEAR);
	glTexGeni(GL_T, GL_TEXTURE_GEN_MODE,
		GL_OBJECT_LINEAR);
	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_T);
	glPushMatrix();
	glTranslatef(0.1, 0.19, -0.9);
	glRotatef(rotationAngle, 1.0f, 0.0f, 0.0f);
	glRotatef(rotationAngle, 0.0f, 1.0f, 0.0f);
	glRotatef(rotationAngle, 0.0f, 0.0f, 1.0f);
	glutSolidCube(0.08);
	glPopMatrix();
	glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_TEXTURE_GEN_T);

	// 토러스랑 구로 이루어진 장식품
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_a);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_d);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_s);
	glMaterialfv(GL_FRONT, GL_SHININESS, low_sh);
	glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION, material_emission);
	glDisable(GL_TEXTURE_2D);
	glEnable(GL_LIGHTING);
	glTranslatef(0.6, -0.4, -0.7);
	glutSolidTorus(0.03, 0.09, 100, 100);
	drawSphere(-0.02, 0.05, 0.05, 0.03, ambient4, diffuse4, specular4, shininess4, emission4);
	drawSphere(0.02, 0.05, 0.05, 0.03, ambient4, diffuse4, specular4, shininess4, emission4);
	glEnable(GL_TEXTURE_2D);
	glPopMatrix();

	glDisable(GL_TEXTURE_2D);
	glDisable(GL_LIGHTING);

	// '박' 글자 그리기 및 고정점 스케일링
	glPushMatrix();
	glTranslatef(-0.5, -0.2, 0.0); // 고정점으로 이동
	glTranslatef(0.75, 0.5, 0.0);  // 원래 위치로 복귀

	// 'ㅂ'의 왼쪽 'ㅣ'
	glPushMatrix();
	glTranslatef(-0.8, 0.0, 0.0);
	glRotatef(20.0, 1.0, 1.0, 0.0);
	glScalef(0.05, 0.1, 0.1);
	drawBox2();
	glPopMatrix();
	// 'ㅂ'의 오른쪽 'ㅣ'
	glPushMatrix();
	glTranslatef(-0.66, 0.0, 0.0);
	glRotatef(20.0, 1.0, 1.0, 0.0);
	glScalef(0.05, 0.1, 0.1);
	drawBox2();
	glPopMatrix();
	// 'ㅂ'의 중간 'ㅡ'
	glPushMatrix();
	glTranslatef(-0.73, 0.08, 0.0);
	glScalef(0.1, 0.02, 0.1);
	glRotatef(20.0, 1.0, 1.0, 0.0);
	drawBox2();
	glPopMatrix();
	// 'ㅂ'의 맨 밑 'ㅡ'
	glPushMatrix();
	glTranslatef(-0.73, 0.0, 0.0);
	glScalef(0.1, 0.02, 0.1);
	glRotatef(20.0, 1.0, 1.0, 0.0);
	drawBox2();
	glPopMatrix();
	// 'ㅏ'의 'ㅣ'
	glPushMatrix();
	glTranslatef(-0.55, -0.02, 0.0);
	glRotatef(20.0, 1.0, 1.0, 0.0);
	glScalef(0.05, 0.13, 0.1);
	drawBox();
	glPopMatrix();
	// 'ㅏ'의 'ㅡ' (원 도형 사용)
	glPushMatrix();
	glTranslatef(-0.48, 0.09, 0.0);
	glColor3f(1.0, 0.71, 0.76);
	glutWireSphere(0.045, 20, 20);
	glPopMatrix();
	// 'ㄱ' 의 'ㅡ' 부분
	glPushMatrix();
	glTranslatef(-0.65, -0.1, 0.0);
	glRotatef(20.0, 1.0, 1.0, 0.0);
	glScalef(0.25, 0.02, 0.1);
	drawBox();
	glPopMatrix();
	// 'ㄱ'의 'ㅣ' 부분 (원뿔 도형 사용)
	glPushMatrix();
	glTranslatef(-0.56, -0.1, 0.0);
	glRotatef(80.0, 1.0, 0.0, 0.0);
	glColor3f(0.5, 0.8, 1.0);
	glutWireCone(0.04, 0.2, 40, 40);
	glPopMatrix();

	glPopMatrix();
	glEnable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);

	// 배경
	glBindTexture(GL_TEXTURE_2D, texID1);
	glBegin(GL_POLYGON);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(-1.0, -1.0, -1);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(-1.0, 1.0, -1);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(1.0, 1.0, -1);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(1.0, -1.0, -1);
	glEnd();

	//cube 1 - 바닥에 있는 오른쪽 선물 상자. 텍스처 매핑
	glBindTexture(GL_TEXTURE_2D, texID3);
	glTexGeni(GL_S, GL_TEXTURE_GEN_MODE,
		GL_OBJECT_LINEAR);
	glTexGeni(GL_T, GL_TEXTURE_GEN_MODE,
		GL_OBJECT_LINEAR);
	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_T);
	glPushMatrix();
	glTranslatef(0.7, -0.7, -0.8);
	glutSolidCube(0.3);
	glPopMatrix();
	glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_TEXTURE_GEN_T);
	
	//cube 2 - 바닥에 있는 왼쪽 선물 상자. 텍스처 매핑
	glBindTexture(GL_TEXTURE_2D, texID4);
	glPushMatrix();
	glTranslatef(0.4, -0.7, -0.7);
	glBegin(GL_QUADS);

	glNormal3f(0, 0, 1);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(-0.1, -0.1, 0.1);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(0.1, -0.1, 0.1);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(0.1, 0.1, 0.1);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(-0.1, 0.1, 0.1);
	
	glNormal3f(0, 1, 0);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(-0.1, 0.1, 0.1);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(0.1, 0.1, 0.1);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(0.1, 0.1, -0.1);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(-0.1, 0.1, -0.1);

	glNormal3f(1, 0, 0);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(0.1, -0.1, 0.1);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(0.1, -0.1, -0.1);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(0.1, 0.1, -0.1);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(0.1, 0.1, 0.1);
	glEnd();
	glPopMatrix();

	glFlush();
}

void idle(void)
{
	rotationAngle += rotationSpeed;
	if (rotationAngle > 360.0f) {
		rotationAngle -= 360.0f;
	}
	vibrationAmount = 0.03 * sin(rotationAngle * PI / 180.0); // 지피티 이용

	updateSnow(); 

	glutPostRedisplay();
}


// Data read from the header of the BMP file// Each BMP file begins by a 54-bytes header
unsigned char header[54];
// Position in the file where the actual data begins
unsigned int dataPos;
// image width and height
unsigned int width, height;
// imageSize = width*height*3
unsigned int imageSize;

unsigned char* loadBMP(char* fname)
{
	FILE* file = fopen(fname, "rb");	 // file open
	if (!file) {
		cout << "Image file could not be opened "
			<< endl; return NULL;
	}
	if (fread(header, 1, 54, file) != 54) {
		// read header: if not 54 bytes read, problem
		cout << "Not a correct BMP file\n";
		return NULL;
	}
	if (header[0] != 'B' || header[1] != 'M') {  // 2 bytes
		cout << "Not a correct BMP file\n";
		return NULL;
	}
	// Read ints from the byte array
	dataPos = *(int*)&(header[0x0A]);
	width = *(int*)&(header[0x12]);
	height = *(int*)&(header[0x16]);
	imageSize = *(int*)&(header[0x22]);
	cout << "width = " << width << " height = " << height << endl;

	// Some BMP files are misformatted, guess missing information
	// 3 : one byte for each Red, Green and Blue component
	if (imageSize == 0)    imageSize = width * height * 3;

	// The BMP header is done that way
	if (dataPos == 0)      dataPos = 54;

	// Create a buffer
	unsigned char* bitmap = new unsigned char[imageSize];

	// Read the actual data from the file into the buffer
	fread(bitmap, 1, imageSize, file);

	// Everything is in memory now, the file can be closed
	fclose(file);

	return bitmap;
}

int initTexture()
{
	unsigned char* bitmap;

	glEnable(GL_TEXTURE_2D);

	// Texture ID1 - 배경
	bitmap = loadBMP((char*)"tree.bmp");
	if (bitmap == NULL) {
		cout << "file open error" << endl;
		return -1;
	}
	cout << "width=" << width << " height=" << height << endl;

	glGenTextures(1, &texID1);
	glBindTexture(GL_TEXTURE_2D, texID1);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height,
		0, GL_BGR_EXT, GL_UNSIGNED_BYTE, bitmap);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	// Texture ID2 - 트리에 달려있는 주전자
	bitmap = loadBMP((char*)"metal.bmp");
	if (bitmap == NULL) {
		cout << "file open error" << endl;
		return -1;
	}
	glGenTextures(2, &texID2);
	glBindTexture(GL_TEXTURE_2D, texID2);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height,
		0, GL_BGR_EXT, GL_UNSIGNED_BYTE, bitmap);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	// Texture ID3 - 오른쪽 선물 상자 
	bitmap = loadBMP((char*)"pattern4.bmp");
	if (bitmap == NULL) {
		cout << "file open error" << endl;
		return -1;
	}
	glGenTextures(3, &texID3);
	glBindTexture(GL_TEXTURE_2D, texID3);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height,
		0, GL_BGR_EXT, GL_UNSIGNED_BYTE, bitmap);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// Texture ID4 - 왼쪽 선물 상자, 바닥에 있는 주전자 
	bitmap = loadBMP((char*)"pattern1.bmp");
	if (bitmap == NULL) {
		cout << "file open error" << endl;
		return -1;
	}
	glGenTextures(4, &texID4);
	glBindTexture(GL_TEXTURE_2D, texID4);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height,
		0, GL_BGR_EXT, GL_UNSIGNED_BYTE, bitmap);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// Texture ID5 - 트리에 달려있는 큐브
	bitmap = loadBMP((char*)"pattern3.bmp");
	if (bitmap == NULL) {
		cout << "file open error" << endl;
		return -1;
	}
	glGenTextures(3, &texID5);
	glBindTexture(GL_TEXTURE_2D, texID5);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height,
		0, GL_BGR_EXT, GL_UNSIGNED_BYTE, bitmap);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// Environment Texture Parameter
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	return 0;

}

void keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case 'u': // 'u' 카메라가 위를 봄
		isUpView = !isUpView;
		if (isUpView) {
			lookAtY = 0.7f;
		}
		else {
			lookAtY = 0.0f;
		}
		break;
	case 'k': // 'k' 카메라가 왼쪽을 봄
		if (isCameraLeft) {
			lookAtX = 0.0f;
			lookAtY = 0.0f;
		}
		else {
			lookAtX = -1.0f;
			lookAtY = 0.0f;
		}
		isCameraLeft = !isCameraLeft; 
		break;
	case 'y': // 'y' 조명 변경
		// 노란색
		ambient[0] = 0.2;
		ambient[1] = 0.2;
		ambient[2] = 0.0;

		// 노란색
		diffuse[0] = 1.0;
		diffuse[1] = 1.0;
		diffuse[2] = 0.0;

		// 빨간색
		specular[0] = 1.0;
		specular[1] = 0.0;
		specular[2] = 0.0;
		break;

	case 'e': upX = 1.0f - upX; break; // 'e' 카메라 회전? 뒤틀림?
	case 'r': toggleRotation(); break; // 'r' 조명 회전
	case 't': animateCamera(); break; // 't' 카메라 이동

	case '1': ltype = 1; break; // '1' Point Light
	case '2': ltype = 2; break; // '2' Directional Light
	case '3': ltype = 3; break; // '3' Spotlight
	case 's': // Increase spotlight angle
		if (spotlightAngle < 90.0f) { // spotlightAngle은 최대 90
			spotlightAngle += 5.0f;
			glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, spotlightAngle); // OpenGL에 반영
		}
		break;
	case 'd': // Decrease spotlight angle
		if (spotlightAngle > 0.0f) { // spotlightAngle은 최소 0
			spotlightAngle -= 5.0f;
			glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, spotlightAngle); // OpenGL에 반영
		}
		break;
	case 'a': spotlightAttenuation -= 0.1; break; // 'a' Increase spotlight attenuation(감쇠)
	case 'q': spotlightAttenuation += 0.1; break; // 'q' decrease spotlight attenuation(감쇠)

	default: break;
	}
	glutPostRedisplay();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_SINGLE);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutCreateWindow("FinalTask_20221365");
	initSnow(); 
	glutIdleFunc(idle);
	glutReshapeFunc(reshape);

	glEnable(GL_DEPTH_TEST);

	initTexture();
	glutKeyboardFunc(keyboard);

	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}