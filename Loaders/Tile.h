#ifndef TILE_H
#define TILE_H

#define MAP 320
#define MAX_HEALTH 255

#include"EtcFunc.h"

#include<iostream>
#include<SFML/Graphics.hpp>

namespace ColorData
{
	
	static const sf::Color *sea = new sf::Color(0, 163, 240);
	static const sf::Color *pro = new sf::Color(78, 219, 66);
	static const sf::Color *con1 = new sf::Color(239, 46, 99);
	static const sf::Color *con2 = new sf::Color(255, 176, 30);
	
}

class Tile
{
public:
	
	enum class CreatureType
	{
		Nothing = 0,
		Producer = 1,
		Consumer1 = 2,
		Consumer2 = 3,
		Abyss = 4
	};
	
	static void deleteColor()
	{
		delete ColorData::sea;
		delete ColorData::pro;
		delete ColorData::con1;
		delete ColorData::con2;
	}
	
	Tile(int spawn);
	
	void reset(CreatureType type);
	void setHealth(int val);
	void healHealth(int amount);
	int getHealth();
	void setType(CreatureType type);
	CreatureType getType();
	const sf::Color* returnColor();
	
	int m_hunger;
	
private:
	
	int m_health;
	CreatureType m_type;
		
};

#endif // TILE_H
