#include "include/GL/glui.h"
#include <iostream>
#include <vector>
#include "ControlPoint.h"

using namespace std;
const int width = 800;
const int height = 800;

vector<ControlPoint> ctrlP1;
vector<ControlPoint> ctrlP2;
vector<ControlPoint> save1;
vector<ControlPoint> save2;

GLUI *glui;
GLUI_Checkbox *checkbox;
GLUI_Panel *panel;
GLUI_EditText *edittext;

int show_ControlPolygon = 1,
show_Curve = 1,
show_CurveExtended = 0,
show_DeCasteljau = 0,
show_ConvexHull = 0,
show_Curve2 = 0;

float pointColorR = 1.0;
float pointColorG = 1.0;
float pointColorB = 0.0;
float polygonColorR = 1.0;
float polygonColorG = 1.0;
float polygonColorB = 0.0;
float curveColorR = 0.0;
float curveColorG = 1.0;
float curveColorB = 0.0;
float hallColorR = 1.0;
float hallColorG = 1.0;
float hallColorB = 1.0;

int displayWin;

void display(void) {
	glClear(GL_COLOR_BUFFER_BIT);

	glPointSize(3);
	glColor3f(pointColorR, pointColorG, pointColorB);

	for (int i = 0; i < ctrlP1.size(); i++) {
		glBegin(GL_POINTS);
		glVertex2f(ctrlP1[i].x, ctrlP1[i].y);
		glEnd();
	}

	glColor3f(polygonColorR, polygonColorG, polygonColorB);
	glBegin(GL_LINE_STRIP);
	for (int i = 0; i < ctrlP1.size(); i++) {
		glVertex2f(ctrlP1[i].x, ctrlP1[i].y);
	}
	glEnd();

	glPointSize(3);
	glColor3f(pointColorR, pointColorG, pointColorB);

	for (int i = 0; i < ctrlP2.size(); i++) {
		glBegin(GL_POINTS);
		glVertex2f(ctrlP2[i].x, ctrlP2[i].y);
		glEnd();
	}

	glColor3f(polygonColorR, polygonColorG, polygonColorB);
	glBegin(GL_LINE_STRIP);
	for (int i = 0; i < ctrlP2.size(); i++) {
		glVertex2f(ctrlP2[i].x, ctrlP2[i].y);
	}
	glEnd();


	int n = ctrlP1.size();
	float xcoord[32];
	float ycoord[32];
	float ps[100][2];

	int temp = 0;
	for (double t = 0;t <= 1;t += 0.01)
	{
		for (int i = 1; i < n; ++i)
		{
			for (int j = 0; j < n - i; ++j)
			{
				if (i == 1) 
				{
					xcoord[j] = ctrlP1[j].x * (1 - t) + ctrlP1[j + 1].x * t;
					ycoord[j] = ctrlP1[j].y * (1 - t) + ctrlP1[j + 1].y * t;
					continue;
				}
	
				xcoord[j] = xcoord[j] * (1 - t) + xcoord[j + 1] * t;
				ycoord[j] = ycoord[j] * (1 - t) + ycoord[j + 1] * t;
			}

		}
		ps[temp][0] = xcoord[0];
		ps[temp][1] = ycoord[0];
		temp++;
	}

	int m = ctrlP2.size();
	float xcoord2[32];
	float ycoord2[32];
	float ps2[100][2];

	int temp2 = 0;
	for (double t = 0;t <= 1;t += 0.01)
	{
		for (int i = 1; i < m; ++i)
		{
			for (int j = 0; j < m - i; ++j)
			{
				if (i == 1)
				{
					xcoord2[j] = ctrlP2[j].x * (1 - t) + ctrlP2[j + 1].x * t;
					ycoord2[j] = ctrlP2[j].y * (1 - t) + ctrlP2[j + 1].y * t;
					continue;
				}

				xcoord2[j] = xcoord2[j] * (1 - t) + xcoord2[j + 1] * t;
				ycoord2[j] = ycoord2[j] * (1 - t) + ycoord2[j + 1] * t;
			}

		}
		ps2[temp2][0] = xcoord2[0];
		ps2[temp2][1] = ycoord2[0];
		temp2++;
	}

	if (show_Curve == 1) {
		glColor3f(curveColorR, curveColorG, curveColorB);
		glBegin(GL_LINE_STRIP);
		for(int i = 0; i < 100; i++)
		{
			glVertex2fv(ps[i]);
		}
		glEnd();

		glColor3f(curveColorR, curveColorG, curveColorB);
		glBegin(GL_LINE_STRIP);
		for (int i = 0; i < 100; i++)
		{
			glVertex2fv(ps2[i]);
		}
		glEnd();
	}

	if (show_ConvexHull == 1) {
		if (ctrlP1.size() > 2) {
			for (int i = 0;i < ctrlP1.size();i++) {
				for (int j = i + 1;j < ctrlP1.size();j++) {
					bool left = 0;
					bool right = 0;
					for (int k = 0;k < ctrlP1.size();k++) {
						if (((ctrlP1[j].x - ctrlP1[i].x) * (ctrlP1[k].y - ctrlP1[i].y) - (ctrlP1[k].x - ctrlP1[i].x) * (ctrlP1[j].y - ctrlP1[i].y)) > 0) {
							left = 1;
						}
						if (((ctrlP1[j].x - ctrlP1[i].x) * (ctrlP1[k].y - ctrlP1[i].y) - (ctrlP1[k].x - ctrlP1[i].x) * (ctrlP1[j].y - ctrlP1[i].y)) < 0) {
							right = 1;
						}						
					}
					if ((left == 1 && right == 0) || (left == 0 && right == 1)) {
						glBegin(GL_LINE_STRIP);
						glColor3f(hallColorR, hallColorG, hallColorB);
						glVertex2f(ctrlP1[i].x, ctrlP1[i].y);
						glVertex2f(ctrlP1[j].x, ctrlP1[j].y);
						glEnd();
					}
				}
			}
		}

		if (ctrlP2.size() > 2) {
			for (int i = 0;i < ctrlP2.size();i++) {
				for (int j = i + 1;j < ctrlP2.size();j++) {
					bool left = 0;
					bool right = 0;
					for (int k = 0;k < ctrlP2.size();k++) {
						if (((ctrlP2[j].x - ctrlP2[i].x) * (ctrlP2[k].y - ctrlP2[i].y) - (ctrlP2[k].x - ctrlP2[i].x) * (ctrlP2[j].y - ctrlP2[i].y)) > 0) {
							left = 1;
						}
						if (((ctrlP2[j].x - ctrlP2[i].x) * (ctrlP2[k].y - ctrlP2[i].y) - (ctrlP2[k].x - ctrlP2[i].x) * (ctrlP2[j].y - ctrlP2[i].y)) < 0) {
							right = 1;
						}
					}
					if ((left == 1 && right == 0) || (left == 0 && right == 1)) {
						glBegin(GL_LINE_STRIP);
						glColor3f(hallColorR, hallColorG, hallColorB);
						glVertex2f(ctrlP2[i].x, ctrlP2[i].y);
						glVertex2f(ctrlP2[j].x, ctrlP2[j].y);
						glEnd();
					}
				}
			}
		}
	}

	glFlush();
	glutSwapBuffers();
}

