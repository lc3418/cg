#ifdef MENU_H_
#define MENU_H_

#include "Evpoly.h"


Class Menu
{

private:
	
	char text[1000];
	pExp *B;

public:
	Menu();
	const int setHeight(const int h) {
		this->height = h;
	}
	const int getHeight() {
		return this->height;
	}
	const int setWidth(const int w) {
		this->width = w;
	}
	const int getWidth() {
		return this->width;
	}
	pExp setB(pExp *In) {
		this->b = In;
	}
	pExp getB() {
		return this->B;
	}
	char setC[](char in[]) {
		this->char text[] = char in[];
	}
	char getC[]() {
		return this->char text[];
	}

	static void display();
	static void menu_callback(int menu);
	static void OAsub_menu_callback(int OAsub_menu);
	static void EVsub_menu_callback(int EVsub_menu);
	static void POLYsub_menu_callback(int POLYsub_menu);
	static void Sample_menu_callback(int Sample_menu);
	void createMenu();
}


#endif // 

