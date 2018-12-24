#include "GL/freeglut.h"
#include "Evaluate.h"
#include "Evpoly.h"
#include <iostream>
#include <stdlib.h>

const int height = 600;
const int width = 800;
using namespace std;

static void display() {
	glutSwapBuffers();
}

static void menu_callback(int menu) {
	if (menu == 18) {
		cout << "To change grid size, change the value of N in Evaluate.cpp" << endl;
	}
	/*else if (menu == EVsub_menu) {
		cout << "Evaluate selected." << endl;
	}
	else if (menu == POLYsub_menu) {
		cout << "Polynomial selected." << endl;
	}
	else {
		cout << "Other Action selected." << endl;
	}*/
}

static void OAsub_menu_callback(int OAsub_menu) {
	if (OAsub_menu == 0) {
		//clear input and graph
		glClear(GL_COLOR_BUFFER_BIT);
		display();
	}
	else if (OAsub_menu == 1) {
		system("cls");
		display();
	}
	else {
		exit(0);
	}
}

static void EVsub_menu_callback(int EVsub_menu) {
	if (EVsub_menu == 3) {
		cout << "Evaluate All" << endl;
		//all grid point
		cout << "Enter your poly here: " << endl;
		char input[1000];
		cin >> input;
		cout << "Your input is: " << input << endl;
		pExp *test = readExp(input);
		evalAll(test);
		display();
	}
	else {
		cout << "Find Curve not finished yet." << endl;
		//part1,part2
	}
}

void input() {
	cout << "Input a polynomial: ";
	char text[1000];
	cin >> text;
	cout<< "Your input is " << text << endl;
}

static void POLYsub_menu_callback(int POLYsub_menu) {
	if (POLYsub_menu == 17) {
		input();	
	}
}

static void Sample_menu_callback(int Sample_menu) {
	switch (Sample_menu) {
		case(5): {
			cout << "Circle selected, the current polynomial is: x^2+y^2©\0.8" << endl;
			char text[] = "x^2+y^2-0.8";
			pExp *B = readExp(text);
			evalAll(B);
			display();
			break;
		}
		case(6): {
			cout << "Ellipse selected, the current polynomial is: x^2+4*y^2©\0.5" << endl;
			char text[] = "x^2+4*y^2-0.5";
			pExp *B = readExp(text);
			evalAll(B);
			display();
			break;
		}
		case(7): {
			cout << "Hyperbola selected, the current polynomial is: x^2©\4*y^2©\0.09" << endl;
			char text[] = "x^2-4*y^2-0.09";
			pExp *B = readExp(text);
			evalAll(B);
			display();
			break;
		}
		case(8): {
			cout << "Semicubic parabola selected, the current polynomial is: y^2©\x^3" << endl;
			char text[] = "y^2-x^3";
			pExp *B = readExp(text);
			evalAll(B);
			display();
			break;
		}
		case(9): {
			cout << "Alpha curve selected, the current polynomial is: y^2©\x^2©\x^3" << endl;
			char text[] = "y^2-x^2-x^3";
			pExp *B = readExp(text);
			evalAll(B);
			display();
			break;
		}
		case(10): {
			cout << "Touching tacnode selected, the current polynomial is: y^2©\x^4©\y^4" << endl;
			char text[] = "y^2-x^4-y^4";
			pExp *B = readExp(text);
			evalAll(B);
			display();
			break;
		}
		case(11): {
			cout << "Crossing tacnode selected, the current polynomial is: y^2©\x^6©\y^6" << endl;
			char text[] = "y^2-x^6-y^6";
			pExp *B = readExp(text);
			evalAll(B);
			display();
			break;
		}
		case(12): {
			cout << "Lemniscate selected, the current polynomial is: (x^2+y^2)^2©\(x^2©\y^2)" << endl;
			char text[] = "(x^2+y^2)^2-(x^2-y^2)";
			pExp *B = readExp(text);
			evalAll(B);
			display();
			break;
		}
		case(13): {
			cout << "Rabbit ears selected, the current polynomial is: 8*x^4©\6*1.1*x^2*y+1.21*y^2©\4*1.331*y^3+4*1.21*1.21*y^4" << endl;
			char text[] = "8*x^4-6*1.1*x^2*y+1.21*y^2-4*1.331*y^3+4*1.21*1.21*y^4";
			pExp *B = readExp(text);
			evalAll(B);
			display();
			break;
		}
		case(14): {
			cout << "Curved lobe selected, the current polynomial is: x^4 + y^2*(x^2©\x+1)*1.44 ©\2*y*x^2*1.2" << endl;
			char text[] = "x^4+y^2*(x^2-x+1)*1.44-2*y*x^2*1.2";
			pExp *B = readExp(text);
			evalAll(B);
			display();
			break;
		}
		case(15): {
			cout << "Trefoil selected, the current polynomial is: (x^2+y^2)^2+3*x^2*y©\y^3" << endl;
			char text[] = "(x^2+y^2)^2+3*x^2*y-y^3";
			pExp *B = readExp(text);
			evalAll(B);
			display();
			break;
		}	
		default: {
			cout << "Clover leaf selected, the current polynomial is: (x^2+y^2)^3©\4*x^2*y^2" << endl;
			char text[] = "(x^2+y^2)^3-4*x^2*y^2";
			pExp *B = readExp(text);
			evalAll(B);
			display();
		}
	}
}

void createMenu() {
	int OAsub_menu;
	OAsub_menu = glutCreateMenu(OAsub_menu_callback);
	glutAddMenuEntry("Clear", 0);
	glutAddMenuEntry("Refresh", 1);
	glutAddMenuEntry("Exit", 2);

	int EVsub_menu;
	EVsub_menu = glutCreateMenu(EVsub_menu_callback);
	glutAddMenuEntry("Evaluate All", 3);
	glutAddMenuEntry("Find Curve", 4);

	int Sample_menu;
	Sample_menu = glutCreateMenu(Sample_menu_callback);
	glutAddMenuEntry("Circle", 5);
	glutAddMenuEntry("Ellipse", 6);
	glutAddMenuEntry("Hyperbola", 7);
	glutAddMenuEntry("Semicubic parabola", 8);
	glutAddMenuEntry("Alpha Curve", 9);
	glutAddMenuEntry("Touching tacnode", 10);
	glutAddMenuEntry("Crossing tacnode", 11);
	glutAddMenuEntry("Lemniscate", 12);
	glutAddMenuEntry("Rabbit Ears", 13);
	glutAddMenuEntry("Curved Lobe", 14);
	glutAddMenuEntry("Trefoil", 15);
	glutAddMenuEntry("Clover Leaf", 16);

	int POLYsub_menu;
	POLYsub_menu = glutCreateMenu(POLYsub_menu_callback);
	glutAddMenuEntry("Read Polynomial", 17);
	glutAddSubMenu("Polynomial Sample", Sample_menu);

	glutCreateMenu(menu_callback);
	glutAddSubMenu("Other Action", OAsub_menu);
	glutAddSubMenu("Evaluate", EVsub_menu);
	glutAddSubMenu("Polynomial", POLYsub_menu);
	glutAddMenuEntry("Grid N[0,1]", 18);


	glutAttachMenu(GLUT_LEFT_BUTTON);
}



int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitWindowSize(width, height);
	glutInitWindowPosition(600, 100);

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutCreateWindow("Algebraic Scalar Field Evaluation");

	glutDisplayFunc(display);
	createMenu();
	glutMainLoop();

	return 0;
}


