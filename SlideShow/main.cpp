#include "stdafx.h"
#include <iostream>
#include "initApi.h"
#include "screen.h"
#include "handle.h"
#include "mySlide.h"
#include "ui.h"
#include "fileHandle.h"
#include "utilities.h"
#include "SlideShow.h"
#include "SlideId.h"

/* Both Screens */
extern Screen mainScreen;
extern Screen inputScreen;
extern SDL_Event event;
extern Image nextButton;
extern Image backButton;
/* Both Screens */

/* Mandatory Functions */
void mainScreenRender();
void inputScreenRender();
void events();
void quit();
void initOthersHere();
void updateOthers();
void nextSlide();
void previousSlide();
void loadAllSlides();
/* Mandatory Functions */

/* Global variables */
MySlide currentSlide;
SlideShow sl;
SlideId slideId;
/* Global variables */

int main(int argc, char * argv[]) {
	
	try {
		initAllApi();
		initBothScreens();
		initUI();
		initOthersHere();
		loop(events, mainScreenRender, inputScreenRender, quit, updateOthers);
	}
	
	catch (const char* msg) {
		std::cout << msg << std::endl;
	}
	
	destroyBothScreens();
	closeAllApi();
	return 0;
}

void updateOthers() {
	currentSlide.update();
}

void initOthersHere() {
	sl.setFile("fileHandle.txt");
	
	slideId.setFile(sl.fileName);
	slideId.loadAllIds();
	loadAllSlides();

	nextButton.action = nextSlide;
	backButton.action = previousSlide;
}

void mainScreenRender() {
	mainScreen.clearScreen();
	renderMainUI();
	currentSlide.renderSlide();
}

void inputScreenRender() {
	renderInputUI();
}

void events() {
	currentSlide.process();
	processSaveButton(currentSlide);
	processMainUI();
	processInputUI();
}

void quit() {
	currentSlide.destroy();
	destroyUI();
}

void nextSlide() {
	slideId.increment();
	sl.setCurrentId(slideId.currentId);
	currentSlide = sl.getCurrentSlide();
}

void previousSlide() {
	slideId.decrement();
	sl.setCurrentId(slideId.currentId);
	currentSlide = sl.getCurrentSlide();
}

void loadAllSlides() {
	int numSlides = slideId.getNumIds();
	for (int i = 0; i < numSlides; i++) {
		slideId.increment();
		sl.setCurrentId(slideId.currentId);
		sl.loadSlide();
	}
	if (numSlides >= 1) {
		slideId.currentIndex = 0;
		slideId.currentId = slideId._ids[0];
		sl.setCurrentId(slideId.currentId);
		currentSlide = sl.getCurrentSlide();
	}
}