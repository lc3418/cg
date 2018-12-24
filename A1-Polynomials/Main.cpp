//
#include <stdio.h>
#include <string.h>
#include <iostream>
#include "Evpoly.h"
using namespace std;
char text[] =
//"x";
//"10*x-y";
"y^2-x^3-x^2";

int main(int argc, char **argv) {
	double r = 0;
	char c;
	pExp *B;
	B = readExp(text);
	printf("polynomial:  %s\n", text);
	r = B->eval(1, 2);
	printf(" eval(1,2) = %f\n", r);
	r = B->eval(2, 3);
	printf(" eval(2,3) = %f\n", r);
	c = getchar();
}
