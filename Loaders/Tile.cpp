#include"Tile.h"

Tile::Tile(int spawn)
{
	if(spawn < 0)
	{
		m_type = CreatureType::Abyss;
		m_health = -1;
	}
	else if(spawn < 90)
		reset(CreatureType::Consumer2);
	else if(spawn < 600)
		reset(CreatureType::Consumer1);
	else if(spawn < 402010)
		reset(CreatureType::Producer);
	else
		reset(CreatureType::Nothing);
	m_hunger = 0;
}

const sf::Color* Tile::returnColor()
{
	switch(m_type)
	{
		case CreatureType::Nothing:
			return ColorData::sea;
			break;
		case CreatureType::Producer:
			return ColorData::pro;
			break;
		case CreatureType::Consumer1:
			return ColorData::con1;
			break;
		case CreatureType::Consumer2:
			return ColorData::con2;
			break;
		case CreatureType::Abyss:
			return &sf::Color::Black;
			break;
	}
}

void Tile::reset(CreatureType type)
{
	m_type = type;
	m_hunger = 0;
	switch(type)
	{
		case CreatureType::Nothing:
			m_health = 0;
			break;
		case CreatureType::Producer:
			m_health = 10;
			break;
		case CreatureType::Consumer1:
			m_health = 50;
			m_hunger = 15;
			break;
		case CreatureType::Consumer2:
			m_health = 90;
			break;
	}
}

void Tile::setHealth(int val)
{
	m_health = val;
}

void Tile::healHealth(int amount)
{
	if((m_health + amount) >= MAX_HEALTH)
		m_health = MAX_HEALTH;
	else
		m_health += amount;
}

int Tile::getHealth()
{
	return m_health;
}

void Tile::setType(CreatureType type)
{
	m_type = type;
}

Tile::CreatureType Tile::getType()
{
	return m_type;
}

