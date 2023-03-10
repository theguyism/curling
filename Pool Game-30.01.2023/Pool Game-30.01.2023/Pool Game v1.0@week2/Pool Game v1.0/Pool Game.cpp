// Pool Game.cpp : Defines the entry point for the console application.
//

#include <thread>     // std::this_thread::sleep_for
#include <chrono> 
#include "stdafx.h"
#include "stdafx.h"
#include<glut.h>
#include<math.h>
#include"simulation.h"
#include <string.h>


//variables
bool startGame = true;
int Gameturn = 0;
int MaxGameTurn = 4;
bool startgame = false;
bool nonRepeat = false;
bool gameOver = false;
bool canhit = true;
float gCueAnglePass = 0.0;
float gCuePowerPass = 0.0;

//cue variables
float gCueAngle = 0.0;
float gCuePower = 0.15;
bool gCueControl[4] = {false,false,false,false};
float gCueAngleSpeed = 2.0f; //radians per second
float gCuePowerSpeed = 0.25f;
float gCuePowerMax = 0.75;
float gCuePowerMin = 0.1;
float gCueBallFactor = 8.0;
bool gDoCue = true;





//camera variables
vec3 gCamPos(0.0,0.7,2.1);
vec3 gCamLookAt(0.0,0.0,0.0);
bool gCamRotate = true;
float gCamRotSpeed = 0.2;
float gCamMoveSpeed = 0.5;
bool gCamL = false;
bool gCamR = false;
bool gCamU = false;
bool gCamD = false;
bool gCamZin = false;
bool gCamZout = false;

//rendering options
#define DRAW_SOLID	(0)

void DoCamera(int ms)
{
	static const vec3 up(0.0,1.0,0.0);

	if(gCamRotate)
	{
		if(gCamL)
		{
			vec3 camDir = (gCamLookAt - gCamPos).Normalised();
			vec3 localL = up.Cross(camDir);
			vec3 inc = (localL* ((gCamRotSpeed*ms)/1000.0) );
			gCamLookAt = gCamPos + camDir + inc;
		}
		if(gCamR)
		{
			vec3 camDir = (gCamLookAt - gCamPos).Normalised();
			vec3 localR = up.Cross(camDir);
			vec3 inc = (localR* ((gCamRotSpeed*ms)/1000.0) );
			gCamLookAt = gCamPos + camDir - inc;
		}
		if(gCamU)
		{
			vec3 camDir = (gCamLookAt - gCamPos).Normalised();
			vec3 localR = camDir.Cross(up);
			vec3 localUp = localR.Cross(camDir);
			vec3 inc = (localUp* ((gCamMoveSpeed*ms)/1000.0) );
			gCamLookAt = gCamPos + camDir + inc;
		}
		if(gCamD)
		{
			vec3 camDir = (gCamLookAt - gCamPos).Normalised();
			vec3 localR = camDir.Cross(up);
			vec3 localUp = localR.Cross(camDir);
			vec3 inc = (localUp* ((gCamMoveSpeed*ms)/1000.0) );
			gCamLookAt = gCamPos + camDir - inc;
		}		
	}
	else
	{
		if(gCamL)
		{
			vec3 camDir = (gCamLookAt - gCamPos).Normalised();
			vec3 localL = up.Cross(camDir);
			vec3 inc = (localL* ((gCamMoveSpeed*ms)/1000.0) );
			gCamPos += inc;
			gCamLookAt += inc;
		}
		if(gCamR)
		{
			vec3 camDir = (gCamLookAt - gCamPos).Normalised();
			vec3 localR = camDir.Cross(up);
			vec3 inc = (localR* ((gCamMoveSpeed*ms)/1000.0) );
			gCamPos += inc;
			gCamLookAt += inc;
		}
		if(gCamU)
		{
			vec3 camDir = (gCamLookAt - gCamPos).Normalised();
			vec3 localR = camDir.Cross(up);
			vec3 localUp = localR.Cross(camDir);
			vec3 inc = (localUp* ((gCamMoveSpeed*ms)/1000.0) );
			gCamPos += inc;
			gCamLookAt += inc;
		}
		if(gCamD)
		{
			vec3 camDir = (gCamLookAt - gCamPos).Normalised();
			vec3 localR = camDir.Cross(up);
			vec3 localDown = camDir.Cross(localR);
			vec3 inc = (localDown* ((gCamMoveSpeed*ms)/1000.0) );
			gCamPos += inc;
			gCamLookAt += inc;
		}
	}

	if(gCamZin)
	{
		vec3 camDir = (gCamLookAt - gCamPos).Normalised();
		vec3 inc = (camDir* ((gCamMoveSpeed*ms)/1000.0) );
		gCamPos += inc;
		gCamLookAt += inc;
	}
	if(gCamZout)
	{
		vec3 camDir = (gCamLookAt - gCamPos).Normalised();
		vec3 inc = (camDir* ((gCamMoveSpeed*ms)/1000.0) );
		gCamPos -= inc;
		gCamLookAt -= inc;
	}
}

