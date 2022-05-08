
#include <GL/glut.h>
#include <stdlib.h>
#include <windows.h>
#include <fstream>
#include <math.h>
#pragma comment(lib, "Winmm.lib")
#include <mmsystem.h>

static int leftArm = 0, rightArm = 0, leftEye = 0, rightEye = 0;
float angle = 0.0f;
float lx = 0.0f, lz = 1.0f;
float x = 0.0f, z = 5.0f;
float deltaAngle = 0.0f;
float deltaMove = 0;
int xOrigin = -1;

//Initializes 3D rendering
void initRendering()
{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING);          // Enable Lighting
	glEnable(GL_LIGHT0);            // Enable light #0 - light color
	glEnable(GL_LIGHT1);            // Enable light #1 - light position
	glEnable(GL_NORMALIZE);         // Automatically normalize normals 
}


void init(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_FLAT);
}

void drawLines()
{
	glColor3f(1, 1, 1);
	glBegin(GL_LINES);
	glVertex3i(-100, 0, 0);
	glVertex3i(100, 0, 0);
	glVertex3i(0, -100, 0);
	glVertex3i(0, 100, 0);
	glVertex3i(0, 0, -100);
	glVertex3i(0, 0, 100);
	glEnd();

}



void reshape(int w, int h)
{
	if (h == 0)
		h = 1;

	float ratio = w * 1.0 / h;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, w, h);
	gluPerspective(60.0f, ratio, 0.1f, 100.0f);

	
}


void keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case 'l':
		if (leftArm < 60)
			leftArm = (leftArm + 5) % 360;
		glutPostRedisplay();
		break;
	case 'L':
		if (leftArm > 0)
			leftArm = (leftArm - 5) % 360;
		glutPostRedisplay();
		break;

	case 'r':
		if (rightArm < 50)
			rightArm = (rightArm + 5) % 360;
		glutPostRedisplay();
		break;
	case 'R':
		if (rightArm > 0)
			rightArm = (rightArm - 5) % 360;
		glutPostRedisplay();
		break;
	case 'a':
		if (leftEye < 20)
			leftEye = (leftEye + 5) % 360;
		glutPostRedisplay();
		break;
	case 'A':
		if (leftEye > 0)
			leftEye = (leftEye - 5) % 360;
		glutPostRedisplay();
		break;
		
	case 's':
		if (rightEye < 20)
			rightEye = (rightEye + 5) % 360;
		glutPostRedisplay();
		break;
	case 'S':
		if (rightEye > 0)
			rightEye = (rightEye - 5) % 360;
		glutPostRedisplay();
		break;
	case 'e':
		glEnable(GL_LIGHTING);
		break;
	case 'd':
		glDisable(GL_LIGHTING);
		break;
	case 'm':
		PlaySound(TEXT("C:\\zmisc\\wall-e.wav"), NULL, SND_ASYNC);
		break;
	case 'n':
		PlaySound(NULL, 0, 0);
		break;
	case 27:
		exit(0);
		break;
	default:
		break;
	}
}

void computePos(float deltaMove)
{
	x += deltaMove * lx * 0.1f;
	z += deltaMove * lz * 0.1f;
}

