#include "stdafx.h"
#include "SlideShow.h"
#include "fileHandle.h"
#include "screen.h"
#include <iostream>

extern Screen mainScreen;

void SlideShow::addSlide(MySlide & _s) {
	_slides.push_back(_s);
}

int SlideShow::getIndexFromId(int id) {
	for (unsigned long i = 0; i < _slides.size(); i++) {
		if (_slides[i].getSlide().getId() == id)
			return i;
	}
	return -1;
}

void SlideShow::updateSlide(int id) {
	if (!ifSlideIdExists(fileName, id)) {
		int index = getIndexFromId(id);
		_slides[index].update();
	}
	else {
		std::cout << "Slide with id: " << id << "Cannot be processed" << std::endl;
	}
}

void SlideShow::loadSlide(int id) {
	if (ifSlideIdExists(fileName, id)) {
		int index = getIndexFromId(id);
		MySlide& tmpSlide = _slides[index];
		tmpSlide.loadSlide(index + 1, fileName, mainScreen.getRenderer());
	}
	else {
		std::cout << "Slide with id: " << id << "Cannot be processed" << std::endl;
	}
}

void SlideShow::processSlide(int id) {
	if (ifSlideIdExists(fileName, id)) {
		int index = getIndexFromId(id);
		_slides[index].process();
	}
	else {
		std::cout << "Slide with id: " << id << "Cannot be processed" << std::endl;
	}
}

void SlideShow::renderSlide(int id) {
	if (ifSlideIdExists(fileName, id)) {
		int index = getIndexFromId(id);
		_slides[index].renderSlide();
	}
	else {
		std::cout << "Slide with id: " << id << "Cannot be processed" << std::endl;
	}
}

void SlideShow::destroySlide(int id) {
	if (ifSlideIdExists(fileName, id)) {
		int index = getIndexFromId(id);
		_slides[index].destroy();
	}
	else {
		std::cout << "Slide with id: " << id << "Cannot be processed" << std::endl;
	}
}