#include "include/GL/freeglut.h"
#include "include/GL/glui.h"
#include <iostream>
#include "Camera.h"
#include "Sphere.h"
#include "Plane.h"
#include "Union.h"

GLUI *glui;
GLUI_Checkbox *checkbox;
GLUI_Panel *panel;
GLUI_EditText *edittext;


const int width = 1160;
const int height = 800;

//moderatable variables//
int m = 800; //resolution
float e = 1; //position of eye
float c = 2; //center of sphere
float r = 1; //radius of sphere, scale and postion of checkerboard
float lightDx = 1; //
float lightDy = 2; //Light Direction
float lightDz = -1; //
float lightCr = 1; //
float lightCg = 1; //Light Color
float lightCb = 1; //
int shadowSwitch = 1; //Default ON
/////////////////////////


Vector front = Vector(0, 0, -1);
Vector up = Vector(0, 1, 0);
Color dif = Color(1.0f,1.0f,1.0f);
Color spe = Color(1.0f,1.0f,1.0f);
float shin = 5;

int displayWin;

using namespace std;

void init() {
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);
	
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glPointSize(1.0);
	Camera cm = Camera(Vector(0, 0, e), front, up, 90);
	Sphere s = Sphere(Vector(0, 0, -c), r);
	Plane p = Plane(Vector(0, r, 0), -r);
	p.ch = CheckerBoard(1.0f);
	s.ph = Phong(dif, spe, shin, Vector(lightDx, lightDy, lightDz), Color(lightCr, lightCg, lightCb));
	Union u = Union(p, s);
	float px = (float)2.0f / m;
	float py = (float)2.0f / m;
	glBegin(GL_POINTS);
	for (float sy = -1;sy <= 1; sy += py) {
		for (float sx = -1;sx <= 1; sx += px) {
			Ray r = cm.getRay(sx, sy);
			Intersect i = u.intersect(r);
			if (i.intersected) {
				
				Vector temp = Vector(lightDx - i.position.x, lightDy - i.position.y, lightDz - i.position.z);
				float distance = (float)sqrt(pow(temp.x,2) + pow(temp.y, 2) + pow(temp.z, 2));
				Ray shadowRay = Ray(i.position, temp.normal());
				Vector shadowDir = temp.normal();
				Intersect lightResult = u.intersect(shadowRay);

				if (i.distance == p.intersect(r).distance) {	
					if (shadowSwitch == 1 && (lightResult.intersected && (lightResult.distance <= distance)))
					{
						Color c = Color(0, 0, 0);
						c.saturate();
						glColor3ub(c.r * 255, c.g * 255, c.b * 255);
					}
					else {
						Color c = p.ch.sample(r, i.position, i.Pnormal);
						c.saturate();
						glColor3ub(c.r * 255, c.g * 255, c.b * 255);
					}
				}
				else if (i.distance == s.intersect(r).distance) {
					Color c = s.ph.sample(r, i.position, i.Pnormal);
					c.saturate();
					glColor3ub(c.r * 255, c.g * 255, c.b * 255);
				}				

				glVertex2f(sx, sy);
			}
		}
	}
	glEnd();
	glutSwapBuffers();
}


void resize(int width, int height) {
	glViewport(0,0,800,800);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90,(double)(width/height),1,20);
}

//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////

