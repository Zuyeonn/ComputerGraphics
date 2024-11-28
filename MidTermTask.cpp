// 컴퓨터그래픽스 중간과제
// 20221365 박주연
#include<iostream>
#include<glut.h>
#include <math.h> 
using namespace std;

#define PI 3.141592
float scaleX = 1.0f, scaleY = 1.0f, scaleZ = 1.0f;
float translateX = 0.0f, translateY = 0.0f, translateZ = 0.0f;
float translatex = 0.0f, translatey = 0.0f, translatez = 0.0f;

float shoulder = 0, elbow = 0;
float legSwing = 0; bool legSwingDirection = true;   // 다리의 움직임 각도, 방향 (true: 앞으로, false: 뒤로)
float moveX = 0.0f, moveY = 0.0f; // 캐릭터의 위치
bool armAnim = false, legAnim = false; // 팔, 다리 애니메이션 활성화 상태
string armDirection = "clockwise", legDirection = "clockwise"; // 팔, 다리 회전 방향

float textScale = 1.0f; // "박" 글자의 스케일 크기
bool scaleAnim = false; // 글자 크기 조절 애니메이션 활성화 상태
bool textScaleDirection = true; // 글자 크기 증가/감소 방향 (true: 증가, false: 감소)

bool giScaleAnim = false;    // 'ㄱ' 글자의 확대/축소 애니메이션 활성화 상태
bool giScaleDirection = true; // 'ㄱ' 글자 확대 방향 (true: 확대, false: 축소)
float giScale = 1.0f;        // 'ㄱ' 글자의 현재 스케일 크기

float rotateBa = 0.0f, rotateGi = 0.0f; // '바' , 'ㄱ' 글자의 회전 각도
bool rotateBaAnim = false, rotateGiAnim = false; // '바' , 'ㄱ' 글자의 회전 애니메이션 활성화
float shakeGi = 0.0f; // 'ㄱ' 진동
bool shakeGiAnim = false;


float beeX = 0.0f, beeY = 0.0f; float speedX = 0.0003f, speedY = 0.0003f; // 벌의 위치와 속도
float beeRotation = 0.0f; // 벌의 회전 각도

float scaleFactor = 1.0f;  // 화면 확대/축소 배율
bool isScalingUp = true;   // 확대 방향 제어
int repeatCount = 0;       // 반복 횟수

float characterRotation = 0.0f; // 캐릭터 회전 각도
bool characterRotateAnim = false; // 캐릭터 회전 애니메이션 활성화 상태

// 점프와 "ㄱ" 글자의 애니메이션을 위한 변수 추가
bool jumpAnim = false;
float jumpHeight = 0.0f;
bool isJumpingUp = true;

bool giMoveAnim = false;
float giMoveOffset = 0.0f;
bool giMovingRightUp = true;

// 다리 파닥파닥 애니메이션을 위한 변수
float legFlapAngle = 0.0f;
bool legFlapAnim = false;
bool legFlapDirection = true; // true면 벌어지고, false면 모이는 방향