void drawRobot()
{
	// Body
	glPushMatrix();
	// FRONT
	// glRotatef(20, 0.0f, 1.0f, 0.0f);
	glColor3f(0.8, 0.5, 0.0);
	glBegin(GL_POLYGON);
	glNormal3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0.5, -0.5, 0.5);
	glVertex3f(0.5, 0.5, 0.5);
	glVertex3f(-0.5, 0.5, 0.5);
	glVertex3f(-0.5, -0.5, 0.5);
	glEnd();

	// BACK
	glBegin(GL_POLYGON);
	glNormal3f(0.0f, 0.0f, -1.0f);
	glVertex3f(-0.5, -0.5, -0.5);
	glVertex3f(-0.5, 0.5, -0.5);
	glVertex3f(0.5, 0.5, -0.5);
	glVertex3f(0.5, -0.5, -0.5);
	glEnd();

	//  RIGHT
	glBegin(GL_POLYGON);
	glNormal3f(1.0f, 0.0f, 0.0f);
	glVertex3f(0.5, -0.5, -0.5);
	glVertex3f(0.5, 0.5, -0.5);
	glVertex3f(0.5, 0.5, 0.5);
	glVertex3f(0.5, -0.5, 0.5);
	glEnd();

	// LEFT
	glBegin(GL_POLYGON);
	glNormal3f(-1.0f, 0.0f, 0.0f);
	glVertex3f(-0.5, -0.5, 0.5);
	glVertex3f(-0.5, 0.5, 0.5);
	glVertex3f(-0.5, 0.5, -0.5);
	glVertex3f(-0.5, -0.5, -0.5);
	glEnd();

	//  TOP
	glBegin(GL_POLYGON);
	glNormal3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.5, 0.5, 0.5);
	glVertex3f(0.5, 0.5, -0.5);
	glVertex3f(-0.5, 0.5, -0.5);
	glVertex3f(-0.5, 0.5, 0.5);
	glEnd();

	// BOTTOM
	glBegin(GL_POLYGON);
	glNormal3f(0.0f, -1.0f, 0.0f);
	glVertex3f(0.5, -0.5, -0.5);
	glVertex3f(0.5, -0.5, 0.5);
	glVertex3f(-0.5, -0.5, 0.5);
	glVertex3f(-0.5, -0.5, -0.5);
	glEnd();

	glPopMatrix();
	// End of Body

	//Left Leg
	glPushMatrix();
	glBegin(GL_TRIANGLES);
	glColor3f(0.6f, 0.4f, 0.1f);
	glNormal3f(1.0f, 0.0f, 0.0f);
	glVertex3f(-0.85, 0.0, 0.0);
	glVertex3f(-0.85, -1.0, 0.5);
	glVertex3f(-0.85, -1.0, -0.5);
	glEnd();

	glBegin(GL_TRIANGLES);
	glColor3f(0.6f, 0.4f, 0.1f);
	glNormal3f(0.0f, 0.0f, -1.0f);
	glVertex3f(-0.55, 0.0, 0.0);
	glVertex3f(-0.55, -1.0, 0.5);
	glVertex3f(-0.55, -1.0, -0.5);
	glEnd();


	glBegin(GL_POLYGON);
	glColor3f(0.75f, 0.75f, 0.75f);
	glNormal3f(0.0f, 0.0f, 1.0f);
	glVertex3f(-0.85, 0.0, 0.0);
	glVertex3f(-0.85, -1.0, 0.5);
	glVertex3f(-0.55, -1.0, 0.5);
	glVertex3f(-0.55, 0.0, -0.5);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(0.75f, 0.75f, 0.75f);
	glNormal3f(0.0f, 0.0f, -1.0f);
	glVertex3f(-0.85, 0.0, 0.0);
	glVertex3f(-0.85, -1.0, -0.5);
	glVertex3f(-0.55, -1.0, -0.5);
	glVertex3f(-0.55, 0.0, -1.0);
	glEnd();
	glPopMatrix();
	// End of Left Leg

	//Right Leg
	glPushMatrix();
	glBegin(GL_TRIANGLES);
	glColor3f(0.6f, 0.4f, 0.1f);
	glNormal3f(1.0f, 0.0f, 0.0f);
	glVertex3f(0.85, 0.0, 0.0);
	glVertex3f(0.85, -1.0, 0.5);
	glVertex3f(0.85, -1.0, -0.5);
	glEnd();

	glBegin(GL_TRIANGLES);
	glColor3f(0.6f, 0.4f, 0.1f);
	glNormal3f(0.0f, 0.0f, -1.0f);
	glVertex3f(0.55, 0.0, 0.0);
	glVertex3f(0.55, -1.0, 0.5);
	glVertex3f(0.55, -1.0, -0.5);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(0.75f, 0.75f, 0.75f);
	glNormal3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0.85, 0.0, 0.0);
	glVertex3f(0.85, -1.0, 0.5);
	glVertex3f(0.55, -1.0, 0.5);
	glVertex3f(0.55, 0.0, -0.5);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(0.75f, 0.75f, 0.75f);
	glNormal3f(0.0f, 0.0f, -1.0f);
	glVertex3f(0.85, 0.0, 0.0);
	glVertex3f(0.85, -1.0, -0.5);
	glVertex3f(0.55, -1.0, 0.5);
	glVertex3f(0.55, 0.0, -0.5);
	glEnd();
	glPopMatrix();
	// End of Left Leg

	// Neck
	// Position and display GLU wire-frame cylinder.
	GLUquadricObj* cylinder; // Set name for GLU quadric object.
	glPushMatrix();
	glTranslatef(0.0, 0.5, 0.5);
	cylinder = gluNewQuadric();
	glColor3f(1.0, 1.0, 0.0);
	// gluQuadricDrawStyle(cylinder, GLU_LINE);
	glRotatef(50, -1.0, 0.0, 0.0);
	gluCylinder(cylinder, 0.2, 0.2, 0.7, 6, 1);
	glPopMatrix();
	//End of neck

	//Left Eye
	GLUquadricObj* cylinder1; // Set name for GLU quadric object.
	glPushMatrix();
	glTranslatef(-0.2, 1.2, 0.5);
	cylinder1 = gluNewQuadric();
	glColor3f(0.5, 0.5, 0.5);
	//  gluQuadricDrawStyle(cylinder1, GLU_LINE);
	glRotatef((GLfloat)leftEye, 0.1, 0.0, 0.0);
	gluCylinder(cylinder1, 0.2, 0.2, 0.7, 10, 1);
	glPopMatrix();
	//End of Left Eye

	//Right Eye
	GLUquadricObj* cylinder2; // Set name for GLU quadric object.
	glPushMatrix();
	glTranslatef(0.2, 1.2, 0.5);
	cylinder2 = gluNewQuadric();
	glColor3f(0.5, 0.5, 0.5);
	//  gluQuadricDrawStyle(cylinder2, GLU_LINE);
	glRotatef((GLfloat)rightEye, 0.1, 0.0, 0.0);
	gluCylinder(cylinder2, 0.2, 0.2, 0.7, 10, 1);
	glPopMatrix();
	//End of Right Eye


	//Left Hand
	glPushMatrix();
	glTranslatef(0.3, 0.0, 0.0);
	glRotatef((GLfloat)leftArm, 0.0, 0.0, 1.0);
	glPushMatrix();
	glTranslatef(1.0, 0.0, 0.0);
	glColor3f(1.0, 1.0, 0.0);
	glScalef(1.5, 0.4, 0.5);
	glutSolidCube(1.0);
	glPopMatrix();
	glPopMatrix();

	//Right Hand
	glPushMatrix();
	glTranslatef(-0.7, 0.0, 0.0);
	glRotatef((GLfloat)rightArm, 0.0, 0.0, 1.0);
	glPushMatrix();
	glTranslatef(-0.5, 0.0, 0.0);
	glColor3f(1.0, 1.0, 0.0);
	glScalef(1.5, 0.4, 0.5);
	glutSolidCube(1.0);
	glPopMatrix();

	glPopMatrix();
}