void param_ctrl(int select) {
	if (select == 1) {
		cout << "Eye position changed to (0,0," << e << ")" << endl;
		glutSetWindow(displayWin);
		glutPostRedisplay();
	}
	if (select == 2) {
		cout << "Resolution changed to " << m << endl;	
		glutSetWindow(displayWin);
		glutPostRedisplay();
	}
	if (select == 3) {
		cout << "Center of the sphere changed to (0,0,-" << c << ")" << endl;
		glutSetWindow(displayWin);
		glutPostRedisplay();
		
	}
	if (select == 4) {
		cout << "Radius of the sphere changed to " << r << endl;
		cout << "CheckerBoard now located on y = -" << r << endl;
		glutSetWindow(displayWin);
		glutPostRedisplay();
	}
	if (select == 5) {
		cout << "X coordinate of light position changed to " << lightDx << endl;
		glutSetWindow(displayWin);
		glutPostRedisplay();
	}
	if (select == 6) {
		cout << "Y coordinate of light position changed to " << lightDy << endl;
		glutSetWindow(displayWin);
		glutPostRedisplay();
	}
	if (select == 7) {
		cout << "Z coordinate of light position changed to " << lightDz << endl;
		glutSetWindow(displayWin);
		glutPostRedisplay();
	}
	if (select == 8) {
		cout << "lightCr->" << lightCr << endl;
		glutSetWindow(displayWin);
		glutPostRedisplay();
	}
	if (select == 9) {
		cout << "lightCg->" << lightCg << endl;
		glutSetWindow(displayWin);
		glutPostRedisplay();
	}
	if (select == 10) {
		cout << "lightCb->" << lightCb << endl;
		glutSetWindow(displayWin);
		glutPostRedisplay();
	}
	if (select == 11) {
		cout << "ShadowSwitch->" << shadowSwitch << endl;
		glutSetWindow(displayWin);
		glutPostRedisplay();
	}
	
}


void show(int r) {
	if (shadowSwitch==0) {
		shadowSwitch = 1;
		cout << "Shadow on" << endl;
		glutSetWindow(displayWin);
		glutPostRedisplay();
	}
	else {
		shadowSwitch = 0;
		cout << "Shadow off" << endl;
		glutSetWindow(displayWin);
		glutPostRedisplay();
	}
}

void Exit(int) {
	exit(0);
}


void buildGlui(int displayWin) {
	GLUI_Master.set_glutReshapeFunc(resize);
	GLUI_Master.set_glutDisplayFunc(display);
	glui = GLUI_Master.create_glui_subwindow(displayWin,GLUI_SUBWINDOW_RIGHT);

	GLUI_Panel * panel1 = new GLUI_Panel(glui, "Variables", GLUI_PANEL_EMBOSSED);
	new GLUI_EditText(panel1, "Camera position 0,0,e  e:", &e,1,param_ctrl);
	new GLUI_EditText(panel1, "Resolution: ", &m, 2, param_ctrl);
	new GLUI_EditText(panel1, "Sphere center 0,0,-c  c:", &c, 3, param_ctrl);
	new GLUI_EditText(panel1, "Sphere radius r, postion of checkboard y = -r  r:", &r, 4, param_ctrl);
	new GLUI_EditText(panel1, "Shadow ON/OFF, 1-ON, 0-OFF ", &shadowSwitch, 11, param_ctrl);

	GLUI_Panel * panel2 = new GLUI_Panel(glui, "Light Control", GLUI_PANEL_EMBOSSED);
	new GLUI_EditText(panel2, "Light Direction x component  x:", &lightDx, 5, param_ctrl);
	new GLUI_EditText(panel2, "Light Direction y component  y:", &lightDy, 6, param_ctrl);
	new GLUI_EditText(panel2, "Light Direction z component  z:", &lightDz, 7, param_ctrl);
	new GLUI_EditText(panel2, "Light Color r component   r:", &lightCr, 8, param_ctrl);
	new GLUI_EditText(panel2, "Light Color g component   g:", &lightCg, 9, param_ctrl);
	new GLUI_EditText(panel2, "Light Color b component   b:", &lightCb, 10, param_ctrl);

	//GLUI_Panel * panel3 = new GLUI_Panel(glui, "Functions", GLUI_PANEL_EMBOSSED);
	//new GLUI_Checkbox(panel3, "Shadow on", &shadowSwitch, 11, show);

	GLUI_Panel * panel4 = new GLUI_Panel(glui, "  ", GLUI_PANEL_NONE);
	new GLUI_Button(panel4, "EXIT", 12, Exit);
}

//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitWindowSize(width, height);
	glutInitWindowPosition(600, 100);
	displayWin = glutCreateWindow("RayTracing");
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGBA);
	init();

	//glutDisplayFunc(display);
	buildGlui(displayWin);
	glutMainLoop();
	return 0;
}