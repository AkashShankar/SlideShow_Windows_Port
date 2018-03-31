#include "stdafx.h"
#include <iostream>
#include "initApi.h"
#include "screen.h"
#include "handle.h"
#include "mySlide.h"
#include "ui.h"

/* Both Screens */
extern Screen mainScreen;
extern Screen inputScreen;
extern SDL_Event event;
/* Both Screens */

/* Mandatory Functions */
void mainScreenRender();
void inputScreenRender();
void events();
void quit();
void initOthersHere();
void updateOthers();
/* Mandatory Functions */

/* Global variables */
MySlide mySlide1;
/* Global variables */

int main(int argc, char * argv[]) {
	initAllApi();
	initBothScreens();
	initUI();
	initOthersHere();
	loop(events, mainScreenRender, inputScreenRender, quit, updateOthers);
	destroyBothScreens();
	closeAllApi();
	return 0;
}

void updateOthers() {
	mySlide1.update();
}

void initOthersHere() {
	loadSlide(mySlide1, 1, "fileHandle.txt", mainScreen.getRenderer());
	//std::cout << mySlide1.getSlide().getId() << std::endl;
}

void mainScreenRender() {
	mainScreen.clearScreen();
	mySlide1.renderSlide();
	renderMainUI();
}

void inputScreenRender() {
	renderInputUI();
}

void events() {
	mySlide1.process();
	processMainUI();
	processInputUI();
}

void quit() {
	mySlide1.destroy();
	destroyUI();
}