void renderScene(void)
{
	if (deltaMove)
		computePos(deltaMove);

	// Clear color and Depth Buffers
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.0f, 0.0f, -10.0f);
	//Add ambient light
	GLfloat ambientColor[] = { 0.2f, 0.2f, 0.2f, 1.0f };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientColor);

	//Add positioned light
	GLfloat lightColor0[] = { 0.5f, 0.5f, 0.5f, 1.0f };
	GLfloat lightPos0[] = { 4.0f, 0.0f, 8.0f, 1.0f };
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor0);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos0);

	//Add directed light
	GLfloat lightColor1[] = { 0.5f, 0.2f, 0.2f, 1.0f };

	//Coming from the direction (-1, 0.5, 0.5)
	GLfloat lightPos1[] = { -1.0f, 0.5f, 0.5f, 0.0f };
	glLightfv(GL_LIGHT1, GL_DIFFUSE, lightColor1);
	glLightfv(GL_LIGHT1, GL_POSITION, lightPos1);

	//Reset transformations
	glLoadIdentity();

	gluLookAt(x, 1.0f, z,
		x + lx, 1.0f, z + lz,
		0.0f, 1.0f, 0.0f);
	drawRobot();

	glutSwapBuffers();
}

void processNormalKeys(unsigned char key, int xx, int yy)
{
	if (key == 27)
		exit(0);
}

void pressKey(int key, int xx, int yy)
{
	switch (key)
	{
	case GLUT_KEY_UP: deltaMove = 0.5f; break;
	case GLUT_KEY_DOWN: deltaMove = -0.5f; break;
	}
}

void releaseKey(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_UP:
	case GLUT_KEY_DOWN:
		deltaMove = 0;
		break;
	}
}

void mouseMove(int x, int y)
{
	if (xOrigin >= 0)
	{
		//update deltaAngle
		deltaAngle = (x - xOrigin) * 0.001f;

		//update camera's direction
		lx = sin(angle + deltaAngle);
		lz = -cos(angle + deltaAngle);
	}
}

void mouseButton(int button, int state, int x, int y)
{
	// only start motion if the the left button is pressed
	if (button == GLUT_LEFT_BUTTON)
	{
		// when the button is released
		if (state == GLUT_UP)
		{
			angle += deltaAngle;
			xOrigin = -1;
		}
		else    //state = GLUT_DOWN
		{
			xOrigin = x;
		}
	}
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(200, 100);
	glutCreateWindow("Final Project (Wall-E Robot)");
	init();
	initRendering();

	//register callbacks
	glutDisplayFunc(renderScene);
	glutDisplayFunc(renderScene);
	glutIdleFunc(renderScene);

	glutIgnoreKeyRepeat(1);
	glutKeyboardFunc(processNormalKeys);
	glutSpecialFunc(pressKey);
	glutSpecialUpFunc(releaseKey);

	//two new functions
	glutMouseFunc(mouseButton);
	glutMotionFunc(mouseMove);

	glutKeyboardFunc(keyboard);
	glutReshapeFunc(reshape);
	glEnable(GL_DEPTH_TEST);

	glutMainLoop();
	return 0;
}