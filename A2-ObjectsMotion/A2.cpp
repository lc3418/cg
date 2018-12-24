#include "GL/freeglut.h"
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <windows.h>
#include <commdlg.h>
#include <string>
#include <sstream>

const int width = 800;
const int height = 600;

int xc = 0; //variables for teapot operations
int yc = 0;
double xDangle = 0.0;
double yDangle = 0.0;
double zDangle = 0.0;
double currentX;
double currentY;
float speed = 0.0;
float slope = 0.0;
float xD = 0.0;
float yD = 0.0;
float zD = 5.0;
float tx = 0.0;
float ty = 0.0;
float tz = 0.0;
float ExD = 0.0;
float EyD = 1.0;
float EzD = 0.0;
float displacementX = 0.0;
float displacementY = 0.0;
bool Rotate = false;
bool Auto = false;
bool world = false;
bool teapot = false;
bool up = true;
bool down = false;

int NOV = 0; //variables for showing files
int NOF = 0;
std::string vet1[100000];
std::string fac1[100000];

GLfloat position0[] = { 1.0,0.0,0.0,0.0 }; //variables for lights
GLfloat position1[] = { -1.0,0.0,0.0,0.0 };
GLfloat position2[] = { 0.0,1.0,0.0,0.0 };
GLfloat position3[] = { 0.0,-1.0,0.0,0.0 };
GLfloat AmbientLight[] = { 0.2,0.2,0.2,1.0 };
GLfloat DiffuseLight0[] = { 0.7,0.7,0.7,1.0 };
GLfloat DiffuseLight1[] = {0.75,0.0,0.1,1.0};
GLfloat DiffuseLight2[] = {0.0,0.8,0.1,1.0};
GLfloat DiffuseLight3[] = {0.0,0.0,0.95,1.0};
GLfloat SpecularLight0[] = {0.7,0.7,0.0,1.0};
GLfloat SpecularLight1[] = {0.7,0.0,0.7,1.0};
GLfloat SpecularLight2[] = {0.0,0.7,0.7,1.0};
GLfloat SpecularLight3[] = {0.7,0.7,0.7,1.0};
bool l0 = true;
bool l1 = false;
bool l2 = false;
bool l3 = false;
bool shade = true;

float nmx = 0.0;
float nmy = 0.0;
float nmz = 0.0;

using namespace std;

static void init() {
	glClearColor(0.0f, 0.0f, 0.0f, 1.f);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0 , width , 0 , height , 1, 100);
	glLightfv(GL_LIGHT0, GL_POSITION, position0);
	glLightfv(GL_LIGHT0, GL_AMBIENT, AmbientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, DiffuseLight0);
	glLightfv(GL_LIGHT0, GL_SPECULAR, SpecularLight0);

	glLightfv(GL_LIGHT1, GL_POSITION, position1);
	glLightfv(GL_LIGHT1, GL_AMBIENT, AmbientLight);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, DiffuseLight1);
	glLightfv(GL_LIGHT1, GL_SPECULAR, SpecularLight1);

	glLightfv(GL_LIGHT2, GL_POSITION, position2);
	glLightfv(GL_LIGHT2, GL_AMBIENT, AmbientLight);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, DiffuseLight2);
	glLightfv(GL_LIGHT2, GL_SPECULAR, SpecularLight2);

	glLightfv(GL_LIGHT3, GL_POSITION, position3);
	glLightfv(GL_LIGHT3, GL_AMBIENT, AmbientLight);
	glLightfv(GL_LIGHT3, GL_DIFFUSE, DiffuseLight3);
	glLightfv(GL_LIGHT3, GL_SPECULAR, SpecularLight3);

	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);

}

void draw() {
	//R = true;
	if (teapot == false) {
		glBegin(GL_LINE_STRIP);
		glLineWidth(5.f);
		glColor3f(0.f, 1.f, 0.f);
		glVertex3f(0, 0, 0);
		glVertex3f((float)xc, (float)yc, 0);
		glEnd();

		glBegin(GL_LINE_STRIP);
		glLineWidth(5.f);
		glColor3f(1.f, 0.f, 0.f);

		if (slope != 0) {
			if ((xc < 0 && yc>0) || (xc > 0 && yc > 0)) {
				glVertex3f(-400, -400 * slope, 0);
				glVertex3f(0, 0, 0);
			}
			else {
				glVertex3f(400, 400 * slope, 0);
				glVertex3f(0, 0, 0);
			}
		}
		glEnd();
	}
	glFlush();
}