static void mouse(int button, int state , int x, int y) {
	float dx; 
	float dy;
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && show_Curve2 == 0) {
		if (ctrlP1.size() >= 32) {
			cout << "max points reached" << endl;
		}
		else {
			dx = (float)(x - (width/2)) / (width / 2);
			dy = -(float)(y - (width / 2)) / (width / 2);
			ControlPoint p = ControlPoint(dx, dy);
			ctrlP1.push_back(p);
			std::cout << dx << " " << dy << std::endl;
			display();
		}
	}

	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && show_Curve2 == 1) {
		if (ctrlP2.size() >= 32) {
			cout << "max points reached" << endl;
		}
		else {
			dx = (float)(x - (width / 2)) / (width / 2);
			dy = -(float)(y - (width / 2)) / (width / 2);
			ControlPoint p = ControlPoint(dx, dy);
			ctrlP2.push_back(p);
			std::cout << dx << " " << dy << std::endl;
			display();
		}
	}
}


void showMe(int select) {
	if (select == 1) {
		cout << "show control polygon ON/OFF." << endl;
	}

	if (select == 2) {
		cout << "show curve ON/OFF." << endl;
		glutSetWindow(displayWin);
		glutPostRedisplay();
	}

	if (select == 3) {
		cout << "show extended curve ON/OFF." << endl;
	}

	if (select == 4) {
		cout << "show De Casteljau ON/OFF." << endl;
	}

	if (select == 5) {
		cout << "show convex hull ON/OFF." << endl;
		glutSetWindow(displayWin);
		glutPostRedisplay();
	}

	if (select == 9) {
		cout << "show bezier curve 2." << endl;
		glutSetWindow(displayWin);
		glutPostRedisplay();
	}

	if (select == 10 || select == 11 || select == 12 || select == 13 || select == 14 || select == 15 || select == 16 || select == 17 || select == 18 || select == 19 || select == 20 || select == 21) {
		glutSetWindow(displayWin);
		glutPostRedisplay();
	}	
}

