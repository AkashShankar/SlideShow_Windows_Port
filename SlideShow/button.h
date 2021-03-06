#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include <string>
#include "utilities.h"
#include "screen.h"

class MySlide;

/*
 Button b1("TNR.ttf", 20, 10, 10);
 b1.initFont();
 b1.setRenderer(mainScreen.getRenderer());
 b1.setColors(RED, BLUE, BLACK, YELLOW);
 b1.initText("Exit", 500, 400);
 events() {
   b1.process();
 }
 render(){
   b1.render(Screen sc);
 }
 */

class Button {
private:
    SDL_Renderer *renderer;
    TTF_Font *font;
    SDL_Texture *texture;
    SDL_Color borderCol;
    SDL_Color insideCol;
    SDL_Color highlightCol;
    SDL_Color fontCol;
    SDL_Color currentCol;
    int xPad , yPad;
    int fontSize;
    std::string fontPath;
    std::string text;
private:
    void setTextRect(int x, int y);
    void render();
    void drawRect(Screen &sc);
    bool isMouseOnButton(int x, int y);
public:
    void(*action1)(void) = nullptr;
	void(*action2)(MySlide&) = nullptr;
    bool clickedToMove = false;
    bool clickedToAction = false;
	SDL_Rect buttonRect;
	SDL_Rect textRect;
public:
    Button(std::string fontPath, int fontSize, int xPad, int yPad);
    Button();
    void init(std::string fontPath, int fontSize, int xPad, int yPad);
    void initFont();
    void initText(std::string text, int x, int y);
	void reInitText(std::string text, int x, int y);
    void setRenderer(SDL_Renderer *renderer);
    void setColors(Color bCol, Color hCol, Color iColor, Color fCol);
    void highLightButton();
    void checkAndTakeAction();
	void checkAndTakeAction(MySlide&);
    void process();
	void process(MySlide&);
    void drawButton(Screen sc);
    void checkBounds1();
    void destroy();
	void adjustPosition();
};
