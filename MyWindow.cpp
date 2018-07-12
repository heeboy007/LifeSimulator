#include"MyWindow.h"

MyWindow::MyWindow(int w, int h)
{
	window = new sf::RenderWindow(sf::VideoMode(w, h), sf::String("Life Simulator"), sf::Style::Default, sf::ContextSettings(0, 0, 0, 3, 0));
	width = w;
	height = h;
	steps = 0;
	fpscalcount = 0;
	running = true;
	alldisabled = false;
	maploader = MapLoader::getInstance();
	window->setFramerateLimit(60);
	makeDisplayText();
	makePixelReady();
	//clockinit();
	//maploader->checkNull();
	std::cout << "MyWindow::MyWindow() Called" << std::endl;
}

void MyWindow::makeDisplayText()
{
	arial = new sf::Font();
	if(!arial->loadFromFile("Resource\\arial.ttf"))
		std::cout << "Error!" << std::endl;
	//this->fps = new sf::Text(sf::String("FPS : 0"), *arial, 15);
	//this->step = new sf::Text(sf::String("Step : 0"), *arial, 15);
	this->pro = new sf::Text(sf::String("Producer : 0"), *arial, 15);
	this->con1 = new sf::Text(sf::String("Consumer1 : 0"), *arial, 15);
	this->con2 = new sf::Text(sf::String("Consumer2 : 0"), *arial, 15);
	//fps->setPosition(0.0f, 0.0f);
	//step->setPosition(0.0f, 20.0f);
	//pro->setPosition(0.0f, 40.0f);
	//con1->setPosition(0.0f, 60.0f);
	//con2->setPosition(0.0f, 80.0f);
	pro->setPosition(0.0f, 0.0f);
	con1->setPosition(0.0f, 20.0f);
	con2->setPosition(0.0f, 40.0f);
	std::cout << "MyWindow::makeDisplayText() Called" << std::endl;
}

void MyWindow::makePixelReady()
{
	pixImage = maploader->makeDrawableImage();
	pixText = new sf::Texture();
	pixText->loadFromImage(*pixImage);
	pixText->setSmooth(false);
	pixSprite = new sf::Sprite(*pixText, sf::IntRect(0, 0, 640, 640));
	std::cout << "MyWindow::makePixelReady() Called" << std::endl;
}

void MyWindow::makePixelUpdate()
{
	pixText->update(*pixImage);
	pixSprite->setTexture(*pixText);
	pixSprite->setScale(2.0f, 2.0f);
}

void MyWindow::displayText()
{
	//window->draw(*fps);
	//window->draw(*step);
	window->draw(*pro);
	window->draw(*con1);
	window->draw(*con2);
}

void MyWindow::deleteBuffers()
{
	maploader->deleteBuffers();
	//delete fps;
	//delete step;
	delete pro;
	delete con1;
	delete con2;
	delete arial;
	delete pixImage;
	delete pixText;
	delete pixSprite;
	delete window;
}

void MyWindow::fpsUpdate()
{
	/*
	if(passed())
	{
		std::string fpsstr = "FPS : ";
		fpsstr += std::to_string(fpscalcount);
		fps->setString(sf::String(fpsstr));
		fpscalcount = 0;
	}
	else fpscalcount++;
	
	std::string stepstr = "Step : ";
	stepstr += std::to_string(steps);
	step->setString(sf::String(stepstr));
	*/
}

void MyWindow::everyCountUpdate()
{
	Total returnedValue = maploader->totalQuery();
	std::string prostr = "Heacho: ", con1str = "Sunge: ", con2str = "Headal : ";
	
	prostr += std::to_string(returnedValue.pro);
	con1str += std::to_string(returnedValue.con1);
	con2str += std::to_string(returnedValue.con2);
	
	pro->setString(sf::String(prostr));
	con1->setString(sf::String(con1str));
	con2->setString(sf::String(con2str));
}

void MyWindow::reshape(int w, int h)
{
	window->setSize(sf::Vector2u((float)width, (float)height));
	std::cout << "Window had resize to X:" << w << " Y:" << h << std::endl;
}

void MyWindow::handleEvent()
{
	static int posx = 0, posy = 0;
	sf::Event event;
	while(window->pollEvent(event))
	{
		switch(event.type)
		{
			case sf::Event::Resized:
				width = event.size.width;
				height = event.size.height;
				reshape(width, height);
				break;
			case sf::Event::MouseButtonReleased:
				std::cout << "Mouse X: " << posx << " Mouse Y: " << posy << std::endl;
				break;
			case sf::Event::MouseMoved:
				posx = event.mouseMove.x;
				posy = event.mouseMove.y;
				break;
			case sf::Event::Closed:
				running = false;
				break;
		}
	}
}

void MyWindow::Run()
{
	std::cout << "MyWindow::Run() Called : Main Loop Started." << std::endl;
	while(running)
	{
		handleEvent();
		
		window->clear();
		
		maploader->updateEntireMap();
		pixImage = maploader->makeDrawableImage();
		makePixelUpdate();
		
		window->draw(*pixSprite);
		
		//fpsUpdate();
		if(steps % 10 == 0)
			everyCountUpdate();
		displayText();
		
		steps++;
		window->display();
	}
	window->close();
	deleteBuffers();
}