//draw circle
void displayRound() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f(0.0, 0.0, 1.0);
	glBegin(GL_POLYGON);

	for (int i = 0; i < 500; i++)
	{
		float theta = TWO_PI * float(i) / 500.0f;
		float x_c = 0.2f * cosf(theta);
		float z_c = 0.2f * sinf(theta);

		glVertex3f(x_c, 0.0f, -0.5f + z_c);
	}


	glEnd();
}

void displayRound2() {
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_POLYGON);

	for (int i = 0; i < 500; i++)
	{
		float theta = TWO_PI * float(i) / 500.0f;
		float x_c = 0.15f * cosf(theta);
		float z_c = 0.15f * sinf(theta);

		glVertex3f(x_c, 0.001f, -0.5f + z_c);
	}


	glEnd();
}

void displayRound3() {
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_POLYGON);

	for (int i = 0; i < 500; i++)
	{
		float theta = TWO_PI * float(i) / 500.0f;
		float x_c = 0.10f * cosf(theta);
		float z_c = 0.10f * sinf(theta);

		glVertex3f(x_c, 0.0011f, -0.5f + z_c);
	}


	glEnd();
}

void displayRound4() {
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_POLYGON);

	for (int i = 0; i < 500; i++)
	{
		float theta = TWO_PI * float(i) / 500.0f;
		float x_c = 0.05f * cosf(theta);
		float z_c = 0.05f * sinf(theta);

		glVertex3f(x_c, 0.00111f, -0.5f + z_c);
	}


	glEnd();
}


void displayRound5() {
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_POLYGON);

	for (int i = 0; i < 500; i++)
	{
		float theta = TWO_PI * float(i) / 500.0f;
		float x_c = 0.05f * cosf(theta);
		float z_c = 0.05f * sinf(theta);

		glVertex3f(x_c, 0.00111f, 1.0f + z_c);
	}


	glEnd();
}