void tp(float size) {
	glutSolidTeapot(size);
}

bool tea = false;
bool file = false;

void show() {
	//cout << NOV << " " << NOF << endl;
	for (int i = 0;i < NOF;i++) {
		int face[3] = { 0,0,0 };//array of 3 vetices that form one polygon
		string str = fac1[i];
		istringstream temp1(str);
		//cout << str << endl;
		while (temp1 >> str) {
			for (int i = 0;i < 3;i++) {
				if (face[i] == 0) {
					//cout << stoi(str) << endl;
					face[i] = stoi(str);
					//cout << face[i] << endl;
					break;
				}
			}
		}
		glBegin(GL_POLYGON);
		for (int i = 0;i < 3;i++) {
			string point = vet1[face[i]];
			float v1 = 0;
			float v2 = 0;
			float v3 = 0;
			bool vv1 = true;
			bool vv2 = true;
			bool vv3 = true;
		
			stringstream temp(point);
			while (temp >> point) {
				if (vv1 == true && vv2 == true && vv3 == true) {
					v1 = stof(point);
					vv1 = false;
				}
				else if (vv1 == false && vv2 == true && vv3 == true) {
					v2 = stof(point);
					vv2 = false;
				}
				else if (vv1 == false && vv2 == false && vv3 == true) {
					v3 = stof(point);
					vv1 = true;
					vv2 = true;
				}
				//cout << v1 << " " << v2 << " " << v3 << endl;
			}
			//cout << v1 << " " << v2 << " " << v3 << endl;
			glVertex3f(v1, v2, v3);
		}
		glEnd();
		glFlush();
	}
}



void display() {
	glClear(GL_COLOR_BUFFER_BIT);
	if (shade == true) {
		glShadeModel(GL_SMOOTH);
	}
	if (shade == false) {
		glShadeModel(GL_FLAT);
	}
	glColor3f(1.f, 1.f, 1.f);
	glLoadIdentity();
	gluLookAt(xD, yD, zD, tx, ty, tz, ExD, EyD, EzD);
	if (world == true && teapot == false) {
		glRotatef(zDangle, 1.0, slope, 0.0);
	}
	if (teapot == true && world == false) {
		glRotatef(xDangle, 1.0, 0.0, 0.0);
		glRotatef(yDangle, 0.0, 1.0, 0.0);
		glRotatef(zDangle, 0.0, 0.0, 1.0);
	}
	glTranslatef(displacementX, 0.0, 0.0);
	glTranslatef(0.0, displacementY, 0.0);

	if (tea == true) {
		tp(1.0);
	}
	if (file == true) {
		show();
		
	}

	draw();
	glFlush();
	glutSwapBuffers;
}


