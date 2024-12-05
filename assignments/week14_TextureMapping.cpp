// 14주차 
// 20221365 박주연

#include <iostream>
#include <cmath>
#include <glut.h>
#include <gl/glu.h>
using namespace std;

#define WIDTH 600
#define HEIGHT 600

// light
GLfloat ambient[] = { 0.0, 0.0, 0.0, 1.0 };
GLfloat diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };

// material
GLfloat mat_a[] = { 0.1, 0.1, 0.1, 1.0 };
GLfloat mat_d[] = { 1, 0.2, 0.2, 1.0 };
GLfloat mat_s[] = { 0, 1, 0, 1.0 };
GLfloat low_sh[] = { 50.0 };
GLfloat material_emission[] = { 0.3,0.3,0,1 };

// light position
GLfloat position[] = { 0, 0, 2, 1 };

// texture ID
GLuint texID1, texID2;

void display()
{
	glClear(GL_COLOR_BUFFER_BIT
		| GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	// View Volume
	glOrtho(-1, 1, -1, 1, 1, 30);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	// Camera
	gluLookAt(1, 1, 2, 0, 0, 0, 0, 1, 0);

	// Light
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);

	// Material
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_a);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_d);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_s);
	glMaterialfv(GL_FRONT, GL_SHININESS, low_sh);
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, material_emission);

	// Teapot
	glBindTexture(GL_TEXTURE_2D, texID2);
	glutSolidTeapot(0.3);

	// Rectangle
	glBindTexture(GL_TEXTURE_2D, texID1);
	glBegin(GL_POLYGON);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(-0.5, -0.5, -1);
	glTexCoord2f(0.0, 0.7);
	glVertex3f(-0.5, 0.5, -1);
	glTexCoord2f(0.7, 0.7);
	glVertex3f(0.5, 0.5, -1);
	glTexCoord2f(0.7, 0.0);
	glVertex3f(0.5, -0.5, -1);
	glEnd();

	glFlush();
}

// Data read from the header of the BMP file// Each BMP file begins by a 54-bytes header
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

	bitmap = loadBMP((char*)"carnation.bmp");
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

	bitmap = loadBMP((char*)"penguin.bmp");
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
	return 0;
}





int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_SINGLE);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutCreateWindow("test");
	glClearColor(1.0, 1.0, 1.0, 1.0); 
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	initTexture();
	glutDisplayFunc(display);
	glutIdleFunc(display);
	glutMainLoop();
	return 0;
}