void RenderScene(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//set camera
	glLoadIdentity();
	gluLookAt(gCamPos(0), gCamPos(1), gCamPos(2), gCamLookAt(0), gCamLookAt(1), gCamLookAt(2), 0.0f, 1.0f, 0.0f);
	displayRound();
	displayRound2();
	displayRound3();
	displayRound4();
	displayRound5();

	//draw the stone
	glColor3f(0.0, 1.0, 0.0);
		for (int i = 0; i < NUM_BALLS; i++)
		{
			glPushMatrix();
			glTranslatef(gTable.balls[i].position(0), (BALL_RADIUS / 2.0), gTable.balls[i].position(1)); //greenball
#if DRAW_SOLID
			glutSolidSphere(gTable.balls[i].radius, 12, 32);
#else
			//glutWireSphere(gTable.balls[i].radius,12,12);
			// CREATING THE CURLING STONES
			glutWireSphere(gTable.balls[i].radius, 10, 5);
#endif
			glPopMatrix();
			glColor3f(0.0, 0.0, 1.0);
		}
		glColor3f(1.0, 1.0, 1.0);//edge

		// (gTable.AnyBallsMoving() == false && nonRepeat == true) {
			if (gameOver == false)
				if(Gameturn<MaxGameTurn){

					if (gTable.AnyBallsMoving() == false) {
						//using namespace std::this_thread;
						//using namespace std::chrono;
						//sleep_for(seconds(1));
						for (int i = 0; i < NUM_BALLS; i++)
						{
							gTable.balls[i].Reset();
				


						}
						
					}
				}
				


	/*
	char  da1[20] = "0";
	itoa(gTable.players[0].score, da1, 10);
	glRasterPos2f(-0.6f, 0.7f);
	glColor3f(1., 0., 0.);
	char  da2[20] = "player 1 Score :";
	int lenc1 = strlen(da2);
	for (int i = 0; i < lenc1; i++) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, da2[i]);
	}
	int lenc = strlen(da1);
	for (int i = 0; i < lenc; i++) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, da1[i]);
	}

	char  da3[20] = "0";
	itoa(gTable.players[1].score, da3, 10);
	glRasterPos2f(-0.6f, 0.8f);
	glColor3f(1., 0., 0.);
	char  da4[20] = "player 2 Score :";
	int lenc2 = strlen(da4);
	for (int i = 0; i < lenc2; i++) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, da4[i]);
	}
	int lenc3 = strlen(da3);
	for (int i = 0; i < lenc3; i++) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, da3[i]);
	}

	*/

		//draw the table
		glPushMatrix();

		glBegin(GL_LINE_LOOP);
		glVertex3f(-TABLE_X, 0.0, -TABLE_Z);
		glVertex3f(-TABLE_X, 0.1, -TABLE_Z);
		glVertex3f(-TABLE_X, 0.1, TABLE_Z);
		glVertex3f(-TABLE_X, 0.0, TABLE_Z);
		glEnd();
		glBegin(GL_LINE_LOOP);
		glVertex3f(TABLE_X, 0.0, -TABLE_Z);
		glVertex3f(TABLE_X, 0.1, -TABLE_Z);
		glVertex3f(TABLE_X, 0.1, TABLE_Z);
		glVertex3f(TABLE_X, 0.0, TABLE_Z);
		glEnd();
		glBegin(GL_LINE_LOOP);
		glVertex3f(TABLE_X, 0.0, -TABLE_Z);
		glVertex3f(TABLE_X, 0.1, -TABLE_Z);
		glVertex3f(-TABLE_X, 0.1, -TABLE_Z);
		glVertex3f(-TABLE_X, 0.0, -TABLE_Z);
		glEnd();
		glBegin(GL_LINE_LOOP);
		glVertex3f(TABLE_X, 0.0, TABLE_Z);
		glVertex3f(TABLE_X, 0.1, TABLE_Z);
		glVertex3f(-TABLE_X, 0.1, TABLE_Z);
		glVertex3f(-TABLE_X, 0.0, TABLE_Z);
		glEnd();





		//draw the cue
		if (gDoCue)
		{
			glBegin(GL_LINES);
			float cuex = sin(gCueAngle) * gCuePower;
			float cuez = cos(gCueAngle) * gCuePower;
			glColor3f(1.0, 0.0, 0.0);
			glVertex3f(gTable.balls[0].position(0), (BALL_RADIUS / 2.0f), gTable.balls[0].position(1));
			glVertex3f((gTable.balls[0].position(0) + cuex), (BALL_RADIUS / 2.0f), (gTable.balls[0].position(1) + cuez));
			glColor3f(1.0, 1.0, 1.0);
			glEnd();
		}

		glPopMatrix();

		glFlush();
		glutSwapBuffers();
	}


void SpecKeyboardFunc(int key, int x, int y) 
{
	switch(key)
	{
		case GLUT_KEY_LEFT:
		{
			gCueControl[0] = true;
			break;
		}
		case GLUT_KEY_RIGHT:
		{
			gCueControl[1] = true;
			break;
		}
		case GLUT_KEY_UP:
		{
			gCueControl[2] = true;
			break;
		}
		case GLUT_KEY_DOWN:
		{
			gCueControl[3] = true;
			break;
		}
	}
}

void SpecKeyboardUpFunc(int key, int x, int y) 
{
	switch(key)
	{
		case GLUT_KEY_LEFT:
		{
			gCueControl[0] = false;
			break;
		}
		case GLUT_KEY_RIGHT:
		{
			gCueControl[1] = false;
			break;
		}
		case GLUT_KEY_UP:
		{
			gCueControl[2] = false;
			break;
		}
		case GLUT_KEY_DOWN:
		{
			gCueControl[3] = false;
			break;
		}
	}
}