void reshape(int w, int h) {
	glViewport(0, 50, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, (double)w / (double)h, 1.0, 20.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(xD, yD, zD, tx, ty, tz, ExD, EyD, EzD);
}

void mouse(int button, int state, int x, int y) {
	int xx, yy;
	if (button == GLUT_LEFT_BUTTON) {
		int key = glutGetModifiers();
		if (state == GLUT_DOWN) {
			if (key == GLUT_ACTIVE_SHIFT) {
				displacementX += 1.0;
			}
			else if (key == GLUT_ACTIVE_ALT) {
				displacementY += 1.0;
			}
			else if (key == GLUT_ACTIVE_CTRL) {			
				if (xD == 0 && yD == 0) {
					if (zD < 15.0 && up == true) {
						zD+=1.0;
					}
					if (zD == 15.0) {
						down = true;
						up = false;
						zD-=1.0;
					}
					if (zD > 1.0 && down == true) {
						zD-=1.0;
					}
					if (zD == 1.0) {
						down = false;
						up = true;
						zD+=1.0;
					}
				}
				//change view angle
			}
			else {
				currentX = x;
				currentY = y;
				xx = x - 400;
				yy = 300 - y;
				speed = (float)((sqrt(pow(xx,2) + pow(yy,2))) / 2500);
				cout << "Rotation speed: " << speed << endl;
			}
		}
	}	
}

void rotate(int x, int y) {
	if (Rotate == true || teapot == true) {
		int x1 = currentX - x;
		int y1 = currentY - y;
		xDangle += 360 * (double)x1 / (double)height + speed;
		yDangle += 360 * (double)y1 / (double)height + speed;
		zDangle += 360 * (double)y1 / (double)height + speed;
		currentX = x;
		currentY = y;
		glutPostRedisplay();
	}
}

void autoRotate() {
	if (speed == 0.0) {
		speed = 0.1;
	}
	if (Auto == true) {
		xDangle += speed;
		yDangle += speed;
		zDangle += speed;
	}	
	glutPostRedisplay();
}

void drawAxes(int button,int state, int x ,int y) {
	xDangle = 0.0;
	yDangle = 0.0;
	zDangle = 0.0;
	if (button == GLUT_LEFT_BUTTON) {
		if (state == GLUT_DOWN) {
			xc = (x-400);
			yc = (-y+300);
			float a = (float)yc / (float)xc;
			slope = -1 / a;//slope
			cout << "X:" << xc << " " << "Y:" << yc << " " << "Z:0" << endl;
			cout << "Slope of A: " << slope << endl<< endl;
			//glutDisplayFunc(display);
		}
	}
}


static void menu_callback(int menu) {}

static void OA_callback(int OA) {
	if (OA == 0) {
		cout << "Clear" << endl;
		xc = 0;
		yc = 0;
		slope = 0.0;
		speed = 0.0;
		xDangle = 0.0;
		yDangle = 0.0;
		zDangle = 0.0;
		xD = 0.0;
		yD = 0.0;
		zD = 5.0;
		ExD = 0.0;
		EyD = 1.0;
		EzD = 0.0;
		displacementX = 0.0;
		displacementY = 0.0;
		Rotate = false;
		Auto = false;
		world = false;
		teapot = false;
		up = true;
		down = false;
		display();
	}
	else if (OA == 1) {
		//R = true;
		xDangle = 0.0;
		yDangle = 0.0;
		zDangle = 0.0;
		displacementX = 0.0;
		displacementY = 0.0;
		speed = 0.1;
	}
	else {
		exit(0);
	}
}

static void Rotate_callback(int Rt) {
	if (Rt == 1) {
		world = true;
		teapot = false;
		if (Rotate == false) {
			cout << "Please select a rotation axis." << endl;
		}
		else {
			cout << "World Rotation begins." << endl << endl;
			glutMouseFunc(mouse);
			glutMotionFunc(rotate);
		}
	}
	if (Rt == 0) {
		xD = 0.0;
		yD = 0.0;
		zD = 5.0;
		tx = 0.0;
		ty = 0.0;
		tz = 0.0;
		ExD = 0.0;
		EyD = 1.0;
		EzD = 0.0;
		xDangle = 0.0;
		yDangle = 0.0;
		zDangle = 0.0;
		displacementX = 0.0;
		displacementY = 0.0;
		display();
	}
	if (Rt == 2) {
		teapot = true;
		world = false;
				
		cout << "Teapot Rotation begins." << endl << endl;
		glutMouseFunc(mouse);
		glutMotionFunc(rotate);
		
	}
}


static void Display_callback(int Dp) {
	if (Dp == 0) {
		Rotate = true;
		teapot = false;
		cout << "Left click to choose a point." << endl;
		xDangle = 0.0;
		yDangle = 0.0;
		zDangle = 0.0;
		xc = 0;
		yc = 0;
		slope = 0;
		if (zDangle == 0.0 && xDangle == 0.0 && yDangle == 0.0) {
			glutMouseFunc(drawAxes);
		}
	}
	if (Dp == 1) {
		if (Auto == false) {
			Auto = true;
			if (world == false && teapot == false) {
				world = true;
				glutMouseFunc(mouse);
				glutMotionFunc(rotate);
			}
			glutIdleFunc(autoRotate);
			cout << "Auto-Rotate On." << endl;
		}
		else {
			Auto = false;
			glutIdleFunc(NULL);
			cout << "Auto-Rotate Off." << endl;
		}
	}
	if (Dp == 2) {
		//show teapot
		tea = true;
		file = false;
		display();
		
	}
	if (Dp == 3) {
		//FileSelect dialog
		glClear(GL_COLOR_BUFFER_BIT);
		TCHAR szBuffer[MAX_PATH] = { 0 };
		OPENFILENAME ofn = { 0 };
		ofn.lStructSize = sizeof(ofn);
		ofn.hwndOwner = NULL;
		ofn.lpstrFilter = L"Poly(*.poly)\0*.poly\0";
		//ofn.lpstrInitialDir = L"D:\Files";
		ofn.lpstrFile = szBuffer;
		ofn.nMaxFile = sizeof(szBuffer) / sizeof(*szBuffer);
		ofn.nFilterIndex = 0;
		//ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
		BOOL bSel = GetOpenFileNameW(&ofn);

		for (int i = 0;i < NOV;i++) {
			vet1[i] = "";
		}
		for (int i = 0;i < NOF;i++) {
			fac1[i] = "";
		}

		ifstream fin(szBuffer);
		if (fin.fail()) {
			cout << "No file choosen" << endl;
			return;
		}
		NOV = 0;
		NOF = 0;
				
		string str;
		int v = 0;
		int f = 0;
		bool flag = false;
		while (!fin.eof()) {
			getline(fin, str);
			if (flag == false) {
				if (str[0] == '/') {
					continue;
				}
				else {
					stringstream temp(str);
					while (temp >> str) {
						if (NOV == 0) {
							NOV = stoi(str); //number of vertices
						}
						else {
							NOF = stoi(str); //number of faces
						}
					}
					flag = true;
					continue;
				}
			}
			else {
				if (v < NOV) {
					vet1[v] = str;
					v++;
					//cout << str << endl;
				}
				else {
					fac1[f] = str;
					f++;
				}
			}
		}
		tea = false;
		file = true;
		//show();
		display();
	}
}

static void Light_callback(int Lt) {
	if (Lt == 0) {
		if (l0 == true) {
			glDisable(GL_LIGHT0);
			display();
			l0 = false;
		}
		else {
			glEnable(GL_LIGHT0);
			display();
			l0 = true;
		}
	}
	if (Lt == 1) {
		if (l1 == true) {
			glDisable(GL_LIGHT1);
			display();
			l1 = false;
		}
		else {
			glEnable(GL_LIGHT1);
			display();
			l1 = true;
		}
	}
	if (Lt == 2) {
		if (l2 == true) {
			glDisable(GL_LIGHT2);
			display();
			l2 = false;
		}
		else {
			glEnable(GL_LIGHT2);
			display();
			l2 = true;
		}
	}
	if (Lt == 3) {
		if (l3 == true) {
			glDisable(GL_LIGHT3);
			display();
			l3 = false;
		}
		else {
			glEnable(GL_LIGHT3);
			display();
			l3 = true;
		}
	}
	if (Lt == 4) {
		if (shade == true) {
			shade = false;
		}
		else {
			shade = true;
		}
		display();
	}
}

void createMenu() {
	int OA;
	OA = glutCreateMenu(OA_callback);
	glutAddMenuEntry("Clear", 0);
	glutAddMenuEntry("Refresh", 1);
	glutAddMenuEntry("Exit", 2);

	int Rt;
	Rt = glutCreateMenu(Rotate_callback);
	glutAddMenuEntry("Reset View", 0);
	glutAddMenuEntry("Rotate Global", 1);
	glutAddMenuEntry("Rotate Local", 2);

	int Dp;
	Dp = glutCreateMenu(Display_callback);
	glutAddMenuEntry("Show AXES", 0);
	glutAddMenuEntry("Auto-Rotate ON/OFF", 1);
	glutAddMenuEntry("Show Teapot",2);
	glutAddMenuEntry("Show File Object(s)",3);

	int Lt;
	Lt = glutCreateMenu(Light_callback);
	glutAddMenuEntry("Light 0 Toggle",0);
	glutAddMenuEntry("Light 1 Toggle",1);
	glutAddMenuEntry("Light 2 Toggle",2);
	glutAddMenuEntry("Light 3 Toggle",3);
	glutAddMenuEntry("Smooth Shade ON/OFF",4);

	glutCreateMenu(menu_callback);
	glutAddSubMenu("Other Action", OA);
	glutAddSubMenu("Rotate", Rt);
	glutAddSubMenu("Display", Dp);
	glutAddSubMenu("Light", Lt);

	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

int main(int argc, char** argv) {

	glutInit(&argc, argv);
	glutInitWindowSize(width, height);
	glutInitWindowPosition(600, 100);
	glutCreateWindow("Global Rotation in 3©\Space");

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	//glutIdleFunc(display);
	createMenu();
	glutMainLoop();

	return 0;
}



