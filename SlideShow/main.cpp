#include "stdafx.h"
#include <iostream>
#include "initApi.h"
#include "screen.h"
#include "handle.h"
#include "mySlide.h"
#include "ui.h"
#include "fileHandle.h"
#include "utilities.h"

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
MySlide& currentSlide = mySlide1;
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
	mySlide1.loadSlide(1, "fileHandle.txt", mainScreen.getRenderer());
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
	processSaveButton(currentSlide);
	processMainUI();
	processInputUI();
}

void quit() {
	mySlide1.destroy();
	destroyUI();
}