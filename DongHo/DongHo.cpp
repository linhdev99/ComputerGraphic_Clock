#pragma warning(disable : 4996)
#include <iostream>
#include <GL/GL.h>
#include <GL/GLU.h>
#include <GL/glut.h>
#include <cmath>
#include <Windows.h>
#include <time.h>

using namespace std;
#define PI 3.1415925
#define D2G PI/180.0f
#define	COLORNUM 14

GLfloat screenWidth = 600, screenHeight = 600;

float ColorArr[COLORNUM][3] = { 
	{1.0, 0.0, 0.0}, //0
	{0.0, 1.0, 0.0}, //1
	{0.0, 0.0, 1.0}, //2
	{1.0, 1.0, 0.3}, //3
	{1.0, 0.0, 1.0}, //4
	{0.0, 1.0, 1.0}, //5		 
	{0.3, 0.3, 0.3}, //6
	{0.5, 0.5, 0.5}, //7
	{0.9, 0.9, 0.9}, //8	
	{1.0, 0.5, 0.5}, //9
	{0.5, 1.0, 0.5}, //10
	{0.5, 0.5, 1.0}, //11
	{0.0, 0.0, 0.0}, //12
	{0.3, 0.7, 0.6}  //13
};

struct Arrow
{
	int colorIdx = 0;
	float length = 1.0f;
	float width = 1.0f;
};

void DrawCircle(GLfloat radius);
void DrawArrow(GLfloat length, GLfloat width, int colorIdx);
void RotateArrow(int idxArrow, Arrow ar);
void myDisplay();
void myInit();
void GetInput(unsigned char key, int x, int y);
void setRealTime(int idx);

int timer = 0;
float angleArrow[] = { 0.0f, 0.0f, 0.0f };
Arrow ar[3];

int main(int argc, char* argv[])
{
	cout << "Dong ho treo tuong" << endl;
	glutInit(&argc, (char**)argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(screenWidth, screenHeight);
	glutInitWindowPosition(300, 100);
	glutCreateWindow("Dong ho treo tuong");

	myInit();
	glutKeyboardFunc(GetInput);
	glutDisplayFunc(myDisplay);
	glutTimerFunc(100, setRealTime, 1);
	glutMainLoop();
	return 0;
}

void myInit()
{
	GLfloat halfSize = 4;
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-halfSize, halfSize, -halfSize, halfSize, -1000, 1000);
	// Init arrow
	{
		ar[0].colorIdx = 0;
		ar[0].length = 1.5f;
		ar[0].width = 6.0f;
		ar[1].colorIdx = 1;
		ar[1].length = 2.0f;
		ar[1].width = 5.0f;
		ar[2].colorIdx = 3;
		ar[2].length = 3.0f;
		ar[2].width = 4.0f;
	}
}

void myDisplay()
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0, 0, 4, 0, 0, 0, 0, 1, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glViewport(0, 0, screenWidth, screenHeight);
	DrawCircle(3.5f);
	for (int i = 0; i < 3; i++)
	{
		RotateArrow(i, ar[i]);
	}
	glFlush();
	glutSwapBuffers();
}

void DrawCircle(GLfloat radius)
{
	GLfloat angle = 0;
	int nSeg = 12;
	glPushMatrix();
	glPointSize(5);
	glBegin(GL_POINTS);
	glColor3f(1, 1, 1);
	for (int i = 0; i < nSeg; i++)
	{
		GLfloat x = radius * cos(i * 2 * PI / nSeg);
		GLfloat y = radius * sin(i * 2 * PI / nSeg);
		glVertex2d(x, y);
	}
	glEnd();
	glPopMatrix();
}

void DrawArrow(GLfloat length, GLfloat width, int colorIdx)
{
	glPushMatrix();
	glColor3f(ColorArr[colorIdx][0], ColorArr[colorIdx][1], ColorArr[colorIdx][2]);
	glLineWidth(width);
	glBegin(GL_LINES);
	glVertex2f(0.0f, 0.0f);
	glVertex2f(0.0f, length * 3 / 4);
	glEnd();
	glBegin(GL_TRIANGLES);
	glVertex2f(0.0f, length);
	glVertex2f(-0.1f, length * 2 / 3);
	glVertex2f(0.1f, length * 2 / 3);
	glEnd();
	glPopMatrix();
}

void RotateArrow(int idxArrow, Arrow ar)
{
	glPushMatrix();
	glRotatef(angleArrow[idxArrow], 0.0f, 0.0f, 1.0f);
	DrawArrow(ar.length, ar.width, ar.colorIdx);
	glPopMatrix();
}
void GetInput(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'q':
	{
		ar[0].colorIdx = rand() % 14;
		ar[1].colorIdx = rand() % 14;
		ar[2].colorIdx = rand() % 14;
		break;
	}
	default:
		break;
	}
	glutPostRedisplay();
}
void setRealTime(int idx)
{
	time_t timer = time(0);
	tm* now = localtime(&timer);
	cout << "Time: " << now->tm_hour << " : " << now->tm_min << " : " << now->tm_sec << endl;
	float hourAngle = -((now->tm_hour % 12) * 3600 + now->tm_min * 60 + now->tm_sec) * 360 / (3600 * 12);
	float minAngle = -(now->tm_min * 60 + now->tm_sec) * 360 / 3600;
	float secAngle = -(now->tm_sec % 60) * 360 / 60;
	angleArrow[0] = hourAngle;
	angleArrow[1] = minAngle;
	angleArrow[2] = secAngle;
	glutTimerFunc(1000, setRealTime, 1);
	glutPostRedisplay();
}