void KeyboardFunc(unsigned char key, int x, int y) 
{
	switch(key)
	{
	case(13):
		{
			if(gDoCue)
			{
				vec2 imp(	(-sin(gCueAngle) * gCuePower * gCueBallFactor),
							(-cos(gCueAngle) * gCuePower * gCueBallFactor));
				gTable.balls[0].ApplyImpulse(imp);				
			}
			break;
		}
	case(27):
		{
			for(int i=0;i<NUM_BALLS;i++)
			{
				gTable.balls[i].Reset();
			}
			break;
		}
	case(32):
		{
			gCamRotate = false;
			break;
		}
	case('z'):
		{
			gCamL = true;
			break;
		}
	case('c'):
		{
			gCamR = true;
			break;
		}
	case('s'):
		{
			gCamU = true;
			break;
		}
	case('x'):
		{
			gCamD = true;
			break;
		}
	case('f'):
		{
			gCamZin = true;
			break;
		}
	case('v'):
		{
			gCamZout = true;
			break;
		}
	}

}

void KeyboardUpFunc(unsigned char key, int x, int y) 
{
	switch(key)
	{
	case(32):
		{
			gCamRotate = true;
			break;
		}
	case('z'):
		{
			gCamL = false;
			break;
		}
	case('c'):
		{
			gCamR = false;
			break;
		}
	case('s'):
		{
			gCamU = false;
			break;
		}
	case('x'):
		{
			gCamD = false;
			break;
		}
	case('f'):
		{
			gCamZin = false;
			break;
		}
	case('v'):
		{
			gCamZout = false;
			break;
		}
	}
}

void ChangeSize(int w, int h) {

	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if(h == 0) h = 1;
	float ratio = 1.0* w / h;

	// Reset the coordinate system before modifying
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);

	// Set the correct perspective.
	gluPerspective(45,ratio,0.2,1000);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	//gluLookAt(0.0,0.7,2.1, 0.0,0.0,0.0, 0.0f,1.0f,0.0f);
	gluLookAt(gCamPos(0),gCamPos(1),gCamPos(2),gCamLookAt(0),gCamLookAt(1),gCamLookAt(2),0.0f,1.0f,0.0f);
}

void InitLights(void)
{
	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat mat_shininess[] = { 50.0 };
	GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };
	glClearColor (0.0, 0.0, 0.0, 0.0);
	glShadeModel (GL_SMOOTH);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	GLfloat light_ambient[] = { 2.0, 2.0, 2.0, 1.0 };
	glLightfv(GL_LIGHT1, GL_AMBIENT, light_ambient);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_DEPTH_TEST);
}

void UpdateScene(int ms) 
{
	if(gTable.AnyBallsMoving()==false) gDoCue = true;
	else gDoCue = false;

	if(gDoCue)
	{
		if(gCueControl[0]) gCueAngle -= ((gCueAngleSpeed * ms)/1000);
		if(gCueControl[1]) gCueAngle += ((gCueAngleSpeed * ms)/1000);
		if (gCueAngle <0.0) gCueAngle += TWO_PI;
		if (gCueAngle >TWO_PI) gCueAngle -= TWO_PI;

		if(gCueControl[2]) gCuePower += ((gCuePowerSpeed * ms)/1000);
		if(gCueControl[3]) gCuePower -= ((gCuePowerSpeed * ms)/1000);
		if(gCuePower > gCuePowerMax) gCuePower = gCuePowerMax;
		if(gCuePower < gCuePowerMin) gCuePower = gCuePowerMin;
	}

	DoCamera(ms);

	gTable.Update(ms);

	glutTimerFunc(SIM_UPDATE_MS, UpdateScene, SIM_UPDATE_MS);
	
}

int _tmain(int argc, _TCHAR* argv[])
{
	glutInit(&argc, ((char **)argv));
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE| GLUT_RGBA);
	glutInitWindowPosition(0,0);
	glutInitWindowSize(1000,700);
	//glutFullScreen();
	glutCreateWindow("MSc Workshop : Pool Game");
	#if DRAW_SOLID
	InitLights();
	#endif
	glutDisplayFunc(RenderScene);
	glutTimerFunc(SIM_UPDATE_MS, UpdateScene, SIM_UPDATE_MS);
	glutReshapeFunc(ChangeSize);
	glutIdleFunc(RenderScene);
	
	glutIgnoreKeyRepeat(1);
	glutKeyboardFunc(KeyboardFunc);
	glutKeyboardUpFunc(KeyboardUpFunc);
	glutSpecialFunc(SpecKeyboardFunc);
	glutSpecialUpFunc(SpecKeyboardUpFunc);
	glEnable(GL_DEPTH_TEST);
	glutMainLoop();
}