void drawBox() {
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

void drawBox2() {
	// 앞면 
	glColor3f(0.0, 0.0, 0.0); // 검정색
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.5, 0.0, -0.5);
	glVertex3f(0.5, 0.0, -0.5);
	glVertex3f(0.5, 2.0, -0.5);
	glVertex3f(-0.5, 2.0, -0.5);
	glEnd();

	// 뒷면 
	glColor3f(0.6, 0.3, 0.0); // 갈색
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.5, 0.0, 0.5);
	glVertex3f(0.5, 0.0, 0.5);
	glVertex3f(0.5, 2.0, 0.5);
	glVertex3f(-0.5, 2.0, 0.5);
	glEnd();

	// 윗면 
	glColor3f(0.5, 0.0, 0.5); // 보라색
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.5, 2.0, -0.5);
	glVertex3f(0.5, 2.0, -0.5);
	glVertex3f(0.5, 2.0, 0.5);
	glVertex3f(-0.5, 2.0, 0.5);
	glEnd();

	// 아랫면 
	glColor3f(0.0, 0.39, 0.0); // 진한 초록색
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
	glScalef(scaleFactor, scaleFactor, scaleFactor); // 전체 장면 확대 적용

	// '바' 글자 회전
	glPushMatrix();
	if (rotateBaAnim) {
		rotateBa += 0.05f;
		if (rotateBa >= 360.0f) rotateBa -= 360.0f;
	}
	glTranslatef(0.0f, 0.0f, 0.0f);
	glRotatef(rotateBa, 0.0f, 1.0f, 0.0f); // y축 회전

	// '박' 글자 그리기 및 고정점 스케일링
	glPushMatrix();
	glTranslatef(-0.75, -0.5, 0.0); // 고정점으로 이동
	glScalef(textScale, textScale, textScale); // 크기 조절
	glTranslatef(0.75, 0.5, 0.0);  // 원래 위치로 복귀

	// 'ㅂ'의 왼쪽 'ㅣ'
	glPushMatrix();
	glTranslatef(-0.8, 0.0, 0.0);
	glTranslatef(translateX, translateY, translateZ);
	glScalef(scaleX, scaleY, scaleZ);
	glRotatef(20.0, 1.0, 1.0, 0.0);
	glScalef(0.1, 0.2, 0.1);
	drawBox();
	glPopMatrix();
	// 'ㅂ'의 오른쪽 'ㅣ'
	glPushMatrix();
	glTranslatef(-0.6, 0.0, 0.0);
	glTranslatef(translateX, translateY, translateZ);
	glScalef(scaleX, scaleY, scaleZ);
	glRotatef(20.0, 1.0, 1.0, 0.0);
	glScalef(0.1, 0.2, 0.1);
	drawBox();
	glPopMatrix();
	// 'ㅂ'의 중간 'ㅡ'
	glPushMatrix();
	glTranslatef(-0.7, 0.18, 0.0);
	glTranslatef(translateX, translateY, translateZ);
	glScalef(scaleX, scaleY, scaleZ);
	glScalef(0.1, 0.05, 0.1);
	glRotatef(20.0, 1.0, 1.0, 0.0);
	drawBox();
	glPopMatrix();
	// 'ㅂ'의 맨 밑 'ㅡ'
	glPushMatrix();
	glTranslatef(-0.7, 0.0, 0.0);
	glTranslatef(translateX, translateY, translateZ);
	glScalef(scaleX, scaleY, scaleZ);
	glScalef(0.1, 0.05, 0.1);
	glRotatef(20.0, 1.0, 1.0, 0.0);
	drawBox();
	glPopMatrix();

	// 'ㅏ'의 'ㅣ'
	glPushMatrix();
	glTranslatef(-0.4, 0.0, 0.0);
	glTranslatef(translateX, translateY, translateZ);
	glScalef(scaleX, scaleY, scaleZ);
	glRotatef(20.0, 1.0, 1.0, 0.0);
	glScalef(0.1, 0.2, 0.1);
	drawBox2();
	glPopMatrix();
	// 'ㅏ'의 'ㅡ' (원 도형 사용)
	glPushMatrix();
	glTranslatef(-0.28, 0.2, 0.0);
	glTranslatef(translateX, translateY, translateZ);
	glScalef(scaleX, scaleY, scaleZ);
	glColor3f(1.0, 0.71, 0.76);
	glutWireSphere(0.07, 20, 20);
	glPopMatrix();

	glPopMatrix(); // '바' 회전 변환 끝


	// 'ㄱ' 글자
	glPushMatrix();
	if (rotateGiAnim) {
		rotateGi += 0.02f;
		if (rotateGi >= 360.0f) rotateGi -= 360.0f;
	}
	if (shakeGiAnim) {
		shakeGi += 0.1f;
		glTranslatef(0.0f, sin(shakeGi * 10) * 0.02f, 0.0f); // 진동 효과
	}
	if (giMoveAnim) {
		glTranslatef(giMoveOffset, giMoveOffset, 0.0f); // 사선 방향 이동
	}

	glTranslatef(0.0f, 0.0f, 0.0f);
	glRotatef(rotateGi, 1.0f, 0.0f, 0.0f); // x축 회전
	glScalef(giScale, giScale, giScale); // 'ㄱ' 글자 확대/축소 적용
	// 'ㄱ' 의 'ㅡ' 부분
	glPushMatrix();
	glTranslatef(-0.6, -0.3, 0.0);
	glTranslatef(translateX, translateY, translateZ);
	glScalef(scaleX, scaleY, scaleZ);
	glRotatef(20.0, 1.0, 1.0, 0.0);
	glScalef(0.4, 0.05, 0.1);
	drawBox2();
	glPopMatrix();
	// 'ㄱ'의 'ㅣ' 부분 (원뿔 도형 사용)
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

	// 벌 생성
	glPushMatrix();
	glTranslatef(beeX, beeY, 0.0f); // 벌의 위치 적용
	glRotatef(beeRotation, 1.0f, 1.0f, 1.0f); // 회전 추가
	// 몸통
	glColor3f(1.0, 0.85, 0.0);
	glTranslatef(0.0, 0.0, 0.0);
	glPushMatrix();
	glScalef(0.06, 0.05, 0.08);
	glutSolidCube(1.0);
	glPopMatrix();
	// 왼쪽 날개 
	glPushMatrix();
	glColor3f(0.53, 0.81, 0.98);
	glTranslatef(-0.03, 0.03, 0.0);
	glutSolidSphere(0.02, 15, 15);
	glPopMatrix();
	// 오른쪽 날개
	glPushMatrix();
	glColor3f(0.53, 0.81, 0.98);
	glTranslatef(0.03, 0.03, 0.0);
	glutSolidSphere(0.02, 15, 15);
	glPopMatrix();

	glPopMatrix();

	// 캐릭터 구현
	glPushMatrix(); // 전체 캐릭터 변환 시작
	// 캐릭터 점프 애니메이션 적용
	if (jumpAnim) {
		glTranslatef(0.0f, jumpHeight, 0.0f);
	}
	// 캐릭터 회전 애니메이션 적용
	if (characterRotateAnim) {
		glRotatef(characterRotation, 0.0f, 1.0f, 0.0f); // y축 기준 회전
	}
	glTranslatef(translatex, translatey, translatez); // 캐릭터 전체 위치 이동

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

	// 눈 (왼쪽)
	glPushMatrix();
	glTranslatef(-0.05, 0.4, -0.15);
	glColor3f(0.0, 0.0, 0.0);
	glutSolidSphere(0.02, 10, 10);
	glPopMatrix();
	// 눈 (오른쪽)
	glPushMatrix();
	glTranslatef(0.05, 0.4, -0.15);
	glColor3f(0.0, 0.0, 0.0);
	glutSolidSphere(0.02, 10, 10);
	glPopMatrix();

	// 오른쪽 팔 Upper Arm
	glPushMatrix();
	glTranslatef(0.1, 0.15, 0.0);
	glRotatef((GLfloat)shoulder, 0.0, 0.0, 1.0);
	if (armAnim) glRotatef((GLfloat)shoulder, 0.0, 0.0, 1.0); // 어깨 회전
	glTranslatef(0.2, 0.0, 0.0);
	glPushMatrix();
	glScalef(0.2, 0.1, 0.1);
	glColor3f(0.68, 0.85, 0.9);
	glutSolidCube(1.0);
	glColor3f(0.0, 0.0, 0.0);
	glutWireCube(1.0);
	glPopMatrix();
	// 오른쪽 팔 Lower Arm
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

	// 왼쪽 팔 Upper Arm
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
	// 왼쪽 팔 Lower Arm
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

	// 오른쪽 다리 Upper Leg
	glPushMatrix();
	glTranslatef(0.1, -0.32, 0.0);
	if (legAnim) glRotatef((GLfloat)legSwing, 1.0, 0.0, 0.0);  // 다리 앞뒤로 움직임
	if (legFlapAnim) glRotatef(legFlapAngle, 0.0, 0.0, 1.0); // 다리 파닥파닥 애니메이션
	glPushMatrix();
	glScalef(0.15, 0.25, 0.1);
	glColor3f(0.55, 0.27, 0.07);
	glutSolidCube(1.0);
	glColor3f(0.0, 0.0, 0.0);
	glutWireCube(1.0);
	glPopMatrix();
	// 오른쪽 다리 Lower Leg
	glTranslatef(0.0, -0.25, 0.0);
	glPushMatrix();
	glScalef(0.15, 0.25, 0.1);
	glColor3f(1.0, 0.85, 0.7);
	glutSolidCube(1.0);
	glColor3f(0.0, 0.0, 0.0);
	glutWireCube(1.0);
	glPopMatrix();
	glPopMatrix();

	// 왼쪽 다리 Upper Leg
	glPushMatrix();
	glTranslatef(-0.1, -0.32, 0.0);
	if (legAnim) glRotatef(-(GLfloat)legSwing, 1.0, 0.0, 0.0);  // 반대 방향으로 움직임
	if (legFlapAnim) glRotatef(-legFlapAngle, 0.0, 0.0, 1.0); // 반대 방향으로 파닥파닥
	glPushMatrix();
	glScalef(0.15, 0.25, 0.1);
	glColor3f(0.55, 0.27, 0.07);
	glutSolidCube(1.0);
	glColor3f(0.0, 0.0, 0.0);
	glutWireCube(1.0);
	glPopMatrix();
	// 왼쪽 다리 Lower Leg
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
	glPopMatrix(); // 전체 장면 확대 변환 끝
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
	// 1. 전체 확대, 축소 3회 반복 애니메이션
	if (repeatCount < 3) {
		if (isScalingUp) {
			scaleFactor += 0.0008f;  // 확대
			if (scaleFactor >= 1.65f) { isScalingUp = false; }
		}
		else {
			scaleFactor -= 0.0008f;  // 축소
			if (scaleFactor <= 1.0f) { isScalingUp = true; repeatCount++; } // 반복 횟수 증가
		}
	}
	// 2. 벌 움직임 애니메이션
	beeX += speedX; beeY += speedY;
	beeRotation += 0.05f;  // 벌의 회전 속도
	if (beeRotation >= 360.0f) beeRotation -= 360.0f;
	// 화면 가장자리에 가까워지면 반대 방향으로 전환하며 무작위 속도 조정
	if (beeX > 0.9f) {
		beeX = 0.9f; // 화면 밖으로 나가지 않도록 고정
		speedX = -0.0002f * (rand() % 5 + 1); // 왼쪽 방향으로 전환
	}
	else if (beeX < -0.9f) {
		beeX = -0.9f;
		speedX = 0.0002f * (rand() % 5 + 1); // 오른쪽 방향으로 전환
	}
	if (beeY > 0.9f) {
		beeY = 0.9f;
		speedY = -0.0002f * (rand() % 5 + 1); // 아래쪽 방향으로 전환
	}
	else if (beeY < -0.9f) {
		beeY = -0.9f;
		speedY = 0.0002f * (rand() % 5 + 1); // 위쪽 방향으로 전환
	}
	// 3. '바' 글자 크기 애니메이션 (FPS)
	if (scaleAnim) {
		if (textScaleDirection) textScale += 0.0004;
		else textScale -= 0.0004;
		if (textScale >= 1.5) textScaleDirection = false; // 크기 감소로 전환
		else if (textScale <= 1.0) textScaleDirection = true; // 크기 증가로 전환
	}
	// 4. 팔 위 아래로 움직이는 애니메이션
	if (armAnim) {
		if (armDirection == "clockwise") shoulder += 0.05;
		else shoulder -= 0.05;
		if (shoulder >= 40) armDirection = "anticlockwise";
		else if (shoulder <= -30) armDirection = "clockwise";
	}
	// 5. 다리 암뒤로 움직이는 애니메이션
	if (legAnim) {
		if (legDirection == "clockwise") legSwing += 0.1;
		else legSwing -= 0.1;
		if (legSwing >= 45) legDirection = "anticlockwise";
		else if (legSwing <= -45) legDirection = "clockwise";
	}
	// 6. 캐릭터 제자리 회전 애니메이션
	if (characterRotateAnim) {
		characterRotation += 0.08f; // 회전 속도 조절
		if (characterRotation >= 360.0f) characterRotation -= 360.0f; // 각도 제한
	}
	// 7. 'ㄱ' 글자 확대/축소 애니메이션
	if (giScaleAnim) {
		if (giScaleDirection) {
			giScale += 0.0015f;
			if (giScale >= 1.5f) giScaleDirection = false; // 축소로 전환
		}
		else {
			giScale -= 0.0015f;
			if (giScale <= 1.0f) giScaleDirection = true; // 확대로 전환
		}
	}
	// 8. 캐릭터 점프 애니메이션
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
	// 9. 'ㄱ' 글자 사선 이동 애니메이션
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
	// 10. 캐릭터 다리 파닥파닥 애니메이션
	if (legFlapAnim) {
		if (legFlapDirection) {
			legFlapAngle += 0.1f;
			if (legFlapAngle >= 20.0f) { legFlapDirection = false; } // 다리가 벌어지는 최대각도
		}
		else {
			legFlapAngle -= 0.1f;
			if (legFlapAngle <= 0.0f) { legFlapDirection = true; } // 다리가 모이는 최대각도
		}
	}
		glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y) {
	switch (key) {
	// '박' 도형에 대한 키보드
	case 'x': xyzRotate('x'); glutPostRedisplay(); break; // 'x, y, z' 도형 회전
	case 'y': xyzRotate('y'); glutPostRedisplay(); break;
	case 'z': xyzRotate('z'); glutPostRedisplay(); break;
	case 's': scaleX += 0.1f; scaleY += 0.1f; scaleZ += 0.1f; glutPostRedisplay(); break; // 's' 도형 확대
	case 'a': scaleX -= 0.1f; scaleY -= 0.1f; scaleZ -= 0.1f; glutPostRedisplay(); break; // 'a' 도형 축소
	case 't': translateX += 0.1f; glutPostRedisplay(); break; // 't' 도형 오른쪽으로 이동
	case 'r': translateX -= 0.1f; glutPostRedisplay(); break; // 'r' 도형 왼쪽으로 이동
	case 'd': rotateBaAnim = !rotateBaAnim; rotateGiAnim = !rotateGiAnim;glutPostRedisplay();break; // 'd' '바','ㄱ' 회전
	case 'q': shakeGiAnim = !shakeGiAnim; break; // 'q' 'ㄱ' 글자 진동

	// 캐릭터에 대한 키보드
	case 'e': elbow += 5; glutPostRedisplay(); break; // 'e' 팔 올림 (시계 방향으로 회전)
	case 'w': elbow -= 5; glutPostRedisplay(); break; // 'w' 팔 내림 (반시계 방향으로 회전)
	case 'h': shoulder += 5; glutPostRedisplay(); break; // 'h' 어깨 올림 (시계 방향으로 회전)
	case 'g': shoulder -= 5; glutPostRedisplay(); break; // 'g' 어깨 내림 (반시계 방향으로 회전)
	case 'l': translatex += 0.1f; glutPostRedisplay(); break; // 'l' 도형 오른쪽으로 이동
	case 'j': translatex -= 0.1f; glutPostRedisplay(); break; // 'j' 도형 왼쪽으로 이동
	case 'i': translatey += 0.1f; glutPostRedisplay(); break; // 'i' 도형 위로 이동
	case 'k': translatey -= 0.1f; glutPostRedisplay(); break; // 'k' 도형 아래로 이동

	// 애니메이션 - 키보드
	case 'p': armAnim = !armAnim; scaleAnim = !scaleAnim; break; // 'p' 팔 애니메이션 + FPS 시작/멈춤
	case 'c': characterRotateAnim = !characterRotateAnim; legAnim = !legAnim; break; // 'c' 캐릭터 회전 시작/정지
	case 'f': repeatCount = 0; scaleFactor = 1.0f; isScalingUp = true; glutIdleFunc(idle); // 'f' 전체 확대, 축소 3회 반복
	case 'u': giScaleAnim = !giScaleAnim; break; // 'u' 'ㄱ' 글자 확대/축소 애니메이션
	case 'v': jumpAnim = !jumpAnim; giMoveAnim = !giMoveAnim; legFlapAnim = !legFlapAnim; break; // 'v' 캐릭터 점프, 캐릭터 다리 파닥파닥, 'ㄱ' 사선으로 이동

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