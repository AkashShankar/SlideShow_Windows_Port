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
#include "TextInput.h"

/* Both Screens */
extern Screen mainScreen;
extern Screen inputScreen;
extern SDL_Event event;
extern Image nextButton;
extern Image backButton;
extern Button saveButton;
extern Button refreshButton;
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
int getIndexWithId(int id);
void save(MySlide& _s);
void refresh();
/* Mandatory Functions */

/* Global variables */
MySlide currentSlide;
SlideShow sl;
SlideId slideId;
TextInput txtInput("courbd.ttf", YELLOW);
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
	system("pause");
	return 0;
}

void updateOthers() {
	currentSlide.update();
}

void initOthersHere() {
	sl.setFile("fileHandle.txt");
	
	slideId.setFile(sl.fileName);
	loadAllSlides();

	nextButton.action = nextSlide;
	backButton.action = previousSlide;
	refreshButton.action1 = refresh;
	saveButton.action2 = save;

	txtInput.setPos(80, 10);
	txtInput.init();
	txtInput.start();
}

void mainScreenRender() {
	mainScreen.clearScreen();
	renderMainUI();
	currentSlide.renderSlide();
}

void inputScreenRender() {
	renderInputUI();
	txtInput.render();
}

void events() {
	currentSlide.process();
	processSaveButton(currentSlide);
	processMainUI();
	processInputUI();
	txtInput.textLoop();
}

void quit() {
	currentSlide.destroy();
	destroyUI();
	txtInput.destroy();
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
	
	slideId.currentIndex = -1;
	slideId._ids.erase(slideId._ids.begin(), slideId._ids.end());
	slideId.loadAllIds();
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

int getIndexWithId(int id) {
	int si = slideId.getNumIds();
	for (int i = 0; i < si; i++) {
		if (slideId._ids[i] == id)
			return i;
	}
	return -1;
}

void save(MySlide& _s) {
	_s.save(_s.fileName);
	std::cout << "Slide with id: " << _s.id << " saved" << std::endl;
}

void refresh() {
	sl._slides.erase(sl._slides.begin(), sl._slides.end());
	loadAllSlides();
}