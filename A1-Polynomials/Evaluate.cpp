#include "Evaluate.h"
#include "Evpoly.h"
#include <iostream>
#include <iomanip>
#include <memory.h>
#include <stdlib.h>
#include <math.h>
#include "GL/freeglut.h"

using namespace std;

const int N = 100;

//char CoordSys[N][N];

void evalAll(pExp *In) {
	int p = 0;
	double Dx[10000];
	double Dy[10000];
	for (int i = N;i >= (-N);i--) {
		double x = double(i) / N;
		for (int j = (-N);j <= N;j++) {
			double y = double(j) / N;
			if ((abs(In->eval(x, y)) - 0) <= 0.01) {
				Dx[p] = x;
				Dy[p] = y;
				p++;
			}
		}
	}
	printGrid();
	glPointSize(2.0f);
	glBegin(GL_POINTS);
	for (int i = 0;i < p;i++) {
		glVertex2d(Dx[i], Dy[i]);
	}
	glEnd();
	glFlush();
}

void printGrid() {
	gluOrtho2D(-1,1,-1,1);
	glPointSize(1.0f);
	glBegin(GL_POINTS);
	for (int i = (-N);i <= N;i++) {
		double x = double(i) / N;
		for (int j = (-N);j <= N;j++) {
			double y = double(j) / N;
			glVertex2d(x,y);
		}
	}
	glEnd();
	glFlush();
}

bool signCheck(double value1, double value2) {
	return ((value1) * (value2) <= 0);
}

/*void evalAll(pExp *In) {
	printGrid();
	double coord1[N+1][N+1];
	//int p = 0;
	//int q = 0;
	for (int i = 0;i <= N;i++) {
		double x = double(i) / N;
		for (int j = 0;j <= N;j++) {
			double y = double(j) / N;
			coord1[i][j] = In->eval(x, y);
			glBegin(GL_LINE_STRIP);

			if ((i < N) && (j < N)) {
				if (signCheck(coord1[i][j], coord1[i + 1][j]) == 1) {
					glVertex2d(x + double((1 / (2 * N))), y);
					
				}
				else if (signCheck(coord1[i][j], coord1[i][j + 1]) == 1) {
					glVertex2d(x, y + double((1 / (2 * N))));
				
				}
				else {
					continue;
				}
			}

			else if (i == N && j < N) {
				if (signCheck(coord1[i][j], coord1[i][j + 1]) == 1) {
					glVertex2d(x, y + double((1 / (2 * N))));
				}
			}

			else if (j == N && i < N) {
				if (signCheck(coord1[i][j], coord1[i + 1][j]) == 1) {
					glVertex2d(x + double((1 / (2 * N))), y);
				}
			}
			else {
				continue;
			}
		}
	}
	glEnd();
	glFlush();
	//cout << In->eval(0,0.1)<<" "<<coord1[0][1];
}*/

void findC(pExp *In) {
	double Ax, Ay, Bx, By;
	cout << "Select Point A: X-coordinate followed by Y-coordinate." << endl;
	cin >> Ax >> Ay;
	cout << "Select Point B: X-coordinate followed by Y-coordinate." << endl;
	cin >> Bx >> By;
	while ((In->eval(Ax, Ay)) * ((In->eval(Bx, By)) > 0)) {
		cout<<"POLY has the same value. Pick another B."<<endl;
		cin >> Bx >> By;
	}
	//both 0
	//diff sign

}