void Clear(int) {
	if (show_Curve2 == 0) {
		save1 = ctrlP1;
		ctrlP1.clear();
	}
	if (show_Curve2 == 1) {
		save2 = ctrlP2;
		ctrlP2.clear();
	}

	glutSetWindow(displayWin);
	glutPostRedisplay();	
}

void Undo(int) {
	if (show_Curve2 == 0) {
		if (!ctrlP1.empty()) {
			ctrlP1.pop_back();
			glutSetWindow(displayWin);
			glutPostRedisplay();
		}
		else {
			ctrlP1 = save1;
			glutSetWindow(displayWin);
			glutPostRedisplay();
		}
	}

	if (show_Curve2 == 1) {
		if (!ctrlP2.empty()) {
			ctrlP2.pop_back();
			glutSetWindow(displayWin);
			glutPostRedisplay();
		}
		else {
			ctrlP2 = save2;
			glutSetWindow(displayWin);
			glutPostRedisplay();
		}
	}
}

void Exit(int) {
	exit(0);
}

void buildGlui(int displayWin) {
	GLUI_Master.set_glutDisplayFunc(display);
	GLUI_Master.set_glutMouseFunc(mouse);
	glui = GLUI_Master.create_glui_subwindow(displayWin, GLUI_SUBWINDOW_RIGHT);

	GLUI_Panel *panel1 = new GLUI_Panel(glui, "Show", GLUI_PANEL_EMBOSSED);
	new GLUI_Checkbox(panel1, "Ctrl Polygon", &show_ControlPolygon, 1, showMe);
	new GLUI_Checkbox(panel1, "Curve", &show_Curve, 2, showMe);
	new GLUI_Checkbox(panel1, "Curve Extdd", &show_CurveExtended, 3, showMe);
	new GLUI_Checkbox(panel1, "De Casteljau", &show_DeCasteljau, 4, showMe);
	new GLUI_Checkbox(panel1, "Convex Hull", &show_ConvexHull, 5, showMe);
	new GLUI_Checkbox(panel1, "Draw the second curve", &show_Curve2, 9, showMe);

	GLUI_Panel *panel5 = new GLUI_Panel(glui, "Color", GLUI_PANEL_EMBOSSED);
	new GLUI_EditText(panel5, "Point Color Red: ", &pointColorR, 10, showMe);
	new GLUI_EditText(panel5, "Point Color Green: ", &pointColorG, 11, showMe);
	new GLUI_EditText(panel5, "Point Color Blue: ", &pointColorB, 12, showMe);
	new GLUI_EditText(panel5, "Polygon Color Red: ", &polygonColorR, 19, showMe);
	new GLUI_EditText(panel5, "Polygon Color Green: ", &polygonColorG, 20, showMe);
	new GLUI_EditText(panel5, "Polygon Color Blue: ", &polygonColorB, 21, showMe);
	new GLUI_EditText(panel5, "Curve Color Red: ", &curveColorR, 13, showMe);
	new GLUI_EditText(panel5, "Curve Color Green: ", &curveColorG, 14, showMe);
	new GLUI_EditText(panel5, "Curve Color Blue: ", &curveColorB, 15, showMe);
	new GLUI_EditText(panel5, "Convex Hall Color Red: ", &hallColorR, 16, showMe);
	new GLUI_EditText(panel5, "Convex Hall Color Green: ", &hallColorG, 17, showMe);
	new GLUI_EditText(panel5, "Convex Hall Color Blue: ", &hallColorB, 18, showMe);
	
	GLUI_Panel * panel3 = new GLUI_Panel(glui, "  ", GLUI_PANEL_NONE);
	new GLUI_Button(panel3, "Undo", 6, Undo);

	GLUI_Panel * panel2 = new GLUI_Panel(glui, "  ", GLUI_PANEL_NONE);
	new GLUI_Button(panel2, "Clear", 7, Clear);

	GLUI_Panel * panel4 = new GLUI_Panel(glui, "  ", GLUI_PANEL_NONE);
	new GLUI_Button(panel4, "EXIT", 8, Exit);
}


int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	
	glutInitWindowSize(width, height);
	glutInitWindowPosition(100, 100);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	
	displayWin = glutCreateWindow("Bezier Curve");
	glutDisplayFunc(display);
	glutMouseFunc(mouse);
	buildGlui(displayWin);

	glutMainLoop();
	return 0;
}





