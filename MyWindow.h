#ifndef MY_WINDOW_H
#define MY_WINDOW_H

#include"Loaders/EtcFunc.h"
#include"Loaders/MapLoader.h"

#include<iostream>
#include<SFML/Window.hpp>
#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>

class MyWindow //: Clock
{
public:
	
	MyWindow(int w, int h);
	
	void Run();
	
private:
	
	int width, height, steps, fpscalcount;
	bool running, alldisabled;
	sf::Font *arial;
	sf::RenderWindow *window;
	sf::Text *pro, *con1, *con2;
	sf::Image *pixImage;
	sf::Texture *pixText;
	sf::Sprite *pixSprite;
	MapLoader *maploader;
	
	void makeDisplayText();
	void makePixelReady();
	void makePixelUpdate();
	void displayText();
	void fpsUpdate();
	void everyCountUpdate();
	void reshape(int w, int h);
	void handleEvent();
	void deleteBuffers();
	
};

#endif // MY_WINDOW_H
