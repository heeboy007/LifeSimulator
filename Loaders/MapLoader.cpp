#include"MapLoader.h"

sf::Image* MapLoader::s_image = new sf::Image();
MapLoader* MapLoader::mapinstance = new MapLoader();

MapLoader::MapLoader()
{
	for(int i=0;i<MAP;i++)
	{
		for(int j=0;j<MAP;j++)
		{
			if(i==0||i==MAP-1||j==0||j==MAP-1)
			{
				grid[i][j] = new Tile(-1);
				continue;
			}
			grid[i][j] = new Tile(pickInRadius(409600));
		}
	}
	std::cout << "MapLoader::MapLoader() Called" << std::endl;
}

sf::Image* MapLoader::makeDrawableImage()
{
	s_image->create(MAP, MAP);
	for(int i=0;i<MAP;i++)
	{
		for(int j=0;j<MAP;j++)
		{
			s_image->setPixel(i, j, *grid[i][j]->returnColor());
		}
	}
	return s_image;
}

void MapLoader::deleteBuffers()
{
	for(int i=0;i<MAP;i++)
	{
		for(int j=0;j<MAP;j++)
		{
			delete grid[i][j];
		}
	}
	Tile::deleteColor();
}

Total MapLoader::totalQuery()
{
	total.pro = 0;
	total.con1 = 0;
	total.con2 = 0;
	for(int i=0;i<MAP;i++)
	{
		for(int j=0;j<MAP;j++)
		{
			switch(grid[i][j]->getType())
			{
				case Tile::CreatureType::Producer:
					total.pro++;
					break;
				case Tile::CreatureType::Consumer1:
					total.con1++;
					break;
				case Tile::CreatureType::Consumer2:
					total.con2++;
					break;
			}
		}
	}
	return total;
}

void MapLoader::updateEntireMap()
{
	for(int i=1;i<MAP-1;i++)
	{
		for(int j=1;j<MAP-1;j++)
		{
			Tile::CreatureType type = grid[i][j]->getType();
			switch(type)
			{
				case Tile::CreatureType::Producer:
					updateProducer(i, j, grid[i][j], i*640+j);
					break;
				case Tile::CreatureType::Consumer1:
					updateConsumer1(i, j, grid[i][j], i*640+j);
					break;
				case Tile::CreatureType::Consumer2:
					updateConsumer2(i, j, grid[i][j], i*640+j);
					break;
			}
		}
	}
}

void MapLoader::updateProducer(int x, int y, Tile* tile, int seed)
{
	//Reproduce
	if(tile->getHealth() > 25)
	{
		Tile* reproducelist[9];
		short index = 0;
		for(int i = -1;i <= 1;i++)
		{
			for(int j = -1;j <= 1;j++)
			{
				if(grid[x + j][y + i]->getType() == Tile::CreatureType::Nothing)
				{
					reproducelist[index] = grid[x + j][y + i];
					index++;
				}
			}
		}
		if(index > 0)
		{
			index = intInRange(index, seed);
			reproducelist[index]->reset(Tile::CreatureType::Producer);
			tile->setHealth(10);
		}
	}
	tile->healHealth(1);
}

void MapLoader::updateConsumer1(int x, int y, Tile* tile, int seed)
{
	tile->m_hunger = tile->m_hunger - 2;
	//Dying
	if(tile->m_hunger <= 0)
	{
		tile->reset(Tile::CreatureType::Nothing);
	}
	
	//Eating
	{
		short index = 1;
		for(int i = -1;i <= 1;i++)
		{
			for(int j = -1;j <= 1;j++)
			{
				if(grid[x + j][y + i]->getType() == Tile::CreatureType::Producer && index % 2==0)
				{
					if(intInRange(2, seed)==0)
					{
						tile->healHealth(grid[x + j][y + i]->getHealth());
						grid[x + j][y + i]->reset(Tile::CreatureType::Nothing);
						tile->m_hunger++;
					}
				}
				index++;
			}
		}
	}
	
	//Reproduce
	if(tile->getHealth() > 90)
	{
		Tile* reproducelist[9];
		short index = 0;
		for(int i = -1;i <= 1;i++)
		{
			for(int j = -1;j <= 1;j++)
			{
				if(grid[x + j][y + i]->getType() == Tile::CreatureType::Nothing)
				{
					reproducelist[index] = grid[x + j][y + i];
					index++;
				}
			}
		}
		if(index > 0)
		{
			index = intInRange(index, seed);
			reproducelist[index]->reset(Tile::CreatureType::Consumer1);
			tile->setHealth(50);
		}
	}
	
	//Moving
	if(intInRange(2, seed)==0)
	{
		Tile* movableplacelist[9];
		short index = 0;
		for(int i = -1;i <= 1;i++)
		{
			for(int j = -1;j <= 1;j++)
			{
				if(grid[x + j][y + i]->getType() == Tile::CreatureType::Nothing)
				{
					movableplacelist[index] = grid[x + j][y + i];
					index++;
				}
			}
		}
		if(index > 0)
		{
			index = intInRange(index, seed);
			movableplacelist[index]->reset(Tile::CreatureType::Consumer1);
			movableplacelist[index]->setHealth(tile->getHealth());
			tile->reset(Tile::CreatureType::Nothing);
		}
	}
}

void MapLoader::updateConsumer2(int x, int y, Tile* tile, int seed)
{
	tile->healHealth(-2);
	//Dying
	if(tile->getHealth() <= 0)
	{
		tile->reset(Tile::CreatureType::Nothing);
	}
	
	//Dying By humans
	if(intInRange(4, seed) <= 0)
	{
		tile->reset(Tile::CreatureType::Nothing);
	}
	
	//Eating
	{
		short index = 1;
		for(int i = -1;i <= 1;i++)
		{
			for(int j = -1;j <= 1;j++)
			{
				if(grid[x + j][y + i]->getType() == Tile::CreatureType::Consumer1 && index % 2==0)
				{
					tile->healHealth(grid[x + j][y + i]->getHealth());
					grid[x + j][y + i]->reset(Tile::CreatureType::Nothing);
				}
				index++;
			}
		}
	}
	
	//Reproduce
	if(tile->getHealth() > 145)
	{
		Tile* reproducelist[9];
		short index = 0;
		for(int i = -1;i <= 1;i++)
		{
			for(int j = -1;j <= 1;j++)
			{
				if(grid[x + j][y + i]->getType() == Tile::CreatureType::Nothing)
				{
					reproducelist[index] = grid[x + j][y + i];
					index++;
				}
			}
		}
		if(index > 0)
		{
			index = intInRange(index, seed);
			reproducelist[index]->reset(Tile::CreatureType::Consumer2);
			tile->setHealth(90);
		}
	}
	
	//Moving
	if(intInRange(2, seed)==0)
	{
		Tile* movableplacelist[9];
		short index = 0;
		for(int i = -1;i <= 1;i++)
		{
			for(int j = -1;j <= 1;j++)
			{
				if(grid[x + j][y + i]->getType() == Tile::CreatureType::Nothing)
				{
					movableplacelist[index] = grid[x + j][y + i];
					index++;
				}
			}
		}
		if(index > 0)
		{
			index = intInRange(index, seed);
			movableplacelist[index]->reset(Tile::CreatureType::Consumer2);
			movableplacelist[index]->setHealth(tile->getHealth());
			tile->reset(Tile::CreatureType::Nothing);
		}
	}
	
}

MapLoader* MapLoader::getInstance()
{
	return MapLoader::mapinstance;
}

